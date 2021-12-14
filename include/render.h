#ifndef _RENDER_H
#define _RENDER_H

#include <stdbool.h>

typedef struct _HackMenu
{
    bool bEnabled;
    char name[64];
} HackMenu;

typedef struct _Resolution
{
    int x;
    int y;
} Resolution;

typedef struct _Coordinates
{
    int x;
    int y;
} Coordinates;

#endif /* _RENDER_H */
