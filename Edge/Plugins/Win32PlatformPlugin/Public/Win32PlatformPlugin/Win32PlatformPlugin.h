#pragma once

#include "EdgeEngine/Platform/IPlatform.h"
#include "EdgeEngine/Platform/PlatformPlugin.h"

namespace Edge_WIN32
{
	class Win32PlatformPlugin final : public Edge::PlatformPlugin
	{
	public:
		Win32PlatformPlugin(Edge::PluginModuleID moduleID)
			: PlatformPlugin(moduleID) {}

		virtual Edge::IPlatform* createPlatform() const override;
	};
}