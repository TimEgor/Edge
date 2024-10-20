#include "TestSpheresBoxCollisionDemo.h"

#include "EdgeCommon/UtilsMacros.h"
#include "EdgeCommon/Random/Random.h"
#include "EdgePhysics/Physics/Physics.h"
#include "EdgePhysics/Physics/PhysicsCore.h"
#include "EdgePhysics/Physics/Collision/PhysicsCollisionContactManager.h"
#include "EdgePhysics/Physics/Collision/Shapes/PhysicsBoxShape.h"
#include "EdgePhysics/Physics/Collision/Shapes/PhysicsSphereShape.h"
#include "EdgePhysics/Physics/Utils/Body/MotionPropertyComputer.h"

bool EdgeDemo::TestSpheresBoxCollisionDemo::initStaticBoxes()
{
	Edge::PhysicsBodyFactory::BodyCreationParam bodyCreationParam;

	Edge::PhysicsEntityFactory::EntityCollisionCreationParam collisionParam;
	collisionParam.m_shape = new Edge::PhysicsBoxShape(Edge::FloatVector3(10.0f, 1.0f, 10.0f));

	bodyCreationParam.m_collisionParam = &collisionParam;

	//bottom
	{
		bodyCreationParam.m_position = Edge::FloatVector3(0.0f, -5.5f, 0.0f);

		const Edge::PhysicsBodyReference box = Edge::GetPhysics().createBody(&bodyCreationParam);

		m_physicsScene->addEntity(box);

		m_staticBoxes.push_back(box);
	}

	//right
	{
		bodyCreationParam.m_position = Edge::FloatVector3(5.5f, 0.0f, 0.0f);
		bodyCreationParam.m_rotation = Edge::ComputeQuaternionFromRollPitchYaw(0.0f, 0.0f, 90.0f * EDGE_DEG_TO_RAD).getFloatQuaternion();

		const Edge::PhysicsBodyReference box = Edge::GetPhysics().createBody(&bodyCreationParam);

		m_physicsScene->addEntity(box);

		m_staticBoxes.push_back(box);
	}

	//left
	{
		bodyCreationParam.m_position = Edge::FloatVector3(-5.5f, 0.0f, 0.0f);
		bodyCreationParam.m_rotation = Edge::ComputeQuaternionFromRollPitchYaw(0.0f, 0.0f, 90.0f * EDGE_DEG_TO_RAD).getFloatQuaternion();

		const Edge::PhysicsBodyReference box = Edge::GetPhysics().createBody(&bodyCreationParam);

		m_physicsScene->addEntity(box);

		m_staticBoxes.push_back(box);
	}

	//forward
	{
		bodyCreationParam.m_position = Edge::FloatVector3(0.0f, 0.0f, 5.5f);
		bodyCreationParam.m_rotation = Edge::ComputeQuaternionFromRollPitchYaw(90.0f * EDGE_DEG_TO_RAD, 0.0f, 0.0f).getFloatQuaternion();

		const Edge::PhysicsBodyReference box = Edge::GetPhysics().createBody(&bodyCreationParam);

		m_physicsScene->addEntity(box);

		m_staticBoxes.push_back(box);
	}

	//backward
	{
		bodyCreationParam.m_position = Edge::FloatVector3(0.0f, 0.0f, -5.5f);
		bodyCreationParam.m_rotation = Edge::ComputeQuaternionFromRollPitchYaw(90.0f * EDGE_DEG_TO_RAD, 0.0f, 0.0f).getFloatQuaternion();

		const Edge::PhysicsBodyReference box = Edge::GetPhysics().createBody(&bodyCreationParam);

		m_physicsScene->addEntity(box);

		m_staticBoxes.push_back(box);
	}

	return true;
}

void EdgeDemo::TestSpheresBoxCollisionDemo::updateSphereSpawningLogic(float deltaTime)
{
	if (m_spheres.size() >= MaxSphereCount)
	{
		return;
	}

	m_spawningDelay -= deltaTime;

	if (m_spawningDelay > 0.0f)
	{
		return;
	}

	m_spawningDelay = SpawningDelay;

	Edge::PhysicsBodyFactory::BodyCreationParam bodyCreationParam;
	bodyCreationParam.m_position = Edge::FloatVector3(0.0f, 5.5f, 0.0f);

	Edge::PhysicsEntityFactory::EntityCollisionCreationParam collisionParam;
	collisionParam.m_shape = new Edge::PhysicsSphereShape(1.0f);

	Edge::PhysicsBodyFactory::BodyMotionCreationParam motionParam;
	motionParam.m_mass = 1.0f;
	motionParam.m_inertia = Edge::MotionPropertyComputer::CalcSphereInertiaTensor(motionParam.m_mass, 1.0f);

	bodyCreationParam.m_collisionParam = &collisionParam;
	bodyCreationParam.m_motionCreationParam = &motionParam;

	const Edge::PhysicsBodyReference sphere = Edge::GetPhysics().createBody(&bodyCreationParam);

	m_physicsScene->addEntity(sphere);

	m_spheres.push_back(sphere);
}

bool EdgeDemo::TestSpheresBoxCollisionDemo::initDemo()
{
	EDGE_CHECK_RETURN_FALSE(initStaticBoxes());

	return true;
}

void EdgeDemo::TestSpheresBoxCollisionDemo::releaseDemo()
{
	for (const auto& sphere : m_spheres)
	{
		m_physicsScene->removeEntity(sphere.getObject());
	}

	for (const auto& box : m_staticBoxes)
	{
		m_physicsScene->removeEntity(box.getObject());
	}
}

void EdgeDemo::TestSpheresBoxCollisionDemo::updateDemoLogic(float deltaTime)
{
	updateSphereSpawningLogic(deltaTime);

	m_debugVisualizationDataController->clear();

	m_debugVisualizationDataController->addWireframeBox(Edge::Transform(), Edge::FloatVector3(10.0f, 10.0f, 10.0f), Edge::NormalizedColorRed);

	//for (const auto& box : m_staticBoxes)
	//{
	//	m_debugVisualizationDataController->addWireframeBox(box->getTransform()->getWorldTransform(),
	//		box->getCollision()->getShape().getObjectCastRef<Edge::PhysicsBoxShape>().getSize());
	//}

	for (const auto& sphere : m_spheres)
	{
		const Edge::Transform sphereTransform = sphere->getTransform()->getWorldTransform();
		m_debugVisualizationDataController->addSphere(sphereTransform,
			sphere->getCollision()->getShape().getObjectCastRef<Edge::PhysicsSphereShape>().getRadius());
		m_debugVisualizationDataController->addArrow(sphereTransform.getOrigin(), (sphereTransform.getAxisY() * 1.5f).getFloatVector3(),
			0.5f, Edge::NormalizedColorBlue);
	}
}
