#include <xrt/xrt_bo.h>
#include <xrt/xrt_device.h>
#include <xrt/xrt_kernel.h>
#include <xrt/xrt_uuid.h>

#include <algorithm>
#include <chrono>
#include <cmath>
#include <cstdint>
#include <cstring>
#include <exception>
#include <filesystem>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <cstdio>
#include <limits>
#include <numeric>
#include <stdexcept>
#include <string>
#include <vector>

namespace fs = std::filesystem;

namespace {

constexpr int kNumLayers = 12;
constexpr size_t F16 = sizeof(uint16_t);
constexpr size_t I32 = sizeof(int32_t);
constexpr size_t I1 = sizeof(uint8_t);

struct NamedBo {
  std::string name;
  size_t bytes;
  xrt::bo bo;
};

struct DiffStats {
  float max_abs = 0.0f;
  double mean_abs = 0.0;
  double mean_ref_abs = 0.0;
  double mean_percent = 0.0;
  size_t count = 0;
};

struct TopToken {
  int token_id = -1;
  float logit = -std::numeric_limits<float>::infinity();
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

std::vector<uint8_t> read_file_exact(const fs::path &path, size_t bytes) {
  std::ifstream file(path, std::ios::binary);
  if (!file)
    throw std::runtime_error("failed to open " + path.string());
  std::vector<uint8_t> data(bytes);
  file.read(reinterpret_cast<char *>(data.data()), data.size());
  if (static_cast<size_t>(file.gcount()) != bytes)
    throw std::runtime_error("wrong byte count in " + path.string() +
                             ": expected " + std::to_string(bytes) +
                             ", got " + std::to_string(file.gcount()));
  return data;
}

bool file_exists(const fs::path &path) {
  std::error_code ec;
  return fs::is_regular_file(path, ec);
}

void load_file_to_bo(NamedBo &buffer, const fs::path &path) {
  auto data = read_file_exact(path, buffer.bytes);
  auto *ptr = buffer.bo.map<uint8_t *>();
  std::memcpy(ptr, data.data(), data.size());
  buffer.bo.sync(XCL_BO_SYNC_BO_TO_DEVICE);
}

void zero_to_device(NamedBo &buffer) {
  auto *ptr = buffer.bo.map<uint8_t *>();
  std::memset(ptr, 0, buffer.bytes);
  buffer.bo.sync(XCL_BO_SYNC_BO_TO_DEVICE);
}

float bf16_to_float(uint16_t value) {
  uint32_t bits = static_cast<uint32_t>(value) << 16;
  float result;
  std::memcpy(&result, &bits, sizeof(result));
  return result;
}

DiffStats compare_bf16_bo_to_file(NamedBo &buffer, const fs::path &golden_path) {
  buffer.bo.sync(XCL_BO_SYNC_BO_FROM_DEVICE);
  auto golden = read_file_exact(golden_path, buffer.bytes);
  auto *actual = buffer.bo.map<uint16_t *>();
  const auto *expected = reinterpret_cast<const uint16_t *>(golden.data());
  const size_t n = buffer.bytes / sizeof(uint16_t);

  DiffStats stats;
  stats.count = n;
  double sum = 0.0;
  double ref_sum = 0.0;
  float max_abs = 0.0f;
  for (size_t i = 0; i < n; ++i) {
    const float a = bf16_to_float(actual[i]);
    const float e = bf16_to_float(expected[i]);
    const float diff = std::abs(a - e);
    if (std::isfinite(diff)) {
      sum += diff;
      max_abs = std::max(max_abs, diff);
    } else {
      max_abs = std::numeric_limits<float>::infinity();
    }
    if (std::isfinite(e))
      ref_sum += std::abs(e);
  }
  stats.max_abs = max_abs;
  stats.mean_abs = n ? sum / static_cast<double>(n) : 0.0;
  stats.mean_ref_abs = n ? ref_sum / static_cast<double>(n) : 0.0;
  stats.mean_percent =
      stats.mean_ref_abs > 0.0 ? 100.0 * stats.mean_abs / stats.mean_ref_abs
                               : std::numeric_limits<double>::infinity();
  return stats;
}

void copy_bo_device_to_device_via_host(NamedBo &dst, NamedBo &src) {
  if (dst.bytes != src.bytes)
    throw std::runtime_error("copy size mismatch: " + dst.name + " and " +
                             src.name);
  src.bo.sync(XCL_BO_SYNC_BO_FROM_DEVICE);
  auto *src_ptr = src.bo.map<uint8_t *>();
  auto *dst_ptr = dst.bo.map<uint8_t *>();
  std::memcpy(dst_ptr, src_ptr, src.bytes);
  dst.bo.sync(XCL_BO_SYNC_BO_TO_DEVICE);
}

void print_first_bf16(NamedBo &buffer, size_t count) {
  buffer.bo.sync(XCL_BO_SYNC_BO_FROM_DEVICE);
  auto *ptr = buffer.bo.map<uint16_t *>();
  const size_t n = std::min(count, buffer.bytes / sizeof(uint16_t));
  std::cout << buffer.name << " first " << n << " bf16:";
  for (size_t i = 0; i < n; ++i)
    std::cout << " " << bf16_to_float(ptr[i]);
  std::cout << "\n";
}

std::vector<float> read_bf16_file_as_float(const fs::path &path,
                                           size_t elements) {
  auto data = read_file_exact(path, elements * sizeof(uint16_t));
  const auto *raw = reinterpret_cast<const uint16_t *>(data.data());
  std::vector<float> result(elements);
  for (size_t i = 0; i < elements; ++i)
    result[i] = bf16_to_float(raw[i]);
  return result;
}

std::vector<float> read_bf16_bo_as_float(NamedBo &buffer) {
  buffer.bo.sync(XCL_BO_SYNC_BO_FROM_DEVICE);
  auto *raw = buffer.bo.map<uint16_t *>();
  const size_t elements = buffer.bytes / sizeof(uint16_t);
  std::vector<float> result(elements);
  for (size_t i = 0; i < elements; ++i)
    result[i] = bf16_to_float(raw[i]);
  return result;
}

int read_first_i32(const fs::path &path) {
  auto data = read_file_exact(path, sizeof(int32_t));
  int32_t value = 0;
  std::memcpy(&value, data.data(), sizeof(value));
  return value;
}

TopToken compute_next_token_cpu(const std::vector<float> &hidden,
                                const std::vector<float> &ln_w,
                                const std::vector<float> &ln_b,
                                const std::vector<float> &lm_head_w) {
  constexpr size_t hidden_size = 768;
  if (hidden.size() != hidden_size || ln_w.size() != hidden_size ||
      ln_b.size() != hidden_size)
    throw std::runtime_error("bad hidden/ln tensor size");
  if (lm_head_w.size() % hidden_size != 0)
    throw std::runtime_error("bad lm_head_w size");
  const size_t vocab = lm_head_w.size() / hidden_size;

  const double mean =
      std::accumulate(hidden.begin(), hidden.end(), 0.0) / hidden_size;
  double var = 0.0;
  for (float v : hidden) {
    const double d = static_cast<double>(v) - mean;
    var += d * d;
  }
  var /= hidden_size;
  const double inv_std = 1.0 / std::sqrt(var + 1.0e-5);

  std::vector<float> norm(hidden_size);
  for (size_t i = 0; i < hidden_size; ++i)
    norm[i] = static_cast<float>((static_cast<double>(hidden[i]) - mean) *
                                     inv_std * ln_w[i] +
                                 ln_b[i]);

  TopToken best;
  for (size_t tok = 0; tok < vocab; ++tok) {
    const float *w = lm_head_w.data() + tok * hidden_size;
    double acc = 0.0;
    for (size_t i = 0; i < hidden_size; ++i)
      acc += static_cast<double>(norm[i]) * static_cast<double>(w[i]);
    const float logit = static_cast<float>(acc);
    if (logit > best.logit) {
      best.logit = logit;
      best.token_id = static_cast<int>(tok);
    }
  }
  return best;
}

void set_b3c0_args(xrt::run &run, NamedBo &hidden_in,
                   NamedBo &cache_position, NamedBo &key_cache_in,
                   NamedBo &value_cache_in, NamedBo &causal_bias,
                   NamedBo &attention_bias, NamedBo &key_cache_out,
                   NamedBo &value_cache_out, NamedBo &c0_ln1_w,
                   NamedBo &c0_ln1_b, NamedBo &c0_qkv_w, NamedBo &c0_qkv_b,
                   NamedBo &c0_attn_out_w) {
  run.set_arg(0, hidden_in.bo);
  run.set_arg(1, cache_position.bo);
  run.set_arg(2, key_cache_in.bo);
  run.set_arg(3, value_cache_in.bo);
  run.set_arg(4, causal_bias.bo);
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

void load_layer_weights(const fs::path &layer_dir, NamedBo &c0_ln1_w,
                        NamedBo &c0_ln1_b, NamedBo &c0_qkv_w,
                        NamedBo &c0_qkv_b, NamedBo &c0_attn_out_w,
                        NamedBo &c1_attn_out_b, NamedBo &c1_ln2_w,
                        NamedBo &c1_ln2_b, NamedBo &c1_fc1_w,
                        NamedBo &c1_fc1_b, NamedBo &c2_fc2_w,
                        NamedBo &c2_fc2_b) {
  load_file_to_bo(c0_ln1_w, layer_dir / "c0_ln1_w.bin");
  load_file_to_bo(c0_ln1_b, layer_dir / "c0_ln1_b.bin");
  load_file_to_bo(c0_qkv_w, layer_dir / "c0_qkv_w.bin");
  load_file_to_bo(c0_qkv_b, layer_dir / "c0_qkv_b.bin");
  load_file_to_bo(c0_attn_out_w, layer_dir / "c0_attn_out_w.bin");

  load_file_to_bo(c1_attn_out_b, layer_dir / "c1_attn_out_b.bin");
  load_file_to_bo(c1_ln2_w, layer_dir / "c1_ln2_w.bin");
  load_file_to_bo(c1_ln2_b, layer_dir / "c1_ln2_b.bin");
  load_file_to_bo(c1_fc1_w, layer_dir / "c1_fc1_w.bin");
  load_file_to_bo(c1_fc1_b, layer_dir / "c1_fc1_b.bin");

  load_file_to_bo(c2_fc2_w, layer_dir / "c2_fc2_w.bin");
  load_file_to_bo(c2_fc2_b, layer_dir / "c2_fc2_b.bin");
}

} // namespace

int main(int argc, char **argv) {
  try {
    if (argc < 3) {
      std::cerr << "usage: " << argv[0]
                << " <base3_3slr_stream.xclbin> <gpt2_real_io_dir>"
                   " [iterations] [device_index]\n";
      return 1;
    }

    const std::string xclbin_path = argv[1];
    const fs::path tensor_dir = fs::path(argv[2]);
    const int iterations = argc >= 4 ? std::stoi(argv[3]) : 1;
    const int device_index = argc >= 5 ? std::stoi(argv[4]) : 0;
    if (iterations <= 0)
      throw std::runtime_error("iterations must be positive");

    auto device = xrt::device(device_index);
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
    auto causal_bias =
        make_bo(device, k0, 4, 1 * 1 * 1024 * 1024 * I1, "causal_bias");
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

    load_file_to_bo(cache_position, tensor_dir / "cache_position.bin");
    load_file_to_bo(causal_bias, tensor_dir / "causal_bias.bin");
    load_file_to_bo(attention_bias, tensor_dir / "attention_bias.bin");

    double total_ms = 0.0;
    DiffStats final_stats;
    int final_token_id = -1;
    float final_token_logit = 0.0f;

    for (int iter = 0; iter < iterations; ++iter) {
      load_file_to_bo(hidden_in, tensor_dir / "hidden_input.bin");

      const auto t0 = std::chrono::high_resolution_clock::now();
      for (int layer = 0; layer < kNumLayers; ++layer) {
        char layer_name[32];
        std::snprintf(layer_name, sizeof(layer_name), "layer_%02d", layer);
        const fs::path layer_dir = tensor_dir / layer_name;

        load_layer_weights(layer_dir, c0_ln1_w, c0_ln1_b, c0_qkv_w, c0_qkv_b,
                           c0_attn_out_w, c1_attn_out_b, c1_ln2_w, c1_ln2_b,
                           c1_fc1_w, c1_fc1_b, c2_fc2_w, c2_fc2_b);

        load_file_to_bo(key_cache_in, tensor_dir / "zero_key_cache.bin");
        load_file_to_bo(value_cache_in, tensor_dir / "zero_value_cache.bin");
        zero_to_device(key_cache_out);
        zero_to_device(value_cache_out);
        zero_to_device(hidden_out);

        xrt::run r2(k2), r1(k1), r0(k0);
        set_b3c2_args(r2, hidden_out, c2_fc2_w, c2_fc2_b);
        set_b3c1_args(r1, c1_attn_out_b, c1_ln2_w, c1_ln2_b, c1_fc1_w,
                      c1_fc1_b);
        set_b3c0_args(r0, hidden_in, cache_position, key_cache_in,
                      value_cache_in, causal_bias, attention_bias,
                      key_cache_out, value_cache_out, c0_ln1_w, c0_ln1_b,
                      c0_qkv_w, c0_qkv_b, c0_attn_out_w);

        r2.start();
        r1.start();
        r0.start();
        r0.wait();
        r1.wait();
        r2.wait();

        const fs::path golden = layer_dir / "golden_hidden_out.bin";
        if (file_exists(golden)) {
          const auto stats = compare_bf16_bo_to_file(hidden_out, golden);
          std::cout << "iter " << iter << " layer " << layer
                    << " hidden_max_abs=" << stats.max_abs
                    << " hidden_mean_abs=" << stats.mean_abs
                    << " hidden_mean_ref_abs=" << stats.mean_ref_abs
                    << " hidden_mean_percent_error=" << stats.mean_percent
                    << "\n";
          final_stats = stats;
        }

        copy_bo_device_to_device_via_host(hidden_in, hidden_out);
      }
      const auto t1 = std::chrono::high_resolution_clock::now();
      const double ms =
          std::chrono::duration<double, std::milli>(t1 - t0).count();
      total_ms += ms;

      const auto hidden = read_bf16_bo_as_float(hidden_out);
      const auto ln_w = read_bf16_file_as_float(tensor_dir / "final_ln_w.bin", 768);
      const auto ln_b = read_bf16_file_as_float(tensor_dir / "final_ln_b.bin", 768);
      const auto lm_head_w =
          read_bf16_file_as_float(tensor_dir / "lm_head_w.bin", 50257 * 768);
      const auto token = compute_next_token_cpu(hidden, ln_w, ln_b, lm_head_w);
      final_token_id = token.token_id;
      final_token_logit = token.logit;

      const int golden_token =
          read_first_i32(tensor_dir / "golden_top10_token_ids.bin");
      std::cout << "iteration " << iter << " fpga_next_token_id="
                << final_token_id << " fpga_next_token_logit="
                << final_token_logit << " golden_next_token_id="
                << golden_token << " top1_match="
                << (final_token_id == golden_token ? "yes" : "no") << "\n";
      std::cout << "iteration " << iter << " 12layer_latency_ms=" << ms
                << "\n";
    }

    print_first_bf16(hidden_out, 16);
    std::cout << "average_12layer_latency_ms=" << (total_ms / iterations)
              << "\n";
    std::cout << "final_hidden_max_abs=" << final_stats.max_abs
              << " final_hidden_mean_abs=" << final_stats.mean_abs
              << " final_hidden_mean_percent_error="
              << final_stats.mean_percent << "\n";
    std::cout << "final_next_token_id=" << final_token_id
              << " final_next_token_logit=" << final_token_logit << "\n";
    return 0;
  } catch (const std::exception &ex) {
    std::cerr << "error: " << ex.what() << "\n";
    return 1;
  }
}
