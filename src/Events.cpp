#ifndef WIN32_LEAN_AND_MEAN
#  define WIN32_LEAN_AND_MEAN
#endif
extern "C" {
#include <windows.h>
}

#include "Events.hpp"
#include "Hacks.hpp"

bool events_HandleKeyboard(void)
{
    // Handle Keyboard Events
    if (GetAsyncKeyState(VK_DELETE))
    {
        return true;
    }

    return false;
}
