#pragma once
#include "core/app_internal.h"
#include "core/window_internal.h"
#include "render/render_internal.h"

typedef struct global
{
	App_State app;
	Window_State window;
	Render_State render;
}Global;

extern Global global;