#pragma once
#include "../defines.h"

#pragma warning (push, 0)
#include <SDL2/SDL.h>
#pragma pop

typedef struct render_state
{
	SDL_Renderer *renderer;
	u32 w;
	u32 h;
}Render_State;

u8 render_create(void);
void render_start(void);
void render_end(void);