#include "Engine.h"

#include "EdgeEngine/Core/UtilsMacros.h"
#include "EdgeEngine/Message/MessageController.h"
#include "EdgeEngine/Plugin/PluginController.h"
#include "EdgeEngine/Event/EventController.h"
#include "EdgeEngine/Utils/ArgParser/Parser.h"

#include "EdgeEngine/Platform/PlatformPlugin.h"
#include "EdgeEngine/Platform/IPlatform.h"
#include "EdgeEngine/Window/WindowController.h"
#include "EdgeEngine/Window/IWindowEventController.h"

#include "EdgeEngine/Graphic/GraphicPlatform/GraphicPlatformPlugin.h"
#include "EdgeEngine/Graphic/GraphicPlatform/IGraphicPlatform.h"
#include "EdgeEngine/Graphic/GraphicPlatform/GraphicObject/SwapChain.h"
#include "EdgeEngine/Graphic/GraphicPresenter/WindowGraphicPresenter.h"
#include "EdgeEngine/Graphic/Render/RenderController.h"

#include <cassert>

void Edge::Engine::parseArgsParams(FileName& platformPluginPath, FileName& graphicPluginPath, FileName& renderPluginPath)
{
	ArgParser parser;
	parser.addOptionValue("--platform", platformPluginPath);

	parser.addOptionValue("--graphic", graphicPluginPath);
	parser.addOptionValue("--render", renderPluginPath);

	parser.parse(__argc, __argv);
}

bool Edge::Engine::initPlatform(const FileName& platformPluginPath)
{
	if (!platformPluginPath)
	{
		const FileName pluginPath = m_pluginController->getNativePluginModulePath("Platform plugin module");
		m_platformPluginHandle = m_pluginController->loadTypedPlugin<PlatformPlugin>(pluginPath);
	}
	else
	{
		m_platformPluginHandle = m_pluginController->loadTypedPlugin<PlatformPlugin>(platformPluginPath);
	}

	EDGE_CHECK_RETURN_FALSE(m_platformPluginHandle);

	const PlatformPlugin& platformPlugin = m_platformPluginHandle->getPluginCast<PlatformPlugin>();
	m_platform = platformPlugin.createPlatform();

	EDGE_CHECK_RETURN_FALSE(m_platform && m_platform->init());

	return true;
}

bool Edge::Engine::initGraphicPlatform(const FileName& graphicPlatformPluginPath)
{
	if (!graphicPlatformPluginPath)
	{
		const FileName pluginPath = m_pluginController->getNativePluginModulePath("Graphic platform plugin module");
		m_graphicPlatformPluginHandle = m_pluginController->loadTypedPlugin<GraphicPlatformPlugin>(pluginPath);
	}
	else
	{
		m_graphicPlatformPluginHandle = m_pluginController->loadTypedPlugin<GraphicPlatformPlugin>(graphicPlatformPluginPath);
	}

	EDGE_CHECK_RETURN_FALSE(m_graphicPlatformPluginHandle);

	const GraphicPlatformPlugin& graphicPlatformPlugin = m_graphicPlatformPluginHandle->getPluginCast<GraphicPlatformPlugin>();
	m_graphicPlatform = graphicPlatformPlugin.createGraphicPlatform();

	EDGE_CHECK_RETURN_FALSE(m_graphicPlatform && m_graphicPlatform->init());

	return true;
}

bool Edge::Engine::initGraphic(const FileName& graphicPluginPath, const FileName& renderPluginPath)
{
	EDGE_CHECK_RETURN_FALSE(initGraphicPlatform(graphicPluginPath));

	m_renderController = new RenderController();
	EDGE_CHECK_RETURN_FALSE(m_renderController && m_renderController->init(renderPluginPath));

	m_mainWindowHandle = m_windowController->createWindow("Edge", WindowSize(500, 500));
	EDGE_CHECK_RETURN_FALSE(m_mainWindowHandle);

	SwapChainDesc swapChainDesc{};
	swapChainDesc.m_bufferCount = 2;
	swapChainDesc.m_format = GraphicResourceFormat::R8G8B8A8_UNORM;

	m_windowGraphicPresenter = new WindowGraphicPresenter();
	EDGE_CHECK_RETURN_FALSE(m_windowGraphicPresenter && m_windowGraphicPresenter->init(m_mainWindowHandle->getWindow(), swapChainDesc));

	return true;
}

void Edge::Engine::releaseGraphic()
{
	EDGE_SAFE_DESTROY_WITH_RELEASING(m_windowGraphicPresenter);

	m_mainWindowHandle.reset();

	EDGE_SAFE_DESTROY_WITH_RELEASING(m_renderController);
	EDGE_SAFE_DESTROY_WITH_RELEASING(m_graphicPlatform);

	m_graphicPlatformPluginHandle.reset();
}

bool Edge::Engine::init(const InitData& initData)
{
	FileName platformPluginPath;
	FileName graphicPluginPath;
	FileName renderPluginPath;

	parseArgsParams(platformPluginPath, graphicPluginPath, renderPluginPath);

	m_messageController = new MessageController();
	EDGE_CHECK_INITIALIZATION(m_messageController && m_messageController->init(initData.m_messageProc));

	m_pluginController = new PluginController();
	EDGE_CHECK_INITIALIZATION(m_pluginController && m_pluginController->init());

	m_eventController = new EventController();
	EDGE_CHECK_INITIALIZATION(m_eventController && m_eventController->init());

	EDGE_CHECK_INITIALIZATION(initPlatform(platformPluginPath));

	m_windowController = new WindowController();
	EDGE_CHECK_INITIALIZATION(m_windowController);

	EDGE_CHECK_INITIALIZATION(initGraphic(graphicPluginPath, renderPluginPath));

	return true;
}

void Edge::Engine::release()
{
	releaseGraphic();

	EDGE_SAFE_DESTROY(m_windowController);
	EDGE_SAFE_DESTROY_WITH_RELEASING(m_platform);

	m_platformPluginHandle.reset();

	EDGE_SAFE_DESTROY_WITH_RELEASING(m_eventController);

	EDGE_SAFE_DESTROY_WITH_RELEASING(m_pluginController);
	EDGE_SAFE_DESTROY_WITH_RELEASING(m_messageController);
}

void Edge::Engine::beginFrame()
{
	m_currentFrameTime = Clock::GetCurrentTimePoint();
	m_deltaTime = Clock::CalcTimePointDelta(m_currentFrameTime, m_prevFrameStartTime);
}

void Edge::Engine::endFrame()
{
	m_prevFrameStartTime = m_currentFrameTime;
}

void Edge::Engine::updateFrame()
{
	if (!m_mainWindowHandle->getWindow().isValid())
	{
		stop();
		return;
	}

	m_platform->getWindowEventController().updateProcessWindowsEvents();
}

void Edge::Engine::run()
{
	beginFrame();
	endFrame();

	while (!m_isStopped)
	{
		//EDGE_PROFILE_BLOCK_EVENT("Frame");

		beginFrame();

		updateFrame();

		endFrame();
	}
}

void Edge::Engine::stop()
{
	m_isStopped = true;
}

void Edge::Engine::pause()
{
	m_isPaused = true;
}

void Edge::Engine::unpause()
{
	m_isPaused = false;
}

float Edge::Engine::getDeltaTime() const
{
	return m_deltaTime;
}

bool Edge::Engine::isStopped() const
{
	return m_isStopped;
}

bool Edge::Engine::isPaused() const
{
	return m_isPaused;
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

Edge::IEventController& Edge::Engine::getEventController() const
{
	assert(m_eventController);
	return *m_eventController;
}

Edge::IWindowController& Edge::Engine::getWindowController() const
{
	assert(m_windowController);
	return *m_windowController;
}

Edge::IGraphicPlatform& Edge::Engine::getGraphicPlatform() const
{
	assert(m_graphicPlatform);
	return *m_graphicPlatform;
}

Edge::IRenderController& Edge::Engine::getRenderController() const
{
	assert(m_renderController);
	return *m_renderController;
}

Edge::IPlatform& Edge::Engine::getPlatform() const
{
	assert(m_platform);
	return *m_platform;
}
