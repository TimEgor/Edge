#pragma once

#include "EdgeEngine/Plugin/PluginBase.h"

#define EDGE_PLUGIN_TYPE_RENDER
#define EDGE_PLUGIN_TYPE_DECLARATION_RENDER Render

namespace Edge
{
	class IRender;

	class RenderPlugin : public PluginBase
	{
	public:
		RenderPlugin(PluginModuleID moduleID) : PluginBase(moduleID) {}

		virtual IRender* createRenderer() const = 0;

		EDGE_PLUGIN_TYPE(EDGE_PLUGIN_TYPE_RENDER, EDGE_PLUGIN_TYPE_DECLARATION_RENDER);
	};
}
