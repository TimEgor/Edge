#include "TestPrismaticConstraintDemoPlugin.h"

#include "EdgeFramework/PluginController/ExternalPluginCore.h"

#include "TestPrismaticConstraintDemo.h"

EDGE_MODULE_LOAD()
EDGE_PLUGIN(EdgeDemo::TestPrismaticConstraintDemoPlugin, EDGE_PLUGIN_TYPE_DECLARATION_DEMO)

EdgeDemo::Demo* EdgeDemo::TestPrismaticConstraintDemoPlugin::createDemo() const
{
	return new TestPrismaticConstraintDemo();
}
