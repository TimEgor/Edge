#include "PreInitedDemo.h"

#include "EdgeCommon/UtilsMacros.h"

#include "EdgePhysics/Physics/PhysicsCore.h"

#include "EdgeDemoFramework/CameraController/DefaultCameraController.h"

bool EdgeDemo::PreInitedDemo::initPhysics()
{
	m_timeStepper.setStepFrequency(60);

	Edge::Physics& physics = Edge::GetPhysics();

	m_physicsWorld = new Edge::PhysicsWorld();
	EDGE_CHECK_INITIALIZATION(m_physicsWorld && m_physicsWorld->init());

	m_physicsScene = new Edge::PhysicsScene(m_physicsWorld);
	EDGE_CHECK_INITIALIZATION(m_physicsScene && m_physicsScene->init());

	return true;
}

bool EdgeDemo::PreInitedDemo::initCameraController()
{
	if (!m_cameraController)
	{
		m_cameraController = new DefaultCameraController();
		m_cameraController->getTransform().setOrigin(Edge::FloatVector3(0.0f, 0.0f, -10.0f));
	}

	return true;
}

bool EdgeDemo::PreInitedDemo::initDebugVisualizationData()
{
	m_debugVisualizationDataController = new Edge::DebugVisualizationDataController();
	EDGE_CHECK_INITIALIZATION(m_debugVisualizationDataController);

	return true;
}

bool EdgeDemo::PreInitedDemo::init()
{
	EDGE_CHECK_RETURN_FALSE(initPhysics());
	EDGE_CHECK_RETURN_FALSE(initCameraController());

	EDGE_CHECK_RETURN_FALSE(initDebugVisualizationData());

	EDGE_CHECK_RETURN_FALSE(initDemo());

	return true;
}

void EdgeDemo::PreInitedDemo::release()
{
	releaseDemo();

	EDGE_SAFE_DESTROY(m_cameraController);
}

void EdgeDemo::PreInitedDemo::updateLogic(float deltaTime)
{
	if (m_cameraController)
	{
		m_cameraController->update(deltaTime);
	}

	updateDemoLogic(deltaTime);
}

void EdgeDemo::PreInitedDemo::prePhysStepUpdate(float deltaTime)
{
	prePhysStepDemoUpdate(deltaTime);
}

void EdgeDemo::PreInitedDemo::physUpdate(float deltaTime)
{
	m_timeStepper.addTime(deltaTime);

	while (m_timeStepper.makeStep())
	{
		const float physStepDeltaTime = m_timeStepper.getStepTime();

		prePhysStepUpdate(physStepDeltaTime);
		m_physicsScene->update(physStepDeltaTime);
	}
}
