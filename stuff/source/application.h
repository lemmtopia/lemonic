#pragma once

#include "defs.h"

typedef struct
{
    i16 width;
    i16 height;
    char* name;
} application_info;

b8 application_create(application_info* info);
b8 application_run();
void application_destroy();
