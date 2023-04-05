// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"
#include <stdio.h>
#include <iostream>
#include <vector>
#include "offsets.h"
#include "mem.h"
#include "mem.cpp"
#include <stdlib.h>
#include <string>

#define DEACTIVATED     "\033[31m"      /* Red */
#define ACTIVATED   "\033[32m"      /* Green */
#define RESET   "\033[0m"
#define BLUE    "\033[34m"      /* Blue */


void fancyPrint(bool bHealth, bool bAmmo, bool bRecoil) {
    system("cls");
    std::string mode;
    std::cout << BLUE << R"(
   __             _               
   \ \ _   _ _ __| |__   __ _ ___ 
    \ | | | | '__| '_ \ / _` / __|
 /\_/ | |_| | |  | |_) | (_| \__ \
 \_____\__,_|_|  |_.__/ \__,_|___/
   / _ \__ _ _ __ ___   ___ ___   
  / /_\/ _` | '_ ` _ \ / _ / __|  
 / /_\| (_| | | | | | |  __\__ \  
 \____/\__,_|_| |_| |_|\___|___/  
                                  
)" << "\n" << RESET;
    if (bAmmo)
        mode = ACTIVATED;
    else
        mode = DEACTIVATED;
    std::cout << mode  << "F1 - Infinite ammo\n" << RESET;
    if (bHealth)
        mode = ACTIVATED;
    else
        mode = DEACTIVATED;
    std::cout << mode << "F2 - Infinite health\n" << RESET;
    if (bRecoil)
        mode = ACTIVATED;
    else
        mode = DEACTIVATED;
    std::cout << mode << "F3 - No recoil\n" << RESET;
    std::cout << "END - Exit\n";

}

DWORD WINAPI HackThread(HMODULE hModule)
{
    //Create Console
    AllocConsole();
    FILE* f;
    freopen_s(&f, "CONOUT$", "w", stdout);

    uintptr_t moduleBase = (uintptr_t)GetModuleHandle(L"ac_client.exe");

    //calling it with NULL also gives you the address of the .exe module
    moduleBase = (uintptr_t)GetModuleHandle(NULL);

    bool bHealth = false, bAmmo = false, bRecoil = false;
    fancyPrint(bHealth, bAmmo, bRecoil);
    while (true)
    {

        uintptr_t* localPlayerPtr = (uintptr_t*)(moduleBase + PlayerBaseOffset);

        if (GetAsyncKeyState(VK_END) & 1)
        {
            break;
        }
        if (GetAsyncKeyState(VK_F1) & 1)
        {
            bAmmo = !bAmmo;
            fancyPrint(bHealth, bAmmo, bRecoil);
        }
        if (GetAsyncKeyState(VK_F2) & 1)
        {
            bHealth = !bHealth;
            fancyPrint(bHealth, bAmmo, bRecoil);
        }
        if (GetAsyncKeyState(VK_F3) & 1) {
            bRecoil = !bRecoil;
            fancyPrint(bHealth, bAmmo, bRecoil);
            BYTE* recoilAddr = (BYTE*)RecoilBegin;
            if (bRecoil) {
                mem::Nop(recoilAddr, 18);
            } 
            else {
                mem::Patch(recoilAddr, (BYTE*)"\x8B\x16\x8B\x52\x14\x50\x8D\x4C\x24\x1C\x51\x8B\xCE\xFF\xD2\x8B\x46\x08", 18);
            }
        }
        


        if (localPlayerPtr)
        {
            if (bHealth)
            {
                *(int*)(*localPlayerPtr + 0xF8) = 1337;
            }

            if (bAmmo)
            {
                *(int*)mem::FindDMAAddy((uintptr_t)localPlayerPtr, PlayerAmmo) = 1337;
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