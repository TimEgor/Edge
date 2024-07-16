#include "PluginHandle.h"

#include "EdgeEngine/EngineCore.h"
#include "EdgeEngine/Engine/IEngine.h"

#include "IPluginController.h"

#include <cassert>

void Edge::PluginHandle::selfDestroy()
{
	EngineCore::getInstance().getEngine().getPluginController().unloadPlugin(this);
}

Edge::PluginHandle::PluginHandle(IPlugin* plugin)
	: m_plugin(plugin)
{
	assert(plugin);
}

Edge::IPlugin& Edge::PluginHandle::getPlugin()
{
	assert(m_plugin);
	return *m_plugin;
}

const Edge::IPlugin& Edge::PluginHandle::getPlugin() const
{
	assert(m_plugin);
	return *m_plugin;
}