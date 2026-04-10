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
// 0x10 : Data signal of c1_attn_out_b
//        bit 31~0 - c1_attn_out_b[31:0] (Read/Write)
// 0x14 : Data signal of c1_attn_out_b
//        bit 31~0 - c1_attn_out_b[63:32] (Read/Write)
// 0x18 : reserved
// 0x1c : Data signal of c1_ln2_w
//        bit 31~0 - c1_ln2_w[31:0] (Read/Write)
// 0x20 : Data signal of c1_ln2_w
//        bit 31~0 - c1_ln2_w[63:32] (Read/Write)
// 0x24 : reserved
// 0x28 : Data signal of c1_ln2_b
//        bit 31~0 - c1_ln2_b[31:0] (Read/Write)
// 0x2c : Data signal of c1_ln2_b
//        bit 31~0 - c1_ln2_b[63:32] (Read/Write)
// 0x30 : reserved
// 0x34 : Data signal of c1_fc1_w
//        bit 31~0 - c1_fc1_w[31:0] (Read/Write)
// 0x38 : Data signal of c1_fc1_w
//        bit 31~0 - c1_fc1_w[63:32] (Read/Write)
// 0x3c : reserved
// 0x40 : Data signal of c1_fc1_b
//        bit 31~0 - c1_fc1_b[31:0] (Read/Write)
// 0x44 : Data signal of c1_fc1_b
//        bit 31~0 - c1_fc1_b[63:32] (Read/Write)
// 0x48 : reserved
// (SC = Self Clear, COR = Clear on Read, TOW = Toggle on Write, COH = Clear on Handshake)

#define XB3C1_CONTROL_ADDR_AP_CTRL            0x00
#define XB3C1_CONTROL_ADDR_GIE                0x04
#define XB3C1_CONTROL_ADDR_IER                0x08
#define XB3C1_CONTROL_ADDR_ISR                0x0c
#define XB3C1_CONTROL_ADDR_C1_ATTN_OUT_B_DATA 0x10
#define XB3C1_CONTROL_BITS_C1_ATTN_OUT_B_DATA 64
#define XB3C1_CONTROL_ADDR_C1_LN2_W_DATA      0x1c
#define XB3C1_CONTROL_BITS_C1_LN2_W_DATA      64
#define XB3C1_CONTROL_ADDR_C1_LN2_B_DATA      0x28
#define XB3C1_CONTROL_BITS_C1_LN2_B_DATA      64
#define XB3C1_CONTROL_ADDR_C1_FC1_W_DATA      0x34
#define XB3C1_CONTROL_BITS_C1_FC1_W_DATA      64
#define XB3C1_CONTROL_ADDR_C1_FC1_B_DATA      0x40
#define XB3C1_CONTROL_BITS_C1_FC1_B_DATA      64

