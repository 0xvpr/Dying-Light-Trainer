/**
 * Creators:  VPR & ALGOL3070
 * Created:   December 13th, 2021
 * Updated:   December 14th, 2021
 * 
 * Description:
 *     Template for Video Game hacking using pure C
**/

#include "Assembly.hpp"
#include "Events.hpp"
#include "Mem.hpp"
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

    fprintf(fp, "foo()   : %d\n", foo());
    fprintf(fp, "bar(69) : %d\n", bar(69));
    
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
