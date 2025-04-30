#include "TestSpheresCollisionDemo.h"

#include "EdgeCommon/Random/Random.h"
#include "EdgePhysics/Physics/Physics.h"
#include "EdgePhysics/Physics/PhysicsCore.h"
#include "EdgePhysics/Physics/Collision/Scene/PhysicsCollisionContactManager.h"
#include "EdgePhysics/Physics/Collision/Shapes/PhysicsSphereShape.h"
#include "EdgePhysics/Physics/Utils/Body/MotionPropertyComputer.h"

bool EdgeDemo::TestSpheresCollisionDemo::initDemo()
{
	Edge::PhysicsBodyFactory::BodyCreationParam bodyCreationParam;

	const Edge::ComputeValueType radius1 = 0.2_ecv;

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
				bodyCreationParam.m_position.setX(i * 0.5);
				bodyCreationParam.m_position.setY(k * 0.5);
				bodyCreationParam.m_position.setZ(j * 0.5);

				const Edge::PhysicsBodyReference sphere = Edge::GetPhysics().createBody(&bodyCreationParam);

				m_physicsScene->addEntity(sphere);

				m_spheres.push_back(sphere);
			}
		}
	}

	{
		const Edge::ComputeValueType radius2 = Edge::Random(1.5, 2.5);

		bodyMotionCreationParam.m_mass = Edge::Random(10.0, 15.0);
		bodyMotionCreationParam.m_inertia = Edge::MotionPropertyComputer::CalcSphereInertiaTensor(bodyMotionCreationParam.m_mass, radius2);

		bodyCollisionCreationParam.m_shape = new Edge::PhysicsSphereShape(radius2);

		bodyCreationParam.m_position.setX(-10.0);
		bodyCreationParam.m_position.setY(1.75);
		bodyCreationParam.m_position.setZ(1.25);

		const Edge::PhysicsBodyReference sphere = Edge::GetPhysics().createBody(&bodyCreationParam);

		m_physicsScene->addEntity(sphere);

		sphere->getMotion()->setLinearVelocity(Edge::ComputeVector3UnitX * Edge::Random(3.0, 10.0));

		m_spheres.push_back(sphere);
	}

	return true;
}

void EdgeDemo::TestSpheresCollisionDemo::releaseDemo()
{
	for (const auto& sphere : m_spheres)
	{
		m_physicsScene->removeEntity(sphere);
	}
}

void EdgeDemo::TestSpheresCollisionDemo::updateDemoLogic(float deltaTime)
{
	m_debugVisualizationDataController->clear();

	for (const auto& sphere : m_spheres)
	{
		m_debugVisualizationDataController->addSphere(sphere->getTransform()->getWorldTransform(),
			sphere->getCollision()->getShape().getObjectCastRef<Edge::PhysicsSphereShape>().getRadius());
	}
}
