#include "math.h"

Vec2 vec2_add(Vec2 vector1, Vec2 vector2)
{
	return (Vec2){vector1.x + vector2.x, vector1.y + vector2.y};
}

Vec2 vec2_sub(Vec2 vector1, Vec2 vector2)
{
	return (Vec2){vector1.x - vector2.x, vector1.y - vector2.y};
}