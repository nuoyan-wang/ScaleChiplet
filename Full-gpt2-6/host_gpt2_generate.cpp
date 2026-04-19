#include <xrt/xrt_bo.h>
#include <xrt/xrt_device.h>
#include <xrt/xrt_kernel.h>
#include <xrt/xrt_uuid.h>

#include <algorithm>
#include <chrono>
#include <cmath>
#include <cstdint>
#include <cstdio>
#include <cstring>
#include <exception>
#include <filesystem>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <limits>
#include <numeric>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

namespace fs = std::filesystem;

namespace {

constexpr int kNumLayers = 12;
constexpr size_t kHidden = 768;
constexpr size_t kHeads = 12;
constexpr size_t kSeq = 128;
constexpr size_t kHeadDim = 64;
constexpr size_t kVocab = 50257;
constexpr size_t kCausalSeq = 1024;
constexpr size_t kFc1 = 3072;
constexpr size_t kQkv = 2304;
constexpr size_t kWordBytes = 32;
constexpr size_t F16 = sizeof(uint16_t);

struct NamedBo {
  std::string name;
  size_t bytes;
  xrt::bo bo;
};

struct TopToken {
  int token_id = -1;
  float logit = -std::numeric_limits<float>::infinity();
};

xrt::kernel open_kernel(xrt::device& device, const xrt::uuid& uuid,
                        const std::vector<std::string>& names) {
  std::exception_ptr last_error;
  for (const auto& name : names) {
    try {
      return xrt::kernel(device, uuid, name);
    } catch (...) {
      last_error = std::current_exception();
    }
  }
  if (last_error)
    std::rethrow_exception(last_error);
  throw std::runtime_error("failed to open kernel");
}

NamedBo make_bo(xrt::device& device, xrt::kernel& kernel, int arg_index,
                size_t bytes, const std::string& name) {
  return NamedBo{name, bytes, xrt::bo(device, bytes, kernel.group_id(arg_index))};
}

std::vector<uint8_t> read_file(const fs::path& path) {
  std::ifstream file(path, std::ios::binary);
  if (!file)
    throw std::runtime_error("failed to open " + path.string());
  return std::vector<uint8_t>(std::istreambuf_iterator<char>(file), {});
}

std::vector<uint8_t> read_file_exact(const fs::path& path, size_t bytes) {
  auto data = read_file(path);
  if (data.size() != bytes)
    throw std::runtime_error("wrong byte count in " + path.string() +
                             ": expected " + std::to_string(bytes) +
                             ", got " + std::to_string(data.size()));
  return data;
}

bool file_exists(const fs::path& path) {
  std::error_code ec;
  return fs::is_regular_file(path, ec);
}

void load_file_to_bo(NamedBo& buffer, const fs::path& path) {
  auto data = read_file_exact(path, buffer.bytes);
  auto* ptr = buffer.bo.map<uint8_t*>();
  std::memcpy(ptr, data.data(), data.size());
  buffer.bo.sync(XCL_BO_SYNC_BO_TO_DEVICE);
}

void write_vector_to_bo(NamedBo& buffer, const std::vector<uint8_t>& data) {
  if (data.size() != buffer.bytes)
    throw std::runtime_error("wrong vector byte count for " + buffer.name);
  auto* ptr = buffer.bo.map<uint8_t*>();
  std::memcpy(ptr, data.data(), data.size());
  buffer.bo.sync(XCL_BO_SYNC_BO_TO_DEVICE);
}

std::vector<uint8_t> read_bo_to_vector(NamedBo& buffer) {
  buffer.bo.sync(XCL_BO_SYNC_BO_FROM_DEVICE);
  auto* ptr = buffer.bo.map<uint8_t*>();
  return std::vector<uint8_t>(ptr, ptr + buffer.bytes);
}

void zero_to_device(NamedBo& buffer) {
  auto* ptr = buffer.bo.map<uint8_t*>();
  std::memset(ptr, 0, buffer.bytes);
  buffer.bo.sync(XCL_BO_SYNC_BO_TO_DEVICE);
}

float bf16_to_float(uint16_t value) {
  uint32_t bits = static_cast<uint32_t>(value) << 16;
  float result;
  std::memcpy(&result, &bits, sizeof(result));
  return result;
}

uint16_t float_to_bf16(float value) {
  uint32_t bits = 0;
  std::memcpy(&bits, &value, sizeof(bits));
  const uint32_t lsb = (bits >> 16) & 1u;
  const uint32_t rounding_bias = 0x7fffu + lsb;
  return static_cast<uint16_t>((bits + rounding_bias) >> 16);
}

std::vector<float> read_bf16_file_as_float(const fs::path& path,
                                           size_t elements) {
  auto data = read_file_exact(path, elements * sizeof(uint16_t));
  const auto* raw = reinterpret_cast<const uint16_t*>(data.data());
  std::vector<float> result(elements);
  for (size_t i = 0; i < elements; ++i)
    result[i] = bf16_to_float(raw[i]);
  return result;
}

std::vector<int32_t> read_i32_file(const fs::path& path) {
  auto data = read_file(path);
  if (data.size() % sizeof(int32_t) != 0)
    throw std::runtime_error("int32 file byte count is not aligned: " +
                             path.string());
  std::vector<int32_t> result(data.size() / sizeof(int32_t));
  std::memcpy(result.data(), data.data(), data.size());
  return result;
}

std::string decode_hex_string(const std::string& hex) {
  std::string out;
  if (hex.size() % 2 != 0)
    return out;
  out.reserve(hex.size() / 2);
  for (size_t i = 0; i < hex.size(); i += 2) {
    const auto byte =
        static_cast<char>(std::stoul(hex.substr(i, 2), nullptr, 16));
    out.push_back(byte);
  }
  return out;
}

std::vector<std::string> load_decoder(const fs::path& path) {
  std::vector<std::string> decoder(kVocab);
  for (size_t i = 0; i < kVocab; ++i)
    decoder[i] = "<" + std::to_string(i) + ">";
  if (!file_exists(path))
    return decoder;

  std::ifstream file(path);
  std::string line;
  while (std::getline(file, line)) {
    const auto tab = line.find('\t');
    if (tab == std::string::npos)
      continue;
    const int id = std::stoi(line.substr(0, tab));
    if (id >= 0 && static_cast<size_t>(id) < decoder.size())
      decoder[id] = decode_hex_string(line.substr(tab + 1));
  }
  return decoder;
}

void write_hidden_embedding_to_bo(NamedBo& hidden_in,
                                  const std::vector<float>& wte,
                                  const std::vector<float>& wpe, int token_id,
                                  int position) {
  if (token_id < 0 || static_cast<size_t>(token_id) >= kVocab)
    throw std::runtime_error("token id out of range");
  if (position < 0 || static_cast<size_t>(position) >= 1024)
    throw std::runtime_error("position out of range");
  auto* ptr = hidden_in.bo.map<uint16_t*>();
  const size_t token_base = static_cast<size_t>(token_id) * kHidden;
  const size_t pos_base = static_cast<size_t>(position) * kHidden;
  for (size_t i = 0; i < kHidden; ++i)
    ptr[i] = float_to_bf16(wte[token_base + i] + wpe[pos_base + i]);
  hidden_in.bo.sync(XCL_BO_SYNC_BO_TO_DEVICE);
}

std::vector<float> read_hidden_bo_as_float(NamedBo& hidden_out) {
  hidden_out.bo.sync(XCL_BO_SYNC_BO_FROM_DEVICE);
  auto* raw = hidden_out.bo.map<uint16_t*>();
  std::vector<float> hidden(kHidden);
  for (size_t i = 0; i < kHidden; ++i)
    hidden[i] = bf16_to_float(raw[i]);
  return hidden;
}

void copy_hidden_out_to_hidden_in(NamedBo& hidden_in, NamedBo& hidden_out) {
  hidden_out.bo.sync(XCL_BO_SYNC_BO_FROM_DEVICE);
  auto* src = hidden_out.bo.map<uint8_t*>();
  auto* dst = hidden_in.bo.map<uint8_t*>();
  std::memcpy(dst, src, hidden_in.bytes);
  hidden_in.bo.sync(XCL_BO_SYNC_BO_TO_DEVICE);
}

TopToken compute_next_token_cpu(const std::vector<float>& hidden,
                                const std::vector<float>& ln_w,
                                const std::vector<float>& ln_b,
                                const std::vector<float>& lm_head_w) {
  const double mean =
      std::accumulate(hidden.begin(), hidden.end(), 0.0) / kHidden;
  double var = 0.0;
  for (float v : hidden) {
    const double d = static_cast<double>(v) - mean;
    var += d * d;
  }
  var /= kHidden;
  const double inv_std = 1.0 / std::sqrt(var + 1.0e-5);

  std::vector<float> norm(kHidden);
  for (size_t i = 0; i < kHidden; ++i)
    norm[i] = static_cast<float>((static_cast<double>(hidden[i]) - mean) *
                                     inv_std * ln_w[i] +
                                 ln_b[i]);

  TopToken best;
  for (size_t tok = 0; tok < kVocab; ++tok) {
    const float* w = lm_head_w.data() + tok * kHidden;
    double acc = 0.0;
    for (size_t i = 0; i < kHidden; ++i)
      acc += static_cast<double>(norm[i]) * static_cast<double>(w[i]);
    const float logit = static_cast<float>(acc);
    if (logit > best.logit) {
      best.logit = logit;
      best.token_id = static_cast<int>(tok);
    }
  }
  return best;
}

void pack_mask_bytes_to_bo(NamedBo& buffer, const fs::path& path) {
  auto bytes = read_file(path);
  if (bytes.size() != buffer.bytes * 8)
    throw std::runtime_error("unexpected causal mask size in " + path.string());
  std::vector<uint8_t> packed(buffer.bytes, 0);
  for (size_t i = 0; i < bytes.size(); ++i) {
    if (bytes[i] != 0)
      packed[i / 8] |= static_cast<uint8_t>(1u << (i % 8));
  }
  write_vector_to_bo(buffer, packed);
}

void load_partitioned_2x2_words_to_bos(const fs::path& path, size_t rows,
                                       size_t cols, NamedBo& part00,
                                       NamedBo& part01, NamedBo& part10,
                                       NamedBo& part11) {
  auto data = read_file_exact(path, rows * cols * kWordBytes);
  const size_t out_rows = rows / 2;
  const size_t out_cols = cols / 2;
  const size_t out_bytes = out_rows * out_cols * kWordBytes;
  if (part00.bytes != out_bytes || part01.bytes != out_bytes ||
      part10.bytes != out_bytes || part11.bytes != out_bytes)
    throw std::runtime_error("partitioned BO size mismatch for " + path.string());

  std::vector<uint8_t> d00(out_bytes), d01(out_bytes), d10(out_bytes), d11(out_bytes);
  auto place_word = [&](std::vector<uint8_t>& out, size_t dst_index,
                        const uint8_t* src) {
    std::memcpy(out.data() + dst_index * kWordBytes, src, kWordBytes);
  };

  for (size_t r = 0; r < rows; ++r) {
    for (size_t c = 0; c < cols; ++c) {
      const size_t src_index = r * cols + c;
      const uint8_t* src = data.data() + src_index * kWordBytes;
      const size_t dst_r = r / 2;
      const size_t dst_c = c / 2;
      const size_t dst_index = dst_r * out_cols + dst_c;
      if ((r & 1u) == 0 && (c & 1u) == 0)
        place_word(d00, dst_index, src);
      else if ((r & 1u) == 0 && (c & 1u) == 1)
        place_word(d01, dst_index, src);
      else if ((r & 1u) == 1 && (c & 1u) == 0)
        place_word(d10, dst_index, src);
      else
        place_word(d11, dst_index, src);
    }
  }

  write_vector_to_bo(part00, d00);
  write_vector_to_bo(part01, d01);
  write_vector_to_bo(part10, d10);
  write_vector_to_bo(part11, d11);
}

void set_s6c0_args(xrt::run& run, NamedBo& hidden_in, NamedBo& c0_ln1_w,
                   NamedBo& c0_ln1_b, NamedBo& c0_qkv_w, NamedBo& c0_qkv_b) {
  run.set_arg(0, hidden_in.bo);
  run.set_arg(3, c0_ln1_w.bo);
  run.set_arg(4, c0_ln1_b.bo);
  run.set_arg(5, c0_qkv_w.bo);
  run.set_arg(6, c0_qkv_b.bo);
}

void set_s6c1_args(xrt::run& run, int32_t cache_position, NamedBo& key_cache_in,
                   NamedBo& value_cache_in, NamedBo& causal_bias_packed,
                   NamedBo& attention_bias, NamedBo& key_cache_out,
                   NamedBo& value_cache_out) {
  run.set_arg(2, cache_position);
  run.set_arg(3, key_cache_in.bo);
  run.set_arg(4, value_cache_in.bo);
  run.set_arg(5, causal_bias_packed.bo);
  run.set_arg(6, attention_bias.bo);
  run.set_arg(7, key_cache_out.bo);
  run.set_arg(8, value_cache_out.bo);
}

void set_s6c2_args(xrt::run& run, NamedBo& c2_attn_out_w,
                   NamedBo& c2_attn_out_b, NamedBo& c2_ln2_w,
                   NamedBo& c2_ln2_b) {
  run.set_arg(4, c2_attn_out_w.bo);
  run.set_arg(5, c2_attn_out_b.bo);
  run.set_arg(6, c2_ln2_w.bo);
  run.set_arg(7, c2_ln2_b.bo);
}

void set_s6c3_args(xrt::run& run, NamedBo& c3_fc1_w_00, NamedBo& c3_fc1_w_01,
                   NamedBo& c3_fc1_w_10, NamedBo& c3_fc1_w_11,
                   NamedBo& c3_fc1_b) {
  run.set_arg(3, c3_fc1_w_00.bo);
  run.set_arg(4, c3_fc1_w_01.bo);
  run.set_arg(5, c3_fc1_w_10.bo);
  run.set_arg(6, c3_fc1_w_11.bo);
  run.set_arg(7, c3_fc1_b.bo);
}

void set_s6c5_args(xrt::run& run, NamedBo& hidden_out, NamedBo& c5_fc2_w_00,
                   NamedBo& c5_fc2_w_01, NamedBo& c5_fc2_w_10,
                   NamedBo& c5_fc2_w_11, NamedBo& c5_fc2_b) {
  run.set_arg(2, hidden_out.bo);
  run.set_arg(3, c5_fc2_w_00.bo);
  run.set_arg(4, c5_fc2_w_01.bo);
  run.set_arg(5, c5_fc2_w_10.bo);
  run.set_arg(6, c5_fc2_w_11.bo);
  run.set_arg(7, c5_fc2_b.bo);
}

void load_layer_weights(const fs::path& layer_dir, NamedBo& c0_ln1_w,
                        NamedBo& c0_ln1_b, NamedBo& c0_qkv_w,
                        NamedBo& c0_qkv_b, NamedBo& c2_attn_out_w,
                        NamedBo& c2_attn_out_b, NamedBo& c2_ln2_w,
                        NamedBo& c2_ln2_b, NamedBo& c3_fc1_w_00,
                        NamedBo& c3_fc1_w_01, NamedBo& c3_fc1_w_10,
                        NamedBo& c3_fc1_w_11, NamedBo& c3_fc1_b,
                        NamedBo& c5_fc2_w_00, NamedBo& c5_fc2_w_01,
                        NamedBo& c5_fc2_w_10, NamedBo& c5_fc2_w_11,
                        NamedBo& c5_fc2_b) {
  load_file_to_bo(c0_ln1_w, layer_dir / "c0_ln1_w.bin");
  load_file_to_bo(c0_ln1_b, layer_dir / "c0_ln1_b.bin");
  load_file_to_bo(c0_qkv_w, layer_dir / "c0_qkv_w.bin");
  load_file_to_bo(c0_qkv_b, layer_dir / "c0_qkv_b.bin");

  load_file_to_bo(c2_attn_out_w, layer_dir / "c0_attn_out_w.bin");
  load_file_to_bo(c2_attn_out_b, layer_dir / "c1_attn_out_b.bin");
  load_file_to_bo(c2_ln2_w, layer_dir / "c1_ln2_w.bin");
  load_file_to_bo(c2_ln2_b, layer_dir / "c1_ln2_b.bin");

  load_partitioned_2x2_words_to_bos(layer_dir / "c1_fc1_w.bin", 768, 192,
                                    c3_fc1_w_00, c3_fc1_w_01, c3_fc1_w_10,
                                    c3_fc1_w_11);
  load_file_to_bo(c3_fc1_b, layer_dir / "c1_fc1_b.bin");

  load_partitioned_2x2_words_to_bos(layer_dir / "c2_fc2_w.bin", 3072, 48,
                                    c5_fc2_w_00, c5_fc2_w_01, c5_fc2_w_10,
                                    c5_fc2_w_11);
  load_file_to_bo(c5_fc2_b, layer_dir / "c2_fc2_b.bin");
}

}  // namespace

int main(int argc, char** argv) {
  try {
    if (argc < 3) {
      std::cerr << "usage: " << argv[0]
                << " <split6_3slr_stream.xclbin> <gpt2_real_io_dir>"
                   " [max_new_tokens=30] [device_index=0]\n";
      return 1;
    }

    const std::string xclbin_path = argv[1];
    const fs::path tensor_dir = fs::path(argv[2]);
    const int max_new_tokens = argc >= 4 ? std::stoi(argv[3]) : 30;
    const int device_index = argc >= 5 ? std::stoi(argv[4]) : 0;
    if (max_new_tokens <= 0)
      throw std::runtime_error("max_new_tokens must be positive");

    const auto prompt_ids = read_i32_file(tensor_dir / "prompt_token_ids.bin");
    if (prompt_ids.empty())
      throw std::runtime_error("prompt_token_ids.bin is empty");

    const auto decoder = load_decoder(tensor_dir / "token_decoder_hex.tsv");
    const auto wte = read_bf16_file_as_float(tensor_dir / "wte.bin", kVocab * kHidden);
    const auto wpe = read_bf16_file_as_float(tensor_dir / "wpe.bin", 1024 * kHidden);
    const auto ln_w = read_bf16_file_as_float(tensor_dir / "final_ln_w.bin", kHidden);
    const auto ln_b = read_bf16_file_as_float(tensor_dir / "final_ln_b.bin", kHidden);
    const auto lm_head_w =
        read_bf16_file_as_float(tensor_dir / "lm_head_w.bin", kVocab * kHidden);

    xrt::device device(device_index);
    auto uuid = device.load_xclbin(xclbin_path);
    auto k0 = open_kernel(device, uuid, {"s6c0:{s6c0_1}", "s6c0"});
    auto k1 = open_kernel(device, uuid, {"s6c1:{s6c1_1}", "s6c1"});
    auto k2 = open_kernel(device, uuid, {"s6c2:{s6c2_1}", "s6c2"});
    auto k3 = open_kernel(device, uuid, {"s6c3:{s6c3_1}", "s6c3"});
    auto k4 = open_kernel(device, uuid, {"s6c4:{s6c4_1}", "s6c4"});
    auto k5 = open_kernel(device, uuid, {"s6c5:{s6c5_1}", "s6c5"});

    auto hidden_in = make_bo(device, k0, 0, 1 * 1 * 48 * kWordBytes, "hidden_in");
    auto c0_ln1_w = make_bo(device, k0, 3, 48 * kWordBytes, "c0_ln1_w");
    auto c0_ln1_b = make_bo(device, k0, 4, 48 * kWordBytes, "c0_ln1_b");
    auto c0_qkv_w = make_bo(device, k0, 5, 768 * 144 * kWordBytes, "c0_qkv_w");
    auto c0_qkv_b = make_bo(device, k0, 6, 144 * kWordBytes, "c0_qkv_b");

    auto key_cache_in =
        make_bo(device, k1, 3, 1 * kHeads * kSeq * 4 * kWordBytes, "key_cache_in");
    auto value_cache_in =
        make_bo(device, k1, 4, 1 * kHeads * kSeq * 4 * kWordBytes, "value_cache_in");
    auto causal_bias_packed =
        make_bo(device, k1, 5, 1 * 1 * kCausalSeq * 4 * kWordBytes, "causal_bias");
    auto attention_bias =
        make_bo(device, k1, 6, 1 * 1 * 1 * 8 * kWordBytes, "attention_bias");
    auto key_cache_out =
        make_bo(device, k1, 7, 1 * kHeads * kSeq * 4 * kWordBytes, "key_cache_out");
    auto value_cache_out =
        make_bo(device, k1, 8, 1 * kHeads * kSeq * 4 * kWordBytes, "value_cache_out");

    auto c2_attn_out_w =
        make_bo(device, k2, 4, 768 * 48 * kWordBytes, "c2_attn_out_w");
    auto c2_attn_out_b = make_bo(device, k2, 5, 48 * kWordBytes, "c2_attn_out_b");
    auto c2_ln2_w = make_bo(device, k2, 6, 48 * kWordBytes, "c2_ln2_w");
    auto c2_ln2_b = make_bo(device, k2, 7, 48 * kWordBytes, "c2_ln2_b");

    constexpr size_t kFc1PartBytes = 384 * 96 * kWordBytes;
    auto c3_fc1_w_00 = make_bo(device, k3, 3, kFc1PartBytes, "c3_fc1_w_00");
    auto c3_fc1_w_01 = make_bo(device, k3, 4, kFc1PartBytes, "c3_fc1_w_01");
    auto c3_fc1_w_10 = make_bo(device, k3, 5, kFc1PartBytes, "c3_fc1_w_10");
    auto c3_fc1_w_11 = make_bo(device, k3, 6, kFc1PartBytes, "c3_fc1_w_11");
    auto c3_fc1_b = make_bo(device, k3, 7, 192 * kWordBytes, "c3_fc1_b");

    auto hidden_out = make_bo(device, k5, 2, 1 * 1 * 48 * kWordBytes, "hidden_out");
    constexpr size_t kFc2PartBytes = 1536 * 24 * kWordBytes;
    auto c5_fc2_w_00 = make_bo(device, k5, 3, kFc2PartBytes, "c5_fc2_w_00");
    auto c5_fc2_w_01 = make_bo(device, k5, 4, kFc2PartBytes, "c5_fc2_w_01");
    auto c5_fc2_w_10 = make_bo(device, k5, 5, kFc2PartBytes, "c5_fc2_w_10");
    auto c5_fc2_w_11 = make_bo(device, k5, 6, kFc2PartBytes, "c5_fc2_w_11");
    auto c5_fc2_b = make_bo(device, k5, 7, 48 * kWordBytes, "c5_fc2_b");

    pack_mask_bytes_to_bo(causal_bias_packed, tensor_dir / "causal_bias.bin");

    const size_t cache_bytes = 1 * kHeads * kSeq * 4 * kWordBytes;
    std::vector<std::vector<uint8_t>> key_cache(kNumLayers,
                                                std::vector<uint8_t>(cache_bytes));
    std::vector<std::vector<uint8_t>> value_cache(kNumLayers,
                                                  std::vector<uint8_t>(cache_bytes));

    std::vector<int> all_tokens(prompt_ids.begin(), prompt_ids.end());
    std::string output_text;
    for (int id : all_tokens)
      output_text += static_cast<size_t>(id) < decoder.size()
                         ? decoder[id]
                         : "<" + std::to_string(id) + ">";

    std::cout << "prompt_tokens:";
    for (int id : all_tokens)
      std::cout << " " << id;
    std::cout << "\n";
    std::cout << "prompt_text: " << output_text << "\n";

    const int total_positions =
        static_cast<int>(prompt_ids.size()) + max_new_tokens - 1;
    if (total_positions > static_cast<int>(kSeq))
      throw std::runtime_error("prompt length + max_new_tokens exceeds 128");

    double total_ms = 0.0;
    double first_token_ms = 0.0;
    int positions_run = 0;
    int generated_tokens = 0;
    bool first_token_emitted = false;
    int current_token = all_tokens.front();
    for (int pos = 0; pos < total_positions; ++pos) {
      if (pos < static_cast<int>(prompt_ids.size()))
        current_token = prompt_ids[pos];

      write_hidden_embedding_to_bo(hidden_in, wte, wpe, current_token, pos);

      std::ostringstream bias_name;
      bias_name << "pos_" << std::setw(4) << std::setfill('0') << pos << ".bin";
      load_file_to_bo(attention_bias, tensor_dir / "attention_bias" / bias_name.str());

      const auto t0 = std::chrono::high_resolution_clock::now();
      for (int layer = 0; layer < kNumLayers; ++layer) {
        char layer_name[32];
        std::snprintf(layer_name, sizeof(layer_name), "layer_%02d", layer);
        const fs::path layer_dir = tensor_dir / layer_name;

        load_layer_weights(layer_dir, c0_ln1_w, c0_ln1_b, c0_qkv_w, c0_qkv_b,
                           c2_attn_out_w, c2_attn_out_b, c2_ln2_w, c2_ln2_b,
                           c3_fc1_w_00, c3_fc1_w_01, c3_fc1_w_10, c3_fc1_w_11,
                           c3_fc1_b, c5_fc2_w_00, c5_fc2_w_01, c5_fc2_w_10,
                           c5_fc2_w_11, c5_fc2_b);

        write_vector_to_bo(key_cache_in, key_cache[layer]);
        write_vector_to_bo(value_cache_in, value_cache[layer]);
        zero_to_device(key_cache_out);
        zero_to_device(value_cache_out);
        zero_to_device(hidden_out);

        xrt::run r5(k5), r4(k4), r3(k3), r2(k2), r1(k1), r0(k0);
        set_s6c5_args(r5, hidden_out, c5_fc2_w_00, c5_fc2_w_01, c5_fc2_w_10,
                      c5_fc2_w_11, c5_fc2_b);
        set_s6c3_args(r3, c3_fc1_w_00, c3_fc1_w_01, c3_fc1_w_10, c3_fc1_w_11,
                      c3_fc1_b);
        set_s6c2_args(r2, c2_attn_out_w, c2_attn_out_b, c2_ln2_w, c2_ln2_b);
        set_s6c1_args(r1, pos, key_cache_in, value_cache_in, causal_bias_packed,
                      attention_bias, key_cache_out, value_cache_out);
        set_s6c0_args(r0, hidden_in, c0_ln1_w, c0_ln1_b, c0_qkv_w, c0_qkv_b);

        r5.start();
        r4.start();
        r3.start();
        r2.start();
        r1.start();
        r0.start();

        r0.wait();
        r1.wait();
        r2.wait();
        r3.wait();
        r4.wait();
        r5.wait();

        key_cache[layer] = read_bo_to_vector(key_cache_out);
        value_cache[layer] = read_bo_to_vector(value_cache_out);

        if (layer + 1 < kNumLayers)
          copy_hidden_out_to_hidden_in(hidden_in, hidden_out);
      }
      const auto t1 = std::chrono::high_resolution_clock::now();
      const double token_ms =
          std::chrono::duration<double, std::milli>(t1 - t0).count();
      total_ms += token_ms;
      positions_run += 1;

      if (pos + 1 >= static_cast<int>(prompt_ids.size())) {
        const auto hidden = read_hidden_bo_as_float(hidden_out);
        const auto next = compute_next_token_cpu(hidden, ln_w, ln_b, lm_head_w);
        current_token = next.token_id;
        all_tokens.push_back(current_token);
        generated_tokens += 1;
        if (!first_token_emitted) {
          first_token_ms = total_ms;
          first_token_emitted = true;
        }
        const std::string piece =
            static_cast<size_t>(current_token) < decoder.size()
                ? decoder[current_token]
                : "<" + std::to_string(current_token) + ">";
        output_text += piece;

        if (current_token == 50256) {
          break;
        }
      }
    }

    const double steady_state_ms =
        generated_tokens > 1 ? (total_ms - first_token_ms) : 0.0;
    const double throughput_tok_per_s =
        steady_state_ms > 0.0 ? (1000.0 * static_cast<double>(generated_tokens - 1) /
                                 steady_state_ms)
                              : 0.0;

    std::cout << "time_to_first_token_ms=" << first_token_ms << "\n";
    std::cout << "throughput_tokens_per_s=" << throughput_tok_per_s << "\n";
    std::cout << "generated_tokens=" << generated_tokens << "\n";
    std::cout << "total_sequence_ms=" << total_ms << "\n";
    std::cout << "final_text:\n" << output_text << "\n";
    return 0;
  } catch (const std::exception& ex) {
    std::cerr << "error: " << ex.what() << "\n";
    return 1;
  }
}
