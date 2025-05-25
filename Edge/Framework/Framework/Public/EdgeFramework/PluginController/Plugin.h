#pragma once

#include "EdgeCommon/HashedType.h"
#include "EdgeCommon/FileName/FileName.h"

#include "ExternalPluginCore.h"
#include "PluginModule.h"

#include <cstdint>

namespace Edge
{
	using PluginID = uint64_t;
	inline constexpr PluginID InvalidPluginID = 0;

	using PluginType = HashedType::Type;

	class Plugin : public HashedType
	{
	private:
		const PluginModuleID m_moduleID = InvalidPluginModuleID;

	public:
		Plugin(PluginModuleID moduleID)
			: m_moduleID(moduleID) {}
		virtual ~Plugin() = default;

		virtual void onLoaded() {}
		virtual void onUnloaded() {}

		PluginModuleID getModuleID() const { return m_moduleID; }
		PluginID getPluginID() const { return calcPluginID(m_moduleID, getType()); }

		virtual PluginType getType() const = 0;
		virtual const char* getModuleGeneratorName() const = 0;

		static constexpr PluginID calcPluginID(PluginModuleID moduleId, PluginType pluginType) { return static_cast<PluginID>(moduleId) << 32 | pluginType; }
	};
}

#define EDGE_PLUGIN_TYPE(PLUGIN_TYPE, MODULE_GENERATOR_NAME)												\
	EDGE_HASH_TYPE(#PLUGIN_TYPE, Edge::PluginType, Plugin)													\
																											\
	static constexpr const char* PluginModuleGeneratorName = EDGE_TO_STRING(MODULE_GENERATOR_NAME);			\
	static constexpr const char* getPluginModuleGeneratorName() { return PluginModuleGeneratorName ; }		\
	virtual const char* getModuleGeneratorName() const override { return getPluginModuleGeneratorName(); }