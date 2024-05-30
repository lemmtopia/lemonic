#pragma once

#include "defs.h"
#include "application.h"
#include "logger.h"

typedef struct
{
    application_info app_info;
    void* state;
} game;

b8 game_initialize(game* g);
void game_run(game* g);
void game_shutdown(game* g);
