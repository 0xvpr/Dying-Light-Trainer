#include "events.h"
#include "hacks.h"

bool events_HandleKeyboard(void)
{
    // Handle Keyboard Events
    if (GetAsyncKeyState(VK_END))
    {
        return true;
    }

    return false;
}
