/**
 * Creators:  VPR & ALGOL3070
 * Created:   December 13th, 2021
 * Updated:   December 16th, 2021
 * 
 * Description:
 *     Dying Light cheats written with C & Assembly.
**/

#include "assembly.h"
#include "events.h"
#include "mem.h"
#include <stdio.h>

uintptr_t module_base_addr = 0;

bool bMaximizeMenu = true;
bool bShutdown     = false;

DWORD WINAPI MainThread(LPVOID lpReserved)
{
    module_base_addr = (uintptr_t)GetModuleHandleA(NULL);

    FILE* fp;
    AllocConsole();
    freopen_s(&fp, "CONOUT$", "w", stdout);
    
    while (!(bShutdown = events_HandleKeyboard()))
    {
        // Main Loop
    }

    fclose(fp);
    FreeConsole();
    FreeLibraryAndExitThread((HMODULE)lpReserved, 0);
}

BOOL WINAPI DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved)
{
    UNREFERENCED_PARAMETER(lpReserved); // Caveman mode

    HANDLE hMainThread;

    switch (dwReason)
    {
        case DLL_PROCESS_ATTACH:
        {
            DisableThreadLibraryCalls((HMODULE)hInstance);
            hMainThread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)MainThread, (HMODULE)hInstance, 0, NULL);

            if (!hMainThread)
            {
                return FALSE;
            }

            CloseHandle(hMainThread);
            break;
        }
        case DLL_PROCESS_DETACH:
        {
            // 0xDEAD
        }
        case DLL_PROCESS_VERIFIER:
        {
            // 0xBEEF
        }
        default:
        {
            return FALSE;
        }
    }

    return TRUE;
}
