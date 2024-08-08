#pragma once

#include "EdgeFramework/PluginController/Plugin.h"

#define EDGE_PLUGIN_TYPE_RENDER
#define EDGE_PLUGIN_TYPE_DECLARATION_RENDER Render

namespace Edge
{
	class Renderer;

	class RendererPlugin : public Plugin
	{
	public:
		RendererPlugin(PluginModuleID moduleID) : Plugin(moduleID) {}

		virtual Renderer* createRenderer() const = 0;

		EDGE_PLUGIN_TYPE(EDGE_PLUGIN_TYPE_RENDER, EDGE_PLUGIN_TYPE_DECLARATION_RENDER);
	};
}
