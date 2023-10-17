#include "../engine/Pocket.h"

void init(void)
{

}

u8 update(f32 delta)
{

}

int main()
{
	if (app_create("test", 256, 240, 4, init, update))
	{
		app_start();
	}

	return 0;
}

