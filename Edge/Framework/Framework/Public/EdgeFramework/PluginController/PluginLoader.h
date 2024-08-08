#pragma once

#include "EdgeCommon/PlatformMacros.h"

#include "EdgeFramework/PluginController/Plugin.h"

namespace Edge
{
	class PhysicsCore;

	class Application;
	class Plugin;
	class FileName;
	
	class PluginLoader
	{
	protected:
		using PluginModuleLoadFunctionPtr = void(*)(PluginModuleID, AssertGenerator*, Application*, const PhysicsCore&, const FileName&);

		using PluginCreatingFunctionPtr = Plugin*(*)(PluginModuleID);
		using PluginReleasingFunctionPtr = void(*)(Plugin*);

	public:
		PluginLoader() = default;
		virtual ~PluginLoader() = default;

		virtual EDGE_PLATFORM_MODULE_HANDLE loadModule(PluginModuleID moduleID, const FileName& moduleName) = 0;
		virtual void unloadModule(EDGE_PLATFORM_MODULE_HANDLE moduleHandle) = 0;

		virtual Plugin* loadPlugin(EDGE_PLATFORM_MODULE_HANDLE moduleHandle, PluginModuleID moduleID, const char* typeName) = 0;
		virtual void unloadPlugin(EDGE_PLATFORM_MODULE_HANDLE moduleHandle, Plugin* plugin) = 0;

		virtual void getNativePluginModulePath(const char* title, FileName& outPath) const = 0;
	};
}
