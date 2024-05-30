#pragma once

#include "defs.h"

typedef struct
{
    void* internal_state;
} platform_state;

b8 platform_startup(
    platform_state* plat_state,
    const char* application_name,
    i32 width,
    i32 height);

void platform_shutdown(platform_state* plat_state);

b8 platform_pump_messages(platform_state* plat_state);

void* platform_alloc(u64 size, b8 aligned);
void platform_free(void* block, u64 size);
void* platform_memset(void* block, i32 value, u64 size);

f64 platform_get_abs_time();
void platform_sleep(u64 ms);

void platform_console_write(const char* message);
