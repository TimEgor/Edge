#include "PluginHandle.h"

#include "EdgeFramework/FrameworkCore.h"

#include "PluginController.h"

#include <cassert>

void Edge::PluginHandle::selfDestroy()
{
	FrameworkCore::getInstance().getApplication().getPluginController().unloadPlugin(this);
}

Edge::PluginHandle::PluginHandle(Plugin* plugin)
	: m_plugin(plugin)
{
	assert(plugin);
}

Edge::Plugin& Edge::PluginHandle::getPlugin()
{
	assert(m_plugin);
	return *m_plugin;
}

const Edge::Plugin& Edge::PluginHandle::getPlugin() const
{
	assert(m_plugin);
	return *m_plugin;
}