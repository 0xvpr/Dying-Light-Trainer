/**
 * Creators:  VPR
 * Created:   December 13th, 2021
 * Updated:   March 28th, 2022
 * 
 * Description:
 *     Dying Light cheats written with C/C++ & Assembly.
**/

#include "Includes.hpp"

#include "Assembly.hpp"
#include "Events.hpp"
#include "Memory.hpp"
#include <stdio.h>

extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

uintptr_t module_base_addr = 0;

static bool bShutdown = false;
static bool init = false;
static HANDLE hMainThread;

Present oPresent;
HWND window = NULL;
WNDPROC oWndProc;
ID3D11Device* pDevice = NULL;
ID3D11DeviceContext* pContext = NULL;
ID3D11RenderTargetView* mainRenderTargetView;

void InitImGui() {

    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags = ImGuiConfigFlags_NoMouseCursorChange;
    ImGui_ImplWin32_Init(window);
    ImGui_ImplDX11_Init(pDevice, pContext);

}

[[nodiscard]]
LRESULT
WINAPI
WndProc(const HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {

    if (true && ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam)) {
        return true;
    }

    return CallWindowProc(oWndProc, hWnd, uMsg, wParam, lParam);
}

[[nodiscard]]
HRESULT
WINAPI
hkPresent(IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags) {

    if (!init) {
        if (SUCCEEDED(pSwapChain->GetDevice(__uuidof(ID3D11Device), (void**)& pDevice))) {
            pDevice->GetImmediateContext(&pContext);
            DXGI_SWAP_CHAIN_DESC sd;
            pSwapChain->GetDesc(&sd);
            window = sd.OutputWindow;
            ID3D11Texture2D* pBackBuffer;
            pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)& pBackBuffer);
            pDevice->CreateRenderTargetView(pBackBuffer, NULL, &mainRenderTargetView);
            pBackBuffer->Release();
            oWndProc = (WNDPROC)SetWindowLongPtr(window, GWLP_WNDPROC, (LONG_PTR)WndProc);
            InitImGui();
            init = true;
        } else {
            return oPresent(pSwapChain, SyncInterval, Flags);
        }
    }

    ImGui_ImplDX11_NewFrame();
    ImGui_ImplWin32_NewFrame();

    ImGui::SetNextWindowSize(ImVec2{100, 60});
    ImGui::SetNextWindowPos(ImVec2{10, 10});
    ImGui::NewFrame();

    auto window_flags = ImGuiWindowFlags_NoMove |
                        ImGuiWindowFlags_AlwaysAutoResize;
    ImGui::Begin("Daylight Savings", nullptr, window_flags);
    ImGui::End();

    ImGui::Render();

    pContext->OMSetRenderTargets(1, &mainRenderTargetView, NULL);
    ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

    return oPresent(pSwapChain, SyncInterval, Flags);

}

[[nodiscard]]
DWORD
WINAPI
MainThread() {

    module_base_addr = (uintptr_t)GetModuleHandle(NULL);

    bool init_hook = false;
    do {
        if (kiero::init(kiero::RenderType::D3D11) == kiero::Status::Success) {
            kiero::bind(8, (void**)& oPresent, hkPresent);
            init_hook = true;
        }
    } while (!init_hook);

    while (!(bShutdown = events_HandleKeyboard())) {
        // Main Loop
    }

    kiero::shutdown();
    return TRUE;
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
        {
            return FALSE;
        }
    }

    return TRUE;
}
