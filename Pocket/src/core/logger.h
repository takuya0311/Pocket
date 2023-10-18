#pragma once
#include "../defines.h"

enum log_level
{
	LOG_FATAL,
	LOG_ERROR,
	LOG_INFO,
	LOG_DEBUG,
}Log_Level;

void _log_output(u8 level, const char * message, ...);
b8 log_initialize(void);
void log_shutdown(void);

// === MACROS ===

// Logs a FATAL level message
#ifndef POFATAL
#define POFATAL(message, ...) _log_output(LOG_FATAL, message, __VA_ARGS__)
#endif 

// Logs a ERROR level message
#ifndef POERROR
#define POERROR(message, ...) _log_output(LOG_ERROR, message, __VA_ARGS__)
#endif 

// Logs a INFO level message
#ifndef POINFO
#define POINFO(message, ...) _log_output(LOG_INFO, message, __VA_ARGS__)
#endif 

// Logs a DEBUG level message
#ifndef PODEBUG
#ifdef _DEBUG
	#define PODEBUG(message, ...) _log_output(LOG_DEBUG, message, __VA_ARGS__)
#else 
	#define PODEBUG 
#endif 
#endif 