#pragma once

#include "PluginBase.h"

#define EDGE_PLUGIN_TYPE_GENERAL
#define EDGE_PLUGIN_TYPE_DECLARATION_GENERAL General

namespace Edge
{
	class PluginGeneral : public PluginBase
	{
	public:
		PluginGeneral(PluginModuleID moduleID)
			: PluginBase(moduleID) {}

		EDGE_PLUGIN_TYPE(EDGE_PLUGIN_TYPE_GENERAL, EDGE_PLUGIN_TYPE_DECLARATION_GENERAL)
	};
}
