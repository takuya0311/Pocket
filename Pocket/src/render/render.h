#pragma once
#include "../defines.h"
#include "../math/math.h"

typedef struct Color32
{
	u8 b;
	u8 g;
	u8 r;
	u8 a;
}Color32;

POAPI void render_fill_rect(Vec2 position, Vec2 size, Color32 color);

#define WHITE (Color32){255, 255, 255, 255}
#define RED (Color32) {0, 0, 255, 255}