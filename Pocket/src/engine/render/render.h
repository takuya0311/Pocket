#pragma once
#include "../defines.h"
#include <SDL2/SDL.h>

typedef struct render_state
{
	SDL_Renderer *renderer;
	u32 w;
	u32 h;
}Render_State;

u8 render_create(void);