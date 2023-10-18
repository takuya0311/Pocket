#include "../defines.h"

#ifdef PO_PLATFORM_WINDOWS

#pragma warning (push,0)
#include <windows.h>
#pragma pop
#include <stdio.h>

void platform_console_log(const char *message, u8 level)
{
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO console_info;
	WORD saved_attributes;

	// Save current attributs
	GetConsoleScreenBufferInfo(console, &console_info);
	saved_attributes = console_info.wAttributes;

	switch (level)
	{
		// FATAL
		case 0:
			SetConsoleTextAttribute(console, BACKGROUND_RED);
			break;
		// ERROR
		case 1:
			SetConsoleTextAttribute(console, FOREGROUND_RED);
			break;
		// INFO
		case 2:
			SetConsoleTextAttribute(console, FOREGROUND_GREEN);
			break;
		// DEBUG
		case 3:
			SetConsoleTextAttribute(console, FOREGROUND_BLUE);
			break;

	}
	puts(message);

	// Restore original attributes
	SetConsoleTextAttribute(console, saved_attributes);
}

#endif