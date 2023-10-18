#include "physics.h"
#include "../ECS/ecs.h"

POAPI b8 physics_aabb_collision_detection(AABB aabb1, AABB aabb2, Vec2 * overlap_container)
{
	// Calculate a center points of each bounding box
	Vec2 e1_center;
	e1_center.x = aabb1.position.x + aabb1.half_size.w;
	e1_center.y = aabb1.position.y + aabb1.half_size.w;

	Vec2 e2_center;
	e2_center.x = aabb2.position.x + aabb2.half_size.w;
	e2_center.y = aabb2.position.y + aabb2.half_size.w;

	// Calculate absolute difference of center points
	f32 dx = fabs(e2_center.x - e1_center.x);
	f32 dy = fabs(e2_center.y - e1_center.y);

	// Calculate overlap amount
	overlap_container->x = aabb2.half_size.w + aabb1.half_size.w - dx;
	overlap_container->y = aabb2.half_size.h + aabb1.half_size.h - dy;

	if (overlap_container->x > 0 && overlap_container->y > 0)
	{
		return TRUE;
	}

	return FALSE;
}

