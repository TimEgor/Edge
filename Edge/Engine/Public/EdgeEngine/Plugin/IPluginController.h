#pragma once

#include "EdgeEngine/Plugin/PluginBase.h"

#include "PluginHandle.h"


namespace Edge
{
	class FileName;

	class IPluginController
	{
		struct ModuleInfo final
		{
			EDGE_PLATFORM_MODULE_HANDLE m_moduleHandle = EDGE_INVALID_PLATFORM_MODULE_HANDLE;
			uint32_t m_counter = 0;

			ModuleInfo() = default;
			ModuleInfo(EDGE_PLATFORM_MODULE_HANDLE moduleHandle)
				: m_moduleHandle(moduleHandle) {}
		};

	public:
		IPluginController() = default;
		virtual ~IPluginController() = default;

		virtual bool init() = 0;
		virtual void release() = 0;

		virtual PluginHandleReference loadPlugin(const FileName& moduleName, PluginType pluginType, const char* generatorName) = 0;
		virtual PluginHandleReference getPlugin(PluginID pluginID) = 0;

		virtual void unloadPlugin(PluginHandle* pluginHandle) = 0;

		template <typename PluginType = PluginBase>
		PluginHandleReference loadPlugin(const FileName& moduleName)
		{
			static_assert(std::is_base_of_v<PluginBase, PluginType>);
			return loadPlugin(moduleName, PluginType::getPluginType(), PluginType::getPluginModuleGeneratorName());
		}

		virtual FileName getNativePluginModulePath(const char* title) const = 0;
		virtual void getNativePluginModulePath(const char* title, FileName& name) const = 0;
	};
}
