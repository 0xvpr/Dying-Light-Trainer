#ifndef WIN32_LEAN_AND_MEAN
#  define WIN32_LEAN_AND_MEAN
#endif
#include <windows.h>

#include "events.h"
#include "hacks.h"

bool events_HandleKeyboard(void)
{
    // Handle Keyboard Events
    if (GetAsyncKeyState(VK_DELETE))
    {
        return true;
    }

    return false;
}
