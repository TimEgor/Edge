#include "Engine.h"

#include "EdgeEngine/Core/UtilsMacros.h"
#include "EdgeEngine/Message/MessageController.h"
#include "EdgeEngine/Plugin/PluginController.h"

#include <cassert>

bool Edge::Engine::init(const InitData& initData)
{
	m_messageController = new MessageController();
	EDGE_CHECK_INITIALIZATION(m_messageController && m_messageController->init(initData.m_messageProc));

	m_pluginController = new PluginController();
	EDGE_CHECK_INITIALIZATION(m_pluginController && m_pluginController->init());

	return true;
}

void Edge::Engine::release()
{
	EDGE_SAFE_DESTROY_WITH_RELEASING(m_pluginController);
	EDGE_SAFE_DESTROY_WITH_RELEASING(m_messageController);
}

Edge::IMessageController& Edge::Engine::getMessageController() const
{
	assert(m_messageController);
	return *m_messageController;
}

Edge::IPluginController& Edge::Engine::getPluginController() const
{
	assert(m_pluginController);
	return *m_pluginController;
}

Edge::IWindowController& Edge::Engine::getWindowController() const
{
	assert(m_windowController);
	return *m_windowController;
}
