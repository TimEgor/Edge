#pragma once

#include "EdgeEngine/Core/Patterns/NonCopyable.h"
#include "EdgeEngine/Core/Reference/MTReference.h"

namespace Edge
{
	class IPlugin;

	class PluginHandle final : public MTCountableObjectBase, public NonCopyable
	{
	private:
		IPlugin* m_plugin = nullptr;

		virtual void selfDestroy() override;

	public:
		PluginHandle(IPlugin* plugin);

		IPlugin& getPlugin();
		const IPlugin& getPlugin() const;

		template <typename PluginType>
		PluginType& getPluginCast()
		{
			static_assert(std::is_base_of_v<IPlugin, PluginType>);
			return reinterpret_cast<PluginType&>(getPlugin());
		}

		template <typename PluginType>
		const PluginType& getPluginCast() const
		{
			static_assert(std::is_base_of_v<IPlugin, PluginType>);
			return reinterpret_cast<const PluginType&>(getPlugin());
		}
	};

	EDGE_MT_REFERENCE(PluginHandle);
}
