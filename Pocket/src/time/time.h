#pragma once

#include "../defines.h"

typedef struct time_state
{
    f32 delta;
    f32 now;
    f32 last;

    f32 frame_last;
    f32 frame_delay;
    f32 frame_time;

    u32 frame_rate;
    u32 frame_count;
}Time_State;

b8 time_initialize(u32 frame_rate);
void time_update(void);
void time_update_late(void);