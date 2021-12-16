#include "events.h"
#include "hacks.h"

#ifndef WIN32_LEAN_AND_MEAN
#  define WIN32_LEAN_AND_MEAN
#endif
#include <windows.h>
#include <stdio.h>

bool events_HandleKeyboard(void)
{
    // Toggle god mode
    if (GetAsyncKeyState(VK_F1) & 1)
    {
        bGodmode = !bGodmode;

        hacks_ToggleGodmode(bGodmode);
        printf("Godmode:\t%s\n", bGodmode ? "Enabled" : "Disabled");
    }

    if (GetAsyncKeyState(VK_F2) & 1)
    {
        bOneShot = !bOneShot;

        hacks_ToggleOneShot(bOneShot);
        printf("Oneshot:\t%s\n", bGodmode ? "Enabled" : "Disabled");
    }

    // Cleanup & reset
    if (GetAsyncKeyState(VK_DELETE))
    {
        hacks_ToggleOneShot(false);
        hacks_ToggleGodmode(false);

        return true;
    }

    return false;
}
