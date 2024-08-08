#pragma once

#if defined(WIN32) || defined(_WIN32)

#include "EdgeFramework/PluginController/PluginLoader.h"

namespace Edge
{
	class PluginLoaderWin32 final : public PluginLoader
	{
	public:
		PluginLoaderWin32() = default;

		virtual EDGE_PLATFORM_MODULE_HANDLE loadModule(PluginModuleID moduleID, const FileName& moduleName) override;
		virtual void unloadModule(EDGE_PLATFORM_MODULE_HANDLE moduleHandle) override;

		virtual Plugin* loadPlugin(EDGE_PLATFORM_MODULE_HANDLE moduleHandle, PluginModuleID moduleID, const char* typeName) override;
		virtual void unloadPlugin(EDGE_PLATFORM_MODULE_HANDLE moduleHandle, Plugin* plugin) override;

		virtual void getNativePluginModulePath(const char* title, FileName& outPath) const override;
	};
}
#endif
