#include <xrt/xrt_bo.h>
#include <xrt/xrt_device.h>
#include <xrt/xrt_kernel.h>
#include <xrt/xrt_uuid.h>

#include <chrono>
#include <cstdint>
#include <cstring>
#include <exception>
#include <iomanip>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

namespace {

constexpr size_t F16 = 2;
constexpr size_t F32 = 4;
constexpr size_t I32 = 4;
constexpr size_t I1_BYTES = 1;

struct NamedBo {
  std::string name;
  size_t bytes;
  xrt::bo bo;
};

xrt::kernel open_kernel(xrt::device &device, const xrt::uuid &uuid,
                        const std::vector<std::string> &names) {
  std::exception_ptr last_error;
  for (const auto &name : names) {
    try {
      return xrt::kernel(device, uuid, name);
    } catch (...) {
      last_error = std::current_exception();
    }
  }
  if (last_error)
    std::rethrow_exception(last_error);
  throw std::runtime_error("no kernel names provided");
}

NamedBo make_bo(xrt::device &device, xrt::kernel &kernel, int arg_index,
                size_t bytes, const std::string &name) {
  auto group = kernel.group_id(arg_index);
  auto bo = xrt::bo(device, bytes, group);
  return NamedBo{name, bytes, std::move(bo)};
}

void zero_to_device(NamedBo &buffer) {
  auto *ptr = buffer.bo.map<uint8_t *>();
  std::memset(ptr, 0, buffer.bytes);
  buffer.bo.sync(XCL_BO_SYNC_BO_TO_DEVICE);
}

void set_i32_to_device(NamedBo &buffer, int32_t value) {
  if (buffer.bytes < sizeof(int32_t))
    throw std::runtime_error(buffer.name + " is too small for int32_t");
  auto *ptr = buffer.bo.map<int32_t *>();
  *ptr = value;
  buffer.bo.sync(XCL_BO_SYNC_BO_TO_DEVICE);
}

void print_first_u16(NamedBo &buffer, size_t count) {
  buffer.bo.sync(XCL_BO_SYNC_BO_FROM_DEVICE);
  auto *ptr = buffer.bo.map<uint16_t *>();
  const size_t n = std::min(count, buffer.bytes / sizeof(uint16_t));
  std::cout << buffer.name << " first " << n << " u16 words:";
  for (size_t i = 0; i < n; ++i) {
    std::cout << " 0x" << std::hex << std::setw(4) << std::setfill('0')
              << ptr[i] << std::dec;
  }
  std::cout << std::setfill(' ') << "\n";
}

void sync_inputs(std::vector<NamedBo *> buffers) {
  for (auto *buffer : buffers)
    zero_to_device(*buffer);
}

void set_b3c0_args(xrt::run &run, NamedBo &hidden_in,
                   NamedBo &cache_position, NamedBo &key_cache_in,
                   NamedBo &value_cache_in, NamedBo &causal_mask,
                   NamedBo &attention_bias, NamedBo &key_cache_out,
                   NamedBo &value_cache_out, NamedBo &c0_ln1_w,
                   NamedBo &c0_ln1_b, NamedBo &c0_qkv_w, NamedBo &c0_qkv_b,
                   NamedBo &c0_attn_out_w) {
  run.set_arg(0, hidden_in.bo);
  run.set_arg(1, cache_position.bo);
  run.set_arg(2, key_cache_in.bo);
  run.set_arg(3, value_cache_in.bo);
  run.set_arg(4, causal_mask.bo);
  run.set_arg(5, attention_bias.bo);
  run.set_arg(6, key_cache_out.bo);
  run.set_arg(7, value_cache_out.bo);
  // Args 8 and 9 are AXI streams connected in system.cfg, not host buffers.
  run.set_arg(10, c0_ln1_w.bo);
  run.set_arg(11, c0_ln1_b.bo);
  run.set_arg(12, c0_qkv_w.bo);
  run.set_arg(13, c0_qkv_b.bo);
  run.set_arg(14, c0_attn_out_w.bo);
}

void set_b3c1_args(xrt::run &run, NamedBo &c1_attn_out_b, NamedBo &c1_ln2_w,
                   NamedBo &c1_ln2_b, NamedBo &c1_fc1_w,
                   NamedBo &c1_fc1_b) {
  // Args 0-3 are AXI streams connected in system.cfg, not host buffers.
  run.set_arg(4, c1_attn_out_b.bo);
  run.set_arg(5, c1_ln2_w.bo);
  run.set_arg(6, c1_ln2_b.bo);
  run.set_arg(7, c1_fc1_w.bo);
  run.set_arg(8, c1_fc1_b.bo);
}

void set_b3c2_args(xrt::run &run, NamedBo &hidden_out, NamedBo &c2_fc2_w,
                   NamedBo &c2_fc2_b) {
  // Args 0 and 1 are AXI streams connected in system.cfg, not host buffers.
  run.set_arg(2, hidden_out.bo);
  run.set_arg(3, c2_fc2_w.bo);
  run.set_arg(4, c2_fc2_b.bo);
}

} // namespace

int main(int argc, char **argv) {
  try {
    if (argc < 2) {
      std::cerr << "usage: " << argv[0]
                << " <base3_3slr_stream.xclbin> [iterations]\n";
      return 1;
    }

    const std::string xclbin_path = argv[1];
    const int iterations = argc >= 3 ? std::stoi(argv[2]) : 1;
    if (iterations <= 0)
      throw std::runtime_error("iterations must be positive");

    auto device = xrt::device(0);
    auto uuid = device.load_xclbin(xclbin_path);

    auto k0 = open_kernel(device, uuid, {"b3c0:{b3c0_1}", "b3c0"});
    auto k1 = open_kernel(device, uuid, {"b3c1:{b3c1_1}", "b3c1"});
    auto k2 = open_kernel(device, uuid, {"b3c2:{b3c2_1}", "b3c2"});

    // b3c0 external memory arguments.
    auto hidden_in = make_bo(device, k0, 0, 1 * 1 * 768 * F16, "hidden_in");
    auto cache_position = make_bo(device, k0, 1, 1 * I32, "cache_position");
    auto key_cache_in =
        make_bo(device, k0, 2, 1 * 12 * 128 * 64 * F16, "key_cache_in");
    auto value_cache_in =
        make_bo(device, k0, 3, 1 * 12 * 128 * 64 * F16, "value_cache_in");
    auto causal_mask =
        make_bo(device, k0, 4, 1 * 1 * 1024 * 1024 * I1_BYTES, "causal_mask");
    auto attention_bias =
        make_bo(device, k0, 5, 1 * 1 * 1 * 128 * F16, "attention_bias");
    auto key_cache_out =
        make_bo(device, k0, 6, 1 * 12 * 128 * 64 * F16, "key_cache_out");
    auto value_cache_out =
        make_bo(device, k0, 7, 1 * 12 * 128 * 64 * F16, "value_cache_out");
    auto c0_ln1_w = make_bo(device, k0, 10, 768 * F16, "c0_ln1_w");
    auto c0_ln1_b = make_bo(device, k0, 11, 768 * F16, "c0_ln1_b");
    auto c0_qkv_w = make_bo(device, k0, 12, 768 * 2304 * F16, "c0_qkv_w");
    auto c0_qkv_b = make_bo(device, k0, 13, 2304 * F16, "c0_qkv_b");
    auto c0_attn_out_w =
        make_bo(device, k0, 14, 768 * 768 * F16, "c0_attn_out_w");

    // b3c1 external memory arguments.
    auto c1_attn_out_b =
        make_bo(device, k1, 4, 768 * F16, "c1_attn_out_b");
    auto c1_ln2_w = make_bo(device, k1, 5, 768 * F16, "c1_ln2_w");
    auto c1_ln2_b = make_bo(device, k1, 6, 768 * F16, "c1_ln2_b");
    auto c1_fc1_w = make_bo(device, k1, 7, 768 * 3072 * F16, "c1_fc1_w");
    auto c1_fc1_b = make_bo(device, k1, 8, 3072 * F16, "c1_fc1_b");

    // b3c2 external memory arguments.
    auto hidden_out = make_bo(device, k2, 2, 1 * 1 * 768 * F16, "hidden_out");
    auto c2_fc2_w = make_bo(device, k2, 3, 3072 * 768 * F16, "c2_fc2_w");
    auto c2_fc2_b = make_bo(device, k2, 4, 768 * F16, "c2_fc2_b");

    sync_inputs({&hidden_in,       &key_cache_in,   &value_cache_in,
                 &causal_mask,     &attention_bias, &key_cache_out,
                 &value_cache_out, &c0_ln1_w,       &c0_ln1_b,
                 &c0_qkv_w,        &c0_qkv_b,       &c0_attn_out_w,
                 &c1_attn_out_b,   &c1_ln2_w,       &c1_ln2_b,
                 &c1_fc1_w,        &c1_fc1_b,       &hidden_out,
                 &c2_fc2_w,        &c2_fc2_b});
    set_i32_to_device(cache_position, 0);

    double total_ms = 0.0;
    for (int i = 0; i < iterations; ++i) {
      xrt::run r2(k2);
      xrt::run r1(k1);
      xrt::run r0(k0);

      set_b3c2_args(r2, hidden_out, c2_fc2_w, c2_fc2_b);
      set_b3c1_args(r1, c1_attn_out_b, c1_ln2_w, c1_ln2_b, c1_fc1_w,
                    c1_fc1_b);
      set_b3c0_args(r0, hidden_in, cache_position, key_cache_in,
                    value_cache_in, causal_mask, attention_bias, key_cache_out,
                    value_cache_out, c0_ln1_w, c0_ln1_b, c0_qkv_w, c0_qkv_b,
                    c0_attn_out_w);

      // Start downstream consumers first so stream producers cannot block.
      const auto t0 = std::chrono::high_resolution_clock::now();
      r2.start();
      r1.start();
      r0.start();
      r0.wait();
      r1.wait();
      r2.wait();
      const auto t1 = std::chrono::high_resolution_clock::now();

      const double ms =
          std::chrono::duration<double, std::milli>(t1 - t0).count();
      total_ms += ms;
      std::cout << "iteration " << i << " latency_ms=" << ms << "\n";
    }

    key_cache_out.bo.sync(XCL_BO_SYNC_BO_FROM_DEVICE);
    value_cache_out.bo.sync(XCL_BO_SYNC_BO_FROM_DEVICE);
    print_first_u16(hidden_out, 16);
    std::cout << "average_latency_ms=" << (total_ms / iterations) << "\n";
    return 0;
  } catch (const std::exception &ex) {
    std::cerr << "error: " << ex.what() << "\n";
    return 1;
  }
}
