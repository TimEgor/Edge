#pragma once

#include "CommonMacros.h"

#if defined(WIN32) || defined(_WIN32)
#define NOMINMAX
#include <Windows.h>

#define EDGE_WIN_PLATFORM

#define EDGE_DYNAMIC_LIB_EXPORT __declspec(dllexport)
#define EDGE_DYNMIC_LIB_IMPORT __declspec(dllimport)

#define EDGE_PLATFORM_MODULE_HANDLE HMODULE
#define EDGE_INVALID_PLATFORM_MODULE_HANDLE nullptr


#define EDGE_DYNAMIC_LIB_EXT dll

#if defined(WIN64) || defined(_WIN64)
#define EDGE_PLATFORM x64
#else
#define EDGE_PLATFORM Win32
#endif

#else
#define EDGE_DYNAMIC_LIB_EXPORT
#define EDGE_DYNMIC_LIB_IMPORT

#define EDGE_PLATFORM_MODULE_HANDLE
#define EDGE_INVALID_PLATFORM_MODULE_HANDLE

#define EDGE_DYNAMIC_LIB_EXT

#define EDGE_PLATFORM
#endif

#define EDGE_DYNAMIC_LIB_EXT_NAME EDGE_TO_STRING_DEF(EDGE_DYNAMIC_LIB_EXT)
#define EDGE_DYNAMIC_LIB_FULL_EXT_NAME EDGE_TO_STRING_DEF(.EDGE_DYNAMIC_LIB_EXT)

#define EDGE_PLATFORM_NAME EDGE_TO_STRING_DEF(EDGE_PLATFORM)