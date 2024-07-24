#pragma once

#include "EdgeEngine/Plugin/PluginBase.h"

#include "PluginHandle.h"

#include <type_traits>

namespace Edge
{
	class FileName;

	class IPluginController
	{
	public:
		IPluginController() = default;
		virtual ~IPluginController() = default;

		virtual bool init() = 0;
		virtual void release() = 0;

		virtual PluginHandleReference loadPlugin(const FileName& moduleName, PluginType pluginType, const char* generatorName) = 0;
		virtual PluginHandleReference getPlugin(PluginID pluginID) = 0;

		virtual void unloadPlugin(PluginHandle* pluginHandle) = 0;

		template <typename PluginType = PluginBase>
		PluginHandleReference loadTypedPlugin(const FileName& moduleName)
		{
			static_assert(std::is_base_of_v<PluginBase, PluginType>);
			return loadPlugin(moduleName, PluginType::getPluginType(), PluginType::GetPluginModuleGeneratorName());
		}

		virtual FileName getNativePluginModulePath(const char* title) const = 0;
		virtual void getNativePluginModulePath(const char* title, FileName& name) const = 0;
	};
}
