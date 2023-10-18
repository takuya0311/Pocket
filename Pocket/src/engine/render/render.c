#include "render.h"
#include "render_internal.h"

#include "../global.h"
#include "../core/logger.h"

u8 render_create(void)
{
	global.render.renderer = SDL_CreateRenderer(global.window.window, -1, SDL_RENDERER_ACCELERATED);
	if (!global.render.renderer)
	{
		POFATAL("Failed to create SDL renderer. SDL_Error: %s", SDL_GetError());
		return FALSE;
	}
	
	if (SDL_RenderSetLogicalSize(global.render.renderer, global.render.w, global.render.h) != 0)
	{
		POERROR("Failed to set renderer logical size. SDL_Error: %s", SDL_GetError());
		return FALSE;
	}
	
	if (SDL_SetRenderDrawBlendMode(global.render.renderer, SDL_BLENDMODE_BLEND) != 0)
	{
		POERROR("Failed to set SDL blend mode. SDL_Error: %s", SDL_GetError());
	}

	POINFO("Renderer created successfully. Width: %d, Height: %d", global.render.w, global.render.h);

	return TRUE;
}

void render_start(void)
{
	SDL_SetRenderDrawColor(global.render.renderer, 0,0,0,255);
	SDL_RenderClear(global.render.renderer);
}

void render_end(void)
{
	SDL_RenderPresent(global.render.renderer);
}

void render_fill_rect(Vec2 position, Vec2 size, Color32 color)
{
	// Set a color of the rectangle
	SDL_SetRenderDrawColor(global.render.renderer, color.r, color.g, color.b, color.a);
	
	SDL_Rect r;
	r.x = position.x;
	r.y = position.y;
	r.w = size.w;
	r.h = size.h;

	SDL_RenderFillRect(global.render.renderer, &r);
}