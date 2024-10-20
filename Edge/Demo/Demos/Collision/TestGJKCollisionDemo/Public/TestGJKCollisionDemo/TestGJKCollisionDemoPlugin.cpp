#include "TestGJKCollisionDemoPlugin.h"

#include "EdgeFramework/PluginController/ExternalPluginCore.h"

#include "TestGJKCollisionDemo.h"

EDGE_MODULE_LOAD()
EDGE_PLUGIN(EdgeDemo::TestGJKCollisionDemoPlugin, EDGE_PLUGIN_TYPE_DECLARATION_DEMO)

EdgeDemo::Demo* EdgeDemo::TestGJKCollisionDemoPlugin::createDemo() const
{
	return new TestGJKCollisionDemo();
}
