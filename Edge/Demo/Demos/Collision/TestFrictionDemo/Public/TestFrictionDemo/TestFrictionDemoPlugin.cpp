#include "TestFrictionDemoPlugin.h"

#include "EdgeFramework/PluginController/ExternalPluginCore.h"

#include "TestFrictionDemo.h"

EDGE_MODULE_LOAD()
EDGE_PLUGIN(EdgeDemo::TestFrictionDemoPlugin, EDGE_PLUGIN_TYPE_DECLARATION_DEMO)

EdgeDemo::Demo* EdgeDemo::TestFrictionDemoPlugin::createDemo() const
{
	return new TestFrictionDemo();
}
