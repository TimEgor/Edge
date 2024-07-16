#pragma once

#include "PlatformMacros.h"
#include "String/StringConverter.h"

namespace Edge
{
	namespace ThreadUtils
	{
		inline void SetThreadName(void* threadNandle, const char* name)
		{
#ifdef EDGE_WIN_PLATFORM
			SetThreadDescription(threadNandle, ConvertStringToWString(name).c_str());
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