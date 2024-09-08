#include "DemoApplication.h"

#include "EdgeCommon/UtilsMacros.h"
#include "EdgeCommon/FileName/FileName.h"
#include "EdgeCommon/Math/ComputeMatrix.h"
#include "EdgeCommon/Math/Const.h"
#include "EdgeCommon/Profile/Profile.h"

#include "EdgeFramework/Graphics/GraphicPresenter/WindowGraphicPresenter.h"
#include "EdgeFramework/Graphics/Render/RenderController.h"
#include "EdgeFramework/Input/InputDeviceController/InputDeviceController.h"
#include "EdgeFramework/Input/InputDeviceController/Devices/Keyboard.h"
#include "EdgeFramework/Input/InputDeviceController/Devices/Mouse.h"
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
				Edge::Renderer::CameraTransforms cameraTransforms;
				prepareCameraTransforms(cameraTransforms);

				getRenderController().prepareData(cameraTransforms, visualizationData);
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

void EdgeDemo::DemoApplication::prepareCameraTransforms(Edge::Renderer::CameraTransforms& cameraTransforms) const
{
	const Edge::Transform& demoCameraTransform = m_demo->getCameraTransform();

	Edge::ComputeMatrix cameraTransform = Edge::ComputeMatrix(Edge::ComputeMath::matrixLookToLH(
		Edge::ComputeVector(demoCameraTransform.getOrigin()).m_vector,
		Edge::ComputeVector(demoCameraTransform.getAxisZ()).m_vector, Edge::ComputeVector(demoCameraTransform.getAxisY()).m_vector));
	cameraTransform.saveToMatrix4x4(cameraTransforms.m_viewTransform);

	cameraTransform = Edge::ComputeMatrix(Edge::ComputeMath::matrixPerspectiveFovLH(90.0f * EDGE_DEG_TO_RAD, 1.0f, 0.05f, 1000.0f));
	cameraTransform.saveToMatrix4x4(cameraTransforms.m_projTransform);
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
