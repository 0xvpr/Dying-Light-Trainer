#include "Events.hpp"
#include "Hacks.hpp"

#ifndef WIN32_LEAN_AND_MEAN
#   define WIN32_LEAN_AND_MEAN
#endif // WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <stdio.h>

extern bool bGodmode;
extern bool bOneShot;
extern bool bStamina;

#define TOGGLE(vkey,func,bState,name)                            \
    if (GetAsyncKeyState(vkey) & 1)                              \
    {                                                            \
        bState = !bState;                                        \
        func(bState);                                            \
        printf(#name":\t%s\n", bState ? "Enabled" : "Disabled"); \
    }

bool events_HandleKeyboard(void) {

    TOGGLE(VK_F1, hacks_ToggleGodmode, bGodmode, "Godmode");
    TOGGLE(VK_F2, hacks_ToggleOneShot, bOneShot, "Oneshot");
    TOGGLE(VK_F3, hacks_ToggleInfiniteStamina, bStamina, "Inf Stamina");

    // Cleanup & reset
    if (GetAsyncKeyState(VK_END)) {
        hacks_ToggleOneShot(false);
        hacks_ToggleGodmode(false);

        return true;
    }

    return false;

}
