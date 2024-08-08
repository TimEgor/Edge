#pragma once

#include "EdgeCommon/Patterns/Singleton.h"

#include <cstdint>

namespace Edge
{
	using PluginModuleID = uint32_t;
	constexpr PluginModuleID InvalidPluginModuleID = 0;

	struct PluginModuleData final
	{
		FileName m_modulePath;
		PluginModuleID m_moduleId = InvalidPluginModuleID;
	};

	class PluginModuleCore final : public Singleton<PluginModuleCore>
	{
	private:
		PluginModuleData m_data;

	public:
		PluginModuleCore() = default;

		void init(const PluginModuleData& data) { m_data = data; }

		const PluginModuleData& getData() const { return m_data; }
	};
}
