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
