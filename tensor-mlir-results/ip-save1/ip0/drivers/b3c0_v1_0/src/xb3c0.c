// ==============================================================
// Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2025.2 (64-bit)
// Tool Version Limit: 2025.11
// Copyright 1986-2022 Xilinx, Inc. All Rights Reserved.
// Copyright 2022-2025 Advanced Micro Devices, Inc. All Rights Reserved.
// 
// ==============================================================
/***************************** Include Files *********************************/
#include "xb3c0.h"

/************************** Function Implementation *************************/
#ifndef __linux__
int XB3c0_CfgInitialize(XB3c0 *InstancePtr, XB3c0_Config *ConfigPtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(ConfigPtr != NULL);

    InstancePtr->Control_BaseAddress = ConfigPtr->Control_BaseAddress;
    InstancePtr->IsReady = XIL_COMPONENT_IS_READY;

    return XST_SUCCESS;
}
#endif

void XB3c0_Start(XB3c0 *InstancePtr) {
    u32 Data;

    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XB3c0_ReadReg(InstancePtr->Control_BaseAddress, XB3C0_CONTROL_ADDR_AP_CTRL) & 0x80;
    XB3c0_WriteReg(InstancePtr->Control_BaseAddress, XB3C0_CONTROL_ADDR_AP_CTRL, Data | 0x01);
}

u32 XB3c0_IsDone(XB3c0 *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XB3c0_ReadReg(InstancePtr->Control_BaseAddress, XB3C0_CONTROL_ADDR_AP_CTRL);
    return (Data >> 1) & 0x1;
}

u32 XB3c0_IsIdle(XB3c0 *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XB3c0_ReadReg(InstancePtr->Control_BaseAddress, XB3C0_CONTROL_ADDR_AP_CTRL);
    return (Data >> 2) & 0x1;
}

u32 XB3c0_IsReady(XB3c0 *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XB3c0_ReadReg(InstancePtr->Control_BaseAddress, XB3C0_CONTROL_ADDR_AP_CTRL);
    // check ap_start to see if the pcore is ready for next input
    return !(Data & 0x1);
}

void XB3c0_Continue(XB3c0 *InstancePtr) {
    u32 Data;

    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XB3c0_ReadReg(InstancePtr->Control_BaseAddress, XB3C0_CONTROL_ADDR_AP_CTRL) & 0x80;
    XB3c0_WriteReg(InstancePtr->Control_BaseAddress, XB3C0_CONTROL_ADDR_AP_CTRL, Data | 0x10);
}

void XB3c0_EnableAutoRestart(XB3c0 *InstancePtr) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XB3c0_WriteReg(InstancePtr->Control_BaseAddress, XB3C0_CONTROL_ADDR_AP_CTRL, 0x80);
}

void XB3c0_DisableAutoRestart(XB3c0 *InstancePtr) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XB3c0_WriteReg(InstancePtr->Control_BaseAddress, XB3C0_CONTROL_ADDR_AP_CTRL, 0);
}

void XB3c0_Set_hidden_in(XB3c0 *InstancePtr, u64 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XB3c0_WriteReg(InstancePtr->Control_BaseAddress, XB3C0_CONTROL_ADDR_HIDDEN_IN_DATA, (u32)(Data));
    XB3c0_WriteReg(InstancePtr->Control_BaseAddress, XB3C0_CONTROL_ADDR_HIDDEN_IN_DATA + 4, (u32)(Data >> 32));
}

u64 XB3c0_Get_hidden_in(XB3c0 *InstancePtr) {
    u64 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XB3c0_ReadReg(InstancePtr->Control_BaseAddress, XB3C0_CONTROL_ADDR_HIDDEN_IN_DATA);
    Data += (u64)XB3c0_ReadReg(InstancePtr->Control_BaseAddress, XB3C0_CONTROL_ADDR_HIDDEN_IN_DATA + 4) << 32;
    return Data;
}

void XB3c0_Set_cache_position(XB3c0 *InstancePtr, u64 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XB3c0_WriteReg(InstancePtr->Control_BaseAddress, XB3C0_CONTROL_ADDR_CACHE_POSITION_DATA, (u32)(Data));
    XB3c0_WriteReg(InstancePtr->Control_BaseAddress, XB3C0_CONTROL_ADDR_CACHE_POSITION_DATA + 4, (u32)(Data >> 32));
}

u64 XB3c0_Get_cache_position(XB3c0 *InstancePtr) {
    u64 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XB3c0_ReadReg(InstancePtr->Control_BaseAddress, XB3C0_CONTROL_ADDR_CACHE_POSITION_DATA);
    Data += (u64)XB3c0_ReadReg(InstancePtr->Control_BaseAddress, XB3C0_CONTROL_ADDR_CACHE_POSITION_DATA + 4) << 32;
    return Data;
}

void XB3c0_Set_key_cache_in(XB3c0 *InstancePtr, u64 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XB3c0_WriteReg(InstancePtr->Control_BaseAddress, XB3C0_CONTROL_ADDR_KEY_CACHE_IN_DATA, (u32)(Data));
    XB3c0_WriteReg(InstancePtr->Control_BaseAddress, XB3C0_CONTROL_ADDR_KEY_CACHE_IN_DATA + 4, (u32)(Data >> 32));
}

u64 XB3c0_Get_key_cache_in(XB3c0 *InstancePtr) {
    u64 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XB3c0_ReadReg(InstancePtr->Control_BaseAddress, XB3C0_CONTROL_ADDR_KEY_CACHE_IN_DATA);
    Data += (u64)XB3c0_ReadReg(InstancePtr->Control_BaseAddress, XB3C0_CONTROL_ADDR_KEY_CACHE_IN_DATA + 4) << 32;
    return Data;
}

void XB3c0_Set_value_cache_in(XB3c0 *InstancePtr, u64 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XB3c0_WriteReg(InstancePtr->Control_BaseAddress, XB3C0_CONTROL_ADDR_VALUE_CACHE_IN_DATA, (u32)(Data));
    XB3c0_WriteReg(InstancePtr->Control_BaseAddress, XB3C0_CONTROL_ADDR_VALUE_CACHE_IN_DATA + 4, (u32)(Data >> 32));
}

u64 XB3c0_Get_value_cache_in(XB3c0 *InstancePtr) {
    u64 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XB3c0_ReadReg(InstancePtr->Control_BaseAddress, XB3C0_CONTROL_ADDR_VALUE_CACHE_IN_DATA);
    Data += (u64)XB3c0_ReadReg(InstancePtr->Control_BaseAddress, XB3C0_CONTROL_ADDR_VALUE_CACHE_IN_DATA + 4) << 32;
    return Data;
}

void XB3c0_Set_causal_mask(XB3c0 *InstancePtr, u64 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XB3c0_WriteReg(InstancePtr->Control_BaseAddress, XB3C0_CONTROL_ADDR_CAUSAL_MASK_DATA, (u32)(Data));
    XB3c0_WriteReg(InstancePtr->Control_BaseAddress, XB3C0_CONTROL_ADDR_CAUSAL_MASK_DATA + 4, (u32)(Data >> 32));
}

u64 XB3c0_Get_causal_mask(XB3c0 *InstancePtr) {
    u64 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XB3c0_ReadReg(InstancePtr->Control_BaseAddress, XB3C0_CONTROL_ADDR_CAUSAL_MASK_DATA);
    Data += (u64)XB3c0_ReadReg(InstancePtr->Control_BaseAddress, XB3C0_CONTROL_ADDR_CAUSAL_MASK_DATA + 4) << 32;
    return Data;
}

void XB3c0_Set_attention_bias(XB3c0 *InstancePtr, u64 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XB3c0_WriteReg(InstancePtr->Control_BaseAddress, XB3C0_CONTROL_ADDR_ATTENTION_BIAS_DATA, (u32)(Data));
    XB3c0_WriteReg(InstancePtr->Control_BaseAddress, XB3C0_CONTROL_ADDR_ATTENTION_BIAS_DATA + 4, (u32)(Data >> 32));
}

u64 XB3c0_Get_attention_bias(XB3c0 *InstancePtr) {
    u64 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XB3c0_ReadReg(InstancePtr->Control_BaseAddress, XB3C0_CONTROL_ADDR_ATTENTION_BIAS_DATA);
    Data += (u64)XB3c0_ReadReg(InstancePtr->Control_BaseAddress, XB3C0_CONTROL_ADDR_ATTENTION_BIAS_DATA + 4) << 32;
    return Data;
}

void XB3c0_Set_key_cache_out(XB3c0 *InstancePtr, u64 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XB3c0_WriteReg(InstancePtr->Control_BaseAddress, XB3C0_CONTROL_ADDR_KEY_CACHE_OUT_DATA, (u32)(Data));
    XB3c0_WriteReg(InstancePtr->Control_BaseAddress, XB3C0_CONTROL_ADDR_KEY_CACHE_OUT_DATA + 4, (u32)(Data >> 32));
}

u64 XB3c0_Get_key_cache_out(XB3c0 *InstancePtr) {
    u64 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XB3c0_ReadReg(InstancePtr->Control_BaseAddress, XB3C0_CONTROL_ADDR_KEY_CACHE_OUT_DATA);
    Data += (u64)XB3c0_ReadReg(InstancePtr->Control_BaseAddress, XB3C0_CONTROL_ADDR_KEY_CACHE_OUT_DATA + 4) << 32;
    return Data;
}

void XB3c0_Set_value_cache_out(XB3c0 *InstancePtr, u64 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XB3c0_WriteReg(InstancePtr->Control_BaseAddress, XB3C0_CONTROL_ADDR_VALUE_CACHE_OUT_DATA, (u32)(Data));
    XB3c0_WriteReg(InstancePtr->Control_BaseAddress, XB3C0_CONTROL_ADDR_VALUE_CACHE_OUT_DATA + 4, (u32)(Data >> 32));
}

u64 XB3c0_Get_value_cache_out(XB3c0 *InstancePtr) {
    u64 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XB3c0_ReadReg(InstancePtr->Control_BaseAddress, XB3C0_CONTROL_ADDR_VALUE_CACHE_OUT_DATA);
    Data += (u64)XB3c0_ReadReg(InstancePtr->Control_BaseAddress, XB3C0_CONTROL_ADDR_VALUE_CACHE_OUT_DATA + 4) << 32;
    return Data;
}

void XB3c0_Set_c0_ln1_w(XB3c0 *InstancePtr, u64 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XB3c0_WriteReg(InstancePtr->Control_BaseAddress, XB3C0_CONTROL_ADDR_C0_LN1_W_DATA, (u32)(Data));
    XB3c0_WriteReg(InstancePtr->Control_BaseAddress, XB3C0_CONTROL_ADDR_C0_LN1_W_DATA + 4, (u32)(Data >> 32));
}

u64 XB3c0_Get_c0_ln1_w(XB3c0 *InstancePtr) {
    u64 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XB3c0_ReadReg(InstancePtr->Control_BaseAddress, XB3C0_CONTROL_ADDR_C0_LN1_W_DATA);
    Data += (u64)XB3c0_ReadReg(InstancePtr->Control_BaseAddress, XB3C0_CONTROL_ADDR_C0_LN1_W_DATA + 4) << 32;
    return Data;
}

void XB3c0_Set_c0_ln1_b(XB3c0 *InstancePtr, u64 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XB3c0_WriteReg(InstancePtr->Control_BaseAddress, XB3C0_CONTROL_ADDR_C0_LN1_B_DATA, (u32)(Data));
    XB3c0_WriteReg(InstancePtr->Control_BaseAddress, XB3C0_CONTROL_ADDR_C0_LN1_B_DATA + 4, (u32)(Data >> 32));
}

u64 XB3c0_Get_c0_ln1_b(XB3c0 *InstancePtr) {
    u64 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XB3c0_ReadReg(InstancePtr->Control_BaseAddress, XB3C0_CONTROL_ADDR_C0_LN1_B_DATA);
    Data += (u64)XB3c0_ReadReg(InstancePtr->Control_BaseAddress, XB3C0_CONTROL_ADDR_C0_LN1_B_DATA + 4) << 32;
    return Data;
}

void XB3c0_Set_c0_qkv_w(XB3c0 *InstancePtr, u64 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XB3c0_WriteReg(InstancePtr->Control_BaseAddress, XB3C0_CONTROL_ADDR_C0_QKV_W_DATA, (u32)(Data));
    XB3c0_WriteReg(InstancePtr->Control_BaseAddress, XB3C0_CONTROL_ADDR_C0_QKV_W_DATA + 4, (u32)(Data >> 32));
}

u64 XB3c0_Get_c0_qkv_w(XB3c0 *InstancePtr) {
    u64 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XB3c0_ReadReg(InstancePtr->Control_BaseAddress, XB3C0_CONTROL_ADDR_C0_QKV_W_DATA);
    Data += (u64)XB3c0_ReadReg(InstancePtr->Control_BaseAddress, XB3C0_CONTROL_ADDR_C0_QKV_W_DATA + 4) << 32;
    return Data;
}

void XB3c0_Set_c0_qkv_b(XB3c0 *InstancePtr, u64 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XB3c0_WriteReg(InstancePtr->Control_BaseAddress, XB3C0_CONTROL_ADDR_C0_QKV_B_DATA, (u32)(Data));
    XB3c0_WriteReg(InstancePtr->Control_BaseAddress, XB3C0_CONTROL_ADDR_C0_QKV_B_DATA + 4, (u32)(Data >> 32));
}

u64 XB3c0_Get_c0_qkv_b(XB3c0 *InstancePtr) {
    u64 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XB3c0_ReadReg(InstancePtr->Control_BaseAddress, XB3C0_CONTROL_ADDR_C0_QKV_B_DATA);
    Data += (u64)XB3c0_ReadReg(InstancePtr->Control_BaseAddress, XB3C0_CONTROL_ADDR_C0_QKV_B_DATA + 4) << 32;
    return Data;
}

void XB3c0_Set_c0_attn_out_w(XB3c0 *InstancePtr, u64 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XB3c0_WriteReg(InstancePtr->Control_BaseAddress, XB3C0_CONTROL_ADDR_C0_ATTN_OUT_W_DATA, (u32)(Data));
    XB3c0_WriteReg(InstancePtr->Control_BaseAddress, XB3C0_CONTROL_ADDR_C0_ATTN_OUT_W_DATA + 4, (u32)(Data >> 32));
}

u64 XB3c0_Get_c0_attn_out_w(XB3c0 *InstancePtr) {
    u64 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XB3c0_ReadReg(InstancePtr->Control_BaseAddress, XB3C0_CONTROL_ADDR_C0_ATTN_OUT_W_DATA);
    Data += (u64)XB3c0_ReadReg(InstancePtr->Control_BaseAddress, XB3C0_CONTROL_ADDR_C0_ATTN_OUT_W_DATA + 4) << 32;
    return Data;
}

void XB3c0_InterruptGlobalEnable(XB3c0 *InstancePtr) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XB3c0_WriteReg(InstancePtr->Control_BaseAddress, XB3C0_CONTROL_ADDR_GIE, 1);
}

void XB3c0_InterruptGlobalDisable(XB3c0 *InstancePtr) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XB3c0_WriteReg(InstancePtr->Control_BaseAddress, XB3C0_CONTROL_ADDR_GIE, 0);
}

void XB3c0_InterruptEnable(XB3c0 *InstancePtr, u32 Mask) {
    u32 Register;

    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Register =  XB3c0_ReadReg(InstancePtr->Control_BaseAddress, XB3C0_CONTROL_ADDR_IER);
    XB3c0_WriteReg(InstancePtr->Control_BaseAddress, XB3C0_CONTROL_ADDR_IER, Register | Mask);
}

void XB3c0_InterruptDisable(XB3c0 *InstancePtr, u32 Mask) {
    u32 Register;

    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Register =  XB3c0_ReadReg(InstancePtr->Control_BaseAddress, XB3C0_CONTROL_ADDR_IER);
    XB3c0_WriteReg(InstancePtr->Control_BaseAddress, XB3C0_CONTROL_ADDR_IER, Register & (~Mask));
}

void XB3c0_InterruptClear(XB3c0 *InstancePtr, u32 Mask) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XB3c0_WriteReg(InstancePtr->Control_BaseAddress, XB3C0_CONTROL_ADDR_ISR, Mask);
}

u32 XB3c0_InterruptGetEnabled(XB3c0 *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return XB3c0_ReadReg(InstancePtr->Control_BaseAddress, XB3C0_CONTROL_ADDR_IER);
}

u32 XB3c0_InterruptGetStatus(XB3c0 *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return XB3c0_ReadReg(InstancePtr->Control_BaseAddress, XB3C0_CONTROL_ADDR_ISR);
}

