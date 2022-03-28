#ifndef RENDER_HEADER
#define RENDER_HEADER

#include <dxgi.h>
#include <windows.h>

typedef HRESULT(__stdcall* Present) (IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags);
typedef LRESULT(CALLBACK* WNDPROC)(HWND, UINT, WPARAM, LPARAM);
typedef uintptr_t PTR;

[[nodiscard]]
LRESULT
WINAPI
WndProc(const HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

[[nodiscard]]
HRESULT
WINAPI
hkPresent(IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags);

#endif // RENDER_HEADER
