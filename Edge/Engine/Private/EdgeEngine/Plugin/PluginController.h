#pragma once

#include "EdgeEngine/Core/Multithreading/Mutex.h"
#include "EdgeEngine/Plugin/IPluginController.h"

#include <unordered_map>


namespace Edge
{
	class PluginLoader;
	class FileName;

	class PluginController final : public IPluginController
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

		void unloadPlugin(IPlugin* plugin);
		void unloadPlugin(PluginID pluginID);

		static PluginModuleID getModuleID(const FileName& moduleName);

	public:
		PluginController() = default;

		virtual bool init() override;
		virtual void release() override;

		virtual PluginHandleReference loadPlugin(const FileName& moduleName, PluginType pluginType, const char* generatorName) override;
		virtual PluginHandleReference getPlugin(PluginID pluginID) override;

		virtual void unloadPlugin(PluginHandle* pluginHandle) override;

		virtual FileName getNativePluginModulePath(const char* title) const override;
		virtual void getNativePluginModulePath(const char* title, FileName& name) const override;
	};
}
