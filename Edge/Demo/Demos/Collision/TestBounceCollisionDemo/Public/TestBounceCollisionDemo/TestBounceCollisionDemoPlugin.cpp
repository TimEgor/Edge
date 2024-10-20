#include "TestBounceCollisionDemoPlugin.h"

#include "EdgeFramework/PluginController/ExternalPluginCore.h"

#include "TestBounceCollisionDemo.h"

EDGE_MODULE_LOAD()
EDGE_PLUGIN(EdgeDemo::TestBounceCollisionDemoPlugin, EDGE_PLUGIN_TYPE_DECLARATION_DEMO)

EdgeDemo::Demo* EdgeDemo::TestBounceCollisionDemoPlugin::createDemo() const
{
	return new TestBounceCollisionDemo();
}
