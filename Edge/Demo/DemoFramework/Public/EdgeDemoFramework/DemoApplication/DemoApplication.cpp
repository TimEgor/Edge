#include "DemoApplication.h"

#include "EdgeCommon/UtilsMacros.h"
#include "EdgeCommon/FileName/FileName.h"
#include "EdgeCommon/Profile/Profile.h"

#include "EdgeFramework/Graphics/GraphicPresenter/WindowGraphicPresenter.h"
#include "EdgeFramework/Graphics/Render/RenderController.h"
#include "EdgeFramework/Input/InputDeviceController/InputDeviceController.h"
#include "EdgeFramework/PluginController/PluginController.h"

#include "EdgeDemoFramework/Demo/Demo.h"
#include "EdgeDemoFramework/Demo/DemoPlugin.h"

bool EdgeDemo::DemoApplication::initDemo()
{
	Edge::PluginController& pluginController = getPluginController();

	const Edge::FileName pluginPath = pluginController.getNativePluginModulePath("Demo");
	m_demoPluginHandle = pluginController.loadPlugin<DemoPlugin>(pluginPath);

	EDGE_CHECK_RETURN_FALSE(m_demoPluginHandle);

	DemoPlugin& demoPlugin = m_demoPluginHandle->getPluginCast<DemoPlugin>();
	m_demo = demoPlugin.createDemo();

	EDGE_CHECK_RETURN_FALSE(m_demo && m_demo->init());

	return true;
}

Edge::JobGraphReference EdgeDemo::DemoApplication::getMainLoopJobGraph()
{
	Edge::JobGraphBuilder m_graphBuilder;

	Edge::JobGraphBuilder::JobGraphJobID updateLogicJobID = m_graphBuilder.addJob(
		Edge::createLambdaJob([this]()
			{
				update(getDeltaTime());
			}, "Demo application update"));

	Edge::JobGraphBuilder::JobGraphJobID updatePhysJobID = m_graphBuilder.addJobAfter(
		Edge::createLambdaJob([this]()
			{
				m_demo->physUpdate(getDeltaTime());
			}, "Physics update"),
		updateLogicJobID
	);

	Edge::JobGraphBuilder::JobGraphJobID renderJobID = m_graphBuilder.addJob(
		Edge::createLambdaJob([this]()
			{
				getRenderController().render(*getWindowGraphicPresenter().getTargetTexture());
			}, "Render"));

	m_graphBuilder.addJobAfter(
		Edge::createLambdaJob([this]()
			{
				getWindowGraphicPresenter().present();
			}, "Graphic presenter"),
		renderJobID);

	Edge::JobGraphBuilder::JobGraphJobID renderPrepareJobID = m_graphBuilder.addJob(
		Edge::createLambdaJob([this]()
			{
				const Edge::DebugVisualizationDataController& visualizationData = m_demo->getDebugVisualizationData();
				Edge::Renderer::CameraParams cameraParams;
				Edge::Transform cameraTransform;
				prepareCameraData(cameraParams, cameraTransform);

				getRenderController().prepareData(cameraParams, cameraTransform, visualizationData);
			}, "Renderer prepare")
	);

	m_graphBuilder.makeDependency(updatePhysJobID, renderPrepareJobID);
	m_graphBuilder.makeDependency(renderJobID, renderPrepareJobID);

	return m_graphBuilder.getGraph();
}

void EdgeDemo::DemoApplication::update(float deltaTime)
{
	EDGE_PROFILE_BLOCK_EVENT("Demo application update");

	if (!m_demo)
	{
		stop();
		return;
	}

	{
		EDGE_PROFILE_BLOCK_EVENT("Demo frame pre phys update");
		m_demo->updateLogic(deltaTime);
	}
}

void EdgeDemo::DemoApplication::prepareCameraData(Edge::Renderer::CameraParams& cameraParams, Edge::Transform& cameraTransform) const
{
	cameraTransform = m_demo->getCameraTransform();

	cameraParams.m_FoV = Edge::Math::ConvertDegToRad(90.0f);
	cameraParams.m_ratio = 1.0f;
	cameraParams.m_nearPlaneDistance = 0.05f;
	cameraParams.m_farPlaneDistance = 1000.0f;
}

bool EdgeDemo::DemoApplication::init()
{
	EDGE_CHECK_RETURN_FALSE(Application::init());
	EDGE_CHECK_RETURN_FALSE(initDemo());

	return true;
}

void EdgeDemo::DemoApplication::release()
{
	EDGE_SAFE_DESTROY_WITH_RELEASING(m_demo);
	m_demoPluginHandle.reset();

	Application::release();
}
