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

b8 ecs_setup(u64 max_entity)
{
	// Allocate memory for giant memory pool
	entity_memory_pool.components.trans_comps = calloc(max_entity ,max_entity * sizeof(*entity_memory_pool.components.trans_comps));
	entity_memory_pool.components.vis_comps = calloc(max_entity, max_entity * sizeof(*entity_memory_pool.components.vis_comps));
	entity_memory_pool.tags = calloc( max_entity ,max_entity * sizeof(*entity_memory_pool.tags));
	entity_memory_pool.flags = calloc(max_entity ,max_entity * sizeof(*entity_memory_pool.flags));
	entity_memory_pool.capacity = max_entity;

	if (!entity_memory_pool.components.trans_comps || !entity_memory_pool.tags|| !entity_memory_pool.flags)
	{
		POFATAL("Failed allocate memory. &s:%d", __FILE__, __LINE__);
		return FALSE;
	}

	return TRUE;
}

u64 ecs_entity_create(const char *tag)
{

	u64 i;

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

	return i;
}

u64 ecs_get_entity_count(void)
{
	return entity_memory_pool.entity_count;
}

b8 ecs_trans_comp_add(u64 entity_id, Vec2 position, Vec2 velocity)
{
	entity_memory_pool.components.trans_comps[entity_id].active = TRUE;
	entity_memory_pool.components.trans_comps[entity_id].position = position;
	entity_memory_pool.components.trans_comps[entity_id].velocity = velocity;

	return TRUE;
}

TransformComp *ecs_trans_comp_get(u64 entity_id)
{
	return &entity_memory_pool.components.trans_comps[entity_id];
}

b8 ecs_vis_comp_add(u64 entity_id, Vec2 size)
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
	entity_memory_pool.components.vis_comps[entity_id].active = TRUE;

	return TRUE;
}

VisibilityComp *ecs_vis_comp_get(u64 entity_id)
{
	return &entity_memory_pool.components.vis_comps[entity_id];
}

const char *ecs_get_tag(u64 entity_id)
{
	return entity_memory_pool.tags[entity_id];
}