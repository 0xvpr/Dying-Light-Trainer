#include "drawing.h"
#include "render.h"

extern bool bMaximizeMenu;

Resolution resolution = { 0, 0 };
Coordinates coordinates = { 30, 25 };
 /*HackMenu hackMenu[MAX_MENU_ITEMS] = { 0 };*/

void render_InitializeRenderer(LPDIRECT3DDEVICE9 pDevice)
{
    (void)pDevice; // Delete when needed
    // Initialize Menu Items
}

void render_Menu(LPDIRECT3DDEVICE9 d3dDevice)
{
    // resolution = *((Resolution *)(offset_resolution));

    float factor = 1.0;
    if (bMaximizeMenu)
    {
        // Title Template
        draw_DrawFilledRect(coordinates.x, coordinates.y, 140, 100, color_DarkGrey, d3dDevice);
        draw_DrawBorderBox(coordinates.x, coordinates.y, 140, 100, 4, color_Black, d3dDevice);

        // Draw text
        draw_DrawText("[ Template Text ]", coordinates.x + 7, coordinates.y + 10, 140, 20, color_LightGrey, m_font);
        draw_DrawText("End to Eject", coordinates.x + 12, coordinates.y + 35, 140, 20, color_LightGrey, m_font);
    }
    else
    {
        factor = 0.25;

        // Title Template
        draw_DrawFilledRect(30, 20, (int)(factor*140), (int)(factor*100), color_DarkGrey, d3dDevice);
        draw_DrawBorderBox(30, 20, (int)(factor*140), (int)(factor*100), 2, color_Black, d3dDevice);
    }
}

void render_CreateFont(LPDIRECT3DDEVICE9 pDevice, int size)
{
    // Draw font
    D3DXCreateFont(
        pDevice,            // LPDIRECT3DDEVICE9 pDevice
        size,               // Height
        0,                  // Width
        FW_BOLD,            // Weight
        0,                  // MIP Levels
        false,              // Italic
        DEFAULT_CHARSET,    // Charset
        OUT_DEFAULT_PRECIS, // Precision
        DEFAULT_QUALITY,    // Quality
        DEFAULT_PITCH | FF_DONTCARE, // Pitch and Family
        "Arial",  // Font name
        &m_font             // LPD3DXFONT
    );
            
}
