#pragma once
#include "core/app.h"
#include "core/window.h"
#include "render/render.h"

typedef struct global
{
	App_State app;
	Window_State window;
	Render_State render;
}Global;

extern Global global;