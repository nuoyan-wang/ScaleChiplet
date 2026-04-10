// ==============================================================
// Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2025.2 (64-bit)
// Tool Version Limit: 2025.11
// Copyright 1986-2022 Xilinx, Inc. All Rights Reserved.
// Copyright 2022-2025 Advanced Micro Devices, Inc. All Rights Reserved.
// 
// ==============================================================
/***************************** Include Files *********************************/
#include "xb3c2.h"

/************************** Function Implementation *************************/
#ifndef __linux__
int XB3c2_CfgInitialize(XB3c2 *InstancePtr, XB3c2_Config *ConfigPtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(ConfigPtr != NULL);

    InstancePtr->Control_BaseAddress = ConfigPtr->Control_BaseAddress;
    InstancePtr->IsReady = XIL_COMPONENT_IS_READY;

    return XST_SUCCESS;
}
#endif

void XB3c2_Start(XB3c2 *InstancePtr) {
    u32 Data;

    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XB3c2_ReadReg(InstancePtr->Control_BaseAddress, XB3C2_CONTROL_ADDR_AP_CTRL) & 0x80;
    XB3c2_WriteReg(InstancePtr->Control_BaseAddress, XB3C2_CONTROL_ADDR_AP_CTRL, Data | 0x01);
}

u32 XB3c2_IsDone(XB3c2 *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XB3c2_ReadReg(InstancePtr->Control_BaseAddress, XB3C2_CONTROL_ADDR_AP_CTRL);
    return (Data >> 1) & 0x1;
}

u32 XB3c2_IsIdle(XB3c2 *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XB3c2_ReadReg(InstancePtr->Control_BaseAddress, XB3C2_CONTROL_ADDR_AP_CTRL);
    return (Data >> 2) & 0x1;
}

u32 XB3c2_IsReady(XB3c2 *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XB3c2_ReadReg(InstancePtr->Control_BaseAddress, XB3C2_CONTROL_ADDR_AP_CTRL);
    // check ap_start to see if the pcore is ready for next input
    return !(Data & 0x1);
}

void XB3c2_Continue(XB3c2 *InstancePtr) {
    u32 Data;

    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XB3c2_ReadReg(InstancePtr->Control_BaseAddress, XB3C2_CONTROL_ADDR_AP_CTRL) & 0x80;
    XB3c2_WriteReg(InstancePtr->Control_BaseAddress, XB3C2_CONTROL_ADDR_AP_CTRL, Data | 0x10);
}

void XB3c2_EnableAutoRestart(XB3c2 *InstancePtr) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XB3c2_WriteReg(InstancePtr->Control_BaseAddress, XB3C2_CONTROL_ADDR_AP_CTRL, 0x80);
}

void XB3c2_DisableAutoRestart(XB3c2 *InstancePtr) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XB3c2_WriteReg(InstancePtr->Control_BaseAddress, XB3C2_CONTROL_ADDR_AP_CTRL, 0);
}

void XB3c2_Set_hidden_out(XB3c2 *InstancePtr, u64 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XB3c2_WriteReg(InstancePtr->Control_BaseAddress, XB3C2_CONTROL_ADDR_HIDDEN_OUT_DATA, (u32)(Data));
    XB3c2_WriteReg(InstancePtr->Control_BaseAddress, XB3C2_CONTROL_ADDR_HIDDEN_OUT_DATA + 4, (u32)(Data >> 32));
}

u64 XB3c2_Get_hidden_out(XB3c2 *InstancePtr) {
    u64 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XB3c2_ReadReg(InstancePtr->Control_BaseAddress, XB3C2_CONTROL_ADDR_HIDDEN_OUT_DATA);
    Data += (u64)XB3c2_ReadReg(InstancePtr->Control_BaseAddress, XB3C2_CONTROL_ADDR_HIDDEN_OUT_DATA + 4) << 32;
    return Data;
}

void XB3c2_Set_c2_fc2_w(XB3c2 *InstancePtr, u64 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XB3c2_WriteReg(InstancePtr->Control_BaseAddress, XB3C2_CONTROL_ADDR_C2_FC2_W_DATA, (u32)(Data));
    XB3c2_WriteReg(InstancePtr->Control_BaseAddress, XB3C2_CONTROL_ADDR_C2_FC2_W_DATA + 4, (u32)(Data >> 32));
}

u64 XB3c2_Get_c2_fc2_w(XB3c2 *InstancePtr) {
    u64 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XB3c2_ReadReg(InstancePtr->Control_BaseAddress, XB3C2_CONTROL_ADDR_C2_FC2_W_DATA);
    Data += (u64)XB3c2_ReadReg(InstancePtr->Control_BaseAddress, XB3C2_CONTROL_ADDR_C2_FC2_W_DATA + 4) << 32;
    return Data;
}

void XB3c2_Set_c2_fc2_b(XB3c2 *InstancePtr, u64 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XB3c2_WriteReg(InstancePtr->Control_BaseAddress, XB3C2_CONTROL_ADDR_C2_FC2_B_DATA, (u32)(Data));
    XB3c2_WriteReg(InstancePtr->Control_BaseAddress, XB3C2_CONTROL_ADDR_C2_FC2_B_DATA + 4, (u32)(Data >> 32));
}

u64 XB3c2_Get_c2_fc2_b(XB3c2 *InstancePtr) {
    u64 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XB3c2_ReadReg(InstancePtr->Control_BaseAddress, XB3C2_CONTROL_ADDR_C2_FC2_B_DATA);
    Data += (u64)XB3c2_ReadReg(InstancePtr->Control_BaseAddress, XB3C2_CONTROL_ADDR_C2_FC2_B_DATA + 4) << 32;
    return Data;
}

void XB3c2_InterruptGlobalEnable(XB3c2 *InstancePtr) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XB3c2_WriteReg(InstancePtr->Control_BaseAddress, XB3C2_CONTROL_ADDR_GIE, 1);
}

void XB3c2_InterruptGlobalDisable(XB3c2 *InstancePtr) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XB3c2_WriteReg(InstancePtr->Control_BaseAddress, XB3C2_CONTROL_ADDR_GIE, 0);
}

void XB3c2_InterruptEnable(XB3c2 *InstancePtr, u32 Mask) {
    u32 Register;

    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Register =  XB3c2_ReadReg(InstancePtr->Control_BaseAddress, XB3C2_CONTROL_ADDR_IER);
    XB3c2_WriteReg(InstancePtr->Control_BaseAddress, XB3C2_CONTROL_ADDR_IER, Register | Mask);
}

void XB3c2_InterruptDisable(XB3c2 *InstancePtr, u32 Mask) {
    u32 Register;

    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Register =  XB3c2_ReadReg(InstancePtr->Control_BaseAddress, XB3C2_CONTROL_ADDR_IER);
    XB3c2_WriteReg(InstancePtr->Control_BaseAddress, XB3C2_CONTROL_ADDR_IER, Register & (~Mask));
}

void XB3c2_InterruptClear(XB3c2 *InstancePtr, u32 Mask) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XB3c2_WriteReg(InstancePtr->Control_BaseAddress, XB3C2_CONTROL_ADDR_ISR, Mask);
}

u32 XB3c2_InterruptGetEnabled(XB3c2 *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return XB3c2_ReadReg(InstancePtr->Control_BaseAddress, XB3C2_CONTROL_ADDR_IER);
}

u32 XB3c2_InterruptGetStatus(XB3c2 *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return XB3c2_ReadReg(InstancePtr->Control_BaseAddress, XB3C2_CONTROL_ADDR_ISR);
}

