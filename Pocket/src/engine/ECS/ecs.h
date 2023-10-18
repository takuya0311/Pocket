#pragma once
#include "../defines.h"
#include "../math/math.h"

#pragma warning (push, 0)
#include <SDL2/SDL.h>
#pragma pop

// Components 
typedef struct TransformComp
{
	Vec2 position;
	Vec2 velocity;
	b8 active;
}TransformComp;

typedef struct VisibilityComp
{
	SDL_Rect rect;
	b8 active;
}VisibilityComp;

typedef struct ComponentArrays
{
	TransformComp *trans_comps;
	VisibilityComp *vis_comps;
}ComponentArrays;

b8 ecs_setup(u64 max_entity);

u64 ecs_get_entity_count(void);

u64 ecs_entity_create(const char *tag);

b8 ecs_trans_comp_add(u64 entity_id, Vec2 position, Vec2 velocity);
TransformComp *ecs_trans_comp_get(u64 entity_id);

b8 ecs_vis_comp_add(u64 entity_id, Vec2 size);
VisibilityComp *ecs_vis_comp_get(u64 entity_id);

const char *ecs_get_tag(u64 entity_id);


