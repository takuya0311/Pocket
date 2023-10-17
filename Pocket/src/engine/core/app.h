#pragma once
#include "../defines.h"
#include <SDL2/SDL.h>

typedef struct App_State
{
	u8 should_quit;
	void (*user_init)(void);
	u8 (*user_update)(f32 delta);
}App_State;

u8 app_create(const char *title, u32 screen_w, u32 screen_h, u32 pixel_size, void(*user_init)(void), u8(*user_update)(f32 delta));
void app_start();