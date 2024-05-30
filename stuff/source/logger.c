#include "logger.h"

#include <stdio.h>
#include <string.h>

void log_output(log_level level, const char* message)
{
    const char* level_tag[] = {	"FATAL", "ERROR", "WARN", "INFO" };

    char buff[32000];
    sprintf(buff, "%s: %s\n", level_tag[level], message);
    platform_console_write(buff);
}
