#include "Win32PlatformPlugin.h"

#include "EdgeEngine/Plugin/ExternalPluginCore.h"

#include "Win32Platform.h"

EDGE_MODULE_LOAD()
EDGE_PLUGIN(Edge_WIN32::Win32PlatformPlugin, EDGE_PLUGIN_TYPE_DECLARATION_PLATFORM)

Edge::IPlatform* Edge_WIN32::Win32PlatformPlugin::createPlatform() const
{
	return new Win32Platform(GetModuleHandle(0));
}
