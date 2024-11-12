#pragma once

#include "EdgeDemoFramework/Demo/DemoPlugin.h"

namespace EdgeDemo
{
	class TestKeepDistanceConstraintDemoPlugin final : public DemoPlugin
	{
	public:
		TestKeepDistanceConstraintDemoPlugin(Edge::PluginModuleID moduleID)
			: DemoPlugin(moduleID) {}

		virtual Demo* createDemo() const override;
	};
}