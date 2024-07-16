#pragma once

#include "IPlugin.h"

namespace Edge
{
	class PluginBase : public IPlugin
	{
	private:
		const PluginModuleID m_moduleID = InvalidPluginModuleID;

	public:
		PluginBase(PluginModuleID moduleID)
			: m_moduleID(moduleID) {}

		virtual void onLoaded() override {}
		virtual void onUnloaded() override {}

		virtual PluginModuleID getModuleID() const override { return m_moduleID; }
		virtual PluginID getPluginID() const override { return calcPluginID(m_moduleID, getType()); }

		static constexpr PluginID calcPluginID(PluginModuleID moduleId, PluginType pluginType) { return static_cast<PluginID>(moduleId) << 32 | pluginType; }
	};
}