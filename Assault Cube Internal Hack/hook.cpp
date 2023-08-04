#include "pch.h"
#include "hook.h"

bool Hook(char* source, char* destination, const intptr_t lenth)
{
    if (lenth < 5) return false;

    DWORD  curProtection;
    VirtualProtect(source, lenth, PAGE_EXECUTE_READWRITE, &curProtection);

    intptr_t  relativeAddress = (intptr_t)(destination - (intptr_t)source) - 5;

    *source = (char)'\xE9'; //truncation of constant values // "\xE9"
    *(intptr_t*)((intptr_t)source + 1) = relativeAddress;

    VirtualProtect(source, lenth, curProtection, &curProtection);
    return true;
}

char* TrampHook(char* source, char* destination, const intptr_t lenth)
{
    // Make sure the length is greater than 5
    if (lenth < 5) return 0;

    // Create the gateway (len + 5 for the overwritten bytes + the jmp)
    void* gateway = VirtualAlloc(0, lenth + 5, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);

    //Write the stolen bytes into the gateway
    memcpy(gateway, source, lenth);

    // Get the gateway to destination addy
    intptr_t  gatewayRelativeAddr = ((intptr_t)source - (intptr_t)gateway) - 5;

    // Add the jmp opcode to the end of the gateway
    *(char*)((intptr_t)gateway + lenth) = 0xE9; //truncation? 0xe9

    // Add the address to the jmp
    *(intptr_t*)((intptr_t)gateway + lenth + 1) = gatewayRelativeAddr;

    // Place the hook at the destination
    Hook(source, destination, lenth);

    return (char*)gateway;
}

bool Detour32(BYTE* source, BYTE* destination, const uintptr_t lenth)
{
    return false;
}

BYTE* TranpHook32(BYTE* source, BYTE* destination, const uintptr_t lenth)
{
    return nullptr;
}

void hook::Enable()
{
}

void hook::Disable()
{
}

void hook::Toggle()
{
}
