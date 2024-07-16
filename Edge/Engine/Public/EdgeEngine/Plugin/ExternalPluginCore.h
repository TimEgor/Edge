#pragma once

#include "EdgeEngine/EngineCore.h"
#include "EdgeEngine/Core/PlatformMacros.h"

#include "IPlugin.h"

#include <type_traits>
#include <cassert>

namespace Edge
{
	class IEngine;
}

#define EDGE_PLUGIN_MODULE_LOAD_FUNC EdgePluginModuleLoad

#define EDGE_PLUGIN_CREATE_FUNC_BASE EdgePluginCreate_
#define EDGE_PLUGIN_RELEASE_FUNC_BASE EdgePluginRelease_

#define EDGE_PLUGIN_CREATE_FUNC(TYPE) EDGE_CONCAT_DEF(EDGE_PLUGIN_CREATE_FUNC_BASE, TYPE)
#define EDGE_PLUGIN_RELEASE_FUNC(TYPE) EDGE_CONCAT_DEF(EDGE_PLUGIN_RELEASE_FUNC_BASE, TYPE)

#define EDGE_PLUGIN_CREATE(PLUGIN, TYPE)																				\
extern "C" EDGE_DYNAMIC_LIB_EXPORT Edge::IPlugin* __cdecl EDGE_PLUGIN_CREATE_FUNC(TYPE)(Edge::PluginModuleID moduleID)	\
{																														\
	static_assert(std::is_base_of_v<Edge::PluginBase, PLUGIN>);															\
	return new PLUGIN(moduleID);																						\
}

#define EDGE_PLUGIN_RELEASE(PLUGIN, TYPE)																				\
extern "C" EDGE_DYNAMIC_LIB_EXPORT void __cdecl EDGE_PLUGIN_RELEASE_FUNC(TYPE)(Edge::IPlugin* plugin)					\
{																														\
	static_assert(std::is_base_of_v<Edge::PluginBase, PLUGIN>);															\
	delete plugin;																										\
}

#define EDGE_PLUGIN(PLUGIN, TYPE)	\
EDGE_PLUGIN_CREATE(PLUGIN, TYPE)	\
EDGE_PLUGIN_RELEASE(PLUGIN, TYPE)

#define EDGE_MODULE_LOAD()																					\
extern "C" EDGE_DYNAMIC_LIB_EXPORT void __cdecl EDGE_PLUGIN_MODULE_LOAD_FUNC(Edge::PluginModuleID moduleID,	\
	Edge::IEngine* engine, const Edge::FileName& moduleName)												\
{																											\
	Edge::EngineCore::getInstance().setEngine(engine);														\
	Edge::PluginModuleCore::getInstance().init(Edge::PluginModuleData{ moduleName, moduleID });				\
}																			

#define EDGE_PLUGIN_MODULE() EDGE_MODULE_LOAD()