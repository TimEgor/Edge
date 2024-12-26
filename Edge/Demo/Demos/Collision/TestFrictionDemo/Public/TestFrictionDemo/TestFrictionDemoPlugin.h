#pragma once

#include "EdgeDemoFramework/Demo/DemoPlugin.h"

namespace EdgeDemo
{
	class TestFrictionDemoPlugin final : public DemoPlugin
	{
	public:
		TestFrictionDemoPlugin(Edge::PluginModuleID moduleID)
			: DemoPlugin(moduleID) {}

		virtual Demo* createDemo() const override;
	};
}