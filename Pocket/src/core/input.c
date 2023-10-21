#include "../defines.h"
#include "input.h"
#include "../global.h"
#include "logger.h"
#include <string.h>

int *array_length;

b8 input_initialize(void)
{
	global.key.current = SDL_GetKeyboardState(array_length);

	global.key.prev = malloc(array_length);
	if (!global.key.prev)
	{
		POFATAL("Failed to malloc.");
		return FALSE;
	}
	memset(global.key.prev, 0, array_length);

	return TRUE;
}

void input_update(void)
{
	memcpy(global.key.prev, global.key.current, sizeof(global.key.prev));
}


POAPI b8 key_held(Keys key)
{
	return (global.key.current[key] && global.key.prev[key]);
}

POAPI b8 key_pressed(Keys key)
{
	return (global.key.current[key] && !global.key.prev[key]);
}

POAPI b8 key_released(Keys key)
{
	return (!global.key.current[key] && global.key.prev[key]);
}