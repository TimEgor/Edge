#pragma once

#include "EdgeFramework/PluginController/Plugin.h"

#define EDGE_PLUGIN_TYPE_GRAPHIC_PLATFORM
#define EDGE_PLUGIN_TYPE_DECLARATION_GRAPHIC_PLATFORM GraphicPlatform

namespace Edge
{
	class GraphicPlatform;

	class GraphicPlatformPlugin : public Plugin
	{
	public:
		GraphicPlatformPlugin(PluginModuleID moduleID) : Plugin(moduleID) {}

		virtual GraphicPlatform* createGraphicPlatform() const = 0;

		EDGE_PLUGIN_TYPE(EDGE_PLUGIN_TYPE_GRAPHIC_PLATFORM, EDGE_PLUGIN_TYPE_DECLARATION_GRAPHIC_PLATFORM);
	};
}
