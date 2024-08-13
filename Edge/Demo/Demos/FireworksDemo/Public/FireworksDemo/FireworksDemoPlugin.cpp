#include "FireworksDemoPlugin.h"

#include "EdgeFramework/PluginController/ExternalPluginCore.h"

#include "FireworksDemo.h"

EDGE_MODULE_LOAD()
EDGE_PLUGIN(EdgeDemo::FireworksDemoPlugin, EDGE_PLUGIN_TYPE_DECLARATION_DEMO)

EdgeDemo::Demo* EdgeDemo::FireworksDemoPlugin::createDemo() const
{
	return new FireworksDemo();
}
