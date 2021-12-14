/**
 * Creator:   VPR
 * Created:   August 27th, 2021
 * Updated:   December 9th, 2021
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
bool bInit         = false;

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wpedantic"
DWORD WINAPI MainThread(LPVOID lpReserved)
{
    module_base_addr = (uintptr_t)GetModuleHandle(NULL);

    FILE* fp;
    AllocConsole();
    freopen_s(&fp, "CONOUT$", "w", stdout);

    fprintf(fp, "%d", foo());
    
    while (!(bShutdown = events_HandleKeyboard()))
    {
        // Main Loop
    }

    fclose(fp);
    FreeConsole();
    FreeLibraryAndExitThread((HMODULE)lpReserved, 0);
}
#pragma GCC diagnostic pop

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
BOOL WINAPI DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved)
{
    HANDLE hack_thread;

    switch (dwReason)
    {
        case DLL_PROCESS_ATTACH:
        {
            DisableThreadLibraryCalls((HMODULE)hInstance);
            hack_thread = CreateThread(0, 0, MainThread, (HMODULE)hInstance, 0, 0);

            if (!hack_thread)
            {
                return FALSE;
            }

            CloseHandle(hack_thread);
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
            break;
        }
    }

    return TRUE;
}
#pragma GCC diagnostic pop
