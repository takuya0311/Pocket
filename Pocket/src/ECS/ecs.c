#include "ecs.h"
#include "../core/logger.h"
#include "../render/render.h"
#include "../global.h"
#include <stdlib.h>


typedef struct EntityManager
{
	u64 entity_count;
	ComponentArrays components;
	const char **tags;
	b8 *flags;
	u64 capacity;
}EntityManager;

static EntityManager entity_memory_pool;

static const i32 max_entity = 3000;

b8 ecs_initialize(void)
{
	// I decided to implement this way to leverage fewer allocation and CPU cash friendliness.
	// Allocate memory for giant memory pool
	entity_memory_pool.components.trans_comps = calloc(max_entity ,max_entity * sizeof(TransformComp));
	entity_memory_pool.components.vis_comps = calloc(max_entity, max_entity * sizeof(VisibilityComp));
	entity_memory_pool.components.bb_comps = calloc(max_entity, max_entity * sizeof(BoundingBoxComp));

	entity_memory_pool.tags = calloc( max_entity ,max_entity * sizeof(const char *));
	entity_memory_pool.flags = calloc(max_entity ,max_entity * sizeof(b8));
	entity_memory_pool.capacity = max_entity;

	if (!entity_memory_pool.components.trans_comps ||!entity_memory_pool.components.vis_comps || !entity_memory_pool.components.bb_comps|| !entity_memory_pool.tags|| !entity_memory_pool.flags)
	{
		POFATAL("Failed allocate memory.");
		return FALSE;
	}

	return TRUE;
}

POAPI i64 ecs_entity_create(const char *tag)
{
	if (entity_memory_pool.capacity == entity_memory_pool.entity_count)
	{
		POERROR("Entity count reaches capacity.");
		return -1;
	}

	i64 i;

	for (i = 0; i < entity_memory_pool.capacity; i++)
	{
		if (entity_memory_pool.flags[i] == FALSE)
		{
			entity_memory_pool.flags[i] = TRUE;
			entity_memory_pool.tags[i] = tag;
			entity_memory_pool.entity_count++;
			break;
		}
	}

	POINFO("Entity created ID: %d", i);

	return i;
}

POAPI u64 ecs_get_entity_count(void)
{
	return entity_memory_pool.entity_count;
}

POAPI b8 ecs_trans_comp_add(u64 entity_id, Vec2 position, Vec2 velocity)
{
	entity_memory_pool.components.trans_comps[entity_id].active = TRUE;
	entity_memory_pool.components.trans_comps[entity_id].position = position;
	entity_memory_pool.components.trans_comps[entity_id].velocity = velocity;

	return TRUE;
}

POAPI void *ecs_trans_comp_get(u64 entity_id)
{
	return &entity_memory_pool.components.trans_comps[entity_id];
}

POAPI b8 ecs_vis_comp_add(u64 entity_id, Vec2 size, Color32 color)
{
	TransformComp *trans_comp = ecs_trans_comp_get(entity_id);
	
	if (!trans_comp->active)
	{
		POERROR("visibility comp need transform comp for position.");
		return FALSE;
	}

	entity_memory_pool.components.vis_comps[entity_id].rect.x = trans_comp->position.x;
	entity_memory_pool.components.vis_comps[entity_id].rect.x = trans_comp->position.x;
	entity_memory_pool.components.vis_comps[entity_id].rect.w = size.w;
	entity_memory_pool.components.vis_comps[entity_id].rect.h = size.h;
	entity_memory_pool.components.vis_comps[entity_id].color = color;
	entity_memory_pool.components.vis_comps[entity_id].active = TRUE;

	return TRUE;
}

POAPI void *ecs_vis_comp_get(u64 entity_id)
{
	return &entity_memory_pool.components.vis_comps[entity_id];
}

POAPI b8 ecs_bb_comp_add(u64 entity_id, Vec2 position, Vec2 size)
{
	entity_memory_pool.components.bb_comps[entity_id].position = position;
	Vec2 temp = { 0 };
	vec2_devide_by(2, &temp, &size);
	entity_memory_pool.components.bb_comps[entity_id].half_size = temp;
	entity_memory_pool.components.bb_comps[entity_id].active = TRUE;

	return TRUE;
}

POAPI void *ecs_bb_comp_get(u64 entity_id)
{
	return &entity_memory_pool.components.bb_comps[entity_id];
}

POAPI const char *ecs_get_tag(u64 entity_id)
{
	return entity_memory_pool.tags[entity_id];
}