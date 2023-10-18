#pragma once
#include "../defines.h"
#include "../math/math.h"

#pragma warning (push, 0)
#include <SDL2/SDL.h>
#pragma pop

typedef struct Color32
{
	u8 b;
	u8 g;
	u8 r;
	u8 a;
}Color32;

typedef struct render_state
{
	SDL_Renderer *renderer;
	u32 w;
	u32 h;
}Render_State;

POAPI void render_fill_rect(Vec2 position, Vec2 size, Color32 color);


u8 render_create(void);
void render_start(void);
void render_end(void);

#define WHITE (Color32){255, 255, 255, 255}
#define RED (Color32) {0, 0, 255, 255}