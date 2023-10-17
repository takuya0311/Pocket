#include "../global.h"
#include "app.h"
#include <stdio.h>

u8 app_create(const char *title, u32 window_w, u32 window_h)
{
    //Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        exit(1);
    }
    // Create SDL Window
   
    global.app.window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, window_w, window_h, SDL_WINDOW_SHOWN);
    if (!global.app.window)
    {
        printf("Window could not be created! SDL_ERROR: %s\n", SDL_GetError());
        exit(1);
    }
    // Create SDL Renderer
    
}