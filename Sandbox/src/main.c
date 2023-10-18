#include <Pocket.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

Config config;

const int max_ent = 1000;

void init(void)
{
	srand(time(NULL));

	for (u64 i = 0; i < 2; i++)
	{
		u64 id = ecs_entity_create("white");
		if (id == -1)
		{
			break;
		}
		ecs_trans_comp_add(id, (Vec2) { rand() % (config.screen_w - 30) + 30, rand() % (config.screen_h - 30) + 30
		}, (Vec2){200, 200 });
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

			if (t_c->position.x + v_c->rect.w > config.screen_w || t_c->position.x < 0)
			{
				t_c->velocity.x *= -1;
			}

			if (t_c->position.y + v_c->rect.h > config.screen_h || t_c->position.y < 0)
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
			Vec2 overlap;
			Vec2 prev_overlap;
			b8 has_collide;
			
			if (i == j)
			{
				continue;
			}
			TransformComp *t_c2 = ecs_trans_comp_get(j);
			BoundingBoxComp *b_c2 = ecs_bb_comp_get(j);
			VisibilityComp *v_c2 = ecs_bb_comp_get(j);
			
			// check for current overlap
			has_collide = physics_aabb_collision_detection(
				(AABB)
			{
				.position = t_c->position, .half_size = b_c->half_size
			},
				(AABB)
			{
				.position = t_c2->position, .half_size = b_c2->half_size
			},
				&overlap
			);

			if (!has_collide)
			{
				continue;
			}

			//calluculate prev overlap
			physics_aabb_collision_detection(
				(AABB)
			{
				.position = t_c->prev_position, .half_size = b_c->half_size
			},
				(AABB)
			{
				.position = t_c2->prev_position, .half_size = b_c2->half_size
			},
				&prev_overlap
			);

			// resolve collision
			if (prev_overlap.x > 0)
			{
				if (t_c->prev_position.y - t_c->position.y < 0)
				{
					t_c->position.y -= overlap.y;
					t_c->velocity.y *= -1;
				}
				else
				{
					t_c->position.y += overlap.y;
					t_c->velocity.y *= -1;
				}

				if (t_c2->prev_position.y - t_c2->position.y < 0)
				{
					t_c2->position.y -= overlap.y;
					t_c2->velocity.y *= -1;
				}
				else
				{
					t_c2->position.y += overlap.y;
					t_c2->velocity.y *= -1;
				}
			}
			else if (prev_overlap.y > 0 || (prev_overlap.x > 0 && prev_overlap.y > 0))
			{
				if (t_c->prev_position.x - t_c->position.x < 0)
				{
					t_c->position.x -= overlap.x;
					t_c->velocity.x *= -1;
				}
				else
				{
					t_c->position.x += overlap.x;
					t_c->velocity.x *= -1;
				}

				if (t_c2->prev_position.x - t_c2->position.x < 0)
				{
					t_c2->position.x -= overlap.x;
					t_c2->velocity.x *= -1;
				}
				else
				{
					t_c2->position.x += overlap.x;
					t_c2->velocity.x *= -1;
				}
			}
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
			render_fill_rect(t_c->position, (Vec2) { v_c->rect.w, v_c->rect.h }, v_c->color);
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

