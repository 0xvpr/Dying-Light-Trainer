/**
 * Creators:  VPR & ALGOL3070
 * Created:   December 13th, 2021
 * Updated:   December 14th, 2021
 * 
 * Description:
 *     Template for Video Game hacking using pure C
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
    module_base_addr = (uintptr_t)GetModuleHandle(NULL);

    FILE* fp;
    AllocConsole();
    freopen_s(&fp, "CONOUT$", "w", stdout);

    fprintf(fp, "%d\n", foo());
    
    while (!(bShutdown = events_HandleKeyboard()))
    {
        // Main Loop
    }

    fclose(fp);
    FreeConsole();
    FreeLibraryAndExitThread((HMODULE)lpReserved, 0);
}

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
BOOL WINAPI DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved)
{
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
#pragma GCC diagnostic pop
