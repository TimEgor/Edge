#pragma once

#include "EdgeCommon/Multithreading/Mutex.h"

#include "PluginHandle.h"
#include "EdgeFramework/PluginController/Plugin.h"

#include <unordered_map>

namespace Edge
{
	class PluginLoader;
	class FileName;

	class PluginController final
	{
		struct ModuleInfo final
		{
			EDGE_PLATFORM_MODULE_HANDLE m_moduleHandle = EDGE_INVALID_PLATFORM_MODULE_HANDLE;
			uint32_t m_counter = 0;

			ModuleInfo() = default;
			ModuleInfo(EDGE_PLATFORM_MODULE_HANDLE moduleHandle)
				: m_moduleHandle(moduleHandle) {}
		};

		using ModuleInfoContainer = std::unordered_map<PluginModuleID, ModuleInfo>;
		using PluginContainer = std::unordered_map<PluginID, PluginHandle>;

	private:
		mutable RecursiveMutex m_mutex;

		ModuleInfoContainer m_moduleInfos;
		PluginContainer m_plugins;

		PluginLoader* m_loader = nullptr;

		void unloadPlugin(Plugin* plugin);
		void unloadPlugin(PluginID pluginID);

		static PluginModuleID getModuleID(const FileName& moduleName);

	public:
		PluginController() = default;
		~PluginController() { release(); }

		bool init();
		void release();

		PluginHandleReference loadPlugin(const FileName& moduleName, PluginType pluginType, const char* generatorName);
		PluginHandleReference getPlugin(PluginID pluginID);

		void unloadPlugin(PluginHandle* pluginHandle);

		template <typename PluginType = Plugin>
		PluginHandleReference loadPlugin(const FileName& moduleName)
		{
			static_assert(std::is_base_of_v<Plugin, PluginType>);
			return loadPlugin(moduleName, PluginType::getPluginType(), PluginType::getPluginModuleGeneratorName());
		}

		FileName getNativePluginModulePath(const char* title) const;
		void getNativePluginModulePath(const char* title, FileName& name) const;
	};
}