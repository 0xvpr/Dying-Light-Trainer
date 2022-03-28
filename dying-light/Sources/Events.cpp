#include "Events.hpp"
#include "Hacks.hpp"
#include "Menu.hpp"

#include <windows.h>
#include <stdio.h>

#define TOGGLE(vkey,func,item_idx)                 \
    if (GetAsyncKeyState(vkey) & 1)                \
    {                                              \
        auto& bState = menu[item_idx].bEnabled; \
        bState = !bState;                          \
        func(bState);                              \
    }

static auto& menu = *Menu::Instance();

bool events::HandleKeyboard() {

    TOGGLE(VK_F1, hacks::ToggleGodmode, item::godmode);
    TOGGLE(VK_F2, hacks::ToggleOneShot, item::oneshot);
    TOGGLE(VK_F3, hacks::ToggleInfiniteStamina, item::infinite_stamina);

    // Handle Menu Position
    if (GetAsyncKeyState(VK_LEFT)  & 1) {
        menu.MovePosLeft();
    }
    if (GetAsyncKeyState(VK_RIGHT) & 1) {
        menu.MovePosRight();
    }
    if (GetAsyncKeyState(VK_UP)    & 1) {
        menu.MovePosUp();
    }
    if (GetAsyncKeyState(VK_DOWN)  & 1) {
        menu.MovePosDown();
    }

    // Cleanup & reset
    if (GetAsyncKeyState(VK_END)) {
        hacks::ToggleGodmode(false);
        hacks::ToggleOneShot(false);

        return true;
    }

    return false;

}
