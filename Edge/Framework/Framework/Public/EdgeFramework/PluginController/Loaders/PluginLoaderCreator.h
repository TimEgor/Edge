#pragma once

#if defined(WIN32) || defined(_WIN32)
#include "PluginLoaderWin32.h"
#endif

namespace Edge
{
	inline PluginLoader* createPluginLoader()
	{
#if defined(WIN32) || defined(_WIN32)
		return new PluginLoaderWin32;
#endif
	}
}
