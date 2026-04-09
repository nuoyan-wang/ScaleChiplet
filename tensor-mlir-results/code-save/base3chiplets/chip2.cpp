
//===------------------------------------------------------------*- C++ -*-===//
//
// Automatically generated file for High-level Synthesis (HLS).
//
//===----------------------------------------------------------------------===//

#include <algorithm>
#include <ap_axi_sdata.h>
#include <ap_fixed.h>
#include <ap_float.h>
#include <ap_int.h>
#include <hls_math.h>
#include <hls_stream.h>
#include <hls_vector.h>
#include <math.h>
#include <stdint.h>
#include <string.h>

using namespace std;

void kernel_0_chip2(ap_float<16, 8> arg0000[1][1][768], ap_float<16, 8> arg0001[1][1][3072], ap_float<16, 8> arg0002[1][1][768], ap_float<16, 8> arg0003[3072][768], ap_float<16, 8> arg0004[768], volatile uint32_t timer[8], volatile uint32_t debug[256]) {
#pragma HLS interface m_axi port=timer offset=slave bundle=timer
#pragma HLS interface s_axilite port=timer bundle=control
#pragma HLS interface s_axilite port=debug bundle=control
#pragma HLS interface s_axilite port=return bundle=control
#pragma HLS interface m_axi port=arg0000 offset=slave bundle=gmem1
#pragma HLS interface s_axilite port=arg0000 bundle=control
#pragma HLS interface m_axi port=arg0001 offset=slave bundle=gmem1
#pragma HLS interface s_axilite port=arg0001 bundle=control
#pragma HLS interface m_axi port=arg0002 offset=slave bundle=gmem1
#pragma HLS interface s_axilite port=arg0002 bundle=control
#pragma HLS interface m_axi port=arg0003 offset=slave bundle=gmem1
#pragma HLS interface s_axilite port=arg0003 bundle=control
#pragma HLS interface m_axi port=arg0004 offset=slave bundle=gmem1
#pragma HLS interface s_axilite port=arg0004 bundle=control
  timer[1] = 0x00000000;
  timer[0] = 0x129;
  timer[0] = (timer[0] & ~(1 << 5)) | (1 << 10);
  ap_float<16, 8> v0000[1][1][3072];
  #pragma HLS bind_storage variable=v0000 type=ram_2p impl=bram latency=2
  for (int v0001 = (int)0; v0001 < (int)3072; v0001 += (int)1) {
    ap_float<16, 8> v0002 = arg0001[(int)0][(int)0][v0001];
    ap_float<16, 8> v0003 = v0002 * (ap_float<16, 8>)0.500000;
    v0000[(int)0][(int)0][v0001] = v0003;
  }
  ap_float<16, 8> v0004[1][1][3072];
  #pragma HLS bind_storage variable=v0004 type=ram_2p impl=bram latency=2
  for (int v0005 = (int)0; v0005 < (int)3072; v0005 += (int)1) {
    ap_float<16, 8> v0006 = arg0001[(int)0][(int)0][v0005];
    ap_float<16, 8> v0007 = hls::pow((float)v0006, (float)(ap_float<16, 8>)3.000000);
    v0004[(int)0][(int)0][v0005] = v0007;
  }
  ap_float<16, 8> v0008[1][1][3072];
  #pragma HLS bind_storage variable=v0008 type=ram_2p impl=bram latency=2
  for (int v0009 = (int)0; v0009 < (int)3072; v0009 += (int)1) {
    ap_float<16, 8> v0010 = v0004[(int)0][(int)0][v0009];
    ap_float<16, 8> v0011 = v0010 * (ap_float<16, 8>)0.044678;
    v0008[(int)0][(int)0][v0009] = v0011;
  }
  ap_float<16, 8> v0012[1][1][3072];
  #pragma HLS bind_storage variable=v0012 type=ram_2p impl=bram latency=2
  for (int v0013 = (int)0; v0013 < (int)3072; v0013 += (int)1) {
    ap_float<16, 8> v0014 = arg0001[(int)0][(int)0][v0013];
    ap_float<16, 8> v0015 = v0008[(int)0][(int)0][v0013];
    ap_float<16, 8> v0016 = v0014 + v0015;
    v0012[(int)0][(int)0][v0013] = v0016;
  }
  ap_float<16, 8> v0017[1][1][3072];
  #pragma HLS bind_storage variable=v0017 type=ram_2p impl=bram latency=2
  for (int v0018 = (int)0; v0018 < (int)3072; v0018 += (int)1) {
    ap_float<16, 8> v0019 = v0012[(int)0][(int)0][v0018];
    ap_float<16, 8> v0020 = v0019 * (ap_float<16, 8>)0.796875;
    v0017[(int)0][(int)0][v0018] = v0020;
  }
  ap_float<16, 8> v0021[1][1][3072];
  #pragma HLS bind_storage variable=v0021 type=ram_2p impl=bram latency=2
  for (int v0022 = (int)0; v0022 < (int)3072; v0022 += (int)1) {
    ap_float<16, 8> v0023 = v0017[(int)0][(int)0][v0022];
    ap_float<16, 8> v0024 = hls::tanh((float)v0023);
    v0021[(int)0][(int)0][v0022] = v0024;
  }
  ap_float<16, 8> v0025[1][1][3072];
  #pragma HLS bind_storage variable=v0025 type=ram_2p impl=bram latency=2
  for (int v0026 = (int)0; v0026 < (int)3072; v0026 += (int)1) {
    ap_float<16, 8> v0027 = v0021[(int)0][(int)0][v0026];
    ap_float<16, 8> v0028 = v0027 + (ap_float<16, 8>)1.000000;
    v0025[(int)0][(int)0][v0026] = v0028;
  }
  ap_float<16, 8> v0029[1][1][3072];
  #pragma HLS bind_storage variable=v0029 type=ram_2p impl=bram latency=2
  for (int v0030 = (int)0; v0030 < (int)3072; v0030 += (int)1) {
    ap_float<16, 8> v0031 = v0000[(int)0][(int)0][v0030];
    ap_float<16, 8> v0032 = v0025[(int)0][(int)0][v0030];
    ap_float<16, 8> v0033 = v0031 * v0032;
    v0029[(int)0][(int)0][v0030] = v0033;
  }
  ap_float<32, 8> v0034[1][1][768];
  #pragma HLS bind_storage variable=v0034 type=ram_2p impl=bram latency=2
  for (int v0035 = (int)0; v0035 < (int)768; v0035 += (int)1) {
    v0034[(int)0][(int)0][v0035] = (ap_float<32, 8>)0.000000;
  }
  ap_float<32, 8> v0036[4];
  for (int v0037 = (int)0; v0037 < (int)768; v0037 += (int)1) {
    for (int v0038 = (int)0; v0038 < (int)4; v0038 += (int)1) {
      v0036[v0038] = (ap_float<32, 8>)0.000000;
    }
    for (int v0039 = (int)0; v0039 < (int)3072; v0039 += (int)1) {
      ap_float<16, 8> v0040 = v0029[(int)0][(int)0][v0039];
      ap_float<16, 8> v0041 = arg0003[v0039][v0037];
      int v0042 = v0039 % (int)4;
      ap_int<1> v0043 = v0042 < (int)0;
      int v0044 = v0042 + (int)4;
      int v0045 = v0043 ? v0044 : v0042;
      ap_float<32, 8> v0046 = v0036[v0045];
      ap_float<32, 8> v0047 = (ap_float<32, 8>)v0040;
      ap_float<32, 8> v0048 = (ap_float<32, 8>)v0041;
      ap_float<32, 8> v0049 = v0047 * v0048;
      ap_float<32, 8> v0050 = v0046 + v0049;
      int v0051 = v0039 % (int)4;
      ap_int<1> v0052 = v0051 < (int)0;
      int v0053 = v0051 + (int)4;
      int v0054 = v0052 ? v0053 : v0051;
      v0036[v0054] = v0050;
    }
    ap_float<32, 8> v0055 = v0034[(int)0][(int)0][v0037];
    ap_float<32, 8> v0056 = v0036[(int)0];
    ap_float<32, 8> v0057 = v0036[(int)1];
    ap_float<32, 8> v0058 = v0036[(int)2];
    ap_float<32, 8> v0059 = v0036[(int)3];
    ap_float<32, 8> v0060 = v0056 + v0057;
    ap_float<32, 8> v0061 = v0058 + v0059;
    ap_float<32, 8> v0062 = v0060 + v0061;
    ap_float<32, 8> v0063 = v0062 + v0055;
    v0034[(int)0][(int)0][v0037] = v0063;
  }
  ap_float<16, 8> v0064[1][768];
  #pragma HLS bind_storage variable=v0064 type=ram_2p impl=bram latency=2
  for (int v0065 = (int)0; v0065 < (int)768; v0065 += (int)1) {
    ap_float<32, 8> v0066 = v0034[(int)0][(int)0][v0065];
    ap_float<16, 8> v0067 = (ap_float<16, 8>)v0066;
    v0064[(int)0][v0065] = v0067;
  }
  ap_float<16, 8> v0068[1][768];
  #pragma HLS bind_storage variable=v0068 type=ram_2p impl=bram latency=2
  for (int v0069 = (int)0; v0069 < (int)768; v0069 += (int)1) {
    ap_float<16, 8> v0070 = v0064[(int)0][v0069];
    ap_float<16, 8> v0071 = arg0004[v0069];
    ap_float<16, 8> v0072 = v0070 + v0071;
    v0068[(int)0][v0069] = v0072;
  }
  ap_float<16, 8> v0073[1][1][768];
  #pragma HLS bind_storage variable=v0073 type=ram_2p impl=bram latency=2
  for (int v0074 = (int)0; v0074 < (int)768; v0074 += (int)1) {
    ap_float<16, 8> v0075 = arg0000[(int)0][(int)0][v0074];
    ap_float<16, 8> v0076 = v0068[(int)0][v0074];
    ap_float<16, 8> v0077 = v0075 + v0076;
    v0073[(int)0][(int)0][v0074] = v0077;
  }
  for (int v0078 = (int)0; v0078 < (int)768; v0078 += (int)1) {
    ap_float<16, 8> v0079 = v0073[(int)0][(int)0][v0078];
    arg0002[(int)0][(int)0][v0078] = v0079;
  }
  return;
}

