#pragma once
#include "../defines.h"

#include <SDL2/SDL.h>

typedef struct Window_State
{
	SDL_Window *window;
	u32 w;
	u32 h;
	char *name;
}Window_State;

u8 window_create(void);