// ==============================================================
// Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2025.2 (64-bit)
// Tool Version Limit: 2025.11
// Copyright 1986-2022 Xilinx, Inc. All Rights Reserved.
// Copyright 2022-2025 Advanced Micro Devices, Inc. All Rights Reserved.
// 
// ==============================================================
#ifndef __linux__

#include "xstatus.h"
#ifdef SDT
#include "xparameters.h"
#endif
#include "xb3c0.h"

extern XB3c0_Config XB3c0_ConfigTable[];

#ifdef SDT
XB3c0_Config *XB3c0_LookupConfig(UINTPTR BaseAddress) {
	XB3c0_Config *ConfigPtr = NULL;

	int Index;

	for (Index = (u32)0x0; XB3c0_ConfigTable[Index].Name != NULL; Index++) {
		if (!BaseAddress || XB3c0_ConfigTable[Index].Control_BaseAddress == BaseAddress) {
			ConfigPtr = &XB3c0_ConfigTable[Index];
			break;
		}
	}

	return ConfigPtr;
}

int XB3c0_Initialize(XB3c0 *InstancePtr, UINTPTR BaseAddress) {
	XB3c0_Config *ConfigPtr;

	Xil_AssertNonvoid(InstancePtr != NULL);

	ConfigPtr = XB3c0_LookupConfig(BaseAddress);
	if (ConfigPtr == NULL) {
		InstancePtr->IsReady = 0;
		return (XST_DEVICE_NOT_FOUND);
	}

	return XB3c0_CfgInitialize(InstancePtr, ConfigPtr);
}
#else
XB3c0_Config *XB3c0_LookupConfig(u16 DeviceId) {
	XB3c0_Config *ConfigPtr = NULL;

	int Index;

	for (Index = 0; Index < XPAR_XB3C0_NUM_INSTANCES; Index++) {
		if (XB3c0_ConfigTable[Index].DeviceId == DeviceId) {
			ConfigPtr = &XB3c0_ConfigTable[Index];
			break;
		}
	}

	return ConfigPtr;
}

int XB3c0_Initialize(XB3c0 *InstancePtr, u16 DeviceId) {
	XB3c0_Config *ConfigPtr;

	Xil_AssertNonvoid(InstancePtr != NULL);

	ConfigPtr = XB3c0_LookupConfig(DeviceId);
	if (ConfigPtr == NULL) {
		InstancePtr->IsReady = 0;
		return (XST_DEVICE_NOT_FOUND);
	}

	return XB3c0_CfgInitialize(InstancePtr, ConfigPtr);
}
#endif

#endif

