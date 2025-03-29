#include "Application.h"

#include "EdgeCommon/ThreadUtils.h"
#include "EdgeCommon/UtilsMacros.h"
#include "EdgeCommon/Job/JobController.h"
#include "EdgeCommon/Profile/Profile.h"

#include "EdgePhysics/Physics/Physics.h"

#include "EdgeFramework/PluginController/PluginController.h"

#include "EdgeFramework/EventController/EventController.h"
#include "EdgeFramework/Input/InputDeviceController/InputDeviceController.h"
#include "EdgeFramework/Platform/Platform.h"
#include "EdgeFramework/Platform/PlatformPlugin.h"
#include "EdgeFramework/WindowController/WindowController.h"
#include "EdgeFramework/WindowController/WindowEventController.h"

#include "EdgeFramework/Recources/AssetsDirectoryController/AssetsDirectoryController.h"

#include "EdgeFramework/Graphics/GraphicPlatform/GraphicPlatform.h"
#include "EdgeFramework/Graphics/GraphicPlatform/GraphicPlatformPlugin.h"
#include "EdgeFramework/Graphics/GraphicPlatform/GraphicObject/SwapChain.h"
#include "EdgeFramework/Graphics/GraphicPresenter/WindowGraphicPresenter.h"
#include "EdgeFramework/Graphics/Render/RenderController.h"
#include "EdgeFramework/Utils/ArgParser/Parser.h"

#include "ApplicationInitUtils.h"

#include <cassert>

void Edge::Application::parseArgsParams(FileName& platformPluginPath, FileName& graphicPluginPath, FileName& rendererPluginPath)
{
	ArgParser parser;
	parser.addOptionValue("--platform", platformPluginPath);

	parser.addOptionValue("--graphic", graphicPluginPath);
	parser.addOptionValue("--renderer", rendererPluginPath);

	parser.parse(__argc, __argv);
}

bool Edge::Application::initPlatform(const FileName& platformPluginPath)
{
	if (!platformPluginPath)
	{
		const FileName pluginPath = m_pluginController->getNativePluginModulePath("Platform plugin module");
		m_platformPluginHandle = m_pluginController->loadPlugin<PlatformPlugin>(pluginPath);
	}
	else
	{
		m_platformPluginHandle = m_pluginController->loadPlugin<PlatformPlugin>(platformPluginPath);
	}

	EDGE_CHECK_RETURN_FALSE(m_platformPluginHandle);

	const PlatformPlugin& platformPlugin = m_platformPluginHandle->getPluginCast<PlatformPlugin>();
	m_platform = platformPlugin.createPlatform();

	EDGE_CHECK_RETURN_FALSE(m_platform && m_platform->init());

	return true;
}

bool Edge::Application::initGraphicPlatform(const FileName& graphicPlatformPluginPath)
{
	if (!graphicPlatformPluginPath)
	{
		const FileName pluginPath = m_pluginController->getNativePluginModulePath("Graphic platform plugin module");
		m_graphicPlatformPluginHandle = m_pluginController->loadPlugin<GraphicPlatformPlugin>(pluginPath);
	}
	else
	{
		m_graphicPlatformPluginHandle = m_pluginController->loadPlugin<GraphicPlatformPlugin>(graphicPlatformPluginPath);
	}

	EDGE_CHECK_RETURN_FALSE(m_graphicPlatformPluginHandle);

	const GraphicPlatformPlugin& graphicPlatformPlugin = m_graphicPlatformPluginHandle->getPluginCast<GraphicPlatformPlugin>();
	m_graphicPlatform = graphicPlatformPlugin.createGraphicPlatform();

	EDGE_CHECK_RETURN_FALSE(m_graphicPlatform && m_graphicPlatform->init());

	return true;
}

bool Edge::Application::initGraphic(const FileName& graphicPluginPath, const FileName& rendererPluginPath)
{
	EDGE_CHECK_RETURN_FALSE(initGraphicPlatform(graphicPluginPath));

	m_renderController = new RenderController();
	EDGE_CHECK_RETURN_FALSE(m_renderController && m_renderController->init(rendererPluginPath));

	m_mainWindowHandle = getWindowController().createWindow("Edge", WindowSize(500, 500));
	EDGE_CHECK_RETURN_FALSE(m_mainWindowHandle);

	SwapChainDesc swapChainDesc{};
	swapChainDesc.m_bufferCount = 2;
	swapChainDesc.m_format = GraphicResourceFormat::R8G8B8A8_UNORM;

	m_windowGraphicPresenter = new WindowGraphicPresenter();
	EDGE_CHECK_RETURN_FALSE(m_windowGraphicPresenter && m_windowGraphicPresenter->init(m_mainWindowHandle->getWindow(), swapChainDesc));

	return true;
}

void Edge::Application::releaseGraphic()
{
	EDGE_SAFE_DESTROY_WITH_RELEASING(m_windowGraphicPresenter);

	m_mainWindowHandle.reset();

	EDGE_SAFE_DESTROY_WITH_RELEASING(m_renderController);
	EDGE_SAFE_DESTROY_WITH_RELEASING(m_graphicPlatform);

	m_graphicPlatformPluginHandle.reset();
}

void Edge::Application::beginFrame()
{
	m_currentFrameTime = Clock::GetCurrentTimePoint();
	m_deltaTime = Clock::CalcTimePointDelta(m_currentFrameTime, m_prevFrameStartTime);
}

void Edge::Application::endFrame()
{
	m_prevFrameStartTime = m_currentFrameTime;
}

bool Edge::Application::init()
{
	PhysicsCore::getInstance().initPhysics();

	FileName platformPluginPath;
	FileName graphicPluginPath;
	FileName rendererPluginPath;

	parseArgsParams(platformPluginPath, graphicPluginPath, rendererPluginPath);

	m_eventController = new EventController();
	EDGE_CHECK_INITIALIZATION(m_eventController && m_eventController->init());

	m_pluginController = new PluginController();
	EDGE_CHECK_INITIALIZATION(m_pluginController && m_pluginController->init());

	m_inputDeviceController = new InputDeviceController();
	EDGE_CHECK_INITIALIZATION(m_inputDeviceController);

	EDGE_CHECK_INITIALIZATION(initPlatform(platformPluginPath));

	EDGE_CHECK_INITIALIZATION(m_inputDeviceController->init());

	m_windowController = new WindowController();
	EDGE_CHECK_INITIALIZATION(m_windowController);

	m_jobController = new JobController();
	EDGE_CHECK_INITIALIZATION(m_jobController && m_jobController->init(4, "Edge Application"));

	m_assetsDirectoryController = new AssetsDirectoryController();
	EDGE_CHECK_INITIALIZATION(m_assetsDirectoryController);

	EDGE_CHECK_INITIALIZATION(initGraphic(graphicPluginPath, rendererPluginPath));

	m_inputDeviceController->setWindowForAllDevices(m_mainWindowHandle->getWindow(), false);

	Physics::InitParams physParams{};

	Physics& physics = GetPhysics();
	EDGE_CHECK_INITIALIZATION(physics.init(physParams));

	ThreadUtils::SetThreadName("Edge Application main");

	return true;
}

void Edge::Application::release()
{
	GetPhysics().release();
	PhysicsCore::getInstance().releasePhysics();

	releaseGraphic();

	EDGE_SAFE_DESTROY_WITH_RELEASING(m_jobController);

	EDGE_SAFE_DESTROY(m_windowController);
	EDGE_SAFE_DESTROY_WITH_RELEASING(m_platform);
	EDGE_SAFE_DESTROY_WITH_RELEASING(m_inputDeviceController);

	m_platformPluginHandle.reset();

	EDGE_SAFE_DESTROY_WITH_RELEASING(m_pluginController);
	EDGE_SAFE_DESTROY_WITH_RELEASING(m_eventController);
}

void Edge::Application::run()
{
	beginFrame();
	endFrame();

	while (!m_isStopped)
	{
		EDGE_PROFILE_BLOCK_EVENT("Frame");

		beginFrame();

		if (!m_mainWindowHandle->getWindow().isValid())
		{
			stop();
			continue;
		}

		m_platform->getWindowEventController().updateProcessWindowsEvents();
		m_inputDeviceController->update();

		JobGraphReference mailLoopJobGraph = getMainLoopJobGraph();
		m_jobController->addJobGraph(mailLoopJobGraph);
		m_jobController->waitAndExecute(mailLoopJobGraph);

		endFrame();
	}
}

void Edge::Application::stop()
{
	m_isStopped = true;
}

void Edge::Application::pause()
{
	m_isPaused = true;
}

void Edge::Application::unpause()
{
	m_isPaused = false;
}

float Edge::Application::getDeltaTime() const
{
	return m_deltaTime * m_timeScale;
}

void Edge::Application::setTimeScale(float scale)
{
	EDGE_ASSERT(scale >= 0);
	m_timeScale = scale;
}

bool Edge::Application::isStopped() const
{
	return m_isStopped;
}

bool Edge::Application::isPaused() const
{
	return m_isPaused;
}

Edge::EventController& Edge::Application::getEventController() const
{
	assert(m_eventController);
	return *m_eventController;
}

Edge::PluginController& Edge::Application::getPluginController() const
{
	assert(m_pluginController);
	return *m_pluginController;
}

Edge::Platform& Edge::Application::getPlatform() const
{
	assert(m_platform);
	return *m_platform;
}

Edge::InputDeviceController& Edge::Application::getInputDeviceController() const
{
	assert(m_inputDeviceController);
	return *m_inputDeviceController;
}

Edge::WindowController& Edge::Application::getWindowController() const
{
	assert(m_windowController);
	return *m_windowController;
}

Edge::JobController& Edge::Application::getJobController() const
{
	assert(m_jobController);
	return *m_jobController;
}

Edge::AssetsDirectoryController& Edge::Application::getAssetsDirectoryController() const
{
	assert(m_assetsDirectoryController);
	return *m_assetsDirectoryController;
}

Edge::GraphicPlatform& Edge::Application::getGraphicPlatform() const
{
	assert(m_graphicPlatform);
	return *m_graphicPlatform;
}

Edge::RenderController& Edge::Application::getRenderController() const
{
	assert(m_renderController);
	return *m_renderController;
}

Edge::WindowGraphicPresenter& Edge::Application::getWindowGraphicPresenter() const
{
	assert(m_windowGraphicPresenter);
	return *m_windowGraphicPresenter;
}
