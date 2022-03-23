/**
 * Creators:  VPR
 * Created:   December 13th, 2021
 * Updated:   March 22nd, 2022
 * 
 * Description:
 *     Dying Light cheats written with C/C++ & Assembly.
**/

#include "Assembly.hpp"
#include "Events.hpp"
#include "Memory.hpp"
#include <stdio.h>

uintptr_t module_base_addr = 0;

bool bShutdown = false;

static HANDLE hMainThread;

[[nodiscard]]
DWORD
WINAPI
MainThread(LPVOID lpReserved) {

    module_base_addr = (uintptr_t)GetModuleHandle(NULL);

    while (!(bShutdown = events_HandleKeyboard())) {
        // Main Loop
    }

    FreeLibraryAndExitThread((HMODULE)lpReserved, 0);

}

[[nodiscard]]
BOOL
WINAPI 
DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved) {

    UNREFERENCED_PARAMETER(lpReserved); // Caveman mode

    switch (dwReason) {

        case DLL_PROCESS_ATTACH:
        {
            DisableThreadLibraryCalls((HMODULE)hInstance);
            hMainThread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)MainThread, (HMODULE)hInstance, 0, NULL);

            if (!hMainThread) {
                return FALSE;
            }

            CloseHandle(hMainThread);
            break;
        }
        case DLL_PROCESS_DETACH:
        {
            // 0xDEADBEAF
        }
        default:
        {
            return FALSE;
        }
    }

    return TRUE;
}
