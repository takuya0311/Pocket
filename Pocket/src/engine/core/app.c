#include "../global.h"
#include "../core/logger.h"
#include "app.h"
#include "window.h"

#include <stdio.h>

u8 app_create(const char *title, u32 screen_w, u32 screen_h, u32 pixel_size, void(*user_init)(void), u8(*user_update)(f32 delta))
{
    // Application configuration
    global.window.name = title;
    global.window.w = screen_w * pixel_size;
    global.window.h = screen_h * pixel_size;
    global.render.w = screen_w;
    global.render.h = screen_h;
    global.app.user_init = user_init;
    global.app.user_update = user_update;
    // Create SDL Window
    if (!window_create())
    {
        POFATAL("Failed in window creation.");
        return FALSE;
    }
    // Create SDL Renderer
    if (!render_create())
    {
        POFATAL("Failed in render creation.");
        return FALSE;
    }

    // Do user initiakization
    global.app.user_init;

    return TRUE;
}

void app_start()
{
    // Game loop
    while (!global.app.should_quit)
    {
        SDL_Event e;
        
        while (SDL_PollEvent(&e))
        {
            switch (e.type)
            {
                case SDL_QUIT:
                    global.app.should_quit = TRUE;
                    break;
            }
        }

        // Do user update
        if (!global.app.user_update)
        {
            POFATAL("Failed to conduct user updates.");
            break;
        }
    }
}