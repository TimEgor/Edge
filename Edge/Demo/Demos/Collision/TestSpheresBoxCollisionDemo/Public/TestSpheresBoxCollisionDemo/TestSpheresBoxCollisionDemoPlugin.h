#pragma once

#include "EdgeDemoFramework/Demo/DemoPlugin.h"

namespace EdgeDemo
{
	class TestSpheresBoxCollisionDemoPlugin final : public DemoPlugin
	{
	public:
		TestSpheresBoxCollisionDemoPlugin(Edge::PluginModuleID moduleID)
			: DemoPlugin(moduleID) {}

		virtual Demo* createDemo() const override;
	};
}