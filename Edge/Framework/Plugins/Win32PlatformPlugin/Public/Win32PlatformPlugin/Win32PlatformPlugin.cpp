#include "Win32PlatformPlugin.h"

#include "EdgeFramework/PluginController/ExternalPluginCore.h"

#include "Win32Platform.h"

EDGE_MODULE_LOAD()
EDGE_PLUGIN(EdgeWin32::Win32PlatformPlugin, EDGE_PLUGIN_TYPE_DECLARATION_PLATFORM)

Edge::Platform* EdgeWin32::Win32PlatformPlugin::createPlatform() const
{
	return new Win32Platform(GetModuleHandle(0));
}
