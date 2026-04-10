// ==============================================================
// Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2025.2 (64-bit)
// Tool Version Limit: 2025.11
// Copyright 1986-2022 Xilinx, Inc. All Rights Reserved.
// Copyright 2022-2025 Advanced Micro Devices, Inc. All Rights Reserved.
// 
// ==============================================================
// control
// 0x00 : Control signals
//        bit 0  - ap_start (Read/Write/COH)
//        bit 1  - ap_done (Read)
//        bit 2  - ap_idle (Read)
//        bit 3  - ap_ready (Read/COR)
//        bit 4  - ap_continue (Read/Write/SC)
//        bit 7  - auto_restart (Read/Write)
//        bit 9  - interrupt (Read)
//        others - reserved
// 0x04 : Global Interrupt Enable Register
//        bit 0  - Global Interrupt Enable (Read/Write)
//        others - reserved
// 0x08 : IP Interrupt Enable Register (Read/Write)
//        bit 0 - enable ap_done interrupt (Read/Write)
//        bit 1 - enable ap_ready interrupt (Read/Write)
//        others - reserved
// 0x0c : IP Interrupt Status Register (Read/TOW)
//        bit 0 - ap_done (Read/TOW)
//        bit 1 - ap_ready (Read/TOW)
//        others - reserved
// 0x10 : Data signal of hidden_in
//        bit 31~0 - hidden_in[31:0] (Read/Write)
// 0x14 : Data signal of hidden_in
//        bit 31~0 - hidden_in[63:32] (Read/Write)
// 0x18 : reserved
// 0x1c : Data signal of cache_position
//        bit 31~0 - cache_position[31:0] (Read/Write)
// 0x20 : Data signal of cache_position
//        bit 31~0 - cache_position[63:32] (Read/Write)
// 0x24 : reserved
// 0x28 : Data signal of key_cache_in
//        bit 31~0 - key_cache_in[31:0] (Read/Write)
// 0x2c : Data signal of key_cache_in
//        bit 31~0 - key_cache_in[63:32] (Read/Write)
// 0x30 : reserved
// 0x34 : Data signal of value_cache_in
//        bit 31~0 - value_cache_in[31:0] (Read/Write)
// 0x38 : Data signal of value_cache_in
//        bit 31~0 - value_cache_in[63:32] (Read/Write)
// 0x3c : reserved
// 0x40 : Data signal of causal_mask
//        bit 31~0 - causal_mask[31:0] (Read/Write)
// 0x44 : Data signal of causal_mask
//        bit 31~0 - causal_mask[63:32] (Read/Write)
// 0x48 : reserved
// 0x4c : Data signal of attention_bias
//        bit 31~0 - attention_bias[31:0] (Read/Write)
// 0x50 : Data signal of attention_bias
//        bit 31~0 - attention_bias[63:32] (Read/Write)
// 0x54 : reserved
// 0x58 : Data signal of key_cache_out
//        bit 31~0 - key_cache_out[31:0] (Read/Write)
// 0x5c : Data signal of key_cache_out
//        bit 31~0 - key_cache_out[63:32] (Read/Write)
// 0x60 : reserved
// 0x64 : Data signal of value_cache_out
//        bit 31~0 - value_cache_out[31:0] (Read/Write)
// 0x68 : Data signal of value_cache_out
//        bit 31~0 - value_cache_out[63:32] (Read/Write)
// 0x6c : reserved
// 0x70 : Data signal of c0_ln1_w
//        bit 31~0 - c0_ln1_w[31:0] (Read/Write)
// 0x74 : Data signal of c0_ln1_w
//        bit 31~0 - c0_ln1_w[63:32] (Read/Write)
// 0x78 : reserved
// 0x7c : Data signal of c0_ln1_b
//        bit 31~0 - c0_ln1_b[31:0] (Read/Write)
// 0x80 : Data signal of c0_ln1_b
//        bit 31~0 - c0_ln1_b[63:32] (Read/Write)
// 0x84 : reserved
// 0x88 : Data signal of c0_qkv_w
//        bit 31~0 - c0_qkv_w[31:0] (Read/Write)
// 0x8c : Data signal of c0_qkv_w
//        bit 31~0 - c0_qkv_w[63:32] (Read/Write)
// 0x90 : reserved
// 0x94 : Data signal of c0_qkv_b
//        bit 31~0 - c0_qkv_b[31:0] (Read/Write)
// 0x98 : Data signal of c0_qkv_b
//        bit 31~0 - c0_qkv_b[63:32] (Read/Write)
// 0x9c : reserved
// 0xa0 : Data signal of c0_attn_out_w
//        bit 31~0 - c0_attn_out_w[31:0] (Read/Write)
// 0xa4 : Data signal of c0_attn_out_w
//        bit 31~0 - c0_attn_out_w[63:32] (Read/Write)
// 0xa8 : reserved
// (SC = Self Clear, COR = Clear on Read, TOW = Toggle on Write, COH = Clear on Handshake)

#define XB3C0_CONTROL_ADDR_AP_CTRL              0x00
#define XB3C0_CONTROL_ADDR_GIE                  0x04
#define XB3C0_CONTROL_ADDR_IER                  0x08
#define XB3C0_CONTROL_ADDR_ISR                  0x0c
#define XB3C0_CONTROL_ADDR_HIDDEN_IN_DATA       0x10
#define XB3C0_CONTROL_BITS_HIDDEN_IN_DATA       64
#define XB3C0_CONTROL_ADDR_CACHE_POSITION_DATA  0x1c
#define XB3C0_CONTROL_BITS_CACHE_POSITION_DATA  64
#define XB3C0_CONTROL_ADDR_KEY_CACHE_IN_DATA    0x28
#define XB3C0_CONTROL_BITS_KEY_CACHE_IN_DATA    64
#define XB3C0_CONTROL_ADDR_VALUE_CACHE_IN_DATA  0x34
#define XB3C0_CONTROL_BITS_VALUE_CACHE_IN_DATA  64
#define XB3C0_CONTROL_ADDR_CAUSAL_MASK_DATA     0x40
#define XB3C0_CONTROL_BITS_CAUSAL_MASK_DATA     64
#define XB3C0_CONTROL_ADDR_ATTENTION_BIAS_DATA  0x4c
#define XB3C0_CONTROL_BITS_ATTENTION_BIAS_DATA  64
#define XB3C0_CONTROL_ADDR_KEY_CACHE_OUT_DATA   0x58
#define XB3C0_CONTROL_BITS_KEY_CACHE_OUT_DATA   64
#define XB3C0_CONTROL_ADDR_VALUE_CACHE_OUT_DATA 0x64
#define XB3C0_CONTROL_BITS_VALUE_CACHE_OUT_DATA 64
#define XB3C0_CONTROL_ADDR_C0_LN1_W_DATA        0x70
#define XB3C0_CONTROL_BITS_C0_LN1_W_DATA        64
#define XB3C0_CONTROL_ADDR_C0_LN1_B_DATA        0x7c
#define XB3C0_CONTROL_BITS_C0_LN1_B_DATA        64
#define XB3C0_CONTROL_ADDR_C0_QKV_W_DATA        0x88
#define XB3C0_CONTROL_BITS_C0_QKV_W_DATA        64
#define XB3C0_CONTROL_ADDR_C0_QKV_B_DATA        0x94
#define XB3C0_CONTROL_BITS_C0_QKV_B_DATA        64
#define XB3C0_CONTROL_ADDR_C0_ATTN_OUT_W_DATA   0xa0
#define XB3C0_CONTROL_BITS_C0_ATTN_OUT_W_DATA   64

