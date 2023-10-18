#pragma once

#include "../defines.h"
#include <math.h>

typedef union Vec2_u
{
	f32 elements[2];
	struct
	{
		union
		{
			f32 x, w;
		};
		union
		{
			f32 y, h;
		};
	};
}Vec2;

Vec2 vec2_add(Vec2 vector1, Vec2 vector2);

Vec2 vec2_sub(Vec2 vector1, Vec2 Vector2);