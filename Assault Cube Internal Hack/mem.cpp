#include "pch.h"
#include "mem.h"
#include <windows.h>
#include <iostream>
#include <vector>
#include <stdio.h>

	uintptr_t mem::FindDMAAddy(uintptr_t pointer, std::vector<unsigned int> offsets) {
		uintptr_t addr = pointer;
		for (unsigned int i = 0; i < offsets.size(); ++i)
		{
			addr = *(uintptr_t*)addr;
			addr += offsets[i];
		}
		return addr;

	}

	void mem::Patch(BYTE* destinationAddr, BYTE* patch, unsigned int size) {
		DWORD oldProtect;
		VirtualProtect(destinationAddr, size, PAGE_EXECUTE_READWRITE, &oldProtect);
		memcpy(destinationAddr, patch, size);
		VirtualProtect(destinationAddr, size, oldProtect, &oldProtect);
	}

	void mem::Nop(BYTE* destinationAddr, unsigned int size) {
		DWORD oldProtect;
		VirtualProtect(destinationAddr, size, PAGE_EXECUTE_READWRITE, &oldProtect);
		memset(destinationAddr, 0x90, size);
		VirtualProtect(destinationAddr, size, oldProtect, &oldProtect);
	}