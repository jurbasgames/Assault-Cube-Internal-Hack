// dllmain.cpp : Define o ponto de entrada para o aplicativo DLL.
#include "pch.h"
#include <iostream>
#include "mem.h"
#include <windows.h>
#include <stdio.h>

DWORD WINAPI HackThread(HMODULE hModule)
{
    AllocConsole();
    FILE* f;
    freopen_s(&f, "CONOUT$", "w", stdout);
    
    std::cout << "F1 - Infinite Ammo\nHOME - Exit\n";

    uintptr_t moduleBase = (uintptr_t)GetModuleHandle(L"ac_client.exe");


    bool bAmmo = false;
    std::vector<unsigned int> ammoOffsets = { 0x368 ,0x14 ,0x0 };
    
    while (true)
    {
        if (GetAsyncKeyState(VK_F1) & 1) {
            bAmmo = !bAmmo;

        }
        if (GetAsyncKeyState(VK_HOME) & 1) {
            break;
        }

        
        if (bAmmo) {
            uintptr_t ammoAddr = FindDMAAddy(moduleBase + 0x17E0A8, ammoOffsets);
            int* ammo = (int*)ammoAddr;
            *ammo = 999;
        }
        
        Sleep(5);

    }

    fclose(f);
    FreeConsole();
    FreeLibraryAndExitThread(hModule, 0);
    return 0;

}

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved)
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        CloseHandle(
            CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)HackThread, hModule, 0, nullptr)
        );
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

