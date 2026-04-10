// ==============================================================
// Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2025.2 (64-bit)
// Tool Version Limit: 2025.11
// Copyright 1986-2022 Xilinx, Inc. All Rights Reserved.
// Copyright 2022-2025 Advanced Micro Devices, Inc. All Rights Reserved.
// 
// ==============================================================
#ifndef XB3C2_H
#define XB3C2_H

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
#include "xb3c2_hw.h"

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
} XB3c2_Config;
#endif

typedef struct {
    u64 Control_BaseAddress;
    u32 IsReady;
} XB3c2;

typedef u32 word_type;

/***************** Macros (Inline Functions) Definitions *********************/
#ifndef __linux__
#define XB3c2_WriteReg(BaseAddress, RegOffset, Data) \
    Xil_Out32((BaseAddress) + (RegOffset), (u32)(Data))
#define XB3c2_ReadReg(BaseAddress, RegOffset) \
    Xil_In32((BaseAddress) + (RegOffset))
#else
#define XB3c2_WriteReg(BaseAddress, RegOffset, Data) \
    *(volatile u32*)((BaseAddress) + (RegOffset)) = (u32)(Data)
#define XB3c2_ReadReg(BaseAddress, RegOffset) \
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
int XB3c2_Initialize(XB3c2 *InstancePtr, UINTPTR BaseAddress);
XB3c2_Config* XB3c2_LookupConfig(UINTPTR BaseAddress);
#else
int XB3c2_Initialize(XB3c2 *InstancePtr, u16 DeviceId);
XB3c2_Config* XB3c2_LookupConfig(u16 DeviceId);
#endif
int XB3c2_CfgInitialize(XB3c2 *InstancePtr, XB3c2_Config *ConfigPtr);
#else
int XB3c2_Initialize(XB3c2 *InstancePtr, const char* InstanceName);
int XB3c2_Release(XB3c2 *InstancePtr);
#endif

void XB3c2_Start(XB3c2 *InstancePtr);
u32 XB3c2_IsDone(XB3c2 *InstancePtr);
u32 XB3c2_IsIdle(XB3c2 *InstancePtr);
u32 XB3c2_IsReady(XB3c2 *InstancePtr);
void XB3c2_Continue(XB3c2 *InstancePtr);
void XB3c2_EnableAutoRestart(XB3c2 *InstancePtr);
void XB3c2_DisableAutoRestart(XB3c2 *InstancePtr);

void XB3c2_Set_hidden_out(XB3c2 *InstancePtr, u64 Data);
u64 XB3c2_Get_hidden_out(XB3c2 *InstancePtr);
void XB3c2_Set_c2_fc2_w(XB3c2 *InstancePtr, u64 Data);
u64 XB3c2_Get_c2_fc2_w(XB3c2 *InstancePtr);
void XB3c2_Set_c2_fc2_b(XB3c2 *InstancePtr, u64 Data);
u64 XB3c2_Get_c2_fc2_b(XB3c2 *InstancePtr);

void XB3c2_InterruptGlobalEnable(XB3c2 *InstancePtr);
void XB3c2_InterruptGlobalDisable(XB3c2 *InstancePtr);
void XB3c2_InterruptEnable(XB3c2 *InstancePtr, u32 Mask);
void XB3c2_InterruptDisable(XB3c2 *InstancePtr, u32 Mask);
void XB3c2_InterruptClear(XB3c2 *InstancePtr, u32 Mask);
u32 XB3c2_InterruptGetEnabled(XB3c2 *InstancePtr);
u32 XB3c2_InterruptGetStatus(XB3c2 *InstancePtr);

#ifdef __cplusplus
}
#endif

#endif
