#ifndef RENDER_HEADER
#define RENDER_HEADER

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

#endif // RENDER_HEADER
