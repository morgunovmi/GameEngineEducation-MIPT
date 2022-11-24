#pragma once

#include <Windows.h>
#include <format>

#ifndef NDEBUG
#define lidl_assert(cond, message, ...) \
do \
{ \
	static bool ignore = false;\
	if (!(cond)) \
	{ \
		std::string output = std::format(message, __VA_ARGS__); \
		std::string msg = std::format("{}({},0): ASSERTION FAIL: {}", __FILE__, __LINE__, output); \
		OutputDebugStringA(msg.c_str()); \
		OutputDebugStringA("\n"); \
		if (!ignore) \
		{ \
			int result = MessageBoxA(NULL, msg.c_str(), "ERROR", MB_ABORTRETRYIGNORE); \
			if (result == IDABORT) \
				abort(); \
			else if (result == IDRETRY) \
				__debugbreak(); \
			else if (result == IDIGNORE) \
			{ \
				ignore = true; \
			} \
		} \
	} \
} \
while (false);
#else
#define lidl_assert(cond, message, ...)
#endif