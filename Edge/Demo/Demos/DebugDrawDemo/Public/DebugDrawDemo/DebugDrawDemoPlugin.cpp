#include "DebugDrawDemoPlugin.h"

#include "EdgeFramework/PluginController/ExternalPluginCore.h"

#include "DebugDrawDemo.h"

EDGE_MODULE_LOAD()
EDGE_PLUGIN(EdgeDemo::DebugDrawDemoPlugin, EDGE_PLUGIN_TYPE_DECLARATION_DEMO)

EdgeDemo::Demo* EdgeDemo::DebugDrawDemoPlugin::createDemo() const
{
	return new DebugDrawDemo();
}
