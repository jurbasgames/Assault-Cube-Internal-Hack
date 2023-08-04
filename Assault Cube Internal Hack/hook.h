#pragma once

#include "mem.h"

bool Detour32(BYTE* source, BYTE* destination, const uintptr_t lenth);
BYTE* TranpHook32(BYTE* source, BYTE* destination, const uintptr_t lenth);

/*
	bool Hook(char* source, char* destination, const intptr_t lenth);
	char* TrampHook(char* source, char* destination, const intptr_t lenth);*/
struct hook {
	bool		bStatus			{ false };
	BYTE*		source			{ nullptr };
	BYTE*		destination		{ nullptr };
	BYTE*		PtrToGatewayPtr { nullptr };
	uintptr_t	lenth			{ 0 };
	BYTE*		originalByte[10]{ 0 };

	Hook(BYTE* source, BYTE* destination, BYTE* PtrToGatewayPtr, const uintptr_t lenth);
	Hook(const char* exportName, const char* modName, BYTE* destination, BYTE* PtrToGatewayPtr, const uintptr_t lenth);

	void Enable(); void Disable(); void Toggle();
}