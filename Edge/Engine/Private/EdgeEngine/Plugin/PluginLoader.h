#pragma once

#include "EdgeEngine/Core/PlatformMacros.h"
#include "EdgeEngine/Plugin/PluginModuleCore.h"

namespace Edge
{
	class IEngine;
	class IPlugin;
	class FileName;
	
	class PluginLoader
	{
	protected:
		using PluginModuleLoadFunctionPtr = void(*)(PluginModuleID, IEngine*, const FileName&);

		using PluginCreatingFunctionPtr = IPlugin*(*)(PluginModuleID);
		using PluginReleasingFunctionPtr = void(*)(IPlugin*);

	public:
		PluginLoader() = default;
		virtual ~PluginLoader() = default;

		virtual EDGE_PLATFORM_MODULE_HANDLE loadModule(PluginModuleID moduleID, const FileName& moduleName) = 0;
		virtual void unloadModule(EDGE_PLATFORM_MODULE_HANDLE moduleHandle) = 0;

		virtual IPlugin* loadPlugin(EDGE_PLATFORM_MODULE_HANDLE moduleHandle, PluginModuleID moduleID, const char* typeName) = 0;
		virtual void unloadPlugin(EDGE_PLATFORM_MODULE_HANDLE moduleHandle, IPlugin* plugin) = 0;

		virtual void getNativePluginModulePath(const char* title, FileName& outPath) const = 0;
	};
}
