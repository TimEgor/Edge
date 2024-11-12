#include "TestKeepDistanceConstraintDemoPlugin.h"

#include "EdgeFramework/PluginController/ExternalPluginCore.h"

#include "TestKeepDistanceConstraintDemo.h"

EDGE_MODULE_LOAD()
EDGE_PLUGIN(EdgeDemo::TestKeepDistanceConstraintDemoPlugin, EDGE_PLUGIN_TYPE_DECLARATION_DEMO)

EdgeDemo::Demo* EdgeDemo::TestKeepDistanceConstraintDemoPlugin::createDemo() const
{
	return new TestKeepDistanceConstraintDemo();
}
