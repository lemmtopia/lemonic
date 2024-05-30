#include "lmemory.h"
#include "logger.h"
#include "platform.h"

struct memory_stats
{
    u64 total_allocated;
    u64 tagged_allocations[MEMORY_TAG_MAX_TAGS];
};

static struct memory_stats stats;

void memory_initialize()
{
    platform_memset(&stats, 0, sizeof(stats));
}

void memory_shutdown()
{
    
}

void* memory_alloc(u64 size, memory_tag tag)
{
    if (tag == MEMORY_TAG_UNKNOWN)
    {
	log_output(
	    LOG_LEVEL_WARN,
	    "memory_alloc called using MEMORY_TAG_UNKNOWN");
    }

    stats.total_allocated += size;
    stats.tagged_allocations[tag] += size;
    
    // TODO: memory alignment
    void* block = platform_alloc(size, FALSE);
    memory_zero(block, size);
    return block;
}

void memory_free(void* block, u64 size, memory_tag tag)
{
    if (tag == MEMORY_TAG_UNKNOWN)
    {
	log_output(
	    LOG_LEVEL_WARN,
	    "memory_free called using MEMORY_TAG_UNKNOWN");
    }

    stats.total_allocated -= size;
    stats.tagged_allocations[tag] -= size;

    // TODO: memory alignment
    platform_free(block, FALSE);
}

void* memory_zero(void* block, u64 size)
{
    return platform_memset(block, 0, size);
}

void* memory_set(void* dest, i32 value, u64 size)
{
    return platform_memset(dest, value, size);
}
