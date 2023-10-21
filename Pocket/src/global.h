#pragma once
#include "core/app.h"
#include "core/window.h"
#include "render/render_internal.h"
#include "time/time.h"
#include "core/input.h"

typedef struct global
{
	App_State app;
	Window_State window;
	Render_State render;
	Time_State time;
	KeyState key;
}Global;

extern Global global;