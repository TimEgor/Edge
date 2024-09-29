#include "TestSpheresCollisionDemo.h"

#include "EdgeCommon/Random/Random.h"
#include "EdgePhysics/Physics/Physics.h"
#include "EdgePhysics/Physics/PhysicsCore.h"
#include "EdgePhysics/Physics/Collision/PhysicsCollisionContactManager.h"
#include "EdgePhysics/Physics/Collision/Shapes/PhysicsBoxShape.h"
#include "EdgePhysics/Physics/Collision/Shapes/PhysicsSphereShape.h"
#include "EdgePhysics/Physics/Utils/Body/MotionPropertyComputer.h"

bool EdgeDemo::TestSpheresCollisionDemo::initDemo()
{
	Edge::PhysicsBodyFactory::BodyCreationParam bodyCreationParam;

	const float radius1 = 0.2f;

	Edge::PhysicsBodyFactory::BodyMotionCreationParam bodyMotionCreationParam;
	bodyMotionCreationParam.m_mass = 4.0f;
	bodyMotionCreationParam.m_angularDamping = 0.2f;
	bodyMotionCreationParam.m_gravityFactor = 0.0f;
	bodyMotionCreationParam.m_inertia = Edge::MotionPropertyComputer::CalcSphereInertiaTensor(bodyMotionCreationParam.m_mass, radius1);

	Edge::PhysicsBodyFactory::EntityCollisionCreationParam bodyCollisionCreationParam;
	bodyCollisionCreationParam.m_shape = new Edge::PhysicsSphereShape(radius1);

	bodyCreationParam.m_motionCreationParam = &bodyMotionCreationParam;
	bodyCreationParam.m_collisionParam = &bodyCollisionCreationParam;

	for (uint32_t i = 0; i < 5; ++i)
	{
		for (uint32_t j = 0; j < 5; ++j)
		{
			for (uint32_t k = 0; k < 7; ++k)
			{
				bodyCreationParam.m_position.m_x = i * 0.5f;
				bodyCreationParam.m_position.m_y = k * 0.5f;
				bodyCreationParam.m_position.m_z = j * 0.5f;

				const Edge::PhysicsBodyReference sphere = Edge::GetPhysics().createBody(&bodyCreationParam);

				m_physicsScene->addEntity(sphere);

				m_spheres.push_back(sphere);
			}
		}
	}

	{
		const float radius2 = Edge::RandomFloat(1.5f, 2.5f);

		bodyMotionCreationParam.m_mass = Edge::RandomFloat(1.0f, 15.0f);
		bodyMotionCreationParam.m_inertia = Edge::MotionPropertyComputer::CalcSphereInertiaTensor(bodyMotionCreationParam.m_mass, radius2);

		bodyCollisionCreationParam.m_shape = new Edge::PhysicsSphereShape(radius2);

		bodyCreationParam.m_position.m_x = -10.0f;
		bodyCreationParam.m_position.m_y = 1.75f;
		bodyCreationParam.m_position.m_z = 1.25f;

		const Edge::PhysicsBodyReference sphere = Edge::GetPhysics().createBody(&bodyCreationParam);

		m_physicsScene->addEntity(sphere);

		sphere->getMotion()->setLinearVelocity((Edge::FloatVector3UnitX * Edge::RandomFloat(3.0f, 10.0f)).getFloatVector3());

		m_spheres.push_back(sphere);
	}

	return true;
}

void EdgeDemo::TestSpheresCollisionDemo::releaseDemo()
{
	for (const auto& sphere : m_spheres)
	{
		m_physicsScene->removeEntity(sphere.getObject());
	}
}

void EdgeDemo::TestSpheresCollisionDemo::updateDemoLogic(float deltaTime)
{
	m_debugVisualizationDataController->clear();

	for (const auto& sphere : m_spheres)
	{
		m_debugVisualizationDataController->addSphere(sphere->getTransform()->getPosition(),
			Edge::FloatVector3UnitZ, Edge::FloatVector3UnitY,
			sphere->getCollision()->getShape().getObjectCastRef<Edge::PhysicsSphereShape>().getRadius());
	}
}
