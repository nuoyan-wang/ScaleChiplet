#include <ap_float.h>
#include <ap_int.h>
#include <xrt/xrt_bo.h>
#include <xrt/xrt_device.h>
#include <xrt/xrt_kernel.h>
#include <xrt/xrt_uuid.h>

#include <algorithm>
#include <chrono>
#include <cstdint>
#include <exception>
#include <iomanip>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

namespace {

constexpr size_t F16 = sizeof(ap_float<16, 8>);
constexpr size_t I32 = sizeof(ap_int<32>);
constexpr size_t I1 = sizeof(ap_int<1>);

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
  return NamedBo{name, bytes, xrt::bo(device, bytes, kernel.group_id(arg_index))};
}

template <typename T>
void fill_bo(NamedBo &buffer, T value) {
  auto *ptr = buffer.bo.map<T *>();
  std::fill_n(ptr, buffer.bytes / sizeof(T), value);
  buffer.bo.sync(XCL_BO_SYNC_BO_TO_DEVICE);
}

ap_float<16, 8> float_pattern(const std::string &pattern) {
  if (pattern == "zero")
    return ap_float<16, 8>(0.0);
  if (pattern == "one")
    return ap_float<16, 8>(1.0);
  if (pattern == "tenth")
    return ap_float<16, 8>(0.1);
  throw std::runtime_error("pattern must be one of: zero, one, tenth");
}

void print_first_output(NamedBo &buffer) {
  buffer.bo.sync(XCL_BO_SYNC_BO_FROM_DEVICE);
  auto *ptr = buffer.bo.map<ap_float<16, 8> *>();
  std::cout << "hidden_out first 16 values:";
  for (size_t i = 0; i < 16; ++i)
    std::cout << " " << static_cast<float>(ptr[i]);
  std::cout << "\n";
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
  run.set_arg(10, c0_ln1_w.bo);
  run.set_arg(11, c0_ln1_b.bo);
  run.set_arg(12, c0_qkv_w.bo);
  run.set_arg(13, c0_qkv_b.bo);
  run.set_arg(14, c0_attn_out_w.bo);
}

void set_b3c1_args(xrt::run &run, NamedBo &c1_attn_out_b, NamedBo &c1_ln2_w,
                   NamedBo &c1_ln2_b, NamedBo &c1_fc1_w,
                   NamedBo &c1_fc1_b) {
  run.set_arg(4, c1_attn_out_b.bo);
  run.set_arg(5, c1_ln2_w.bo);
  run.set_arg(6, c1_ln2_b.bo);
  run.set_arg(7, c1_fc1_w.bo);
  run.set_arg(8, c1_fc1_b.bo);
}

void set_b3c2_args(xrt::run &run, NamedBo &hidden_out, NamedBo &c2_fc2_w,
                   NamedBo &c2_fc2_b) {
  run.set_arg(2, hidden_out.bo);
  run.set_arg(3, c2_fc2_w.bo);
  run.set_arg(4, c2_fc2_b.bo);
}

} // namespace

int main(int argc, char **argv) {
  try {
    if (argc < 2) {
      std::cerr << "usage: " << argv[0]
                << " <xclbin> [zero|one|tenth] [iterations]\n";
      return 1;
    }

    const std::string xclbin_path = argv[1];
    const std::string pattern = argc >= 3 ? argv[2] : "tenth";
    const int iterations = argc >= 4 ? std::stoi(argv[3]) : 1;
    if (iterations <= 0)
      throw std::runtime_error("iterations must be positive");

    const ap_float<16, 8> f16_value = float_pattern(pattern);
    const ap_int<32> i32_value = pattern == "zero" ? 0 : 1;
    const ap_int<1> i1_value = pattern == "zero" ? 0 : 1;

    auto device = xrt::device(0);
    auto uuid = device.load_xclbin(xclbin_path);
    auto k0 = open_kernel(device, uuid, {"b3c0:{b3c0_1}", "b3c0"});
    auto k1 = open_kernel(device, uuid, {"b3c1:{b3c1_1}", "b3c1"});
    auto k2 = open_kernel(device, uuid, {"b3c2:{b3c2_1}", "b3c2"});

    auto hidden_in = make_bo(device, k0, 0, 1 * 1 * 768 * F16, "hidden_in");
    auto cache_position = make_bo(device, k0, 1, 1 * I32, "cache_position");
    auto key_cache_in =
        make_bo(device, k0, 2, 1 * 12 * 128 * 64 * F16, "key_cache_in");
    auto value_cache_in =
        make_bo(device, k0, 3, 1 * 12 * 128 * 64 * F16, "value_cache_in");
    auto causal_mask =
        make_bo(device, k0, 4, 1 * 1 * 1024 * 1024 * I1, "causal_mask");
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

    auto c1_attn_out_b =
        make_bo(device, k1, 4, 768 * F16, "c1_attn_out_b");
    auto c1_ln2_w = make_bo(device, k1, 5, 768 * F16, "c1_ln2_w");
    auto c1_ln2_b = make_bo(device, k1, 6, 768 * F16, "c1_ln2_b");
    auto c1_fc1_w = make_bo(device, k1, 7, 768 * 3072 * F16, "c1_fc1_w");
    auto c1_fc1_b = make_bo(device, k1, 8, 3072 * F16, "c1_fc1_b");

    auto hidden_out = make_bo(device, k2, 2, 1 * 1 * 768 * F16, "hidden_out");
    auto c2_fc2_w = make_bo(device, k2, 3, 3072 * 768 * F16, "c2_fc2_w");
    auto c2_fc2_b = make_bo(device, k2, 4, 768 * F16, "c2_fc2_b");

    std::vector<NamedBo *> f16_buffers = {
        &hidden_in,       &key_cache_in,   &value_cache_in, &attention_bias,
        &key_cache_out,   &value_cache_out, &c0_ln1_w,       &c0_ln1_b,
        &c0_qkv_w,        &c0_qkv_b,       &c0_attn_out_w,  &c1_attn_out_b,
        &c1_ln2_w,        &c1_ln2_b,       &c1_fc1_w,       &c1_fc1_b,
        &hidden_out,      &c2_fc2_w,       &c2_fc2_b};
    for (auto *buffer : f16_buffers)
      fill_bo(*buffer, f16_value);
    fill_bo(cache_position, i32_value);
    fill_bo(causal_mask, i1_value);

    double total_ms = 0.0;
    for (int i = 0; i < iterations; ++i) {
      xrt::run r2(k2), r1(k1), r0(k0);
      set_b3c2_args(r2, hidden_out, c2_fc2_w, c2_fc2_b);
      set_b3c1_args(r1, c1_attn_out_b, c1_ln2_w, c1_ln2_b, c1_fc1_w,
                    c1_fc1_b);
      set_b3c0_args(r0, hidden_in, cache_position, key_cache_in,
                    value_cache_in, causal_mask, attention_bias, key_cache_out,
                    value_cache_out, c0_ln1_w, c0_ln1_b, c0_qkv_w, c0_qkv_b,
                    c0_attn_out_w);

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
      std::cout << "iteration " << i << " pattern=" << pattern
                << " latency_ms=" << ms << "\n";
    }

    print_first_output(hidden_out);
    std::cout << "average_latency_ms=" << (total_ms / iterations) << "\n";
    return 0;
  } catch (const std::exception &ex) {
    std::cerr << "error: " << ex.what() << "\n";
    return 1;
  }
}
