#include "application.h"

#include "platform.h"
#include "logger.h"

typedef struct
{
    b8 is_running;
    b8 is_active;
    platform_state plat_state;
    i16 width;
    i16 height;
} application_state;

static b8 initialized = FALSE;
static application_state app_state;

b8 application_create(application_info* info)
{
    if (initialized)
    {
	log_output(LOG_LEVEL_FATAL, "application_create called more than once.");
	return FALSE;
    }

    app_state.is_running = TRUE;
    app_state.is_active = TRUE;

    if (!platform_startup(
	    &app_state.plat_state,
	    info->name,
	    info->width,
	    info->height))
    {
	return FALSE;
    }

    initialized = TRUE;
    return TRUE;
}

b8 application_run()
{
    while (app_state.is_running)
    {
	if (!platform_pump_messages(&app_state.plat_state))
	{
	    app_state.is_running = FALSE;
	}
    }

    return TRUE;
}

void application_destroy()
{
    platform_shutdown(&app_state.plat_state);
}
