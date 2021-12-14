#ifndef _RENDER_H
#define _RENDER_H

#include "d3d9hook.h"
#include <stdbool.h>

void render_InitializeRenderer(LPDIRECT3DDEVICE9 pDevice);

void render_Menu(LPDIRECT3DDEVICE9 d3dDevice);

void render_CreateFont(LPDIRECT3DDEVICE9 pDevice, int size);

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
