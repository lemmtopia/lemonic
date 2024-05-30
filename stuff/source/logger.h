#include "defs.h"
#include "platform.h"

typedef enum
{
    LOG_LEVEL_FATAL,
    LOG_LEVEL_ERROR,
    LOG_LEVEL_WARN,
    LOG_LEVEL_INFO	
} log_level;

void log_output(log_level level, const char* message);
