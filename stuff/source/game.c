#include "game.h"

#include "lmemory.h"

// This file just abstracts the platform to the main.c file
b8 game_initialize(game* g)
{
    memory_initialize();
    
    g->app_info.width = 800;
    g->app_info.height = 600;
    g->app_info.name = "lemonic";
    
    g->state = memory_alloc(1024, MEMORY_TAG_GAME);
    memory_zero(g->state, 1024);
    return application_create(&g->app_info);
}

void game_run(game* g)
{
    application_run();
}

void game_shutdown(game* g)
{
    application_destroy();

    memory_free(g->state, 1024, MEMORY_TAG_GAME);
    memory_shutdown();
}
