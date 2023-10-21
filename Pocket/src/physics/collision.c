#include "collision.h"
#include "../ECS/ecs.h"

POAPI b8 phys_collision_aabb_detect(Vec2 pos1, Vec2 half_size1, Vec2 pos2, Vec2 half_size2, Vec2 *overlap_container)
{
	// Calculate a center points of each bounding box
	Vec2 e1_center;
	e1_center.x = pos1.x + half_size1.w;
	e1_center.y = pos1.y + half_size1.h;

	Vec2 e2_center;
	e2_center.x = pos2.x + half_size2.w;
	e2_center.y = pos2.y + half_size2.h;

	// Calculate absolute difference of center points
	f32 dx = fabs(e2_center.x - (f64)e1_center.x);
	f32 dy = fabs(e2_center.y - (f64)e1_center.y);

	// Calculate overlap amount
	overlap_container->x = half_size2.w + half_size1.w - dx;
	overlap_container->y = half_size2.h + half_size1.h - dy;

	if (overlap_container->x > 0 && overlap_container->y > 0)
	{
		return TRUE;
	}

	return FALSE;
}

POAPI void phys_collision_resolute(Vec2 *pos, Vec2 *vel, Vec2 *prev_pos, Vec2 overlap, Vec2 prev_overlap, b8 bounce)
{
	if (prev_overlap.x > 0)
	{
		if (prev_pos->y - pos->y < 0)
		{
			pos->y -= overlap.y;
			if (bounce) { vel->y *= -1; }
		}
		else
		{
			pos->y += overlap.y;
			if (bounce) { vel->y *= -1; }
		}
	}
	else if (prev_overlap.y > 0 || (prev_overlap.x > 0 && prev_overlap.y > 0))
	{
		if (prev_pos->x - pos->x < 0)
		{
			pos->x -= overlap.x;
			if (bounce) { vel->x *= -1; }
		}
		else
		{
			pos->x += overlap.x;
			if (bounce) { vel->x *= -1; }
		}
	}
}

