#include "IkDemoPlugin.h"

#include "EdgeFramework/PluginController/ExternalPluginCore.h"

#include "IKDemo.h"

EDGE_MODULE_LOAD()
EDGE_PLUGIN(EdgeDemo::IkDemoPlugin, EDGE_PLUGIN_TYPE_DECLARATION_DEMO)

EdgeDemo::Demo* EdgeDemo::IkDemoPlugin::createDemo() const
{
	return new IkDemo();
}
