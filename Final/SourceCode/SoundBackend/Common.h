#pragma once

#pragma warning(disable:4251)

#ifdef SOUNDBACKEND_EXPORTS
#define SOUNDBACKEND_API __declspec(dllexport)
#else
#define SOUNDBACKEND_API __declspec(dllimport)
#endif