
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

void kernel_0_chip1(ap_float<16, 8> arg0000[1][1][768], ap_float<32, 8> arg0001[1][1][768], ap_float<16, 8> arg0002[1][1][3072], ap_float<16, 8> arg0003[1][1][768], ap_float<16, 8> arg0004[768], ap_float<16, 8> arg0005[768], ap_float<16, 8> arg0006[768], ap_float<16, 8> arg0007[768][3072], ap_float<16, 8> arg0008[3072], volatile uint32_t timer[8], volatile uint32_t debug[256]) {
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
#pragma HLS interface m_axi port=arg0005 offset=slave bundle=gmem1
#pragma HLS interface s_axilite port=arg0005 bundle=control
#pragma HLS interface m_axi port=arg0006 offset=slave bundle=gmem1
#pragma HLS interface s_axilite port=arg0006 bundle=control
#pragma HLS interface m_axi port=arg0007 offset=slave bundle=gmem1
#pragma HLS interface s_axilite port=arg0007 bundle=control
#pragma HLS interface m_axi port=arg0008 offset=slave bundle=gmem1
#pragma HLS interface s_axilite port=arg0008 bundle=control
  timer[1] = 0x00000000;
  timer[0] = 0x129;
  timer[0] = (timer[0] & ~(1 << 5)) | (1 << 10);
  ap_float<16, 8> v0000[1][768];
  #pragma HLS bind_storage variable=v0000 type=ram_2p impl=bram latency=2
  for (int v0001 = (int)0; v0001 < (int)768; v0001 += (int)1) {
    ap_float<32, 8> v0002 = arg0001[(int)0][(int)0][v0001];
    ap_float<16, 8> v0003 = (ap_float<16, 8>)v0002;
    v0000[(int)0][v0001] = v0003;
  }
  ap_float<16, 8> v0004[1][768];
  #pragma HLS bind_storage variable=v0004 type=ram_2p impl=bram latency=2
  for (int v0005 = (int)0; v0005 < (int)768; v0005 += (int)1) {
    ap_float<16, 8> v0006 = v0000[(int)0][v0005];
    ap_float<16, 8> v0007 = arg0004[v0005];
    ap_float<16, 8> v0008 = v0006 + v0007;
    v0004[(int)0][v0005] = v0008;
  }
  ap_float<16, 8> v0009[1][1][768];
  #pragma HLS bind_storage variable=v0009 type=ram_2p impl=bram latency=2
  for (int v0010 = (int)0; v0010 < (int)768; v0010 += (int)1) {
    ap_float<16, 8> v0011 = v0004[(int)0][v0010];
    ap_float<16, 8> v0012 = arg0000[(int)0][(int)0][v0010];
    ap_float<16, 8> v0013 = v0011 + v0012;
    v0009[(int)0][(int)0][v0010] = v0013;
  }
  ap_float<32, 8> v0014[1][1];
  v0014[(int)0][(int)0] = (ap_float<32, 8>)0.000000;
  ap_float<32, 8> v0015[4];
  for (int v0016 = (int)0; v0016 < (int)4; v0016 += (int)1) {
    v0015[v0016] = (ap_float<32, 8>)0.000000;
  }
  for (int v0017 = (int)0; v0017 < (int)768; v0017 += (int)1) {
    ap_float<16, 8> v0018 = v0009[(int)0][(int)0][v0017];
    int v0019 = v0017 % (int)4;
    ap_int<1> v0020 = v0019 < (int)0;
    int v0021 = v0019 + (int)4;
    int v0022 = v0020 ? v0021 : v0019;
    ap_float<32, 8> v0023 = v0015[v0022];
    ap_float<32, 8> v0024 = (ap_float<32, 8>)v0018;
    ap_float<32, 8> v0025 = v0024 + v0023;
    int v0026 = v0017 % (int)4;
    ap_int<1> v0027 = v0026 < (int)0;
    int v0028 = v0026 + (int)4;
    int v0029 = v0027 ? v0028 : v0026;
    v0015[v0029] = v0025;
  }
  ap_float<32, 8> v0030 = v0014[(int)0][(int)0];
  ap_float<32, 8> v0031 = v0015[(int)0];
  ap_float<32, 8> v0032 = v0015[(int)1];
  ap_float<32, 8> v0033 = v0015[(int)2];
  ap_float<32, 8> v0034 = v0015[(int)3];
  ap_float<32, 8> v0035 = v0031 + v0032;
  ap_float<32, 8> v0036 = v0033 + v0034;
  ap_float<32, 8> v0037 = v0035 + v0036;
  ap_float<32, 8> v0038 = v0037 + v0030;
  v0014[(int)0][(int)0] = v0038;
  ap_float<16, 8> v0039[1][1];
  ap_float<32, 8> v0040 = v0014[(int)0][(int)0];
  ap_float<16, 8> v0041 = (ap_float<16, 8>)v0040;
  v0039[(int)0][(int)0] = v0041;
  ap_float<16, 8> v0042[1][1][1];
  ap_float<16, 8> v0043 = v0039[(int)0][(int)0];
  ap_float<16, 8> v0044 = v0043 * (ap_float<16, 8>)0.001305;
  v0042[(int)0][(int)0][(int)0] = v0044;
  ap_float<16, 8> v0045[1][1][1][1][768][1];
  #pragma HLS bind_storage variable=v0045 type=ram_2p impl=bram latency=2
  for (int v0046 = (int)0; v0046 < (int)768; v0046 += (int)1) {
    ap_float<16, 8> v0047 = v0042[(int)0][(int)0][(int)0];
    v0045[(int)0][(int)0][(int)0][(int)0][v0046][(int)0] = v0047;
  }
  ap_float<16, 8> v0048[1][1][768];
  #pragma HLS bind_storage variable=v0048 type=ram_2p impl=bram latency=2
  for (int v0049 = (int)0; v0049 < (int)768; v0049 += (int)1) {
    ap_float<16, 8> v0050 = v0009[(int)0][(int)0][v0049];
    ap_float<16, 8> v0051 = v0045[(int)0][(int)0][(int)0][(int)0][v0049][(int)0];
    ap_float<16, 8> v0052 = v0050 - v0051;
    v0048[(int)0][(int)0][v0049] = v0052;
  }
  ap_float<16, 8> v0053[1][1][768];
  #pragma HLS bind_storage variable=v0053 type=ram_2p impl=bram latency=2
  for (int v0054 = (int)0; v0054 < (int)768; v0054 += (int)1) {
    ap_float<16, 8> v0055 = v0048[(int)0][(int)0][v0054];
    ap_float<16, 8> v0056 = v0048[(int)0][(int)0][v0054];
    ap_float<16, 8> v0057 = v0055 * v0056;
    v0053[(int)0][(int)0][v0054] = v0057;
  }
  ap_float<32, 8> v0058[1][1];
  v0058[(int)0][(int)0] = (ap_float<32, 8>)0.000000;
  ap_float<32, 8> v0059[4];
  for (int v0060 = (int)0; v0060 < (int)4; v0060 += (int)1) {
    v0059[v0060] = (ap_float<32, 8>)0.000000;
  }
  for (int v0061 = (int)0; v0061 < (int)768; v0061 += (int)1) {
    ap_float<16, 8> v0062 = v0053[(int)0][(int)0][v0061];
    int v0063 = v0061 % (int)4;
    ap_int<1> v0064 = v0063 < (int)0;
    int v0065 = v0063 + (int)4;
    int v0066 = v0064 ? v0065 : v0063;
    ap_float<32, 8> v0067 = v0059[v0066];
    ap_float<32, 8> v0068 = (ap_float<32, 8>)v0062;
    ap_float<32, 8> v0069 = v0068 + v0067;
    int v0070 = v0061 % (int)4;
    ap_int<1> v0071 = v0070 < (int)0;
    int v0072 = v0070 + (int)4;
    int v0073 = v0071 ? v0072 : v0070;
    v0059[v0073] = v0069;
  }
  ap_float<32, 8> v0074 = v0058[(int)0][(int)0];
  ap_float<32, 8> v0075 = v0059[(int)0];
  ap_float<32, 8> v0076 = v0059[(int)1];
  ap_float<32, 8> v0077 = v0059[(int)2];
  ap_float<32, 8> v0078 = v0059[(int)3];
  ap_float<32, 8> v0079 = v0075 + v0076;
  ap_float<32, 8> v0080 = v0077 + v0078;
  ap_float<32, 8> v0081 = v0079 + v0080;
  ap_float<32, 8> v0082 = v0081 + v0074;
  v0058[(int)0][(int)0] = v0082;
  ap_float<16, 8> v0083[1][1];
  ap_float<32, 8> v0084 = v0058[(int)0][(int)0];
  ap_float<16, 8> v0085 = (ap_float<16, 8>)v0084;
  v0083[(int)0][(int)0] = v0085;
  ap_float<16, 8> v0086[1][1][1];
  ap_float<16, 8> v0087 = v0083[(int)0][(int)0];
  ap_float<16, 8> v0088 = v0087 * (ap_float<16, 8>)0.001305;
  v0086[(int)0][(int)0][(int)0] = v0088;
  ap_float<16, 8> v0089[1][1][1];
  ap_float<16, 8> v0090 = v0086[(int)0][(int)0][(int)0];
  ap_float<16, 8> v0091 = v0090 + (ap_float<16, 8>)0.000010;
  v0089[(int)0][(int)0][(int)0] = v0091;
  ap_float<16, 8> v0092[1][1][1];
  ap_float<16, 8> v0093 = v0089[(int)0][(int)0][(int)0];
  ap_float<16, 8> v0094 = hls::rsqrt((float)v0093);
  v0092[(int)0][(int)0][(int)0] = v0094;
  ap_float<16, 8> v0095[1][1][1][1][768][1];
  #pragma HLS bind_storage variable=v0095 type=ram_2p impl=bram latency=2
  for (int v0096 = (int)0; v0096 < (int)768; v0096 += (int)1) {
    ap_float<16, 8> v0097 = v0092[(int)0][(int)0][(int)0];
    v0095[(int)0][(int)0][(int)0][(int)0][v0096][(int)0] = v0097;
  }
  ap_float<16, 8> v0098[1][1][768];
  #pragma HLS bind_storage variable=v0098 type=ram_2p impl=bram latency=2
  for (int v0099 = (int)0; v0099 < (int)768; v0099 += (int)1) {
    ap_float<16, 8> v0100 = v0048[(int)0][(int)0][v0099];
    ap_float<16, 8> v0101 = v0095[(int)0][(int)0][(int)0][(int)0][v0099][(int)0];
    ap_float<16, 8> v0102 = v0100 * v0101;
    v0098[(int)0][(int)0][v0099] = v0102;
  }
  ap_float<16, 8> v0103[1][1][768];
  #pragma HLS bind_storage variable=v0103 type=ram_2p impl=bram latency=2
  for (int v0104 = (int)0; v0104 < (int)768; v0104 += (int)1) {
    ap_float<16, 8> v0105 = v0098[(int)0][(int)0][v0104];
    ap_float<16, 8> v0106 = arg0005[v0104];
    ap_float<16, 8> v0107 = v0105 * v0106;
    v0103[(int)0][(int)0][v0104] = v0107;
  }
  ap_float<16, 8> v0108[1][1][768];
  #pragma HLS bind_storage variable=v0108 type=ram_2p impl=bram latency=2
  for (int v0109 = (int)0; v0109 < (int)768; v0109 += (int)1) {
    ap_float<16, 8> v0110 = v0103[(int)0][(int)0][v0109];
    ap_float<16, 8> v0111 = arg0006[v0109];
    ap_float<16, 8> v0112 = v0110 + v0111;
    v0108[(int)0][(int)0][v0109] = v0112;
  }
  ap_float<32, 8> v0113[1][1][3072];
  #pragma HLS bind_storage variable=v0113 type=ram_2p impl=bram latency=2
  for (int v0114 = (int)0; v0114 < (int)3072; v0114 += (int)1) {
    v0113[(int)0][(int)0][v0114] = (ap_float<32, 8>)0.000000;
  }
  ap_float<32, 8> v0115[4];
  for (int v0116 = (int)0; v0116 < (int)3072; v0116 += (int)1) {
    for (int v0117 = (int)0; v0117 < (int)4; v0117 += (int)1) {
      v0115[v0117] = (ap_float<32, 8>)0.000000;
    }
    for (int v0118 = (int)0; v0118 < (int)768; v0118 += (int)1) {
      ap_float<16, 8> v0119 = v0108[(int)0][(int)0][v0118];
      ap_float<16, 8> v0120 = arg0007[v0118][v0116];
      int v0121 = v0118 % (int)4;
      ap_int<1> v0122 = v0121 < (int)0;
      int v0123 = v0121 + (int)4;
      int v0124 = v0122 ? v0123 : v0121;
      ap_float<32, 8> v0125 = v0115[v0124];
      ap_float<32, 8> v0126 = (ap_float<32, 8>)v0119;
      ap_float<32, 8> v0127 = (ap_float<32, 8>)v0120;
      ap_float<32, 8> v0128 = v0126 * v0127;
      ap_float<32, 8> v0129 = v0125 + v0128;
      int v0130 = v0118 % (int)4;
      ap_int<1> v0131 = v0130 < (int)0;
      int v0132 = v0130 + (int)4;
      int v0133 = v0131 ? v0132 : v0130;
      v0115[v0133] = v0129;
    }
    ap_float<32, 8> v0134 = v0113[(int)0][(int)0][v0116];
    ap_float<32, 8> v0135 = v0115[(int)0];
    ap_float<32, 8> v0136 = v0115[(int)1];
    ap_float<32, 8> v0137 = v0115[(int)2];
    ap_float<32, 8> v0138 = v0115[(int)3];
    ap_float<32, 8> v0139 = v0135 + v0136;
    ap_float<32, 8> v0140 = v0137 + v0138;
    ap_float<32, 8> v0141 = v0139 + v0140;
    ap_float<32, 8> v0142 = v0141 + v0134;
    v0113[(int)0][(int)0][v0116] = v0142;
  }
  ap_float<16, 8> v0143[1][3072];
  #pragma HLS bind_storage variable=v0143 type=ram_2p impl=bram latency=2
  for (int v0144 = (int)0; v0144 < (int)3072; v0144 += (int)1) {
    ap_float<32, 8> v0145 = v0113[(int)0][(int)0][v0144];
    ap_float<16, 8> v0146 = (ap_float<16, 8>)v0145;
    v0143[(int)0][v0144] = v0146;
  }
  ap_float<16, 8> v0147[1][3072];
  #pragma HLS bind_storage variable=v0147 type=ram_2p impl=bram latency=2
  for (int v0148 = (int)0; v0148 < (int)3072; v0148 += (int)1) {
    ap_float<16, 8> v0149 = v0143[(int)0][v0148];
    ap_float<16, 8> v0150 = arg0008[v0148];
    ap_float<16, 8> v0151 = v0149 + v0150;
    v0147[(int)0][v0148] = v0151;
  }
  for (int v0152 = (int)0; v0152 < (int)3072; v0152 += (int)1) {
    ap_float<16, 8> v0153 = v0147[(int)0][v0152];
    arg0002[(int)0][(int)0][v0152] = v0153;
  }
  for (int v0154 = (int)0; v0154 < (int)768; v0154 += (int)1) {
    ap_float<16, 8> v0155 = v0009[(int)0][(int)0][v0154];
    arg0003[(int)0][(int)0][v0154] = v0155;
  }
  return;
}

