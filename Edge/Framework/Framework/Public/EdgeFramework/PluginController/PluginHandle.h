#pragma once

#include "EdgeCommon/Patterns/NonCopyable.h"
#include "EdgeCommon/Reference/Reference.h"

namespace Edge
{
	class Plugin;

	class PluginHandle final : public MTCountableObjectBase, public NonCopyable
	{
	private:
		Plugin* m_plugin = nullptr;

		virtual void selfDestroy() override;

	public:
		PluginHandle(Plugin* plugin);

		Plugin& getPlugin();
		const Plugin& getPlugin() const;

		template <typename PluginType>
		PluginType& getPluginCast()
		{
			static_assert(std::is_base_of_v<Plugin, PluginType>);
			return reinterpret_cast<PluginType&>(getPlugin());
		}

		template <typename PluginType>
		const PluginType& getPluginCast() const
		{
			static_assert(std::is_base_of_v<Plugin, PluginType>);
			return reinterpret_cast<const PluginType&>(getPlugin());
		}
	};

	EDGE_REFERENCE(PluginHandle);
}
