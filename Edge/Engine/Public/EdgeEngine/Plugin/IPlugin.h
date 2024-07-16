#pragma once

#include "EdgeEngine/Core/HashedType.h"
#include "EdgeEngine/Core/FileName/FileName.h"

#include "ExternalPluginCore.h"
#include "PluginModuleCore.h"

#include <cstdint>

namespace Edge
{
	using PluginID = uint64_t;
	constexpr PluginID InvalidPluginID = 0;

	using PluginType = HashedType::Type;

	class IPlugin : public HashedType
	{
	public:
		IPlugin() = default;
		virtual ~IPlugin() = default;

		virtual void onLoaded() = 0;
		virtual void onUnloaded() = 0;

		virtual PluginModuleID getModuleID() const = 0;
		virtual PluginID getPluginID() const = 0;

		virtual PluginType getType() const = 0;
		virtual const char* getModuleGeneratorName() const = 0;
	};
}

#define EDGE_PLUGIN_TYPE(PLUGIN_TYPE, MODULE_GENERATOR_NAME)												\
	EDGE_HASH_TYPE(#PLUGIN_TYPE, Edge::PluginType, Plugin)													\
																											\
	static constexpr const char* PluginModuleGeneratorName = EDGE_TO_STRING(MODULE_GENERATOR_NAME);			\
	static constexpr const char* GetPluginModuleGeneratorName() { return PluginModuleGeneratorName ; }		\
	virtual const char* getModuleGeneratorName() const override { return GetPluginModuleGeneratorName(); }