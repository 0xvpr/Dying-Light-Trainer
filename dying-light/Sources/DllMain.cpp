/**
 * Creator:  VPR
 * Created:   December 13th, 2021
 * Updated:   March 28th, 2022
 * 
 * Description:
 *     Dying Light cheats written with C/C++ & Assembly.
**/

#include "kiero/kiero.h"

#include "Assembly.hpp"
#include "Events.hpp"
#include "Render.hpp"

#include <windows.h>

extern Present oPresent;

uintptr_t module_base_addr = 0;

static constexpr uint16_t bind_index = 8u;
static HANDLE hMainThread = nullptr;

DWORD
WINAPI
MainThread() {

    for (;;) {
        if (kiero::init(kiero::RenderType::D3D11) == kiero::Status::Success) {
            kiero::bind(bind_index, reinterpret_cast<void **>(&oPresent), reinterpret_cast<void *>(hkPresent));
            break;
        }
    }

    for (;!events::HandleKeyboard();) {
        // Main Loop
    }

    kiero::unbind(bind_index);
    kiero::shutdown();
    return TRUE;
}

BOOL
WINAPI 
DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved) {

    UNREFERENCED_PARAMETER(lpReserved);
    module_base_addr = (uintptr_t)GetModuleHandle(nullptr);

    switch (dwReason) {
        case DLL_PROCESS_ATTACH:
        {
            DisableThreadLibraryCalls((HMODULE)hInstance);
            hMainThread = CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)MainThread, (HMODULE)hInstance, 0, nullptr);

            if (!hMainThread) {
                return FALSE;
            }

            break;
        }
        case DLL_PROCESS_DETACH:
        {
            FreeLibraryAndExitThread((HMODULE)lpReserved, 0);
            CloseHandle(hMainThread);
            break;
        }
        default:
            return FALSE;
    }

    return TRUE;
}
