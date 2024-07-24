#pragma once

#include "EdgeEngine/Plugin/PluginBase.h"

#define EDGE_PLUGIN_TYPE_GRAPHIC_PLATFORM
#define EDGE_PLUGIN_TYPE_DECLARATION_GRAPHIC_PLATFORM GraphicPlatform

namespace Edge
{
	class IGraphicPlatform;

	class GraphicPlatformPlugin : public PluginBase
	{
	public:
		GraphicPlatformPlugin(PluginModuleID moduleID) : PluginBase(moduleID) {}

		virtual IGraphicPlatform* createGraphicPlatform() const = 0;

		EDGE_PLUGIN_TYPE(EDGE_PLUGIN_TYPE_GRAPHIC_PLATFORM, EDGE_PLUGIN_TYPE_DECLARATION_GRAPHIC_PLATFORM);
	};
}
