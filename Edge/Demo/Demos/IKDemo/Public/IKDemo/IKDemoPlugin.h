#pragma once

#include "EdgeDemoFramework/Demo/DemoPlugin.h"

namespace EdgeDemo
{
	class IkDemoPlugin final : public DemoPlugin
	{
	public:
		IkDemoPlugin(Edge::PluginModuleID moduleID)
			: DemoPlugin(moduleID) {}

		virtual Demo* createDemo() const override;
	};
}