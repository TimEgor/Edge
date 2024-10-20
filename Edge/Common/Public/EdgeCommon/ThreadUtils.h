#pragma once

#include "PlatformMacros.h"
#include "String/StringConverter.h"

namespace Edge
{
	namespace ThreadUtils
	{
		inline void SetThreadName(void* threadHandle, const char* name)
		{
#ifdef EDGE_WIN_PLATFORM
			SetThreadDescription(threadHandle, ConvertStringToWString(name).c_str());
#endif
		}

		inline void SetThreadName(const char* name)
		{
#ifdef EDGE_WIN_PLATFORM
			SetThreadName(GetCurrentThread(), name);
#endif
		}
	}
}