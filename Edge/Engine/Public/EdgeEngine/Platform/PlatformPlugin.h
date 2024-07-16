#pragma once

#include "EdgeEngine/Plugin/PluginBase.h"

#define EDGE_PLUGIN_TYPE_PLATFORM
#define EDGE_PLUGIN_TYPE_DECLARATION_PLATFORM Platform

namespace Edge
{
	class Platform;

	class PlatformPlugin : public PluginBase
	{
	public:
		PlatformPlugin(PluginModuleID moduleID) : PluginBase(moduleID) {}

		virtual Platform* createPlatform() const = 0;

		EDGE_PLUGIN_TYPE(EDGE_PLUGIN_TYPE_PLATFORM, EDGE_PLUGIN_TYPE_DECLARATION_PLATFORM);
	};
}
