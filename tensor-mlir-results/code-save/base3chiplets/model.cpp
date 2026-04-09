#include <hls_stream.h>
#include <stdint.h>

#include "chip0.cpp"
#include "chip1.cpp"
#include "chip2.cpp"

using namespace std;

static void read_hidden_stream(hls::stream<ap_float<16, 8>> &in,
                               ap_float<16, 8> out[1][1][768]) {
  for (int i = 0; i < 1; ++i)
    for (int j = 0; j < 1; ++j)
      for (int k = 0; k < 768; ++k)
        out[i][j][k] = in.read();
}

static void write_hidden_stream(ap_float<16, 8> in[1][1][768],
                                hls::stream<ap_float<16, 8>> &out) {
  for (int i = 0; i < 1; ++i)
    for (int j = 0; j < 1; ++j)
      for (int k = 0; k < 768; ++k)
        out.write(in[i][j][k]);
}

static void read_hidden_fp32_stream(hls::stream<ap_float<32, 8>> &in,
                                    ap_float<32, 8> out[1][1][768]) {
  for (int i = 0; i < 1; ++i)
    for (int j = 0; j < 1; ++j)
      for (int k = 0; k < 768; ++k)
        out[i][j][k] = in.read();
}

static void write_hidden_fp32_stream(ap_float<32, 8> in[1][1][768],
                                     hls::stream<ap_float<32, 8>> &out) {
  for (int i = 0; i < 1; ++i)
    for (int j = 0; j < 1; ++j)
      for (int k = 0; k < 768; ++k)
        out.write(in[i][j][k]);
}

static void read_mlp_stream(hls::stream<ap_float<16, 8>> &in,
                            ap_float<16, 8> out[1][1][3072]) {
  for (int a = 0; a < 1; ++a)
    for (int b = 0; b < 1; ++b)
      for (int c = 0; c < 3072; ++c)
        out[a][b][c] = in.read();
}

static void write_mlp_stream(ap_float<16, 8> in[1][1][3072],
                             hls::stream<ap_float<16, 8>> &out) {
  for (int a = 0; a < 1; ++a)
    for (int b = 0; b < 1; ++b)
      for (int c = 0; c < 3072; ++c)
        out.write(in[a][b][c]);
}

static void duplicate_hidden_input(
    hls::stream<ap_float<16, 8>> &hidden_in_stream,
    hls::stream<ap_float<16, 8>> &hidden_to_chip0,
    hls::stream<ap_float<16, 8>> &hidden_to_chip1) {
  #pragma HLS inline off

  for (int i = 0; i < 1; ++i)
    for (int j = 0; j < 1; ++j)
      for (int k = 0; k < 768; ++k) {
        ap_float<16, 8> value = hidden_in_stream.read();
        hidden_to_chip0.write(value);
        hidden_to_chip1.write(value);
      }
}

static void chip0_stream_wrapper(
    hls::stream<ap_float<16, 8>> &hidden_in_stream, ap_int<32> cache_position[1],
    ap_float<16, 8> key_cache_in[1][12][128][64],
    ap_float<16, 8> value_cache_in[1][12][128][64],
    ap_int<1> causal_mask[1][1][1024][1024],
    ap_float<16, 8> attention_bias[1][1][1][128],
    ap_float<16, 8> key_cache_out[1][12][128][64],
    ap_float<16, 8> value_cache_out[1][12][128][64],
    hls::stream<ap_float<32, 8>> &hidden_to_chip1, ap_float<16, 8> c0_ln1_w[768],
    ap_float<16, 8> c0_ln1_b[768], ap_float<16, 8> c0_qkv_w[768][2304],
    ap_float<16, 8> c0_qkv_b[2304], ap_float<16, 8> c0_attn_out_w[768][768]) {
  #pragma HLS inline off

  ap_float<16, 8> hidden_in[1][1][768];
  ap_float<32, 8> hidden_local[1][1][768];
  static volatile uint32_t timer0[8];
  static volatile uint32_t debug0[256];

  read_hidden_stream(hidden_in_stream, hidden_in);
  kernel_0_chip0(hidden_in, cache_position, key_cache_in, value_cache_in,
                 causal_mask, attention_bias, key_cache_out, value_cache_out,
                 hidden_local, c0_ln1_w, c0_ln1_b, c0_qkv_w, c0_qkv_b,
                 c0_attn_out_w, timer0, debug0);
  write_hidden_fp32_stream(hidden_local, hidden_to_chip1);
}

static void chip1_stream_wrapper(
    hls::stream<ap_float<16, 8>> &hidden_original_stream,
    hls::stream<ap_float<32, 8>> &hidden_from_chip0,
    hls::stream<ap_float<16, 8>> &mlp_to_chip2,
    hls::stream<ap_float<16, 8>> &residual_to_chip2,
    ap_float<16, 8> c1_attn_out_b[768], ap_float<16, 8> c1_ln2_w[768],
    ap_float<16, 8> c1_ln2_b[768], ap_float<16, 8> c1_fc1_w[768][3072],
    ap_float<16, 8> c1_fc1_b[3072]) {
  #pragma HLS inline off

  ap_float<16, 8> hidden_original[1][1][768];
  ap_float<32, 8> hidden_local[1][1][768];
  ap_float<16, 8> mlp_local[1][1][3072];
  ap_float<16, 8> residual_local[1][1][768];
  static volatile uint32_t timer1[8];
  static volatile uint32_t debug1[256];

  read_hidden_stream(hidden_original_stream, hidden_original);
  read_hidden_fp32_stream(hidden_from_chip0, hidden_local);

  kernel_0_chip1(hidden_original, hidden_local, mlp_local, residual_local,
                 c1_attn_out_b, c1_ln2_w, c1_ln2_b, c1_fc1_w, c1_fc1_b, timer1,
                 debug1);

  write_mlp_stream(mlp_local, mlp_to_chip2);
  write_hidden_stream(residual_local, residual_to_chip2);
}

static void chip2_stream_wrapper(
    hls::stream<ap_float<16, 8>> &residual_from_chip1,
    hls::stream<ap_float<16, 8>> &mlp_from_chip1,
    hls::stream<ap_float<16, 8>> &hidden_out_stream,
    ap_float<16, 8> c2_fc2_w[3072][768], ap_float<16, 8> c2_fc2_b[768]) {
  #pragma HLS inline off

  ap_float<16, 8> residual_local[1][1][768];
  ap_float<16, 8> mlp_local[1][1][3072];
  ap_float<16, 8> hidden_out[1][1][768];
  static volatile uint32_t timer2[8];
  static volatile uint32_t debug2[256];

  read_hidden_stream(residual_from_chip1, residual_local);
  read_mlp_stream(mlp_from_chip1, mlp_local);

  kernel_0_chip2(residual_local, mlp_local, hidden_out, c2_fc2_w, c2_fc2_b,
                 timer2, debug2);

  write_hidden_stream(hidden_out, hidden_out_stream);
}

void base3_stitched_stream_top(
    hls::stream<ap_float<16, 8>> &hidden_in_stream, ap_int<32> cache_position[1],
    ap_float<16, 8> key_cache_in[1][12][128][64],
    ap_float<16, 8> value_cache_in[1][12][128][64],
    ap_int<1> causal_mask[1][1][1024][1024],
    ap_float<16, 8> attention_bias[1][1][1][128],
    ap_float<16, 8> key_cache_out[1][12][128][64],
    ap_float<16, 8> value_cache_out[1][12][128][64],
    hls::stream<ap_float<16, 8>> &hidden_out_stream,
    ap_float<16, 8> c0_ln1_w[768], ap_float<16, 8> c0_ln1_b[768],
    ap_float<16, 8> c0_qkv_w[768][2304], ap_float<16, 8> c0_qkv_b[2304],
    ap_float<16, 8> c0_attn_out_w[768][768], ap_float<16, 8> c1_attn_out_b[768],
    ap_float<16, 8> c1_ln2_w[768], ap_float<16, 8> c1_ln2_b[768],
    ap_float<16, 8> c1_fc1_w[768][3072], ap_float<16, 8> c1_fc1_b[3072],
    ap_float<16, 8> c2_fc2_w[3072][768], ap_float<16, 8> c2_fc2_b[768]) {
  #pragma HLS interface axis port=hidden_in_stream
  #pragma HLS interface axis port=hidden_out_stream
  #pragma HLS interface s_axilite port=return bundle=control
  #pragma HLS dataflow

  hls::stream<ap_float<16, 8>> hidden_00("hidden_00");
  hls::stream<ap_float<16, 8>> hidden_orig_01("hidden_orig_01");
  hls::stream<ap_float<32, 8>> hidden_01("hidden_01");
  hls::stream<ap_float<16, 8>> mlp_12("mlp_12");
  hls::stream<ap_float<16, 8>> residual_12("residual_12");

  #pragma HLS stream variable=hidden_00 depth=32
  #pragma HLS stream variable=hidden_orig_01 depth=32
  #pragma HLS stream variable=hidden_01 depth=32
  #pragma HLS stream variable=mlp_12 depth=32
  #pragma HLS stream variable=residual_12 depth=32

  duplicate_hidden_input(hidden_in_stream, hidden_00, hidden_orig_01);

  chip0_stream_wrapper(hidden_00, cache_position, key_cache_in, value_cache_in,
                       causal_mask, attention_bias, key_cache_out,
                       value_cache_out, hidden_01, c0_ln1_w, c0_ln1_b,
                       c0_qkv_w, c0_qkv_b, c0_attn_out_w);

  chip1_stream_wrapper(hidden_orig_01, hidden_01, mlp_12, residual_12,
                       c1_attn_out_b, c1_ln2_w, c1_ln2_b, c1_fc1_w, c1_fc1_b);

  chip2_stream_wrapper(residual_12, mlp_12, hidden_out_stream, c2_fc2_w,
                       c2_fc2_b);
}
