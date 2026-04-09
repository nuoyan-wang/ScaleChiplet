
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

void kernel_0(ap_int<1> arg0000[1][1][1024][1024], ap_float<16, 8> arg0001[1], ap_int<1> arg0002[1][1][1024][1024], ap_float<16, 8> arg0003[1], ap_int<1> arg0004[1][1][1024][1024], ap_float<16, 8> arg0005[1], ap_int<1> arg0006[1][1][1024][1024], ap_float<16, 8> arg0007[1], ap_int<1> arg0008[1][1][1024][1024], ap_float<16, 8> arg0009[1], ap_int<1> arg0010[1][1][1024][1024], ap_float<16, 8> arg0011[1], ap_int<1> arg0012[1][1][1024][1024], ap_float<16, 8> arg0013[1], ap_int<1> arg0014[1][1][1024][1024], ap_float<16, 8> arg0015[1], ap_int<1> arg0016[1][1][1024][1024], ap_float<16, 8> arg0017[1], ap_int<1> arg0018[1][1][1024][1024], ap_float<16, 8> arg0019[1], ap_int<1> arg0020[1][1][1024][1024], ap_float<16, 8> arg0021[1], ap_int<1> arg0022[1][1][1024][1024], ap_float<16, 8> arg0023[1], ap_float<16, 8> arg0024[1][1][768], ap_int<32> arg0025[1], ap_float<16, 8> arg0026[1][1][1][128], ap_float<16, 8> arg0027[1][12][128][64], ap_float<16, 8> arg0028[1][12][128][64], ap_float<16, 8> arg0029[1][1][768], ap_float<16, 8> arg0030[1][12][128][64], ap_float<16, 8> arg0031[1][12][128][64], ap_float<16, 8> arg0032[768], ap_float<16, 8> arg0033[3072][768], ap_float<16, 8> arg0034[3072], ap_float<16, 8> arg0035[768][3072], ap_float<16, 8> arg0036[768], ap_float<16, 8> arg0037[768], ap_float<16, 8> arg0038[768], ap_float<16, 8> arg0039[768][768], ap_float<16, 8> arg0040[2304], ap_float<16, 8> arg0041[768][2304], ap_float<16, 8> arg0042[768], ap_float<16, 8> arg0043[768], volatile uint32_t timer[8], volatile uint32_t debug[256]) {
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
#pragma HLS interface m_axi port=arg0009 offset=slave bundle=gmem1
#pragma HLS interface s_axilite port=arg0009 bundle=control
#pragma HLS interface m_axi port=arg0010 offset=slave bundle=gmem1
#pragma HLS interface s_axilite port=arg0010 bundle=control
#pragma HLS interface m_axi port=arg0011 offset=slave bundle=gmem1
#pragma HLS interface s_axilite port=arg0011 bundle=control
#pragma HLS interface m_axi port=arg0012 offset=slave bundle=gmem1
#pragma HLS interface s_axilite port=arg0012 bundle=control
#pragma HLS interface m_axi port=arg0013 offset=slave bundle=gmem1
#pragma HLS interface s_axilite port=arg0013 bundle=control
#pragma HLS interface m_axi port=arg0014 offset=slave bundle=gmem1
#pragma HLS interface s_axilite port=arg0014 bundle=control
#pragma HLS interface m_axi port=arg0015 offset=slave bundle=gmem1
#pragma HLS interface s_axilite port=arg0015 bundle=control
#pragma HLS interface m_axi port=arg0016 offset=slave bundle=gmem1
#pragma HLS interface s_axilite port=arg0016 bundle=control
#pragma HLS interface m_axi port=arg0017 offset=slave bundle=gmem1
#pragma HLS interface s_axilite port=arg0017 bundle=control
#pragma HLS interface m_axi port=arg0018 offset=slave bundle=gmem1
#pragma HLS interface s_axilite port=arg0018 bundle=control
#pragma HLS interface m_axi port=arg0019 offset=slave bundle=gmem1
#pragma HLS interface s_axilite port=arg0019 bundle=control
#pragma HLS interface m_axi port=arg0020 offset=slave bundle=gmem1
#pragma HLS interface s_axilite port=arg0020 bundle=control
#pragma HLS interface m_axi port=arg0021 offset=slave bundle=gmem1
#pragma HLS interface s_axilite port=arg0021 bundle=control
#pragma HLS interface m_axi port=arg0022 offset=slave bundle=gmem1
#pragma HLS interface s_axilite port=arg0022 bundle=control
#pragma HLS interface m_axi port=arg0023 offset=slave bundle=gmem1
#pragma HLS interface s_axilite port=arg0023 bundle=control
#pragma HLS interface m_axi port=arg0024 offset=slave bundle=gmem1
#pragma HLS interface s_axilite port=arg0024 bundle=control
#pragma HLS interface m_axi port=arg0025 offset=slave bundle=gmem1
#pragma HLS interface s_axilite port=arg0025 bundle=control
#pragma HLS interface m_axi port=arg0026 offset=slave bundle=gmem1
#pragma HLS interface s_axilite port=arg0026 bundle=control
#pragma HLS interface m_axi port=arg0027 offset=slave bundle=gmem1
#pragma HLS interface s_axilite port=arg0027 bundle=control
#pragma HLS interface m_axi port=arg0028 offset=slave bundle=gmem1
#pragma HLS interface s_axilite port=arg0028 bundle=control
#pragma HLS interface m_axi port=arg0029 offset=slave bundle=gmem1
#pragma HLS interface s_axilite port=arg0029 bundle=control
#pragma HLS interface m_axi port=arg0030 offset=slave bundle=gmem1
#pragma HLS interface s_axilite port=arg0030 bundle=control
#pragma HLS interface m_axi port=arg0031 offset=slave bundle=gmem1
#pragma HLS interface s_axilite port=arg0031 bundle=control
#pragma HLS interface m_axi port=arg0032 offset=slave bundle=gmem1
#pragma HLS interface s_axilite port=arg0032 bundle=control
#pragma HLS interface m_axi port=arg0033 offset=slave bundle=gmem1
#pragma HLS interface s_axilite port=arg0033 bundle=control
#pragma HLS interface m_axi port=arg0034 offset=slave bundle=gmem1
#pragma HLS interface s_axilite port=arg0034 bundle=control
#pragma HLS interface m_axi port=arg0035 offset=slave bundle=gmem1
#pragma HLS interface s_axilite port=arg0035 bundle=control
#pragma HLS interface m_axi port=arg0036 offset=slave bundle=gmem1
#pragma HLS interface s_axilite port=arg0036 bundle=control
#pragma HLS interface m_axi port=arg0037 offset=slave bundle=gmem1
#pragma HLS interface s_axilite port=arg0037 bundle=control
#pragma HLS interface m_axi port=arg0038 offset=slave bundle=gmem1
#pragma HLS interface s_axilite port=arg0038 bundle=control
#pragma HLS interface m_axi port=arg0039 offset=slave bundle=gmem1
#pragma HLS interface s_axilite port=arg0039 bundle=control
#pragma HLS interface m_axi port=arg0040 offset=slave bundle=gmem1
#pragma HLS interface s_axilite port=arg0040 bundle=control
#pragma HLS interface m_axi port=arg0041 offset=slave bundle=gmem1
#pragma HLS interface s_axilite port=arg0041 bundle=control
#pragma HLS interface m_axi port=arg0042 offset=slave bundle=gmem1
#pragma HLS interface s_axilite port=arg0042 bundle=control
#pragma HLS interface m_axi port=arg0043 offset=slave bundle=gmem1
#pragma HLS interface s_axilite port=arg0043 bundle=control
  timer[1] = 0x00000000;
  timer[0] = 0x129;
  timer[0] = (timer[0] & ~(1 << 5)) | (1 << 10);
  ap_int<64> v0000[1][1][128][1] = {{{{0}, {1}, {2}, {3}, {4}, {5}, {6}, {7}, {8}, {9}, {10}, {11}, {12}, {13}, {14}, {15}, {16}, {17}, {18}, {19}, {20}, {21}, {22}, {23}, {24}, {25}, {26}, {27}, {28}, {29}, {30}, {31}, {32}, {33}, {34}, {35}, {36}, {37}, {38}, {39}, {40}, {41}, {42}, {43}, {44}, {45}, {46}, {47}, {48}, {49}, {50}, {51}, {52}, {53}, {54}, {55}, {56}, {57}, {58}, {59}, {60}, {61}, {62}, {63}, {64}, {65}, {66}, {67}, {68}, {69}, {70}, {71}, {72}, {73}, {74}, {75}, {76}, {77}, {78}, {79}, {80}, {81}, {82}, {83}, {84}, {85}, {86}, {87}, {88}, {89}, {90}, {91}, {92}, {93}, {94}, {95}, {96}, {97}, {98}, {99}, {100}, {101}, {102}, {103}, {104}, {105}, {106}, {107}, {108}, {109}, {110}, {111}, {112}, {113}, {114}, {115}, {116}, {117}, {118}, {119}, {120}, {121}, {122}, {123}, {124}, {125}, {126}, {127}}}};
  ap_float<32, 8> v0001[1][1];
  v0001[(int)0][(int)0] = (ap_float<32, 8>)0.000000;
  ap_float<32, 8> v0002[4];
  for (int v0003 = (int)0; v0003 < (int)4; v0003 += (int)1) {
    v0002[v0003] = (ap_float<32, 8>)0.000000;
  }
  for (int v0004 = (int)0; v0004 < (int)768; v0004 += (int)1) {
    ap_float<16, 8> v0005 = arg0024[(int)0][(int)0][v0004];
    int v0006 = v0004 % (int)4;
    ap_int<1> v0007 = v0006 < (int)0;
    int v0008 = v0006 + (int)4;
    int v0009 = v0007 ? v0008 : v0006;
    ap_float<32, 8> v0010 = v0002[v0009];
    ap_float<32, 8> v0011 = (ap_float<32, 8>)v0005;
    ap_float<32, 8> v0012 = v0011 + v0010;
    int v0013 = v0004 % (int)4;
    ap_int<1> v0014 = v0013 < (int)0;
    int v0015 = v0013 + (int)4;
    int v0016 = v0014 ? v0015 : v0013;
    v0002[v0016] = v0012;
  }
  ap_float<32, 8> v0017 = v0001[(int)0][(int)0];
  ap_float<32, 8> v0018 = v0002[(int)0];
  ap_float<32, 8> v0019 = v0002[(int)1];
  ap_float<32, 8> v0020 = v0002[(int)2];
  ap_float<32, 8> v0021 = v0002[(int)3];
  ap_float<32, 8> v0022 = v0018 + v0019;
  ap_float<32, 8> v0023 = v0020 + v0021;
  ap_float<32, 8> v0024 = v0022 + v0023;
  ap_float<32, 8> v0025 = v0024 + v0017;
  v0001[(int)0][(int)0] = v0025;
  ap_float<16, 8> v0026[1][1];
  ap_float<32, 8> v0027 = v0001[(int)0][(int)0];
  ap_float<16, 8> v0028 = (ap_float<16, 8>)v0027;
  v0026[(int)0][(int)0] = v0028;
  ap_float<16, 8> v0029[1][1][1];
  ap_float<16, 8> v0030 = v0026[(int)0][(int)0];
  ap_float<16, 8> v0031 = v0030 * (ap_float<16, 8>)0.001305;
  v0029[(int)0][(int)0][(int)0] = v0031;
  ap_float<16, 8> v0032[1][1][1][1][768][1];
  #pragma HLS bind_storage variable=v0032 type=ram_2p impl=bram latency=2
  for (int v0033 = (int)0; v0033 < (int)768; v0033 += (int)1) {
    ap_float<16, 8> v0034 = v0029[(int)0][(int)0][(int)0];
    v0032[(int)0][(int)0][(int)0][(int)0][v0033][(int)0] = v0034;
  }
  ap_float<16, 8> v0035[1][1][768];
  #pragma HLS bind_storage variable=v0035 type=ram_2p impl=bram latency=2
  for (int v0036 = (int)0; v0036 < (int)768; v0036 += (int)1) {
    ap_float<16, 8> v0037 = arg0024[(int)0][(int)0][v0036];
    ap_float<16, 8> v0038 = v0032[(int)0][(int)0][(int)0][(int)0][v0036][(int)0];
    ap_float<16, 8> v0039 = v0037 - v0038;
    v0035[(int)0][(int)0][v0036] = v0039;
  }
  ap_float<16, 8> v0040[1][1][768];
  #pragma HLS bind_storage variable=v0040 type=ram_2p impl=bram latency=2
  for (int v0041 = (int)0; v0041 < (int)768; v0041 += (int)1) {
    ap_float<16, 8> v0042 = v0035[(int)0][(int)0][v0041];
    ap_float<16, 8> v0043 = v0035[(int)0][(int)0][v0041];
    ap_float<16, 8> v0044 = v0042 * v0043;
    v0040[(int)0][(int)0][v0041] = v0044;
  }
  ap_float<32, 8> v0045[1][1];
  v0045[(int)0][(int)0] = (ap_float<32, 8>)0.000000;
  ap_float<32, 8> v0046[4];
  for (int v0047 = (int)0; v0047 < (int)4; v0047 += (int)1) {
    v0046[v0047] = (ap_float<32, 8>)0.000000;
  }
  for (int v0048 = (int)0; v0048 < (int)768; v0048 += (int)1) {
    ap_float<16, 8> v0049 = v0040[(int)0][(int)0][v0048];
    int v0050 = v0048 % (int)4;
    ap_int<1> v0051 = v0050 < (int)0;
    int v0052 = v0050 + (int)4;
    int v0053 = v0051 ? v0052 : v0050;
    ap_float<32, 8> v0054 = v0046[v0053];
    ap_float<32, 8> v0055 = (ap_float<32, 8>)v0049;
    ap_float<32, 8> v0056 = v0055 + v0054;
    int v0057 = v0048 % (int)4;
    ap_int<1> v0058 = v0057 < (int)0;
    int v0059 = v0057 + (int)4;
    int v0060 = v0058 ? v0059 : v0057;
    v0046[v0060] = v0056;
  }
  ap_float<32, 8> v0061 = v0045[(int)0][(int)0];
  ap_float<32, 8> v0062 = v0046[(int)0];
  ap_float<32, 8> v0063 = v0046[(int)1];
  ap_float<32, 8> v0064 = v0046[(int)2];
  ap_float<32, 8> v0065 = v0046[(int)3];
  ap_float<32, 8> v0066 = v0062 + v0063;
  ap_float<32, 8> v0067 = v0064 + v0065;
  ap_float<32, 8> v0068 = v0066 + v0067;
  ap_float<32, 8> v0069 = v0068 + v0061;
  v0045[(int)0][(int)0] = v0069;
  ap_float<16, 8> v0070[1][1];
  ap_float<32, 8> v0071 = v0045[(int)0][(int)0];
  ap_float<16, 8> v0072 = (ap_float<16, 8>)v0071;
  v0070[(int)0][(int)0] = v0072;
  ap_float<16, 8> v0073[1][1][1];
  ap_float<16, 8> v0074 = v0070[(int)0][(int)0];
  ap_float<16, 8> v0075 = v0074 * (ap_float<16, 8>)0.001305;
  v0073[(int)0][(int)0][(int)0] = v0075;
  ap_float<16, 8> v0076[1][1][1];
  ap_float<16, 8> v0077 = v0073[(int)0][(int)0][(int)0];
  ap_float<16, 8> v0078 = v0077 + (ap_float<16, 8>)0.000010;
  v0076[(int)0][(int)0][(int)0] = v0078;
  ap_float<16, 8> v0079[1][1][1];
  ap_float<16, 8> v0080 = v0076[(int)0][(int)0][(int)0];
  ap_float<16, 8> v0081 = hls::rsqrt((float)v0080);
  v0079[(int)0][(int)0][(int)0] = v0081;
  ap_float<16, 8> v0082[1][1][1][1][768][1];
  #pragma HLS bind_storage variable=v0082 type=ram_2p impl=bram latency=2
  for (int v0083 = (int)0; v0083 < (int)768; v0083 += (int)1) {
    ap_float<16, 8> v0084 = v0079[(int)0][(int)0][(int)0];
    v0082[(int)0][(int)0][(int)0][(int)0][v0083][(int)0] = v0084;
  }
  ap_float<16, 8> v0085[1][1][768];
  #pragma HLS bind_storage variable=v0085 type=ram_2p impl=bram latency=2
  for (int v0086 = (int)0; v0086 < (int)768; v0086 += (int)1) {
    ap_float<16, 8> v0087 = v0035[(int)0][(int)0][v0086];
    ap_float<16, 8> v0088 = v0082[(int)0][(int)0][(int)0][(int)0][v0086][(int)0];
    ap_float<16, 8> v0089 = v0087 * v0088;
    v0085[(int)0][(int)0][v0086] = v0089;
  }
  ap_float<16, 8> v0090[1][1][768];
  #pragma HLS bind_storage variable=v0090 type=ram_2p impl=bram latency=2
  for (int v0091 = (int)0; v0091 < (int)768; v0091 += (int)1) {
    ap_float<16, 8> v0092 = v0085[(int)0][(int)0][v0091];
    ap_float<16, 8> v0093 = arg0043[v0091];
    ap_float<16, 8> v0094 = v0092 * v0093;
    v0090[(int)0][(int)0][v0091] = v0094;
  }
  ap_float<16, 8> v0095[1][1][768];
  #pragma HLS bind_storage variable=v0095 type=ram_2p impl=bram latency=2
  for (int v0096 = (int)0; v0096 < (int)768; v0096 += (int)1) {
    ap_float<16, 8> v0097 = v0090[(int)0][(int)0][v0096];
    ap_float<16, 8> v0098 = arg0042[v0096];
    ap_float<16, 8> v0099 = v0097 + v0098;
    v0095[(int)0][(int)0][v0096] = v0099;
  }
  ap_float<32, 8> v0100[1][1][2304];
  #pragma HLS bind_storage variable=v0100 type=ram_2p impl=bram latency=2
  for (int v0101 = (int)0; v0101 < (int)2304; v0101 += (int)1) {
    v0100[(int)0][(int)0][v0101] = (ap_float<32, 8>)0.000000;
  }
  ap_float<32, 8> v0102[4];
  for (int v0103 = (int)0; v0103 < (int)2304; v0103 += (int)1) {
    for (int v0104 = (int)0; v0104 < (int)4; v0104 += (int)1) {
      v0102[v0104] = (ap_float<32, 8>)0.000000;
    }
    for (int v0105 = (int)0; v0105 < (int)768; v0105 += (int)1) {
      ap_float<16, 8> v0106 = v0095[(int)0][(int)0][v0105];
      ap_float<16, 8> v0107 = arg0041[v0105][v0103];
      int v0108 = v0105 % (int)4;
      ap_int<1> v0109 = v0108 < (int)0;
      int v0110 = v0108 + (int)4;
      int v0111 = v0109 ? v0110 : v0108;
      ap_float<32, 8> v0112 = v0102[v0111];
      ap_float<32, 8> v0113 = (ap_float<32, 8>)v0106;
      ap_float<32, 8> v0114 = (ap_float<32, 8>)v0107;
      ap_float<32, 8> v0115 = v0113 * v0114;
      ap_float<32, 8> v0116 = v0112 + v0115;
      int v0117 = v0105 % (int)4;
      ap_int<1> v0118 = v0117 < (int)0;
      int v0119 = v0117 + (int)4;
      int v0120 = v0118 ? v0119 : v0117;
      v0102[v0120] = v0116;
    }
    ap_float<32, 8> v0121 = v0100[(int)0][(int)0][v0103];
    ap_float<32, 8> v0122 = v0102[(int)0];
    ap_float<32, 8> v0123 = v0102[(int)1];
    ap_float<32, 8> v0124 = v0102[(int)2];
    ap_float<32, 8> v0125 = v0102[(int)3];
    ap_float<32, 8> v0126 = v0122 + v0123;
    ap_float<32, 8> v0127 = v0124 + v0125;
    ap_float<32, 8> v0128 = v0126 + v0127;
    ap_float<32, 8> v0129 = v0128 + v0121;
    v0100[(int)0][(int)0][v0103] = v0129;
  }
  ap_float<16, 8> v0130[1][2304];
  #pragma HLS bind_storage variable=v0130 type=ram_2p impl=bram latency=2
  for (int v0131 = (int)0; v0131 < (int)2304; v0131 += (int)1) {
    ap_float<32, 8> v0132 = v0100[(int)0][(int)0][v0131];
    ap_float<16, 8> v0133 = (ap_float<16, 8>)v0132;
    v0130[(int)0][v0131] = v0133;
  }
  ap_float<16, 8> v0134[1][2304];
  #pragma HLS bind_storage variable=v0134 type=ram_2p impl=bram latency=2
  for (int v0135 = (int)0; v0135 < (int)2304; v0135 += (int)1) {
    ap_float<16, 8> v0136 = v0130[(int)0][v0135];
    ap_float<16, 8> v0137 = arg0040[v0135];
    ap_float<16, 8> v0138 = v0136 + v0137;
    v0134[(int)0][v0135] = v0138;
  }
  ap_int<64> v0139[1][1][1][1];
  ap_int<32> v0140 = arg0025[(int)0];
  ap_int<64> v0141 = (ap_int<64>)v0140;
  v0139[(int)0][(int)0][(int)0][(int)0] = v0141;
  ap_int<1> v0142[1][1][128][1];
  #pragma HLS bind_storage variable=v0142 type=ram_2p impl=bram latency=2
  for (int v0143 = (int)0; v0143 < (int)128; v0143 += (int)1) {
    ap_int<64> v0144 = v0139[(int)0][(int)0][(int)0][(int)0];
    ap_int<64> v0145 = v0000[(int)0][(int)0][v0143][(int)0];
    ap_int<1> v0146 = v0144 == v0145;
    v0142[(int)0][(int)0][v0143][(int)0] = v0146;
  }
  ap_float<16, 8> v0147[1][1][1][12][128][1][1][64];
  #pragma HLS bind_storage variable=v0147 type=ram_2p impl=bram latency=2
  for (int v0148 = (int)0; v0148 < (int)12; v0148 += (int)1) {
    for (int v0149 = (int)0; v0149 < (int)128; v0149 += (int)1) {
      for (int v0150 = (int)0; v0150 < (int)64; v0150 += (int)1) {
        int v0151 = v0148 * (int)64;
        int v0152 = v0151 + v0150;
        int v0153 = v0152 + (int)768;
        ap_float<16, 8> v0154 = v0134[(int)0][v0153];
        v0147[(int)0][(int)0][(int)0][v0148][v0149][(int)0][(int)0][v0150] = v0154;
      }
    }
  }
  ap_float<16, 8> v0155[1][1][1][12][128][1][1][64];
  #pragma HLS bind_storage variable=v0155 type=ram_2p impl=bram latency=2
  for (int v0156 = (int)0; v0156 < (int)12; v0156 += (int)1) {
    for (int v0157 = (int)0; v0157 < (int)128; v0157 += (int)1) {
      for (int v0158 = (int)0; v0158 < (int)64; v0158 += (int)1) {
        int v0159 = v0156 * (int)64;
        int v0160 = v0159 + v0158;
        int v0161 = v0160 + (int)1536;
        ap_float<16, 8> v0162 = v0134[(int)0][v0161];
        v0155[(int)0][(int)0][(int)0][v0156][v0157][(int)0][(int)0][v0158] = v0162;
      }
    }
  }
  ap_float<16, 8> v0163[1][12][128][64];
  #pragma HLS bind_storage variable=v0163 type=ram_2p impl=bram latency=2
  for (int v0164 = (int)0; v0164 < (int)12; v0164 += (int)1) {
    for (int v0165 = (int)0; v0165 < (int)128; v0165 += (int)1) {
      for (int v0166 = (int)0; v0166 < (int)64; v0166 += (int)1) {
        ap_int<1> v0167 = v0142[(int)0][(int)0][v0165][(int)0];
        ap_float<16, 8> v0168 = v0147[(int)0][(int)0][(int)0][v0164][v0165][(int)0][(int)0][v0166];
        ap_float<16, 8> v0169 = arg0027[(int)0][v0164][v0165][v0166];
        ap_float<16, 8> v0170 = v0167 ? v0168 : v0169;
        v0163[(int)0][v0164][v0165][v0166] = v0170;
      }
    }
  }
  ap_float<16, 8> v0171[1][12][128][64];
  #pragma HLS bind_storage variable=v0171 type=ram_2p impl=bram latency=2
  for (int v0172 = (int)0; v0172 < (int)12; v0172 += (int)1) {
    for (int v0173 = (int)0; v0173 < (int)128; v0173 += (int)1) {
      for (int v0174 = (int)0; v0174 < (int)64; v0174 += (int)1) {
        ap_int<1> v0175 = v0142[(int)0][(int)0][v0173][(int)0];
        ap_float<16, 8> v0176 = v0155[(int)0][(int)0][(int)0][v0172][v0173][(int)0][(int)0][v0174];
        ap_float<16, 8> v0177 = arg0028[(int)0][v0172][v0173][v0174];
        ap_float<16, 8> v0178 = v0175 ? v0176 : v0177;
        v0171[(int)0][v0172][v0173][v0174] = v0178;
      }
    }
  }
  ap_float<16, 8> v0179[1][12][64][128];
  #pragma HLS bind_storage variable=v0179 type=ram_2p impl=bram latency=2
  for (int v0180 = (int)0; v0180 < (int)12; v0180 += (int)1) {
    for (int v0181 = (int)0; v0181 < (int)64; v0181 += (int)1) {
      for (int v0182 = (int)0; v0182 < (int)128; v0182 += (int)1) {
        ap_float<16, 8> v0183 = v0163[(int)0][v0180][v0182][v0181];
        v0179[(int)0][v0180][v0181][v0182] = v0183;
      }
    }
  }
  ap_float<32, 8> v0184[12][1][128];
  #pragma HLS bind_storage variable=v0184 type=ram_2p impl=bram latency=2
  for (int v0185 = (int)0; v0185 < (int)12; v0185 += (int)1) {
    for (int v0186 = (int)0; v0186 < (int)128; v0186 += (int)1) {
      v0184[v0185][(int)0][v0186] = (ap_float<32, 8>)0.000000;
    }
  }
  ap_float<32, 8> v0187[4];
  for (int v0188 = (int)0; v0188 < (int)12; v0188 += (int)1) {
    for (int v0189 = (int)0; v0189 < (int)128; v0189 += (int)1) {
      for (int v0190 = (int)0; v0190 < (int)4; v0190 += (int)1) {
        v0187[v0190] = (ap_float<32, 8>)0.000000;
      }
      for (int v0191 = (int)0; v0191 < (int)64; v0191 += (int)1) {
        int v0192 = v0188 * (int)64;
        int v0193 = v0192 + v0191;
        int v0194 = v0193 / (int)768;
        int v0195 = v0194 * (int)768;
        ap_int<1> v0196 = v0193 != v0195;
        ap_int<1> v0197 = v0193 < (int)0;
        ap_int<1> v0198 = v0196 & v0197;
        int v0199 = v0194 + (int)-1;
        int v0200 = v0198 ? v0199 : v0194;
        int v0201 = v0193 % (int)768;
        ap_int<1> v0202 = v0201 < (int)0;
        int v0203 = v0201 + (int)768;
        int v0204 = v0202 ? v0203 : v0201;
        int v0205 = v0204 / (int)768;
        int v0206 = v0193 % (int)768;
        ap_int<1> v0207 = v0206 < (int)0;
        int v0208 = v0206 + (int)768;
        int v0209 = v0207 ? v0208 : v0206;
        int v0210 = v0200 + v0205;
        ap_float<16, 8> v0211 = v0134[v0210][v0209];
        int v0212 = v0188 / (int)12;
        int v0213 = v0212 * (int)12;
        ap_int<1> v0214 = v0188 != v0213;
        ap_int<1> v0215 = v0188 < (int)0;
        ap_int<1> v0216 = v0214 & v0215;
        int v0217 = v0212 + (int)-1;
        int v0218 = v0216 ? v0217 : v0212;
        int v0219 = v0188 % (int)12;
        ap_int<1> v0220 = v0219 < (int)0;
        int v0221 = v0219 + (int)12;
        int v0222 = v0220 ? v0221 : v0219;
        ap_float<16, 8> v0223 = v0179[v0218][v0222][v0191][v0189];
        int v0224 = v0191 % (int)4;
        ap_int<1> v0225 = v0224 < (int)0;
        int v0226 = v0224 + (int)4;
        int v0227 = v0225 ? v0226 : v0224;
        ap_float<32, 8> v0228 = v0187[v0227];
        ap_float<32, 8> v0229 = (ap_float<32, 8>)v0211;
        ap_float<32, 8> v0230 = (ap_float<32, 8>)v0223;
        ap_float<32, 8> v0231 = v0229 * v0230;
        ap_float<32, 8> v0232 = v0228 + v0231;
        int v0233 = v0191 % (int)4;
        ap_int<1> v0234 = v0233 < (int)0;
        int v0235 = v0233 + (int)4;
        int v0236 = v0234 ? v0235 : v0233;
        v0187[v0236] = v0232;
      }
      ap_float<32, 8> v0237 = v0184[v0188][(int)0][v0189];
      ap_float<32, 8> v0238 = v0187[(int)0];
      ap_float<32, 8> v0239 = v0187[(int)1];
      ap_float<32, 8> v0240 = v0187[(int)2];
      ap_float<32, 8> v0241 = v0187[(int)3];
      ap_float<32, 8> v0242 = v0238 + v0239;
      ap_float<32, 8> v0243 = v0240 + v0241;
      ap_float<32, 8> v0244 = v0242 + v0243;
      ap_float<32, 8> v0245 = v0244 + v0237;
      v0184[v0188][(int)0][v0189] = v0245;
    }
  }
  ap_float<16, 8> v0246[1][12][1][128];
  #pragma HLS bind_storage variable=v0246 type=ram_2p impl=bram latency=2
  for (int v0247 = (int)0; v0247 < (int)12; v0247 += (int)1) {
    for (int v0248 = (int)0; v0248 < (int)128; v0248 += (int)1) {
      ap_float<32, 8> v0249 = v0184[v0247][(int)0][v0248];
      ap_float<16, 8> v0250 = (ap_float<16, 8>)v0249;
      v0246[(int)0][v0247][(int)0][v0248] = v0250;
    }
  }
  ap_float<16, 8> v0251[1][12][1][128];
  #pragma HLS bind_storage variable=v0251 type=ram_2p impl=bram latency=2
  for (int v0252 = (int)0; v0252 < (int)12; v0252 += (int)1) {
    for (int v0253 = (int)0; v0253 < (int)128; v0253 += (int)1) {
      ap_float<16, 8> v0254 = v0246[(int)0][v0252][(int)0][v0253];
      ap_float<16, 8> v0255 = v0254 * (ap_float<16, 8>)0.125000;
      v0251[(int)0][v0252][(int)0][v0253] = v0255;
    }
  }
  ap_float<16, 8> v0256[1][12][1][128];
  #pragma HLS bind_storage variable=v0256 type=ram_2p impl=bram latency=2
  for (int v0257 = (int)0; v0257 < (int)12; v0257 += (int)1) {
    for (int v0258 = (int)0; v0258 < (int)128; v0258 += (int)1) {
      ap_int<1> v0259 = arg0000[(int)0][(int)0][(int)127][v0258];
      ap_float<16, 8> v0260 = v0251[(int)0][v0257][(int)0][v0258];
      ap_float<16, 8> v0261 = v0259 ? v0260 : (ap_float<16, 8>)-338953138925153547590470800371487866880.000000;
      v0256[(int)0][v0257][(int)0][v0258] = v0261;
    }
  }
  ap_float<16, 8> v0262[1][12][1][128];
  #pragma HLS bind_storage variable=v0262 type=ram_2p impl=bram latency=2
  for (int v0263 = (int)0; v0263 < (int)12; v0263 += (int)1) {
    for (int v0264 = (int)0; v0264 < (int)128; v0264 += (int)1) {
      ap_float<16, 8> v0265 = v0256[(int)0][v0263][(int)0][v0264];
      ap_float<16, 8> v0266 = arg0026[(int)0][(int)0][(int)0][v0264];
      ap_float<16, 8> v0267 = v0265 + v0266;
      v0262[(int)0][v0263][(int)0][v0264] = v0267;
    }
  }
  ap_float<32, 8> v0268[1][12][1][128];
  #pragma HLS bind_storage variable=v0268 type=ram_2p impl=bram latency=2
  for (int v0269 = (int)0; v0269 < (int)12; v0269 += (int)1) {
    for (int v0270 = (int)0; v0270 < (int)128; v0270 += (int)1) {
      ap_float<16, 8> v0271 = v0262[(int)0][v0269][(int)0][v0270];
      ap_float<32, 8> v0272 = (ap_float<32, 8>)v0271;
      v0268[(int)0][v0269][(int)0][v0270] = v0272;
    }
  }
  ap_float<32, 8> v0273[1][12][1];
  for (int v0274 = (int)0; v0274 < (int)12; v0274 += (int)1) {
    v0273[(int)0][v0274][(int)0] = (ap_float<32, 8>)-340282346638528859811704183484516925440.000000;
  }
  ap_float<32, 8> v0275[4];
  for (int v0276 = (int)0; v0276 < (int)12; v0276 += (int)1) {
    for (int v0277 = (int)0; v0277 < (int)4; v0277 += (int)1) {
      v0275[v0277] = (ap_float<32, 8>)-340282346638528859811704183484516925440.000000;
    }
    for (int v0278 = (int)0; v0278 < (int)128; v0278 += (int)1) {
      ap_float<32, 8> v0279 = v0268[(int)0][v0276][(int)0][v0278];
      int v0280 = v0278 % (int)4;
      ap_int<1> v0281 = v0280 < (int)0;
      int v0282 = v0280 + (int)4;
      int v0283 = v0281 ? v0282 : v0280;
      ap_float<32, 8> v0284 = v0275[v0283];
      ap_int<1> v0285 = (float)v0279 > (float)v0284;
      ap_float<32, 8> v0286 = v0285 ? v0279 : v0284;
      ap_int<1> v0287 = false;
      ap_float<32, 8> v0288 = v0287 ? v0284 : v0286;
      int v0289 = v0278 % (int)4;
      ap_int<1> v0290 = v0289 < (int)0;
      int v0291 = v0289 + (int)4;
      int v0292 = v0290 ? v0291 : v0289;
      v0275[v0292] = v0288;
    }
    ap_float<32, 8> v0293 = v0273[(int)0][v0276][(int)0];
    ap_float<32, 8> v0294 = v0275[(int)0];
    ap_float<32, 8> v0295 = v0275[(int)1];
    ap_float<32, 8> v0296 = v0275[(int)2];
    ap_float<32, 8> v0297 = v0275[(int)3];
    ap_int<1> v0298 = (float)v0294 > (float)v0295;
    ap_float<32, 8> v0299 = v0298 ? v0294 : v0295;
    ap_int<1> v0300 = false;
    ap_float<32, 8> v0301 = v0300 ? v0295 : v0299;
    ap_int<1> v0302 = (float)v0296 > (float)v0297;
    ap_float<32, 8> v0303 = v0302 ? v0296 : v0297;
    ap_int<1> v0304 = false;
    ap_float<32, 8> v0305 = v0304 ? v0297 : v0303;
    ap_int<1> v0306 = (float)v0301 > (float)v0305;
    ap_float<32, 8> v0307 = v0306 ? v0301 : v0305;
    ap_int<1> v0308 = false;
    ap_float<32, 8> v0309 = v0308 ? v0305 : v0307;
    ap_int<1> v0310 = (float)v0309 > (float)v0293;
    ap_float<32, 8> v0311 = v0310 ? v0309 : v0293;
    ap_int<1> v0312 = false;
    ap_float<32, 8> v0313 = v0312 ? v0293 : v0311;
    v0273[(int)0][v0276][(int)0] = v0313;
  }
  ap_float<32, 8> v0314[1][12][1][128];
  #pragma HLS bind_storage variable=v0314 type=ram_2p impl=bram latency=2
  for (int v0315 = (int)0; v0315 < (int)12; v0315 += (int)1) {
    for (int v0316 = (int)0; v0316 < (int)128; v0316 += (int)1) {
      ap_float<32, 8> v0317 = v0268[(int)0][v0315][(int)0][v0316];
      ap_float<32, 8> v0318 = v0273[(int)0][v0315][(int)0];
      ap_float<32, 8> v0319 = v0317 - v0318;
      v0314[(int)0][v0315][(int)0][v0316] = v0319;
    }
  }
  ap_float<32, 8> v0320[1][12][1][128];
  #pragma HLS bind_storage variable=v0320 type=ram_2p impl=bram latency=2
  for (int v0321 = (int)0; v0321 < (int)12; v0321 += (int)1) {
    for (int v0322 = (int)0; v0322 < (int)128; v0322 += (int)1) {
      ap_float<32, 8> v0323 = v0314[(int)0][v0321][(int)0][v0322];
      ap_float<32, 8> v0324 = hls::exp((float)v0323);
      v0320[(int)0][v0321][(int)0][v0322] = v0324;
    }
  }
  ap_float<32, 8> v0325[1][12][1];
  for (int v0326 = (int)0; v0326 < (int)12; v0326 += (int)1) {
    v0325[(int)0][v0326][(int)0] = (ap_float<32, 8>)0.000000;
  }
  ap_float<32, 8> v0327[4];
  for (int v0328 = (int)0; v0328 < (int)12; v0328 += (int)1) {
    for (int v0329 = (int)0; v0329 < (int)4; v0329 += (int)1) {
      v0327[v0329] = (ap_float<32, 8>)0.000000;
    }
    for (int v0330 = (int)0; v0330 < (int)128; v0330 += (int)1) {
      ap_float<32, 8> v0331 = v0320[(int)0][v0328][(int)0][v0330];
      int v0332 = v0330 % (int)4;
      ap_int<1> v0333 = v0332 < (int)0;
      int v0334 = v0332 + (int)4;
      int v0335 = v0333 ? v0334 : v0332;
      ap_float<32, 8> v0336 = v0327[v0335];
      ap_float<32, 8> v0337 = v0331 + v0336;
      int v0338 = v0330 % (int)4;
      ap_int<1> v0339 = v0338 < (int)0;
      int v0340 = v0338 + (int)4;
      int v0341 = v0339 ? v0340 : v0338;
      v0327[v0341] = v0337;
    }
    ap_float<32, 8> v0342 = v0325[(int)0][v0328][(int)0];
    ap_float<32, 8> v0343 = v0327[(int)0];
    ap_float<32, 8> v0344 = v0327[(int)1];
    ap_float<32, 8> v0345 = v0327[(int)2];
    ap_float<32, 8> v0346 = v0327[(int)3];
    ap_float<32, 8> v0347 = v0343 + v0344;
    ap_float<32, 8> v0348 = v0345 + v0346;
    ap_float<32, 8> v0349 = v0347 + v0348;
    ap_float<32, 8> v0350 = v0349 + v0342;
    v0325[(int)0][v0328][(int)0] = v0350;
  }
  ap_float<32, 8> v0351[1][12][1][1];
  for (int v0352 = (int)0; v0352 < (int)12; v0352 += (int)1) {
    ap_float<32, 8> v0353 = v0325[(int)0][v0352][(int)0];
    ap_float<32, 8> v0354 = hls::divide((float)(ap_float<32, 8>)1.000000, (float)v0353);
    v0351[(int)0][v0352][(int)0][(int)0] = v0354;
  }
  ap_float<32, 8> v0355[1][12][1][128];
  #pragma HLS bind_storage variable=v0355 type=ram_2p impl=bram latency=2
  for (int v0356 = (int)0; v0356 < (int)12; v0356 += (int)1) {
    for (int v0357 = (int)0; v0357 < (int)128; v0357 += (int)1) {
      ap_float<32, 8> v0358 = v0320[(int)0][v0356][(int)0][v0357];
      ap_float<32, 8> v0359 = v0351[(int)0][v0356][(int)0][(int)0];
      ap_float<32, 8> v0360 = v0358 * v0359;
      v0355[(int)0][v0356][(int)0][v0357] = v0360;
    }
  }
  ap_float<16, 8> v0361[1][12][1][128];
  #pragma HLS bind_storage variable=v0361 type=ram_2p impl=bram latency=2
  for (int v0362 = (int)0; v0362 < (int)12; v0362 += (int)1) {
    for (int v0363 = (int)0; v0363 < (int)128; v0363 += (int)1) {
      ap_float<32, 8> v0364 = v0355[(int)0][v0362][(int)0][v0363];
      ap_float<16, 8> v0365 = (ap_float<16, 8>)v0364;
      v0361[(int)0][v0362][(int)0][v0363] = v0365;
    }
  }
  ap_float<32, 8> v0366[12][1][64];
  #pragma HLS bind_storage variable=v0366 type=ram_2p impl=bram latency=2
  for (int v0367 = (int)0; v0367 < (int)12; v0367 += (int)1) {
    for (int v0368 = (int)0; v0368 < (int)64; v0368 += (int)1) {
      v0366[v0367][(int)0][v0368] = (ap_float<32, 8>)0.000000;
    }
  }
  ap_float<32, 8> v0369[4];
  for (int v0370 = (int)0; v0370 < (int)12; v0370 += (int)1) {
    for (int v0371 = (int)0; v0371 < (int)64; v0371 += (int)1) {
      for (int v0372 = (int)0; v0372 < (int)4; v0372 += (int)1) {
        v0369[v0372] = (ap_float<32, 8>)0.000000;
      }
      for (int v0373 = (int)0; v0373 < (int)128; v0373 += (int)1) {
        int v0374 = v0370 / (int)12;
        int v0375 = v0374 * (int)12;
        ap_int<1> v0376 = v0370 != v0375;
        ap_int<1> v0377 = v0370 < (int)0;
        ap_int<1> v0378 = v0376 & v0377;
        int v0379 = v0374 + (int)-1;
        int v0380 = v0378 ? v0379 : v0374;
        int v0381 = v0370 % (int)12;
        ap_int<1> v0382 = v0381 < (int)0;
        int v0383 = v0381 + (int)12;
        int v0384 = v0382 ? v0383 : v0381;
        ap_float<16, 8> v0385 = v0361[v0380][v0384][(int)0][v0373];
        int v0386 = v0370 / (int)12;
        int v0387 = v0386 * (int)12;
        ap_int<1> v0388 = v0370 != v0387;
        ap_int<1> v0389 = v0370 < (int)0;
        ap_int<1> v0390 = v0388 & v0389;
        int v0391 = v0386 + (int)-1;
        int v0392 = v0390 ? v0391 : v0386;
        int v0393 = v0370 % (int)12;
        ap_int<1> v0394 = v0393 < (int)0;
        int v0395 = v0393 + (int)12;
        int v0396 = v0394 ? v0395 : v0393;
        ap_float<16, 8> v0397 = v0171[v0392][v0396][v0373][v0371];
        int v0398 = v0373 % (int)4;
        ap_int<1> v0399 = v0398 < (int)0;
        int v0400 = v0398 + (int)4;
        int v0401 = v0399 ? v0400 : v0398;
        ap_float<32, 8> v0402 = v0369[v0401];
        ap_float<32, 8> v0403 = (ap_float<32, 8>)v0385;
        ap_float<32, 8> v0404 = (ap_float<32, 8>)v0397;
        ap_float<32, 8> v0405 = v0403 * v0404;
        ap_float<32, 8> v0406 = v0402 + v0405;
        int v0407 = v0373 % (int)4;
        ap_int<1> v0408 = v0407 < (int)0;
        int v0409 = v0407 + (int)4;
        int v0410 = v0408 ? v0409 : v0407;
        v0369[v0410] = v0406;
      }
      ap_float<32, 8> v0411 = v0366[v0370][(int)0][v0371];
      ap_float<32, 8> v0412 = v0369[(int)0];
      ap_float<32, 8> v0413 = v0369[(int)1];
      ap_float<32, 8> v0414 = v0369[(int)2];
      ap_float<32, 8> v0415 = v0369[(int)3];
      ap_float<32, 8> v0416 = v0412 + v0413;
      ap_float<32, 8> v0417 = v0414 + v0415;
      ap_float<32, 8> v0418 = v0416 + v0417;
      ap_float<32, 8> v0419 = v0418 + v0411;
      v0366[v0370][(int)0][v0371] = v0419;
    }
  }
  ap_float<16, 8> v0420[1][12][1][64];
  #pragma HLS bind_storage variable=v0420 type=ram_2p impl=bram latency=2
  for (int v0421 = (int)0; v0421 < (int)12; v0421 += (int)1) {
    for (int v0422 = (int)0; v0422 < (int)64; v0422 += (int)1) {
      ap_float<32, 8> v0423 = v0366[v0421][(int)0][v0422];
      ap_float<16, 8> v0424 = (ap_float<16, 8>)v0423;
      v0420[(int)0][v0421][(int)0][v0422] = v0424;
    }
  }
  ap_float<32, 8> v0425[1][1][768];
  #pragma HLS bind_storage variable=v0425 type=ram_2p impl=bram latency=2
  for (int v0426 = (int)0; v0426 < (int)768; v0426 += (int)1) {
    v0425[(int)0][(int)0][v0426] = (ap_float<32, 8>)0.000000;
  }
  ap_float<32, 8> v0427[4];
  for (int v0428 = (int)0; v0428 < (int)768; v0428 += (int)1) {
    for (int v0429 = (int)0; v0429 < (int)4; v0429 += (int)1) {
      v0427[v0429] = (ap_float<32, 8>)0.000000;
    }
    for (int v0430 = (int)0; v0430 < (int)768; v0430 += (int)1) {
      int v0431 = v0430 / (int)64;
      int v0432 = v0431 * (int)64;
      ap_int<1> v0433 = v0430 != v0432;
      ap_int<1> v0434 = v0430 < (int)0;
      ap_int<1> v0435 = v0433 & v0434;
      int v0436 = v0431 + (int)-1;
      int v0437 = v0435 ? v0436 : v0431;
      int v0438 = v0430 % (int)64;
      ap_int<1> v0439 = v0438 < (int)0;
      int v0440 = v0438 + (int)64;
      int v0441 = v0439 ? v0440 : v0438;
      int v0442 = v0441 / (int)64;
      int v0443 = v0430 % (int)64;
      ap_int<1> v0444 = v0443 < (int)0;
      int v0445 = v0443 + (int)64;
      int v0446 = v0444 ? v0445 : v0443;
      ap_float<16, 8> v0447 = v0420[(int)0][v0437][v0442][v0446];
      ap_float<16, 8> v0448 = arg0039[v0430][v0428];
      int v0449 = v0430 % (int)4;
      ap_int<1> v0450 = v0449 < (int)0;
      int v0451 = v0449 + (int)4;
      int v0452 = v0450 ? v0451 : v0449;
      ap_float<32, 8> v0453 = v0427[v0452];
      ap_float<32, 8> v0454 = (ap_float<32, 8>)v0447;
      ap_float<32, 8> v0455 = (ap_float<32, 8>)v0448;
      ap_float<32, 8> v0456 = v0454 * v0455;
      ap_float<32, 8> v0457 = v0453 + v0456;
      int v0458 = v0430 % (int)4;
      ap_int<1> v0459 = v0458 < (int)0;
      int v0460 = v0458 + (int)4;
      int v0461 = v0459 ? v0460 : v0458;
      v0427[v0461] = v0457;
    }
    ap_float<32, 8> v0462 = v0425[(int)0][(int)0][v0428];
    ap_float<32, 8> v0463 = v0427[(int)0];
    ap_float<32, 8> v0464 = v0427[(int)1];
    ap_float<32, 8> v0465 = v0427[(int)2];
    ap_float<32, 8> v0466 = v0427[(int)3];
    ap_float<32, 8> v0467 = v0463 + v0464;
    ap_float<32, 8> v0468 = v0465 + v0466;
    ap_float<32, 8> v0469 = v0467 + v0468;
    ap_float<32, 8> v0470 = v0469 + v0462;
    v0425[(int)0][(int)0][v0428] = v0470;
  }
  ap_float<16, 8> v0471[1][768];
  #pragma HLS bind_storage variable=v0471 type=ram_2p impl=bram latency=2
  for (int v0472 = (int)0; v0472 < (int)768; v0472 += (int)1) {
    ap_float<32, 8> v0473 = v0425[(int)0][(int)0][v0472];
    ap_float<16, 8> v0474 = (ap_float<16, 8>)v0473;
    v0471[(int)0][v0472] = v0474;
  }
  ap_float<16, 8> v0475[1][768];
  #pragma HLS bind_storage variable=v0475 type=ram_2p impl=bram latency=2
  for (int v0476 = (int)0; v0476 < (int)768; v0476 += (int)1) {
    ap_float<16, 8> v0477 = v0471[(int)0][v0476];
    ap_float<16, 8> v0478 = arg0038[v0476];
    ap_float<16, 8> v0479 = v0477 + v0478;
    v0475[(int)0][v0476] = v0479;
  }
  ap_float<16, 8> v0480[1][1][768];
  #pragma HLS bind_storage variable=v0480 type=ram_2p impl=bram latency=2
  for (int v0481 = (int)0; v0481 < (int)768; v0481 += (int)1) {
    ap_float<16, 8> v0482 = v0475[(int)0][v0481];
    ap_float<16, 8> v0483 = arg0024[(int)0][(int)0][v0481];
    ap_float<16, 8> v0484 = v0482 + v0483;
    v0480[(int)0][(int)0][v0481] = v0484;
  }
  ap_float<32, 8> v0485[1][1];
  v0485[(int)0][(int)0] = (ap_float<32, 8>)0.000000;
  ap_float<32, 8> v0486[4];
  for (int v0487 = (int)0; v0487 < (int)4; v0487 += (int)1) {
    v0486[v0487] = (ap_float<32, 8>)0.000000;
  }
  for (int v0488 = (int)0; v0488 < (int)768; v0488 += (int)1) {
    ap_float<16, 8> v0489 = v0480[(int)0][(int)0][v0488];
    int v0490 = v0488 % (int)4;
    ap_int<1> v0491 = v0490 < (int)0;
    int v0492 = v0490 + (int)4;
    int v0493 = v0491 ? v0492 : v0490;
    ap_float<32, 8> v0494 = v0486[v0493];
    ap_float<32, 8> v0495 = (ap_float<32, 8>)v0489;
    ap_float<32, 8> v0496 = v0495 + v0494;
    int v0497 = v0488 % (int)4;
    ap_int<1> v0498 = v0497 < (int)0;
    int v0499 = v0497 + (int)4;
    int v0500 = v0498 ? v0499 : v0497;
    v0486[v0500] = v0496;
  }
  ap_float<32, 8> v0501 = v0485[(int)0][(int)0];
  ap_float<32, 8> v0502 = v0486[(int)0];
  ap_float<32, 8> v0503 = v0486[(int)1];
  ap_float<32, 8> v0504 = v0486[(int)2];
  ap_float<32, 8> v0505 = v0486[(int)3];
  ap_float<32, 8> v0506 = v0502 + v0503;
  ap_float<32, 8> v0507 = v0504 + v0505;
  ap_float<32, 8> v0508 = v0506 + v0507;
  ap_float<32, 8> v0509 = v0508 + v0501;
  v0485[(int)0][(int)0] = v0509;
  ap_float<16, 8> v0510[1][1];
  ap_float<32, 8> v0511 = v0485[(int)0][(int)0];
  ap_float<16, 8> v0512 = (ap_float<16, 8>)v0511;
  v0510[(int)0][(int)0] = v0512;
  ap_float<16, 8> v0513[1][1][1];
  ap_float<16, 8> v0514 = v0510[(int)0][(int)0];
  ap_float<16, 8> v0515 = v0514 * (ap_float<16, 8>)0.001305;
  v0513[(int)0][(int)0][(int)0] = v0515;
  ap_float<16, 8> v0516[1][1][1][1][768][1];
  #pragma HLS bind_storage variable=v0516 type=ram_2p impl=bram latency=2
  for (int v0517 = (int)0; v0517 < (int)768; v0517 += (int)1) {
    ap_float<16, 8> v0518 = v0513[(int)0][(int)0][(int)0];
    v0516[(int)0][(int)0][(int)0][(int)0][v0517][(int)0] = v0518;
  }
  ap_float<16, 8> v0519[1][1][768];
  #pragma HLS bind_storage variable=v0519 type=ram_2p impl=bram latency=2
  for (int v0520 = (int)0; v0520 < (int)768; v0520 += (int)1) {
    ap_float<16, 8> v0521 = v0480[(int)0][(int)0][v0520];
    ap_float<16, 8> v0522 = v0516[(int)0][(int)0][(int)0][(int)0][v0520][(int)0];
    ap_float<16, 8> v0523 = v0521 - v0522;
    v0519[(int)0][(int)0][v0520] = v0523;
  }
  ap_float<16, 8> v0524[1][1][768];
  #pragma HLS bind_storage variable=v0524 type=ram_2p impl=bram latency=2
  for (int v0525 = (int)0; v0525 < (int)768; v0525 += (int)1) {
    ap_float<16, 8> v0526 = v0519[(int)0][(int)0][v0525];
    ap_float<16, 8> v0527 = v0519[(int)0][(int)0][v0525];
    ap_float<16, 8> v0528 = v0526 * v0527;
    v0524[(int)0][(int)0][v0525] = v0528;
  }
  ap_float<32, 8> v0529[1][1];
  v0529[(int)0][(int)0] = (ap_float<32, 8>)0.000000;
  ap_float<32, 8> v0530[4];
  for (int v0531 = (int)0; v0531 < (int)4; v0531 += (int)1) {
    v0530[v0531] = (ap_float<32, 8>)0.000000;
  }
  for (int v0532 = (int)0; v0532 < (int)768; v0532 += (int)1) {
    ap_float<16, 8> v0533 = v0524[(int)0][(int)0][v0532];
    int v0534 = v0532 % (int)4;
    ap_int<1> v0535 = v0534 < (int)0;
    int v0536 = v0534 + (int)4;
    int v0537 = v0535 ? v0536 : v0534;
    ap_float<32, 8> v0538 = v0530[v0537];
    ap_float<32, 8> v0539 = (ap_float<32, 8>)v0533;
    ap_float<32, 8> v0540 = v0539 + v0538;
    int v0541 = v0532 % (int)4;
    ap_int<1> v0542 = v0541 < (int)0;
    int v0543 = v0541 + (int)4;
    int v0544 = v0542 ? v0543 : v0541;
    v0530[v0544] = v0540;
  }
  ap_float<32, 8> v0545 = v0529[(int)0][(int)0];
  ap_float<32, 8> v0546 = v0530[(int)0];
  ap_float<32, 8> v0547 = v0530[(int)1];
  ap_float<32, 8> v0548 = v0530[(int)2];
  ap_float<32, 8> v0549 = v0530[(int)3];
  ap_float<32, 8> v0550 = v0546 + v0547;
  ap_float<32, 8> v0551 = v0548 + v0549;
  ap_float<32, 8> v0552 = v0550 + v0551;
  ap_float<32, 8> v0553 = v0552 + v0545;
  v0529[(int)0][(int)0] = v0553;
  ap_float<16, 8> v0554[1][1];
  ap_float<32, 8> v0555 = v0529[(int)0][(int)0];
  ap_float<16, 8> v0556 = (ap_float<16, 8>)v0555;
  v0554[(int)0][(int)0] = v0556;
  ap_float<16, 8> v0557[1][1][1];
  ap_float<16, 8> v0558 = v0554[(int)0][(int)0];
  ap_float<16, 8> v0559 = v0558 * (ap_float<16, 8>)0.001305;
  v0557[(int)0][(int)0][(int)0] = v0559;
  ap_float<16, 8> v0560[1][1][1];
  ap_float<16, 8> v0561 = v0557[(int)0][(int)0][(int)0];
  ap_float<16, 8> v0562 = v0561 + (ap_float<16, 8>)0.000010;
  v0560[(int)0][(int)0][(int)0] = v0562;
  ap_float<16, 8> v0563[1][1][1];
  ap_float<16, 8> v0564 = v0560[(int)0][(int)0][(int)0];
  ap_float<16, 8> v0565 = hls::rsqrt((float)v0564);
  v0563[(int)0][(int)0][(int)0] = v0565;
  ap_float<16, 8> v0566[1][1][1][1][768][1];
  #pragma HLS bind_storage variable=v0566 type=ram_2p impl=bram latency=2
  for (int v0567 = (int)0; v0567 < (int)768; v0567 += (int)1) {
    ap_float<16, 8> v0568 = v0563[(int)0][(int)0][(int)0];
    v0566[(int)0][(int)0][(int)0][(int)0][v0567][(int)0] = v0568;
  }
  ap_float<16, 8> v0569[1][1][768];
  #pragma HLS bind_storage variable=v0569 type=ram_2p impl=bram latency=2
  for (int v0570 = (int)0; v0570 < (int)768; v0570 += (int)1) {
    ap_float<16, 8> v0571 = v0519[(int)0][(int)0][v0570];
    ap_float<16, 8> v0572 = v0566[(int)0][(int)0][(int)0][(int)0][v0570][(int)0];
    ap_float<16, 8> v0573 = v0571 * v0572;
    v0569[(int)0][(int)0][v0570] = v0573;
  }
  ap_float<16, 8> v0574[1][1][768];
  #pragma HLS bind_storage variable=v0574 type=ram_2p impl=bram latency=2
  for (int v0575 = (int)0; v0575 < (int)768; v0575 += (int)1) {
    ap_float<16, 8> v0576 = v0569[(int)0][(int)0][v0575];
    ap_float<16, 8> v0577 = arg0037[v0575];
    ap_float<16, 8> v0578 = v0576 * v0577;
    v0574[(int)0][(int)0][v0575] = v0578;
  }
  ap_float<16, 8> v0579[1][1][768];
  #pragma HLS bind_storage variable=v0579 type=ram_2p impl=bram latency=2
  for (int v0580 = (int)0; v0580 < (int)768; v0580 += (int)1) {
    ap_float<16, 8> v0581 = v0574[(int)0][(int)0][v0580];
    ap_float<16, 8> v0582 = arg0036[v0580];
    ap_float<16, 8> v0583 = v0581 + v0582;
    v0579[(int)0][(int)0][v0580] = v0583;
  }
  ap_float<32, 8> v0584[1][1][3072];
  #pragma HLS bind_storage variable=v0584 type=ram_2p impl=bram latency=2
  for (int v0585 = (int)0; v0585 < (int)3072; v0585 += (int)1) {
    v0584[(int)0][(int)0][v0585] = (ap_float<32, 8>)0.000000;
  }
  ap_float<32, 8> v0586[4];
  for (int v0587 = (int)0; v0587 < (int)3072; v0587 += (int)1) {
    for (int v0588 = (int)0; v0588 < (int)4; v0588 += (int)1) {
      v0586[v0588] = (ap_float<32, 8>)0.000000;
    }
    for (int v0589 = (int)0; v0589 < (int)768; v0589 += (int)1) {
      ap_float<16, 8> v0590 = v0579[(int)0][(int)0][v0589];
      ap_float<16, 8> v0591 = arg0035[v0589][v0587];
      int v0592 = v0589 % (int)4;
      ap_int<1> v0593 = v0592 < (int)0;
      int v0594 = v0592 + (int)4;
      int v0595 = v0593 ? v0594 : v0592;
      ap_float<32, 8> v0596 = v0586[v0595];
      ap_float<32, 8> v0597 = (ap_float<32, 8>)v0590;
      ap_float<32, 8> v0598 = (ap_float<32, 8>)v0591;
      ap_float<32, 8> v0599 = v0597 * v0598;
      ap_float<32, 8> v0600 = v0596 + v0599;
      int v0601 = v0589 % (int)4;
      ap_int<1> v0602 = v0601 < (int)0;
      int v0603 = v0601 + (int)4;
      int v0604 = v0602 ? v0603 : v0601;
      v0586[v0604] = v0600;
    }
    ap_float<32, 8> v0605 = v0584[(int)0][(int)0][v0587];
    ap_float<32, 8> v0606 = v0586[(int)0];
    ap_float<32, 8> v0607 = v0586[(int)1];
    ap_float<32, 8> v0608 = v0586[(int)2];
    ap_float<32, 8> v0609 = v0586[(int)3];
    ap_float<32, 8> v0610 = v0606 + v0607;
    ap_float<32, 8> v0611 = v0608 + v0609;
    ap_float<32, 8> v0612 = v0610 + v0611;
    ap_float<32, 8> v0613 = v0612 + v0605;
    v0584[(int)0][(int)0][v0587] = v0613;
  }
  ap_float<16, 8> v0614[1][3072];
  #pragma HLS bind_storage variable=v0614 type=ram_2p impl=bram latency=2
  for (int v0615 = (int)0; v0615 < (int)3072; v0615 += (int)1) {
    ap_float<32, 8> v0616 = v0584[(int)0][(int)0][v0615];
    ap_float<16, 8> v0617 = (ap_float<16, 8>)v0616;
    v0614[(int)0][v0615] = v0617;
  }
  ap_float<16, 8> v0618[1][3072];
  #pragma HLS bind_storage variable=v0618 type=ram_2p impl=bram latency=2
  for (int v0619 = (int)0; v0619 < (int)3072; v0619 += (int)1) {
    ap_float<16, 8> v0620 = v0614[(int)0][v0619];
    ap_float<16, 8> v0621 = arg0034[v0619];
    ap_float<16, 8> v0622 = v0620 + v0621;
    v0618[(int)0][v0619] = v0622;
  }
  ap_float<16, 8> v0623[1][1][3072];
  #pragma HLS bind_storage variable=v0623 type=ram_2p impl=bram latency=2
  for (int v0624 = (int)0; v0624 < (int)3072; v0624 += (int)1) {
    ap_float<16, 8> v0625 = v0618[(int)0][v0624];
    ap_float<16, 8> v0626 = v0625 * (ap_float<16, 8>)0.500000;
    v0623[(int)0][(int)0][v0624] = v0626;
  }
  ap_float<16, 8> v0627[1][1][3072];
  #pragma HLS bind_storage variable=v0627 type=ram_2p impl=bram latency=2
  for (int v0628 = (int)0; v0628 < (int)3072; v0628 += (int)1) {
    ap_float<16, 8> v0629 = v0618[(int)0][v0628];
    ap_float<16, 8> v0630 = hls::pow((float)v0629, (float)(ap_float<16, 8>)3.000000);
    v0627[(int)0][(int)0][v0628] = v0630;
  }
  ap_float<16, 8> v0631[1][1][3072];
  #pragma HLS bind_storage variable=v0631 type=ram_2p impl=bram latency=2
  for (int v0632 = (int)0; v0632 < (int)3072; v0632 += (int)1) {
    ap_float<16, 8> v0633 = v0627[(int)0][(int)0][v0632];
    ap_float<16, 8> v0634 = v0633 * (ap_float<16, 8>)0.044678;
    v0631[(int)0][(int)0][v0632] = v0634;
  }
  ap_float<16, 8> v0635[1][1][3072];
  #pragma HLS bind_storage variable=v0635 type=ram_2p impl=bram latency=2
  for (int v0636 = (int)0; v0636 < (int)3072; v0636 += (int)1) {
    ap_float<16, 8> v0637 = v0618[(int)0][v0636];
    ap_float<16, 8> v0638 = v0631[(int)0][(int)0][v0636];
    ap_float<16, 8> v0639 = v0637 + v0638;
    v0635[(int)0][(int)0][v0636] = v0639;
  }
  ap_float<16, 8> v0640[1][1][3072];
  #pragma HLS bind_storage variable=v0640 type=ram_2p impl=bram latency=2
  for (int v0641 = (int)0; v0641 < (int)3072; v0641 += (int)1) {
    ap_float<16, 8> v0642 = v0635[(int)0][(int)0][v0641];
    ap_float<16, 8> v0643 = v0642 * (ap_float<16, 8>)0.796875;
    v0640[(int)0][(int)0][v0641] = v0643;
  }
  ap_float<16, 8> v0644[1][1][3072];
  #pragma HLS bind_storage variable=v0644 type=ram_2p impl=bram latency=2
  for (int v0645 = (int)0; v0645 < (int)3072; v0645 += (int)1) {
    ap_float<16, 8> v0646 = v0640[(int)0][(int)0][v0645];
    ap_float<16, 8> v0647 = hls::tanh((float)v0646);
    v0644[(int)0][(int)0][v0645] = v0647;
  }
  ap_float<16, 8> v0648[1][1][3072];
  #pragma HLS bind_storage variable=v0648 type=ram_2p impl=bram latency=2
  for (int v0649 = (int)0; v0649 < (int)3072; v0649 += (int)1) {
    ap_float<16, 8> v0650 = v0644[(int)0][(int)0][v0649];
    ap_float<16, 8> v0651 = v0650 + (ap_float<16, 8>)1.000000;
    v0648[(int)0][(int)0][v0649] = v0651;
  }
  ap_float<16, 8> v0652[1][1][3072];
  #pragma HLS bind_storage variable=v0652 type=ram_2p impl=bram latency=2
  for (int v0653 = (int)0; v0653 < (int)3072; v0653 += (int)1) {
    ap_float<16, 8> v0654 = v0623[(int)0][(int)0][v0653];
    ap_float<16, 8> v0655 = v0648[(int)0][(int)0][v0653];
    ap_float<16, 8> v0656 = v0654 * v0655;
    v0652[(int)0][(int)0][v0653] = v0656;
  }
  ap_float<32, 8> v0657[1][1][768];
  #pragma HLS bind_storage variable=v0657 type=ram_2p impl=bram latency=2
  for (int v0658 = (int)0; v0658 < (int)768; v0658 += (int)1) {
    v0657[(int)0][(int)0][v0658] = (ap_float<32, 8>)0.000000;
  }
  ap_float<32, 8> v0659[4];
  for (int v0660 = (int)0; v0660 < (int)768; v0660 += (int)1) {
    for (int v0661 = (int)0; v0661 < (int)4; v0661 += (int)1) {
      v0659[v0661] = (ap_float<32, 8>)0.000000;
    }
    for (int v0662 = (int)0; v0662 < (int)3072; v0662 += (int)1) {
      ap_float<16, 8> v0663 = v0652[(int)0][(int)0][v0662];
      ap_float<16, 8> v0664 = arg0033[v0662][v0660];
      int v0665 = v0662 % (int)4;
      ap_int<1> v0666 = v0665 < (int)0;
      int v0667 = v0665 + (int)4;
      int v0668 = v0666 ? v0667 : v0665;
      ap_float<32, 8> v0669 = v0659[v0668];
      ap_float<32, 8> v0670 = (ap_float<32, 8>)v0663;
      ap_float<32, 8> v0671 = (ap_float<32, 8>)v0664;
      ap_float<32, 8> v0672 = v0670 * v0671;
      ap_float<32, 8> v0673 = v0669 + v0672;
      int v0674 = v0662 % (int)4;
      ap_int<1> v0675 = v0674 < (int)0;
      int v0676 = v0674 + (int)4;
      int v0677 = v0675 ? v0676 : v0674;
      v0659[v0677] = v0673;
    }
    ap_float<32, 8> v0678 = v0657[(int)0][(int)0][v0660];
    ap_float<32, 8> v0679 = v0659[(int)0];
    ap_float<32, 8> v0680 = v0659[(int)1];
    ap_float<32, 8> v0681 = v0659[(int)2];
    ap_float<32, 8> v0682 = v0659[(int)3];
    ap_float<32, 8> v0683 = v0679 + v0680;
    ap_float<32, 8> v0684 = v0681 + v0682;
    ap_float<32, 8> v0685 = v0683 + v0684;
    ap_float<32, 8> v0686 = v0685 + v0678;
    v0657[(int)0][(int)0][v0660] = v0686;
  }
  ap_float<16, 8> v0687[1][768];
  #pragma HLS bind_storage variable=v0687 type=ram_2p impl=bram latency=2
  for (int v0688 = (int)0; v0688 < (int)768; v0688 += (int)1) {
    ap_float<32, 8> v0689 = v0657[(int)0][(int)0][v0688];
    ap_float<16, 8> v0690 = (ap_float<16, 8>)v0689;
    v0687[(int)0][v0688] = v0690;
  }
  ap_float<16, 8> v0691[1][768];
  #pragma HLS bind_storage variable=v0691 type=ram_2p impl=bram latency=2
  for (int v0692 = (int)0; v0692 < (int)768; v0692 += (int)1) {
    ap_float<16, 8> v0693 = v0687[(int)0][v0692];
    ap_float<16, 8> v0694 = arg0032[v0692];
    ap_float<16, 8> v0695 = v0693 + v0694;
    v0691[(int)0][v0692] = v0695;
  }
  ap_float<16, 8> v0696[1][1][768];
  #pragma HLS bind_storage variable=v0696 type=ram_2p impl=bram latency=2
  for (int v0697 = (int)0; v0697 < (int)768; v0697 += (int)1) {
    ap_float<16, 8> v0698 = v0480[(int)0][(int)0][v0697];
    ap_float<16, 8> v0699 = v0691[(int)0][v0697];
    ap_float<16, 8> v0700 = v0698 + v0699;
    v0696[(int)0][(int)0][v0697] = v0700;
  }
  for (int v0701 = (int)0; v0701 < (int)768; v0701 += (int)1) {
    ap_float<16, 8> v0702 = v0696[(int)0][(int)0][v0701];
    arg0029[(int)0][(int)0][v0701] = v0702;
  }
  for (int v0703 = (int)0; v0703 < (int)12; v0703 += (int)1) {
    for (int v0704 = (int)0; v0704 < (int)128; v0704 += (int)1) {
      for (int v0705 = (int)0; v0705 < (int)64; v0705 += (int)1) {
        ap_float<16, 8> v0706 = v0163[(int)0][v0703][v0704][v0705];
        arg0030[(int)0][v0703][v0704][v0705] = v0706;
      }
    }
  }
  for (int v0707 = (int)0; v0707 < (int)12; v0707 += (int)1) {
    for (int v0708 = (int)0; v0708 < (int)128; v0708 += (int)1) {
      for (int v0709 = (int)0; v0709 < (int)64; v0709 += (int)1) {
        ap_float<16, 8> v0710 = v0171[(int)0][v0707][v0708][v0709];
        arg0031[(int)0][v0707][v0708][v0709] = v0710;
      }
    }
  }
  return;
}

