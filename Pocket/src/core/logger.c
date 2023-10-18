#include "logger.h"
#include "../platform/platform.h"

#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>

// Memory bools for store log messages
const char *memory_pool1;
const char *memory_pool2;
const u16 MAX_CHAR = 1024;

b8 log_initialize(void)
{
	// Allocate memory for memory pool
	memory_pool1 = malloc(MAX_CHAR);
	memory_pool2 = malloc(MAX_CHAR);

	if (!memory_pool1 || !memory_pool2)
	{
		POFATAL("Failed to allocate memory for logging buffer. %s:%d", __FILE__, __LINE__);
		return FALSE;
	}

	POINFO("Logging system initialized.");

	return TRUE;
}

void _log_output(u8 level, const char* message, ...)
{
	// Level strings 
	const char *level_string[4] = { "[FATAL]: ", "[ERROR]: ", "[INFO ]: ", "[DEBUG]: "};

	// Create formatted message buffer
	va_list args_ptr;
	va_start(args_ptr, message);
	vsnprintf_s(memory_pool1, MAX_CHAR, MAX_CHAR, message, args_ptr);
	va_end(args_ptr);

	// Concatenate level_string
	sprintf_s(memory_pool2, MAX_CHAR, "%s%s", level_string[level], memory_pool1);
	
	// Output the buffer to console with colors
	platform_console_log(memory_pool2, level);
}

void log_shutdown(void)
{
	if (memory_pool1) { free(memory_pool1); }
	if (memory_pool2) { free(memory_pool2); }
}