#include "PluginController.h"

#include "EdgeCommon/UtilsMacros.h"
#include "EdgeCommon/FileName/FileName.h"
#include "EdgeCommon/Multithreading/LockGuard.h"

#include "Loaders/PluginLoaderCreator.h"

#include <cassert>


Edge::PluginModuleID Edge::PluginController::getModuleID(const FileName& moduleName)
{
	return moduleName.hash();
}

bool Edge::PluginController::init()
{
	LockGuard lock(m_mutex);

	m_loader = createPluginLoader();
	EDGE_CHECK_INITIALIZATION(m_loader);

	return true;
}

void Edge::PluginController::release()
{
	LockGuard lock(m_mutex);

	assert(m_moduleInfos.empty());
	assert(m_plugins.empty());

	m_moduleInfos = ModuleInfoContainer();
	m_plugins = PluginContainer();

	EDGE_SAFE_DESTROY(m_loader);
}

Edge::PluginHandleReference Edge::PluginController::loadPlugin(const FileName& moduleName, PluginType pluginType, const char* generatorName)
{
	assert(m_loader);
	assert(moduleName);

	LockGuard lock(m_mutex);

	const PluginModuleID moduleID = getModuleID(moduleName);

	auto moduleIter = m_moduleInfos.find(moduleID);
	if (moduleIter == m_moduleInfos.end())
	{
		EDGE_PLATFORM_MODULE_HANDLE moduleHandle = m_loader->loadModule(moduleID, moduleName);
		if (moduleHandle == EDGE_INVALID_PLATFORM_MODULE_HANDLE)
		{
			return nullptr;
		}

		moduleIter = m_moduleInfos.emplace(moduleID, ModuleInfo(moduleHandle)).first;
	}

	ModuleInfo& moduleInfo = moduleIter->second;

	const PluginID pluginID = Plugin::calcPluginID(moduleID, pluginType);
	auto pluginIter = m_plugins.find(pluginID);
	if (pluginIter == m_plugins.end())
	{
		Plugin* plugin = m_loader->loadPlugin(moduleInfo.m_moduleHandle, moduleID, generatorName);
		if (!plugin)
		{
			if (moduleInfo.m_counter == 0)
			{
				m_loader->unloadModule(moduleInfo.m_moduleHandle);
				m_moduleInfos.erase(moduleIter);
			}

			return nullptr;
		}

		pluginIter = m_plugins.emplace(pluginID, plugin).first;

		++moduleInfo.m_counter;

		plugin->onLoaded();
	}

	return &pluginIter->second;
}

void Edge::PluginController::unloadPlugin(PluginHandle* pluginHandle)
{
	assert(pluginHandle);
	assert(pluginHandle->getReferenceCount() == 0);

	LockGuard lock(m_mutex);

	unloadPlugin(pluginHandle->getPlugin().getPluginID());
}

Edge::FileName Edge::PluginController::getNativePluginModulePath(const char* title) const
{
	LockGuard locker(m_mutex);

	FileName name;
	m_loader->getNativePluginModulePath(title, name);

	return name;
}

void Edge::PluginController::getNativePluginModulePath(const char* title, FileName& name) const
{
	LockGuard locker(m_mutex);

	m_loader->getNativePluginModulePath(title, name);
}

void Edge::PluginController::unloadPlugin(Plugin* plugin)
{
	assert(m_loader);
	assert(plugin);

	const PluginModuleID moduleID = plugin->getModuleID();

	auto moduleIter = m_moduleInfos.find(moduleID);
	assert(moduleIter != m_moduleInfos.end());

	ModuleInfo& moduleInfo = moduleIter->second;
	assert(moduleInfo.m_counter != 0);

	plugin->onUnloaded();
	m_loader->unloadPlugin(moduleInfo.m_moduleHandle, plugin);

	--moduleInfo.m_counter;

	if (moduleInfo.m_counter == 0)
	{
		m_loader->unloadModule(moduleInfo.m_moduleHandle);
		m_moduleInfos.erase(moduleIter);
	}
}

void Edge::PluginController::unloadPlugin(PluginID pluginID)
{
	auto pluginIter = m_plugins.find(pluginID);
	if (pluginIter != m_plugins.end())
	{
		unloadPlugin(&pluginIter->second.getPlugin());
		m_plugins.erase(pluginIter);
	}
}

Edge::PluginHandleReference Edge::PluginController::getPlugin(PluginID pluginID)
{
	LockGuard locker(m_mutex);

	auto pluginIter = m_plugins.find(pluginID);
	if (pluginIter != m_plugins.end())
	{
		return &pluginIter->second;
	}

	return nullptr;
}
