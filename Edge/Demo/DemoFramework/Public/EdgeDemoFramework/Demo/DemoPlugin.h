#pragma once

#include "EdgeFramework/PluginController/Plugin.h"

#define EDGE_PLUGIN_TYPE_DEMO
#define EDGE_PLUGIN_TYPE_DECLARATION_DEMO Demo

namespace EdgeDemo
{
	class Demo;

	class DemoPlugin : public Edge::Plugin
	{
	public:
		DemoPlugin(Edge::PluginModuleID moduleID) : Plugin(moduleID) {}

		virtual Demo* createDemo() const = 0;

		EDGE_PLUGIN_TYPE(EDGE_PLUGIN_TYPE_DEMO, EDGE_PLUGIN_TYPE_DECLARATION_DEMO);
	};
}
