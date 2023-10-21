#pragma once
#include "../math/math.h"

POAPI b8 phys_collision_aabb_detect(Vec2 pos1, Vec2 half_size1, Vec2 pos2, Vec2 half_size2, Vec2 *overlap_container);
POAPI void phys_collision_resolute(Vec2 *pos, Vec2 *vel, Vec2 *prev_pos, Vec2 overlap, Vec2 prev_overlap, b8 bounce);