#pragma once
#include "../defines.h"

#pragma warning (push, 0)
#include <SDL2/SDL.h>
#pragma pop

typedef struct Window_State
{
	SDL_Window *window;
	u32 w;
	u32 h;
	const char *name;
}Window_State;

u8 window_create(void);