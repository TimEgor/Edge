#include "TestSpheresCollisionDemoPlugin.h"

#include "EdgeFramework/PluginController/ExternalPluginCore.h"

#include "TestSpheresCollisionDemo.h"

EDGE_MODULE_LOAD()
EDGE_PLUGIN(EdgeDemo::TestSpheresCollisionDemoPlugin, EDGE_PLUGIN_TYPE_DECLARATION_DEMO)

EdgeDemo::Demo* EdgeDemo::TestSpheresCollisionDemoPlugin::createDemo() const
{
	return new TestSpheresCollisionDemo();
}
