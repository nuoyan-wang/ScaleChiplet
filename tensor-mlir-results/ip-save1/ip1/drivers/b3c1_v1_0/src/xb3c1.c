// ==============================================================
// Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2025.2 (64-bit)
// Tool Version Limit: 2025.11
// Copyright 1986-2022 Xilinx, Inc. All Rights Reserved.
// Copyright 2022-2025 Advanced Micro Devices, Inc. All Rights Reserved.
// 
// ==============================================================
/***************************** Include Files *********************************/
#include "xb3c1.h"

/************************** Function Implementation *************************/
#ifndef __linux__
int XB3c1_CfgInitialize(XB3c1 *InstancePtr, XB3c1_Config *ConfigPtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(ConfigPtr != NULL);

    InstancePtr->Control_BaseAddress = ConfigPtr->Control_BaseAddress;
    InstancePtr->IsReady = XIL_COMPONENT_IS_READY;

    return XST_SUCCESS;
}
#endif

void XB3c1_Start(XB3c1 *InstancePtr) {
    u32 Data;

    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XB3c1_ReadReg(InstancePtr->Control_BaseAddress, XB3C1_CONTROL_ADDR_AP_CTRL) & 0x80;
    XB3c1_WriteReg(InstancePtr->Control_BaseAddress, XB3C1_CONTROL_ADDR_AP_CTRL, Data | 0x01);
}

u32 XB3c1_IsDone(XB3c1 *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XB3c1_ReadReg(InstancePtr->Control_BaseAddress, XB3C1_CONTROL_ADDR_AP_CTRL);
    return (Data >> 1) & 0x1;
}

u32 XB3c1_IsIdle(XB3c1 *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XB3c1_ReadReg(InstancePtr->Control_BaseAddress, XB3C1_CONTROL_ADDR_AP_CTRL);
    return (Data >> 2) & 0x1;
}

u32 XB3c1_IsReady(XB3c1 *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XB3c1_ReadReg(InstancePtr->Control_BaseAddress, XB3C1_CONTROL_ADDR_AP_CTRL);
    // check ap_start to see if the pcore is ready for next input
    return !(Data & 0x1);
}

void XB3c1_Continue(XB3c1 *InstancePtr) {
    u32 Data;

    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XB3c1_ReadReg(InstancePtr->Control_BaseAddress, XB3C1_CONTROL_ADDR_AP_CTRL) & 0x80;
    XB3c1_WriteReg(InstancePtr->Control_BaseAddress, XB3C1_CONTROL_ADDR_AP_CTRL, Data | 0x10);
}

void XB3c1_EnableAutoRestart(XB3c1 *InstancePtr) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XB3c1_WriteReg(InstancePtr->Control_BaseAddress, XB3C1_CONTROL_ADDR_AP_CTRL, 0x80);
}

void XB3c1_DisableAutoRestart(XB3c1 *InstancePtr) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XB3c1_WriteReg(InstancePtr->Control_BaseAddress, XB3C1_CONTROL_ADDR_AP_CTRL, 0);
}

void XB3c1_Set_c1_attn_out_b(XB3c1 *InstancePtr, u64 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XB3c1_WriteReg(InstancePtr->Control_BaseAddress, XB3C1_CONTROL_ADDR_C1_ATTN_OUT_B_DATA, (u32)(Data));
    XB3c1_WriteReg(InstancePtr->Control_BaseAddress, XB3C1_CONTROL_ADDR_C1_ATTN_OUT_B_DATA + 4, (u32)(Data >> 32));
}

u64 XB3c1_Get_c1_attn_out_b(XB3c1 *InstancePtr) {
    u64 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XB3c1_ReadReg(InstancePtr->Control_BaseAddress, XB3C1_CONTROL_ADDR_C1_ATTN_OUT_B_DATA);
    Data += (u64)XB3c1_ReadReg(InstancePtr->Control_BaseAddress, XB3C1_CONTROL_ADDR_C1_ATTN_OUT_B_DATA + 4) << 32;
    return Data;
}

void XB3c1_Set_c1_ln2_w(XB3c1 *InstancePtr, u64 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XB3c1_WriteReg(InstancePtr->Control_BaseAddress, XB3C1_CONTROL_ADDR_C1_LN2_W_DATA, (u32)(Data));
    XB3c1_WriteReg(InstancePtr->Control_BaseAddress, XB3C1_CONTROL_ADDR_C1_LN2_W_DATA + 4, (u32)(Data >> 32));
}

u64 XB3c1_Get_c1_ln2_w(XB3c1 *InstancePtr) {
    u64 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XB3c1_ReadReg(InstancePtr->Control_BaseAddress, XB3C1_CONTROL_ADDR_C1_LN2_W_DATA);
    Data += (u64)XB3c1_ReadReg(InstancePtr->Control_BaseAddress, XB3C1_CONTROL_ADDR_C1_LN2_W_DATA + 4) << 32;
    return Data;
}

void XB3c1_Set_c1_ln2_b(XB3c1 *InstancePtr, u64 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XB3c1_WriteReg(InstancePtr->Control_BaseAddress, XB3C1_CONTROL_ADDR_C1_LN2_B_DATA, (u32)(Data));
    XB3c1_WriteReg(InstancePtr->Control_BaseAddress, XB3C1_CONTROL_ADDR_C1_LN2_B_DATA + 4, (u32)(Data >> 32));
}

u64 XB3c1_Get_c1_ln2_b(XB3c1 *InstancePtr) {
    u64 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XB3c1_ReadReg(InstancePtr->Control_BaseAddress, XB3C1_CONTROL_ADDR_C1_LN2_B_DATA);
    Data += (u64)XB3c1_ReadReg(InstancePtr->Control_BaseAddress, XB3C1_CONTROL_ADDR_C1_LN2_B_DATA + 4) << 32;
    return Data;
}

void XB3c1_Set_c1_fc1_w(XB3c1 *InstancePtr, u64 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XB3c1_WriteReg(InstancePtr->Control_BaseAddress, XB3C1_CONTROL_ADDR_C1_FC1_W_DATA, (u32)(Data));
    XB3c1_WriteReg(InstancePtr->Control_BaseAddress, XB3C1_CONTROL_ADDR_C1_FC1_W_DATA + 4, (u32)(Data >> 32));
}

u64 XB3c1_Get_c1_fc1_w(XB3c1 *InstancePtr) {
    u64 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XB3c1_ReadReg(InstancePtr->Control_BaseAddress, XB3C1_CONTROL_ADDR_C1_FC1_W_DATA);
    Data += (u64)XB3c1_ReadReg(InstancePtr->Control_BaseAddress, XB3C1_CONTROL_ADDR_C1_FC1_W_DATA + 4) << 32;
    return Data;
}

void XB3c1_Set_c1_fc1_b(XB3c1 *InstancePtr, u64 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XB3c1_WriteReg(InstancePtr->Control_BaseAddress, XB3C1_CONTROL_ADDR_C1_FC1_B_DATA, (u32)(Data));
    XB3c1_WriteReg(InstancePtr->Control_BaseAddress, XB3C1_CONTROL_ADDR_C1_FC1_B_DATA + 4, (u32)(Data >> 32));
}

u64 XB3c1_Get_c1_fc1_b(XB3c1 *InstancePtr) {
    u64 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XB3c1_ReadReg(InstancePtr->Control_BaseAddress, XB3C1_CONTROL_ADDR_C1_FC1_B_DATA);
    Data += (u64)XB3c1_ReadReg(InstancePtr->Control_BaseAddress, XB3C1_CONTROL_ADDR_C1_FC1_B_DATA + 4) << 32;
    return Data;
}

void XB3c1_InterruptGlobalEnable(XB3c1 *InstancePtr) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XB3c1_WriteReg(InstancePtr->Control_BaseAddress, XB3C1_CONTROL_ADDR_GIE, 1);
}

void XB3c1_InterruptGlobalDisable(XB3c1 *InstancePtr) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XB3c1_WriteReg(InstancePtr->Control_BaseAddress, XB3C1_CONTROL_ADDR_GIE, 0);
}

void XB3c1_InterruptEnable(XB3c1 *InstancePtr, u32 Mask) {
    u32 Register;

    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Register =  XB3c1_ReadReg(InstancePtr->Control_BaseAddress, XB3C1_CONTROL_ADDR_IER);
    XB3c1_WriteReg(InstancePtr->Control_BaseAddress, XB3C1_CONTROL_ADDR_IER, Register | Mask);
}

void XB3c1_InterruptDisable(XB3c1 *InstancePtr, u32 Mask) {
    u32 Register;

    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Register =  XB3c1_ReadReg(InstancePtr->Control_BaseAddress, XB3C1_CONTROL_ADDR_IER);
    XB3c1_WriteReg(InstancePtr->Control_BaseAddress, XB3C1_CONTROL_ADDR_IER, Register & (~Mask));
}

void XB3c1_InterruptClear(XB3c1 *InstancePtr, u32 Mask) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XB3c1_WriteReg(InstancePtr->Control_BaseAddress, XB3C1_CONTROL_ADDR_ISR, Mask);
}

u32 XB3c1_InterruptGetEnabled(XB3c1 *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return XB3c1_ReadReg(InstancePtr->Control_BaseAddress, XB3C1_CONTROL_ADDR_IER);
}

u32 XB3c1_InterruptGetStatus(XB3c1 *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return XB3c1_ReadReg(InstancePtr->Control_BaseAddress, XB3C1_CONTROL_ADDR_ISR);
}

