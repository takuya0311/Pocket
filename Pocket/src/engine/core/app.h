#pragma once
#include "../defines.h"

typedef struct Config
{
	const char *title;
	u32 screen_w;
	u32 screen_h;
	u32 pixel_size;
	void(*user_init)(void);
	b8(*user_update)(f32 delta);
	b8(*user_render)(void);
}Config;

u8 app_start(Config *config);
