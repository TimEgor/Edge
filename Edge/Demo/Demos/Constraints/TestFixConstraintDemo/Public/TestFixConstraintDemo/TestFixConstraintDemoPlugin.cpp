#include "TestFixConstraintDemoPlugin.h"

#include "EdgeFramework/PluginController/ExternalPluginCore.h"

#include "TestFixConstraintDemo.h"

EDGE_MODULE_LOAD()
EDGE_PLUGIN(EdgeDemo::TestFixConstraintDemoPlugin, EDGE_PLUGIN_TYPE_DECLARATION_DEMO)

EdgeDemo::Demo* EdgeDemo::TestFixConstraintDemoPlugin::createDemo() const
{
	return new TestFixConstraintDemo();
}
