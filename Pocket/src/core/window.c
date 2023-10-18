#include "window.h"
#include "../global.h"
#include "../core/logger.h"

u8 window_create(void)
{
    //Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        POFATAL("SDL could not initialize. SDL_ERROR: %s", SDL_GetError());
        return FALSE;
    }
    // Create SDL Window

    global.window.window = SDL_CreateWindow(
        global.window.name,
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        global.window.w, global.window.h,
        SDL_WINDOW_SHOWN);

    if (!global.window.window)
    {
       POFATAL("Failed to create SDL window.");
       return FALSE;
    }

    POINFO("Window created succesfully. Width: %d, Height: %d", global.window.w, global.window.h);

    return TRUE;
}