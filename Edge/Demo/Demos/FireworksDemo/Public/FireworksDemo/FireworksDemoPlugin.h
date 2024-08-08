#pragma once

#include "TinySimDemoFramework/Demo/DemoPlugin.h"

namespace TS_DEMO
{
	class FireworksDemoPlugin final : public DemoPlugin
	{
	public:
		FireworksDemoPlugin(TS::PluginModuleID moduleID)
			: DemoPlugin(moduleID) {}

		virtual Demo* createDemo() const override;
	};
}