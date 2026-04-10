// ==============================================================
// Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2025.2 (64-bit)
// Tool Version Limit: 2025.11
// Copyright 1986-2022 Xilinx, Inc. All Rights Reserved.
// Copyright 2022-2025 Advanced Micro Devices, Inc. All Rights Reserved.
// 
// ==============================================================
#ifndef XB3C1_H
#define XB3C1_H

#ifdef __cplusplus
extern "C" {
#endif

/***************************** Include Files *********************************/
#ifndef __linux__
#include "xil_types.h"
#include "xil_assert.h"
#include "xstatus.h"
#include "xil_io.h"
#else
#include <stdint.h>
#include <assert.h>
#include <dirent.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <unistd.h>
#include <stddef.h>
#endif
#include "xb3c1_hw.h"

/**************************** Type Definitions ******************************/
#ifdef __linux__
typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;
#else
typedef struct {
#ifdef SDT
    char *Name;
#else
    u16 DeviceId;
#endif
    u64 Control_BaseAddress;
} XB3c1_Config;
#endif

typedef struct {
    u64 Control_BaseAddress;
    u32 IsReady;
} XB3c1;

typedef u32 word_type;

/***************** Macros (Inline Functions) Definitions *********************/
#ifndef __linux__
#define XB3c1_WriteReg(BaseAddress, RegOffset, Data) \
    Xil_Out32((BaseAddress) + (RegOffset), (u32)(Data))
#define XB3c1_ReadReg(BaseAddress, RegOffset) \
    Xil_In32((BaseAddress) + (RegOffset))
#else
#define XB3c1_WriteReg(BaseAddress, RegOffset, Data) \
    *(volatile u32*)((BaseAddress) + (RegOffset)) = (u32)(Data)
#define XB3c1_ReadReg(BaseAddress, RegOffset) \
    *(volatile u32*)((BaseAddress) + (RegOffset))

#define Xil_AssertVoid(expr)    assert(expr)
#define Xil_AssertNonvoid(expr) assert(expr)

#define XST_SUCCESS             0
#define XST_DEVICE_NOT_FOUND    2
#define XST_OPEN_DEVICE_FAILED  3
#define XIL_COMPONENT_IS_READY  1
#endif

/************************** Function Prototypes *****************************/
#ifndef __linux__
#ifdef SDT
int XB3c1_Initialize(XB3c1 *InstancePtr, UINTPTR BaseAddress);
XB3c1_Config* XB3c1_LookupConfig(UINTPTR BaseAddress);
#else
int XB3c1_Initialize(XB3c1 *InstancePtr, u16 DeviceId);
XB3c1_Config* XB3c1_LookupConfig(u16 DeviceId);
#endif
int XB3c1_CfgInitialize(XB3c1 *InstancePtr, XB3c1_Config *ConfigPtr);
#else
int XB3c1_Initialize(XB3c1 *InstancePtr, const char* InstanceName);
int XB3c1_Release(XB3c1 *InstancePtr);
#endif

void XB3c1_Start(XB3c1 *InstancePtr);
u32 XB3c1_IsDone(XB3c1 *InstancePtr);
u32 XB3c1_IsIdle(XB3c1 *InstancePtr);
u32 XB3c1_IsReady(XB3c1 *InstancePtr);
void XB3c1_Continue(XB3c1 *InstancePtr);
void XB3c1_EnableAutoRestart(XB3c1 *InstancePtr);
void XB3c1_DisableAutoRestart(XB3c1 *InstancePtr);

void XB3c1_Set_c1_attn_out_b(XB3c1 *InstancePtr, u64 Data);
u64 XB3c1_Get_c1_attn_out_b(XB3c1 *InstancePtr);
void XB3c1_Set_c1_ln2_w(XB3c1 *InstancePtr, u64 Data);
u64 XB3c1_Get_c1_ln2_w(XB3c1 *InstancePtr);
void XB3c1_Set_c1_ln2_b(XB3c1 *InstancePtr, u64 Data);
u64 XB3c1_Get_c1_ln2_b(XB3c1 *InstancePtr);
void XB3c1_Set_c1_fc1_w(XB3c1 *InstancePtr, u64 Data);
u64 XB3c1_Get_c1_fc1_w(XB3c1 *InstancePtr);
void XB3c1_Set_c1_fc1_b(XB3c1 *InstancePtr, u64 Data);
u64 XB3c1_Get_c1_fc1_b(XB3c1 *InstancePtr);

void XB3c1_InterruptGlobalEnable(XB3c1 *InstancePtr);
void XB3c1_InterruptGlobalDisable(XB3c1 *InstancePtr);
void XB3c1_InterruptEnable(XB3c1 *InstancePtr, u32 Mask);
void XB3c1_InterruptDisable(XB3c1 *InstancePtr, u32 Mask);
void XB3c1_InterruptClear(XB3c1 *InstancePtr, u32 Mask);
u32 XB3c1_InterruptGetEnabled(XB3c1 *InstancePtr);
u32 XB3c1_InterruptGetStatus(XB3c1 *InstancePtr);

#ifdef __cplusplus
}
#endif

#endif
