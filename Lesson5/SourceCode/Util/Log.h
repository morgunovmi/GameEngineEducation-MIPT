#pragma once
#include <Windows.h>

#define LogZA(fmt, ...) \
{ \
	char message[2048]; \
	sprintf_s(message, 2048, fmt, __VA_ARGS__); \
	char file_line_message[2048]; \
	sprintf_s(file_line_message, 2048, "%s(%i,0): %s\n", __FILE__, __LINE__, message); \
	printf(file_line_message); \
	OutputDebugStringA(file_line_message); \
}

#define LogError(fmt, ...) \
{ \
	char message[2048]; \
	sprintf_s(message, 2048, fmt, __VA_ARGS__); \
	char file_line_message[2048]; \
	sprintf_s(file_line_message, 2048, "%s(%i,0): %s\n", __FILE__, __LINE__, message); \
	printf(file_line_message); \
	OutputDebugStringA(file_line_message); \
	assert(0 && file_line_message); \
}