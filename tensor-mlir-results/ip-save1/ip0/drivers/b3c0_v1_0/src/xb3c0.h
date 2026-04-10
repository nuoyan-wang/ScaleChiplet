// ==============================================================
// Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2025.2 (64-bit)
// Tool Version Limit: 2025.11
// Copyright 1986-2022 Xilinx, Inc. All Rights Reserved.
// Copyright 2022-2025 Advanced Micro Devices, Inc. All Rights Reserved.
// 
// ==============================================================
#ifndef XB3C0_H
#define XB3C0_H

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
#include "xb3c0_hw.h"

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
} XB3c0_Config;
#endif

typedef struct {
    u64 Control_BaseAddress;
    u32 IsReady;
} XB3c0;

typedef u32 word_type;

/***************** Macros (Inline Functions) Definitions *********************/
#ifndef __linux__
#define XB3c0_WriteReg(BaseAddress, RegOffset, Data) \
    Xil_Out32((BaseAddress) + (RegOffset), (u32)(Data))
#define XB3c0_ReadReg(BaseAddress, RegOffset) \
    Xil_In32((BaseAddress) + (RegOffset))
#else
#define XB3c0_WriteReg(BaseAddress, RegOffset, Data) \
    *(volatile u32*)((BaseAddress) + (RegOffset)) = (u32)(Data)
#define XB3c0_ReadReg(BaseAddress, RegOffset) \
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
int XB3c0_Initialize(XB3c0 *InstancePtr, UINTPTR BaseAddress);
XB3c0_Config* XB3c0_LookupConfig(UINTPTR BaseAddress);
#else
int XB3c0_Initialize(XB3c0 *InstancePtr, u16 DeviceId);
XB3c0_Config* XB3c0_LookupConfig(u16 DeviceId);
#endif
int XB3c0_CfgInitialize(XB3c0 *InstancePtr, XB3c0_Config *ConfigPtr);
#else
int XB3c0_Initialize(XB3c0 *InstancePtr, const char* InstanceName);
int XB3c0_Release(XB3c0 *InstancePtr);
#endif

void XB3c0_Start(XB3c0 *InstancePtr);
u32 XB3c0_IsDone(XB3c0 *InstancePtr);
u32 XB3c0_IsIdle(XB3c0 *InstancePtr);
u32 XB3c0_IsReady(XB3c0 *InstancePtr);
void XB3c0_Continue(XB3c0 *InstancePtr);
void XB3c0_EnableAutoRestart(XB3c0 *InstancePtr);
void XB3c0_DisableAutoRestart(XB3c0 *InstancePtr);

void XB3c0_Set_hidden_in(XB3c0 *InstancePtr, u64 Data);
u64 XB3c0_Get_hidden_in(XB3c0 *InstancePtr);
void XB3c0_Set_cache_position(XB3c0 *InstancePtr, u64 Data);
u64 XB3c0_Get_cache_position(XB3c0 *InstancePtr);
void XB3c0_Set_key_cache_in(XB3c0 *InstancePtr, u64 Data);
u64 XB3c0_Get_key_cache_in(XB3c0 *InstancePtr);
void XB3c0_Set_value_cache_in(XB3c0 *InstancePtr, u64 Data);
u64 XB3c0_Get_value_cache_in(XB3c0 *InstancePtr);
void XB3c0_Set_causal_mask(XB3c0 *InstancePtr, u64 Data);
u64 XB3c0_Get_causal_mask(XB3c0 *InstancePtr);
void XB3c0_Set_attention_bias(XB3c0 *InstancePtr, u64 Data);
u64 XB3c0_Get_attention_bias(XB3c0 *InstancePtr);
void XB3c0_Set_key_cache_out(XB3c0 *InstancePtr, u64 Data);
u64 XB3c0_Get_key_cache_out(XB3c0 *InstancePtr);
void XB3c0_Set_value_cache_out(XB3c0 *InstancePtr, u64 Data);
u64 XB3c0_Get_value_cache_out(XB3c0 *InstancePtr);
void XB3c0_Set_c0_ln1_w(XB3c0 *InstancePtr, u64 Data);
u64 XB3c0_Get_c0_ln1_w(XB3c0 *InstancePtr);
void XB3c0_Set_c0_ln1_b(XB3c0 *InstancePtr, u64 Data);
u64 XB3c0_Get_c0_ln1_b(XB3c0 *InstancePtr);
void XB3c0_Set_c0_qkv_w(XB3c0 *InstancePtr, u64 Data);
u64 XB3c0_Get_c0_qkv_w(XB3c0 *InstancePtr);
void XB3c0_Set_c0_qkv_b(XB3c0 *InstancePtr, u64 Data);
u64 XB3c0_Get_c0_qkv_b(XB3c0 *InstancePtr);
void XB3c0_Set_c0_attn_out_w(XB3c0 *InstancePtr, u64 Data);
u64 XB3c0_Get_c0_attn_out_w(XB3c0 *InstancePtr);

void XB3c0_InterruptGlobalEnable(XB3c0 *InstancePtr);
void XB3c0_InterruptGlobalDisable(XB3c0 *InstancePtr);
void XB3c0_InterruptEnable(XB3c0 *InstancePtr, u32 Mask);
void XB3c0_InterruptDisable(XB3c0 *InstancePtr, u32 Mask);
void XB3c0_InterruptClear(XB3c0 *InstancePtr, u32 Mask);
u32 XB3c0_InterruptGetEnabled(XB3c0 *InstancePtr);
u32 XB3c0_InterruptGetStatus(XB3c0 *InstancePtr);

#ifdef __cplusplus
}
#endif

#endif
