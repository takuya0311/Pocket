#pragma once
#include "../defines.h"
#include <SDL2/SDL.h>

typedef struct App_State
{
	SDL_Window *window;
	SDL_Renderer *renderer;
	u8 test;
}App_State;

u8 app_create(const char *title, u32 window_w, u32 window_h);