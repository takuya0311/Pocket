#pragma once
#include "../math/math.h"

typedef struct AABB
{
	Vec2 position;
	Vec2 half_size;
}AABB;

POAPI b8 physics_aabb_collision_detection(AABB aabb1, AABB aabb2, Vec2 *overlap_container);