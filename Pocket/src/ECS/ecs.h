#pragma once
#include "../defines.h"
#include "../math/math.h"
#include "../render/render.h"

#pragma warning (push, 0)
#include <SDL2/SDL.h>
#pragma pop

// Components 
typedef struct TransformComp
{
	Vec2 position;
	Vec2 prev_position;
	Vec2 velocity;
	b8 active;
}TransformComp;

typedef struct VisibilityComp
{
	SDL_Rect rect;
	Color32 color;
	b8 active;
}VisibilityComp;

typedef struct BoundingBoxComp
{
	Vec2 position;
	Vec2 half_size;
	b8 active;
}BoundingBoxComp;

typedef struct ComponentArrays
{
	TransformComp *trans_comps;
	VisibilityComp *vis_comps;
	BoundingBoxComp *bb_comps;
}ComponentArrays;

b8 ecs_initialize();

POAPI u64 ecs_get_entity_count(void);

POAPI u64 ecs_entity_create(const char *tag);

POAPI b8 ecs_trans_comp_add(u64 entity_id, Vec2 position, Vec2 velocity);

POAPI void *ecs_trans_comp_get(u64 entity_id);

POAPI b8 ecs_vis_comp_add(u64 entity_id, Vec2 size, Color32 color);

POAPI void *ecs_vis_comp_get(u64 entity_id);

POAPI b8 ecs_bb_comp_add(u64 entity_id, Vec2 Position, Vec2 size);

POAPI void *ecs_bb_comp_get(u64 entity_id);

POAPI const char *ecs_get_tag(u64 entity_id);


