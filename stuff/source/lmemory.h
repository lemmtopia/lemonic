#pragma once

#include "defs.h"

typedef enum
{
    MEMORY_TAG_UNKNOWN,
    MEMORY_TAG_ARRAY,
    MEMORY_TAG_STRING,
    MEMORY_TAG_ENTITY,
    MEMORY_TAG_SCENE,
    MEMORY_TAG_GAME,

    MEMORY_TAG_MAX_TAGS
} memory_tag;

void memory_initialize();
void memory_shutdown();

void* memory_alloc(u64 size, memory_tag tag);
void memory_free(void* block, u64 size, memory_tag tag);
void* memory_zero(void* block, u64 size);
void* memory_set(void* dest, i32 value, u64 size);
