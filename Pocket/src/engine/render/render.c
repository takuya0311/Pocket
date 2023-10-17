#include "render.h"
#include "../global.h"
#include "../core/logger.h"

u8 render_create(void)
{
	global.render.renderer = SDL_CreateRenderer(global.window.window, -1, SDL_RENDERER_ACCELERATED);
	if (!global.render.renderer)
	{
		POFATAL("Failed to create SDL renderer.");
		return FALSE;
	}
	
	if (SDL_RenderSetLogicalSize(global.render.renderer, global.render.w, global.render.h) < 0)
	{
		POERROR("Failed to set renderer logical size.");
		return FALSE;
	}

	return TRUE;
}