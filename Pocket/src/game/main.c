#include "../engine/Pocket.h"

Config config;

void init(void)
{
	
	ecs_setup(100);


	u64 id = ecs_entity_create("player");
	ecs_trans_comp_add(id, (Vec2) { config.screen_w * 0.5, config.screen_h * 0.5 }, (Vec2) { 1, 0 });
	ecs_vis_comp_add(id, (Vec2) { 10, 10 });
}

b8 update(f32 delta)
{

	for (u64 i = 0; i < ecs_get_entity_count(); i++)
	{
		TransformComp *t_c = ecs_trans_comp_get(i);
		if (t_c->active)
		{
			t_c->position.x += t_c->velocity.x;
			t_c->position.y += t_c->velocity.y;

			if (t_c->position.x > config.screen_w || t_c->position.x < 0)
			{
				t_c->velocity.x *= -1;
			}

			if (t_c->position.y > config.screen_w || t_c->position.y < 0)
			{
				t_c->velocity.y *= -1;
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
		if (t_c->active || v_c->active)
		{
			render_fill_rect(t_c->position, (Vec2) { v_c->rect.w, v_c->rect.h }, WHITE);
		}
	}

	return TRUE;
}

int main(int argc, char * argv[])
{
	config.title = "test";
	config.screen_w = 256;
	config.screen_h = 240;
	config.pixel_size = 4;
	config.user_init = init;
	config.user_update = update;
	config.user_render = render;

	
	app_start(&config);

	return 0;
}

