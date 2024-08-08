#include "FireworksDemoPlugin.h"

#include "TinySimFramework/PluginController/ExternalPluginCore.h"

#include "FireworksDemo.h"

TS_MODULE_LOAD()
TS_PLUGIN(TS_DEMO::FireworksDemoPlugin, TS_PLUGIN_TYPE_DECLARATION_DEMO)

TS_DEMO::Demo* TS_DEMO::FireworksDemoPlugin::createDemo() const
{
	return new FireworksDemo();
}
