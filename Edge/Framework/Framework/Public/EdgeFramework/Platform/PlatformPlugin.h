#pragma once

#include "EdgeFramework/PluginController/Plugin.h"

#define EDGE_PLUGIN_TYPE_PLATFORM
#define EDGE_PLUGIN_TYPE_DECLARATION_PLATFORM Platform

namespace Edge
{
	class Platform;

	class PlatformPlugin : public Plugin
	{
	public:
		PlatformPlugin(PluginModuleID moduleID) : Plugin(moduleID) {}

		virtual Platform* createPlatform() const = 0;

		EDGE_PLUGIN_TYPE(EDGE_PLUGIN_TYPE_PLATFORM, EDGE_PLUGIN_TYPE_DECLARATION_PLATFORM);
	};
}
