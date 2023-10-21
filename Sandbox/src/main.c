#include <Pocket.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

Config config;

const int max_ent = 1000;

void init(void)
{
	srand(time(NULL));

	for (u64 i = 0; i < 5; i++)
	{
		u64 id = ecs_entity_create("white");
		if (id == -1)
		{
			break;
		}
		ecs_trans_comp_add(id, (Vec2) { rand() % (config.screen_w - 50) + 50, rand() % (config.screen_h - 100) + 50}, (Vec2){200, 200 });
		ecs_vis_comp_add(id, (Vec2) { 50, 50}, WHITE);
		TransformComp *t_c = (TransformComp *)ecs_trans_comp_get(id);
		ecs_bb_comp_add(id, t_c->position, (Vec2) { 50, 50 });
	}
}

b8 update(f32 delta)
{
	// update position
	for (u64 i = 0; i < ecs_get_entity_count(); i++)
	{	
		TransformComp *t_c = ecs_trans_comp_get(i);
		VisibilityComp *v_c = ecs_vis_comp_get(i);
		if (t_c->active && v_c->active)
		{
			t_c->prev_position = t_c->position;
			
			t_c->position.x += t_c->velocity.x * delta;
			t_c->position.y += t_c->velocity.y * delta;

			if (t_c->position.x + v_c->size.w > config.screen_w || t_c->position.x < 0)
			{
				t_c->velocity.x *= -1;
			}

			if (t_c->position.y + v_c->size.h > config.screen_h || t_c->position.y < 0)
			{
				t_c->velocity.y *= -1;
			}
		}
	}

	// collision detection
	for (u64 i = 0; i < ecs_get_entity_count(); i++)
	{
		TransformComp *t_c = ecs_trans_comp_get(i);
		BoundingBoxComp *b_c = ecs_bb_comp_get(i);
		VisibilityComp *v_c = ecs_bb_comp_get(i);
		if (!t_c->active || !b_c->active)
		{
			continue;
		}

		for (u64 j = 0; j < ecs_get_entity_count(); j++)
		{
			Vec2 overlap = {0};
			Vec2 prev_overlap = {0};
			b8 has_collide = FALSE;
			
			if (i == j)
			{
				continue;
			}
			TransformComp *t_c2 = ecs_trans_comp_get(j);
			BoundingBoxComp *b_c2 = ecs_bb_comp_get(j);
			VisibilityComp *v_c2 = ecs_bb_comp_get(j);
			
			// check for current overlap
			has_collide = phys_collision_aabb_detect(t_c->position, b_c->half_size, t_c2->position, b_c2->half_size, &overlap);

			if (!has_collide)
			{
				continue;
			}

			//calluculate prev overlap
			phys_collision_aabb_detect(t_c->prev_position, b_c->half_size, t_c2->prev_position, b_c2->half_size, &prev_overlap);

			// resolve collision
			phys_collision_resolute(&t_c->position, &t_c->velocity, &t_c->prev_position, overlap, prev_overlap, TRUE);
			phys_collision_resolute(&t_c2->position, &t_c2->velocity, &t_c2->prev_position, overlap, prev_overlap, TRUE);
		}
		
	}

	return TRUE;
}

b8 render(void)
{
	
	for (u64 i = 0; i < ecs_get_entity_count(); i++)
	{
		TransformComp *t_c = ecs_trans_comp_get(i);
		VisibilityComp *v_c = ecs_vis_comp_get(i);
		if (t_c->active && v_c->active)
		{
			render_fill_rect(t_c->position, (Vec2) { v_c->size.w, v_c->size.h }, v_c->color);
		}
	}

	return TRUE;
}

int main(int argc, char * argv[])
{
	config.title = "test";
	config.screen_w = 800;
	config.screen_h = 600;
	config.pixel_size = 1;
	config.user_init = init;
	config.user_update = update;
	config.user_render = render;
	config.frame_rate_target = 100;

	app_start(&config);

	return 0;
}

