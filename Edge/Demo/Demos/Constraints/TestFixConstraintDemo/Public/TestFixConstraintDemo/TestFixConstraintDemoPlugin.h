#pragma once

#include "EdgeDemoFramework/Demo/DemoPlugin.h"

namespace EdgeDemo
{
	class TestFixConstraintDemoPlugin final : public DemoPlugin
	{
	public:
		TestFixConstraintDemoPlugin(Edge::PluginModuleID moduleID)
			: DemoPlugin(moduleID) {}

		virtual Demo* createDemo() const override;
	};
}