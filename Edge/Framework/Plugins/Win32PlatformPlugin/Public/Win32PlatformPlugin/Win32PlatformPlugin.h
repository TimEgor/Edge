#pragma once

#include "EdgeFramework/Platform/PlatformPlugin.h"

namespace EdgeWin32
{
	class Win32PlatformPlugin final : public Edge::PlatformPlugin
	{
	public:
		Win32PlatformPlugin(Edge::PluginModuleID moduleID)
			: PlatformPlugin(moduleID) {}

		virtual Edge::Platform* createPlatform() const override;
	};
}
