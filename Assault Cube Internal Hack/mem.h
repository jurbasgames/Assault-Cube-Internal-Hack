#pragma once
#include <iostream>

namespace mem
{
	uintptr_t FindDMAAddy(uintptr_t pointer, std::vector<unsigned int> offsets);
	void Patch(BYTE* destinationAddr, BYTE* patch, unsigned int size);
	void Nop(BYTE* destinationAddr, unsigned int size);
}

