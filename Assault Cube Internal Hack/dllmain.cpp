// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"
#include <stdio.h>
#include <iostream>
#include <vector>


uintptr_t FindDMAAddy(uintptr_t ptr, std::vector<unsigned int> offsets) {
    uintptr_t addr = ptr;
    for (unsigned int i = 0; i < offsets.size(); ++i)
    {
        addr = *(uintptr_t*)addr;
        addr += offsets[i];
    }
    return addr;

}

DWORD WINAPI HackThread(HMODULE hModule)
{
    //Create Console
    AllocConsole();
    FILE* f;
    freopen_s(&f, "CONOUT$", "w", stdout);

    std::cout << "F1 - Infinite heath(Not working)\nF2 - Infinite ammo\nF3 - No recoil(Not working)\n";

    uintptr_t moduleBase = (uintptr_t)GetModuleHandle(L"ac_client.exe");

    //calling it with NULL also gives you the address of the .exe module
    moduleBase = (uintptr_t)GetModuleHandle(NULL);

    bool bHealth = false, bAmmo = false, bRecoil = false;

    while (true)
    {
        if (GetAsyncKeyState(VK_END) & 1)
        {
            break;
        }

        if (GetAsyncKeyState(VK_F2) & 1)
            bHealth = !bHealth;
        if (GetAsyncKeyState(VK_F1) & 1)
        {
            bAmmo = !bAmmo;
        }

        uintptr_t* localPlayerPtr = (uintptr_t*)(moduleBase + 0x17E0A8);


        if (localPlayerPtr)
        {
            if (bHealth)
            {
                *(int*)(*localPlayerPtr + 0xF8) = 1337;
            }

            if (bAmmo)
            {
                *(int*)FindDMAAddy(moduleBase + 0x17E0A8, { 0x368, 0x14, 0x0 }) = 1337;
            }

        }
        Sleep(5);
    }

    fclose(f);
    FreeConsole();
    FreeLibraryAndExitThread(hModule, 0);
    return 0;
}


BOOL APIENTRY DllMain(HMODULE hModule,
    DWORD  ul_reason_for_call,
    LPVOID lpReserved
)
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        CloseHandle(CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)HackThread, hModule, 0, nullptr));
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}
