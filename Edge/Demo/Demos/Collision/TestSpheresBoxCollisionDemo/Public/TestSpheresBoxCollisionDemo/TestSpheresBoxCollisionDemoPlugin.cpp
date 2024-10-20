#include "TestSpheresBoxCollisionDemoPlugin.h"

#include "EdgeFramework/PluginController/ExternalPluginCore.h"

#include "TestSpheresBoxCollisionDemo.h"

EDGE_MODULE_LOAD()
EDGE_PLUGIN(EdgeDemo::TestSpheresBoxCollisionDemoPlugin, EDGE_PLUGIN_TYPE_DECLARATION_DEMO)

EdgeDemo::Demo* EdgeDemo::TestSpheresBoxCollisionDemoPlugin::createDemo() const
{
	return new TestSpheresBoxCollisionDemo();
}
