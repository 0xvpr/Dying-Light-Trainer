/**
 * Creator:   VPR
 * Created:   August 27th, 2021
 * Updated:   December 9th, 2021
 * 
 * Description:
 *     Template for Video Game hacking using pure C
**/

#include "d3d9hook.h"
#include "render.h"
#include "events.h"
#include "mem.h"

uintptr_t module_base_addr = 0;
HWND dll_handle = NULL;

LPVOID d3d9Device[119];
tEndScene oEndScene = NULL;
char oEndScene_bytes[7] = { 0 };

bool bMaximizeMenu = true;
bool bShutdown     = false;
bool bInit         = false;

HRESULT APIENTRY hkEndScene(LPDIRECT3DDEVICE9 pDevice)
{
    if (bInit == false)
    {
        bInit = true;

        render_InitializeRenderer(pDevice);
        render_CreateFont(pDevice, 20);
    }
    render_Menu(pDevice);

    return oEndScene(pDevice);
}

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wpedantic"
DWORD WINAPI MainThread(LPVOID lpReserved)
{
    module_base_addr = (uintptr_t)GetModuleHandle(NULL);
    
    if (GetD3D9Device(d3d9Device, sizeof(d3d9Device)))
    {
        memcpy(oEndScene_bytes, d3d9Device[42], 7);
        oEndScene = (tEndScene)TrampHook((char *)d3d9Device[42], (char *)hkEndScene, 7);
    }

    while (!(bShutdown = events_HandleKeyboard()))
    {
        // Main Loop
    }

    Patch((char *)d3d9Device[42], (char *)oEndScene_bytes, 7);
    FreeLibraryAndExitThread((HMODULE)lpReserved, 0);
    return TRUE;
}
#pragma GCC diagnostic pop

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
BOOL WINAPI DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved)
{
    switch (dwReason)
    {
        case DLL_PROCESS_ATTACH:
        {
            dll_handle = (HWND)hInstance;
            DisableThreadLibraryCalls(hInstance);
            CreateThread(0, 0, MainThread, hInstance, 0, 0);
            break;
        }
        case DLL_PROCESS_DETACH:
        {
            break;
        }
        default:
        {
            break;
        }
    }

    return TRUE;
}
#pragma GCC diagnostic pop
