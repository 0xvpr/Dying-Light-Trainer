#ifndef _DRAWING_H
#define _DRAWING_H

#include "d3d9hook.h"

LPD3DXFONT m_font;
LPD3DXFONT m_font_small;

static const D3DCOLOR color_LightGrey = D3DCOLOR_ARGB(255, 80, 80, 80);
static const D3DCOLOR color_DarkGrey  = D3DCOLOR_ARGB(255, 25, 25, 25);
static const D3DCOLOR color_White     = D3DCOLOR_ARGB(255, 255, 255, 255);
static const D3DCOLOR color_Black     = D3DCOLOR_ARGB(255, 0, 0, 0);
static const D3DCOLOR color_Green     = D3DCOLOR_ARGB(255, 10, 200, 10);
static const D3DCOLOR color_Blue      = D3DCOLOR_ARGB(255, 0, 42, 255);
static const D3DCOLOR color_Red       = D3DCOLOR_ARGB(255, 255, 0, 0);

void draw_DrawBorderBox(int x, int y, int w, int h, int thickness, D3DCOLOR Colour, LPDIRECT3DDEVICE9 d3dDevice);

void draw_DrawFilledRect(int x, int y, int w, int h, D3DCOLOR color, LPDIRECT3DDEVICE9 d3dDevice);

void draw_DrawText(LPCSTR text, int x, int y, int width, int height, D3DCOLOR color, LPD3DXFONT font);

#endif /* _DRAWING_H */
