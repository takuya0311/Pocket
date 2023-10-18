#pragma once
#include "core/app.h"
#include "core/window.h"
#include "render/render.h"
#include "time/time.h"

typedef struct global
{
	App_State app;
	Window_State window;
	Render_State render;
	Time_State time;
}Global;

extern Global global;