
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

void kernel_0_chip0(ap_float<16, 8> arg0000[1][1][768], ap_int<32> arg0001[1], ap_float<16, 8> arg0002[1][12][128][64], ap_float<16, 8> arg0003[1][12][128][64], ap_int<1> arg0004[1][1][1024][1024], ap_float<16, 8> arg0005[1][1][1][128], ap_float<16, 8> arg0006[1][12][128][64], ap_float<16, 8> arg0007[1][12][128][64], ap_float<32, 8> arg0008[1][1][768], ap_float<16, 8> arg0009[768], ap_float<16, 8> arg0010[768], ap_float<16, 8> arg0011[768][2304], ap_float<16, 8> arg0012[2304], ap_float<16, 8> arg0013[768][768], volatile uint32_t timer[8], volatile uint32_t debug[256]) {
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
    ap_float<16, 8> v0005 = arg0000[(int)0][(int)0][v0004];
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
    ap_float<16, 8> v0037 = arg0000[(int)0][(int)0][v0036];
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
    ap_float<16, 8> v0093 = arg0009[v0091];
    ap_float<16, 8> v0094 = v0092 * v0093;
    v0090[(int)0][(int)0][v0091] = v0094;
  }
  ap_float<16, 8> v0095[1][1][768];
  #pragma HLS bind_storage variable=v0095 type=ram_2p impl=bram latency=2
  for (int v0096 = (int)0; v0096 < (int)768; v0096 += (int)1) {
    ap_float<16, 8> v0097 = v0090[(int)0][(int)0][v0096];
    ap_float<16, 8> v0098 = arg0010[v0096];
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
      ap_float<16, 8> v0107 = arg0011[v0105][v0103];
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
    ap_float<16, 8> v0137 = arg0012[v0135];
    ap_float<16, 8> v0138 = v0136 + v0137;
    v0134[(int)0][v0135] = v0138;
  }
  ap_int<64> v0139[1][1][1][1];
  ap_int<32> v0140 = arg0001[(int)0];
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
        ap_float<16, 8> v0169 = arg0002[(int)0][v0164][v0165][v0166];
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
        ap_float<16, 8> v0177 = arg0003[(int)0][v0172][v0173][v0174];
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
      ap_int<1> v0259 = arg0004[(int)0][(int)0][(int)127][v0258];
      ap_float<16, 8> v0260 = v0251[(int)0][v0257][(int)0][v0258];
      ap_float<16, 8> v0261 = v0259 ? v0260 : (ap_float<16, 8>)-338953138925153547590470800371487866880.000000;
      v0256[(int)0][v0257][(int)0][v0258] = v0261;
    }
  }
  ap_float<16, 8> v0262[1][1][12][1][1][1][1][128];
  #pragma HLS bind_storage variable=v0262 type=ram_2p impl=bram latency=2
  for (int v0263 = (int)0; v0263 < (int)12; v0263 += (int)1) {
    for (int v0264 = (int)0; v0264 < (int)128; v0264 += (int)1) {
      ap_float<16, 8> v0265 = arg0005[(int)0][(int)0][(int)0][v0264];
      v0262[(int)0][(int)0][v0263][(int)0][(int)0][(int)0][(int)0][v0264] = v0265;
    }
  }
  ap_float<16, 8> v0266[1][12][1][128];
  #pragma HLS bind_storage variable=v0266 type=ram_2p impl=bram latency=2
  for (int v0267 = (int)0; v0267 < (int)12; v0267 += (int)1) {
    for (int v0268 = (int)0; v0268 < (int)128; v0268 += (int)1) {
      ap_float<16, 8> v0269 = v0256[(int)0][v0267][(int)0][v0268];
      ap_float<16, 8> v0270 = v0262[(int)0][(int)0][v0267][(int)0][(int)0][(int)0][(int)0][v0268];
      ap_float<16, 8> v0271 = v0269 + v0270;
      v0266[(int)0][v0267][(int)0][v0268] = v0271;
    }
  }
  ap_float<32, 8> v0272[1][12][1][128];
  #pragma HLS bind_storage variable=v0272 type=ram_2p impl=bram latency=2
  for (int v0273 = (int)0; v0273 < (int)12; v0273 += (int)1) {
    for (int v0274 = (int)0; v0274 < (int)128; v0274 += (int)1) {
      ap_float<16, 8> v0275 = v0266[(int)0][v0273][(int)0][v0274];
      ap_float<32, 8> v0276 = (ap_float<32, 8>)v0275;
      v0272[(int)0][v0273][(int)0][v0274] = v0276;
    }
  }
  ap_float<32, 8> v0277[1][12][1];
  for (int v0278 = (int)0; v0278 < (int)12; v0278 += (int)1) {
    v0277[(int)0][v0278][(int)0] = (ap_float<32, 8>)-340282346638528859811704183484516925440.000000;
  }
  ap_float<32, 8> v0279[4];
  for (int v0280 = (int)0; v0280 < (int)12; v0280 += (int)1) {
    for (int v0281 = (int)0; v0281 < (int)4; v0281 += (int)1) {
      v0279[v0281] = (ap_float<32, 8>)-340282346638528859811704183484516925440.000000;
    }
    for (int v0282 = (int)0; v0282 < (int)128; v0282 += (int)1) {
      ap_float<32, 8> v0283 = v0272[(int)0][v0280][(int)0][v0282];
      int v0284 = v0282 % (int)4;
      ap_int<1> v0285 = v0284 < (int)0;
      int v0286 = v0284 + (int)4;
      int v0287 = v0285 ? v0286 : v0284;
      ap_float<32, 8> v0288 = v0279[v0287];
      ap_int<1> v0289 = (float)v0283 > (float)v0288;
      ap_float<32, 8> v0290 = v0289 ? v0283 : v0288;
      ap_int<1> v0291 = false;
      ap_float<32, 8> v0292 = v0291 ? v0288 : v0290;
      int v0293 = v0282 % (int)4;
      ap_int<1> v0294 = v0293 < (int)0;
      int v0295 = v0293 + (int)4;
      int v0296 = v0294 ? v0295 : v0293;
      v0279[v0296] = v0292;
    }
    ap_float<32, 8> v0297 = v0277[(int)0][v0280][(int)0];
    ap_float<32, 8> v0298 = v0279[(int)0];
    ap_float<32, 8> v0299 = v0279[(int)1];
    ap_float<32, 8> v0300 = v0279[(int)2];
    ap_float<32, 8> v0301 = v0279[(int)3];
    ap_int<1> v0302 = (float)v0298 > (float)v0299;
    ap_float<32, 8> v0303 = v0302 ? v0298 : v0299;
    ap_int<1> v0304 = false;
    ap_float<32, 8> v0305 = v0304 ? v0299 : v0303;
    ap_int<1> v0306 = (float)v0300 > (float)v0301;
    ap_float<32, 8> v0307 = v0306 ? v0300 : v0301;
    ap_int<1> v0308 = false;
    ap_float<32, 8> v0309 = v0308 ? v0301 : v0307;
    ap_int<1> v0310 = (float)v0305 > (float)v0309;
    ap_float<32, 8> v0311 = v0310 ? v0305 : v0309;
    ap_int<1> v0312 = false;
    ap_float<32, 8> v0313 = v0312 ? v0309 : v0311;
    ap_int<1> v0314 = (float)v0313 > (float)v0297;
    ap_float<32, 8> v0315 = v0314 ? v0313 : v0297;
    ap_int<1> v0316 = false;
    ap_float<32, 8> v0317 = v0316 ? v0297 : v0315;
    v0277[(int)0][v0280][(int)0] = v0317;
  }
  ap_float<32, 8> v0318[1][12][1][128];
  #pragma HLS bind_storage variable=v0318 type=ram_2p impl=bram latency=2
  for (int v0319 = (int)0; v0319 < (int)12; v0319 += (int)1) {
    for (int v0320 = (int)0; v0320 < (int)128; v0320 += (int)1) {
      ap_float<32, 8> v0321 = v0272[(int)0][v0319][(int)0][v0320];
      ap_float<32, 8> v0322 = v0277[(int)0][v0319][(int)0];
      ap_float<32, 8> v0323 = v0321 - v0322;
      v0318[(int)0][v0319][(int)0][v0320] = v0323;
    }
  }
  ap_float<32, 8> v0324[1][12][1][128];
  #pragma HLS bind_storage variable=v0324 type=ram_2p impl=bram latency=2
  for (int v0325 = (int)0; v0325 < (int)12; v0325 += (int)1) {
    for (int v0326 = (int)0; v0326 < (int)128; v0326 += (int)1) {
      ap_float<32, 8> v0327 = v0318[(int)0][v0325][(int)0][v0326];
      ap_float<32, 8> v0328 = hls::exp((float)v0327);
      v0324[(int)0][v0325][(int)0][v0326] = v0328;
    }
  }
  ap_float<32, 8> v0329[1][12][1];
  for (int v0330 = (int)0; v0330 < (int)12; v0330 += (int)1) {
    v0329[(int)0][v0330][(int)0] = (ap_float<32, 8>)0.000000;
  }
  ap_float<32, 8> v0331[4];
  for (int v0332 = (int)0; v0332 < (int)12; v0332 += (int)1) {
    for (int v0333 = (int)0; v0333 < (int)4; v0333 += (int)1) {
      v0331[v0333] = (ap_float<32, 8>)0.000000;
    }
    for (int v0334 = (int)0; v0334 < (int)128; v0334 += (int)1) {
      ap_float<32, 8> v0335 = v0324[(int)0][v0332][(int)0][v0334];
      int v0336 = v0334 % (int)4;
      ap_int<1> v0337 = v0336 < (int)0;
      int v0338 = v0336 + (int)4;
      int v0339 = v0337 ? v0338 : v0336;
      ap_float<32, 8> v0340 = v0331[v0339];
      ap_float<32, 8> v0341 = v0335 + v0340;
      int v0342 = v0334 % (int)4;
      ap_int<1> v0343 = v0342 < (int)0;
      int v0344 = v0342 + (int)4;
      int v0345 = v0343 ? v0344 : v0342;
      v0331[v0345] = v0341;
    }
    ap_float<32, 8> v0346 = v0329[(int)0][v0332][(int)0];
    ap_float<32, 8> v0347 = v0331[(int)0];
    ap_float<32, 8> v0348 = v0331[(int)1];
    ap_float<32, 8> v0349 = v0331[(int)2];
    ap_float<32, 8> v0350 = v0331[(int)3];
    ap_float<32, 8> v0351 = v0347 + v0348;
    ap_float<32, 8> v0352 = v0349 + v0350;
    ap_float<32, 8> v0353 = v0351 + v0352;
    ap_float<32, 8> v0354 = v0353 + v0346;
    v0329[(int)0][v0332][(int)0] = v0354;
  }
  ap_float<32, 8> v0355[1][12][1][1];
  for (int v0356 = (int)0; v0356 < (int)12; v0356 += (int)1) {
    ap_float<32, 8> v0357 = v0329[(int)0][v0356][(int)0];
    ap_float<32, 8> v0358 = hls::divide((float)(ap_float<32, 8>)1.000000, (float)v0357);
    v0355[(int)0][v0356][(int)0][(int)0] = v0358;
  }
  ap_float<32, 8> v0359[1][1][1][12][1][1][128][1];
  #pragma HLS bind_storage variable=v0359 type=ram_2p impl=bram latency=2
  for (int v0360 = (int)0; v0360 < (int)12; v0360 += (int)1) {
    for (int v0361 = (int)0; v0361 < (int)128; v0361 += (int)1) {
      ap_float<32, 8> v0362 = v0355[(int)0][v0360][(int)0][(int)0];
      v0359[(int)0][(int)0][(int)0][v0360][(int)0][(int)0][v0361][(int)0] = v0362;
    }
  }
  ap_float<32, 8> v0363[1][12][1][128];
  #pragma HLS bind_storage variable=v0363 type=ram_2p impl=bram latency=2
  for (int v0364 = (int)0; v0364 < (int)12; v0364 += (int)1) {
    for (int v0365 = (int)0; v0365 < (int)128; v0365 += (int)1) {
      ap_float<32, 8> v0366 = v0324[(int)0][v0364][(int)0][v0365];
      ap_float<32, 8> v0367 = v0359[(int)0][(int)0][(int)0][v0364][(int)0][(int)0][v0365][(int)0];
      ap_float<32, 8> v0368 = v0366 * v0367;
      v0363[(int)0][v0364][(int)0][v0365] = v0368;
    }
  }
  ap_float<16, 8> v0369[1][12][1][128];
  #pragma HLS bind_storage variable=v0369 type=ram_2p impl=bram latency=2
  for (int v0370 = (int)0; v0370 < (int)12; v0370 += (int)1) {
    for (int v0371 = (int)0; v0371 < (int)128; v0371 += (int)1) {
      ap_float<32, 8> v0372 = v0363[(int)0][v0370][(int)0][v0371];
      ap_float<16, 8> v0373 = (ap_float<16, 8>)v0372;
      v0369[(int)0][v0370][(int)0][v0371] = v0373;
    }
  }
  ap_float<32, 8> v0374[12][1][64];
  #pragma HLS bind_storage variable=v0374 type=ram_2p impl=bram latency=2
  for (int v0375 = (int)0; v0375 < (int)12; v0375 += (int)1) {
    for (int v0376 = (int)0; v0376 < (int)64; v0376 += (int)1) {
      v0374[v0375][(int)0][v0376] = (ap_float<32, 8>)0.000000;
    }
  }
  ap_float<32, 8> v0377[4];
  for (int v0378 = (int)0; v0378 < (int)12; v0378 += (int)1) {
    for (int v0379 = (int)0; v0379 < (int)64; v0379 += (int)1) {
      for (int v0380 = (int)0; v0380 < (int)4; v0380 += (int)1) {
        v0377[v0380] = (ap_float<32, 8>)0.000000;
      }
      for (int v0381 = (int)0; v0381 < (int)128; v0381 += (int)1) {
        int v0382 = v0378 / (int)12;
        int v0383 = v0382 * (int)12;
        ap_int<1> v0384 = v0378 != v0383;
        ap_int<1> v0385 = v0378 < (int)0;
        ap_int<1> v0386 = v0384 & v0385;
        int v0387 = v0382 + (int)-1;
        int v0388 = v0386 ? v0387 : v0382;
        int v0389 = v0378 % (int)12;
        ap_int<1> v0390 = v0389 < (int)0;
        int v0391 = v0389 + (int)12;
        int v0392 = v0390 ? v0391 : v0389;
        ap_float<16, 8> v0393 = v0369[v0388][v0392][(int)0][v0381];
        int v0394 = v0378 / (int)12;
        int v0395 = v0394 * (int)12;
        ap_int<1> v0396 = v0378 != v0395;
        ap_int<1> v0397 = v0378 < (int)0;
        ap_int<1> v0398 = v0396 & v0397;
        int v0399 = v0394 + (int)-1;
        int v0400 = v0398 ? v0399 : v0394;
        int v0401 = v0378 % (int)12;
        ap_int<1> v0402 = v0401 < (int)0;
        int v0403 = v0401 + (int)12;
        int v0404 = v0402 ? v0403 : v0401;
        ap_float<16, 8> v0405 = v0171[v0400][v0404][v0381][v0379];
        int v0406 = v0381 % (int)4;
        ap_int<1> v0407 = v0406 < (int)0;
        int v0408 = v0406 + (int)4;
        int v0409 = v0407 ? v0408 : v0406;
        ap_float<32, 8> v0410 = v0377[v0409];
        ap_float<32, 8> v0411 = (ap_float<32, 8>)v0393;
        ap_float<32, 8> v0412 = (ap_float<32, 8>)v0405;
        ap_float<32, 8> v0413 = v0411 * v0412;
        ap_float<32, 8> v0414 = v0410 + v0413;
        int v0415 = v0381 % (int)4;
        ap_int<1> v0416 = v0415 < (int)0;
        int v0417 = v0415 + (int)4;
        int v0418 = v0416 ? v0417 : v0415;
        v0377[v0418] = v0414;
      }
      ap_float<32, 8> v0419 = v0374[v0378][(int)0][v0379];
      ap_float<32, 8> v0420 = v0377[(int)0];
      ap_float<32, 8> v0421 = v0377[(int)1];
      ap_float<32, 8> v0422 = v0377[(int)2];
      ap_float<32, 8> v0423 = v0377[(int)3];
      ap_float<32, 8> v0424 = v0420 + v0421;
      ap_float<32, 8> v0425 = v0422 + v0423;
      ap_float<32, 8> v0426 = v0424 + v0425;
      ap_float<32, 8> v0427 = v0426 + v0419;
      v0374[v0378][(int)0][v0379] = v0427;
    }
  }
  ap_float<16, 8> v0428[1][12][1][64];
  #pragma HLS bind_storage variable=v0428 type=ram_2p impl=bram latency=2
  for (int v0429 = (int)0; v0429 < (int)12; v0429 += (int)1) {
    for (int v0430 = (int)0; v0430 < (int)64; v0430 += (int)1) {
      ap_float<32, 8> v0431 = v0374[v0429][(int)0][v0430];
      ap_float<16, 8> v0432 = (ap_float<16, 8>)v0431;
      v0428[(int)0][v0429][(int)0][v0430] = v0432;
    }
  }
  ap_float<32, 8> v0433[1][1][768];
  #pragma HLS bind_storage variable=v0433 type=ram_2p impl=bram latency=2
  for (int v0434 = (int)0; v0434 < (int)768; v0434 += (int)1) {
    v0433[(int)0][(int)0][v0434] = (ap_float<32, 8>)0.000000;
  }
  ap_float<32, 8> v0435[4];
  for (int v0436 = (int)0; v0436 < (int)768; v0436 += (int)1) {
    for (int v0437 = (int)0; v0437 < (int)4; v0437 += (int)1) {
      v0435[v0437] = (ap_float<32, 8>)0.000000;
    }
    for (int v0438 = (int)0; v0438 < (int)768; v0438 += (int)1) {
      int v0439 = v0438 / (int)64;
      int v0440 = v0439 * (int)64;
      ap_int<1> v0441 = v0438 != v0440;
      ap_int<1> v0442 = v0438 < (int)0;
      ap_int<1> v0443 = v0441 & v0442;
      int v0444 = v0439 + (int)-1;
      int v0445 = v0443 ? v0444 : v0439;
      int v0446 = v0438 % (int)64;
      ap_int<1> v0447 = v0446 < (int)0;
      int v0448 = v0446 + (int)64;
      int v0449 = v0447 ? v0448 : v0446;
      int v0450 = v0449 / (int)64;
      int v0451 = v0438 % (int)64;
      ap_int<1> v0452 = v0451 < (int)0;
      int v0453 = v0451 + (int)64;
      int v0454 = v0452 ? v0453 : v0451;
      ap_float<16, 8> v0455 = v0428[(int)0][v0445][v0450][v0454];
      ap_float<16, 8> v0456 = arg0013[v0438][v0436];
      int v0457 = v0438 % (int)4;
      ap_int<1> v0458 = v0457 < (int)0;
      int v0459 = v0457 + (int)4;
      int v0460 = v0458 ? v0459 : v0457;
      ap_float<32, 8> v0461 = v0435[v0460];
      ap_float<32, 8> v0462 = (ap_float<32, 8>)v0455;
      ap_float<32, 8> v0463 = (ap_float<32, 8>)v0456;
      ap_float<32, 8> v0464 = v0462 * v0463;
      ap_float<32, 8> v0465 = v0461 + v0464;
      int v0466 = v0438 % (int)4;
      ap_int<1> v0467 = v0466 < (int)0;
      int v0468 = v0466 + (int)4;
      int v0469 = v0467 ? v0468 : v0466;
      v0435[v0469] = v0465;
    }
    ap_float<32, 8> v0470 = v0433[(int)0][(int)0][v0436];
    ap_float<32, 8> v0471 = v0435[(int)0];
    ap_float<32, 8> v0472 = v0435[(int)1];
    ap_float<32, 8> v0473 = v0435[(int)2];
    ap_float<32, 8> v0474 = v0435[(int)3];
    ap_float<32, 8> v0475 = v0471 + v0472;
    ap_float<32, 8> v0476 = v0473 + v0474;
    ap_float<32, 8> v0477 = v0475 + v0476;
    ap_float<32, 8> v0478 = v0477 + v0470;
    v0433[(int)0][(int)0][v0436] = v0478;
  }
  for (int v0479 = (int)0; v0479 < (int)12; v0479 += (int)1) {
    for (int v0480 = (int)0; v0480 < (int)128; v0480 += (int)1) {
      for (int v0481 = (int)0; v0481 < (int)64; v0481 += (int)1) {
        ap_float<16, 8> v0482 = v0163[(int)0][v0479][v0480][v0481];
        arg0006[(int)0][v0479][v0480][v0481] = v0482;
      }
    }
  }
  for (int v0483 = (int)0; v0483 < (int)12; v0483 += (int)1) {
    for (int v0484 = (int)0; v0484 < (int)128; v0484 += (int)1) {
      for (int v0485 = (int)0; v0485 < (int)64; v0485 += (int)1) {
        ap_float<16, 8> v0486 = v0171[(int)0][v0483][v0484][v0485];
        arg0007[(int)0][v0483][v0484][v0485] = v0486;
      }
    }
  }
  for (int v0487 = (int)0; v0487 < (int)768; v0487 += (int)1) {
    ap_float<32, 8> v0488 = v0433[(int)0][(int)0][v0487];
    arg0008[(int)0][(int)0][v0487] = v0488;
  }
  return;
}

