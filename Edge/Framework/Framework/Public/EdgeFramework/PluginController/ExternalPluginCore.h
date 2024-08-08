#pragma once

#include "EdgeCommon/PlatformMacros.h"
#include "EdgeCommon/Assert/AssertCore.h"

#include "EdgePhysics/Physics/PhysicsCore.h"

#include "EdgeFramework/FrameworkCore.h"

#include "Plugin.h"

#include <type_traits>


namespace Edge
{
	class Application;
}

#define EDGE_PLUGIN_MODULE_LOAD_FUNC EdgePluginModuleLoad

#define EDGE_PLUGIN_CREATE_FUNC_BASE EdgePluginCreate_
#define EDGE_PLUGIN_RELEASE_FUNC_BASE EdgePluginRelease_

#define EDGE_PLUGIN_CREATE_FUNC(TYPE) EDGE_CONCAT_DEF(EDGE_PLUGIN_CREATE_FUNC_BASE, TYPE)
#define EDGE_PLUGIN_RELEASE_FUNC(TYPE) EDGE_CONCAT_DEF(EDGE_PLUGIN_RELEASE_FUNC_BASE, TYPE)

#define EDGE_PLUGIN_CREATE(PLUGIN, TYPE)																				\
extern "C" EDGE_DYNAMIC_LIB_EXPORT Edge::Plugin* __cdecl EDGE_PLUGIN_CREATE_FUNC(TYPE)(Edge::PluginModuleID moduleID)	\
{																														\
	static_assert(std::is_base_of_v<Edge::Plugin, PLUGIN>);																\
	return new PLUGIN(moduleID);																						\
}

#define EDGE_PLUGIN_RELEASE(PLUGIN, TYPE)																				\
extern "C" EDGE_DYNAMIC_LIB_EXPORT void __cdecl EDGE_PLUGIN_RELEASE_FUNC(TYPE)(Edge::Plugin* plugin)					\
{																														\
	static_assert(std::is_base_of_v<Edge::Plugin, PLUGIN>);																\
	delete plugin;																										\
}

#define EDGE_PLUGIN(PLUGIN, TYPE)	\
EDGE_PLUGIN_CREATE(PLUGIN, TYPE)	\
EDGE_PLUGIN_RELEASE(PLUGIN, TYPE)

#define EDGE_MODULE_LOAD()																								\
extern "C" EDGE_DYNAMIC_LIB_EXPORT void __cdecl EDGE_PLUGIN_MODULE_LOAD_FUNC(Edge::PluginModuleID moduleID,				\
	Edge::AssertGenerator* assertGenerator, Edge::Application* application,												\
	const Edge::PhysicsCore& physicsCore, const Edge::FileName& moduleName)												\
{																														\
	Edge::AssertCore::getInstance().setGenerator(assertGenerator);														\
	Edge::FrameworkCore::getInstance().setApplication(application);														\
	Edge::PhysicsCore::getInstance().copyState(physicsCore);															\
	Edge::PluginModuleCore::getInstance().init(Edge::PluginModuleData{ moduleName, moduleID });							\
}																			

#define EDGE_PLUGIN_MODULE() EDGE_MODULE_LOAD()