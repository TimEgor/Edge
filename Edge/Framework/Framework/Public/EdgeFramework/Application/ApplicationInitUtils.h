#pragma once

#include "EdgeCommon/PlatformMacros.h"
#include "EdgeCommon/FileName/FileName.h"

namespace Edge::ApplicationInitUtils
{
	inline FileName preparePluginName(const FileName& pluginName)
	{
		static const FileName pluginExtension = '_' + FileName(EDGE_CONFIG_NAME) + '_'
			+ FileName(EDGE_PLATFORM_NAME) + FileName(EDGE_DYNAMIC_LIB_FULL_EXT_NAME);

		return pluginName + pluginExtension;
	}

	inline FileName getPlatformPluginName()
	{
		FileName pluginName;

#if defined(WIN32)
		pluginName = "Win32PlatformPlugin";
#endif

		return pluginName ? preparePluginName(pluginName) : "";
	}
}
