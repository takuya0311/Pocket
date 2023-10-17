#include "logger.h"
#include "../platform/platform.h"

#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>

void _log_output(Log_Level level, const char* message, ...)
{
	// Max message size
	const int MAX = 32000;

	// Level strings 
	const char *level_string[4] = { "[FATAL]: ", "[ERROR]: ", "[INFO ]: ", "[DEBUG]: "};

	char * buffer = malloc(MAX);
	if (!buffer)
	{
		puts("Failed to malloc.");
		exit(1);
	}

	// Create formatted message buffer
	va_list args_ptr;
	va_start(args_ptr, message);
	vsnprintf_s(buffer, MAX, MAX, message, args_ptr);
	va_end(args_ptr);

	// Concatenate level_string
	char *buffer2 = malloc(MAX);
	if (!buffer2)
	{
		puts("Failed to malloc.");
		exit(1);
	}
	sprintf_s(buffer2, MAX, "%s%s", level_string[level], buffer);
	
	// Output the buffer to console with colors
	platform_console_log(buffer2, level);
	
	// Free buffers
	free(buffer);
	free(buffer2);
}