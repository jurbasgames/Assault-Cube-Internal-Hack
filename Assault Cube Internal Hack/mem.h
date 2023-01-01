#pragma once
#include "pch.h"
#include <windows.h>
#include <iostream>
#include <vector>

uintptr_t FindDMAAddy(uintptr_t ptr, std::vector<unsigned int> offsets);
