#include "app.h"

#include "../global.h"
#include "logger.h"
#include "window.h"
#include "../time/time.h"
#include "../ECS/ecs.h"

static void app_run(Config *config);

u8 app_start(Config *config)
{
    // Application configuration
    global.window.name = config->title;
    global.window.w = config->screen_w * config->pixel_size;
    global.window.h = config->screen_h * config->pixel_size;
    global.render.w = config->screen_w;
    global.render.h = config->screen_h;

    // Connect to user defined functions
    if (!config->user_init || !config->user_update || !config->user_render)
    {
        POFATAL("User defined functions has not been set. Shutting down.");
        return FALSE;
    }

    // Initializing subsystems
    if (!log_initialize())
    {
        POFATAL("Failed to initialize logging system. Shutting down.");
        return FALSE;
    }

    if (!time_initialize(config->frame_rate_target))
    {
        POFATAL("Failed to initialize time system. Shutting down");
        return FALSE;
    }

    if (!ecs_initialize())
    {
        POFATAL("Failed to initialize ECS system. Shutting down.");
        return FALSE;
    }
    
    if (!window_create())
    {
        POFATAL("Failed in window creation.");
        return FALSE;
    }
   
    if (!render_create())
    {
        POFATAL("Failed in render creation.");
        return FALSE;
    }

    // Do user initiakization
    config->user_init();
    POINFO("Conducted user initialization successfully.");

    app_run(config);

    return TRUE;
}

static void app_run(Config *config)
{
    // Game loop
    while (!global.app.should_quit)
    {
        time_update();
        
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
        if (!config->user_update((f32)global.time.delta))
        {
            POFATAL("Failed to conduct user updates.");
            break;
        }

        render_start();
        
        if (!config->user_render())
        {
            POFATAL("Failed to conduct user render function.");
            break;
        }

        render_end();

        time_update_late();
    }

    // Shutdown subsystems
    log_shutdown();
}