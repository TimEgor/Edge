#pragma once

#include "Plugin.h"

#define EDGE_PLUGIN_TYPE_GENERAL
#define EDGE_PLUGIN_TYPE_DECLARATION_GENERAL General

namespace Edge
{
	class PluginGeneral : public Plugin
	{
	public:
		PluginGeneral(PluginModuleID moduleID)
			: Plugin(moduleID) {}

		EDGE_PLUGIN_TYPE(EDGE_PLUGIN_TYPE_GENERAL, EDGE_PLUGIN_TYPE_DECLARATION_GENERAL)
	};
}
