#include "TestHingeConstraintDemoPlugin.h"

#include "EdgeFramework/PluginController/ExternalPluginCore.h"

#include "TestHingeConstraintDemo.h"

EDGE_MODULE_LOAD()
EDGE_PLUGIN(EdgeDemo::TestHingeConstraintDemoPlugin, EDGE_PLUGIN_TYPE_DECLARATION_DEMO)

EdgeDemo::Demo* EdgeDemo::TestHingeConstraintDemoPlugin::createDemo() const
{
	return new TestHingeConstraintDemo();
}
