#include "TestBoxStackCollisionDemo.h"

#include "EdgePhysics/Physics/Physics.h"
#include "EdgePhysics/Physics/PhysicsCore.h"
#include "EdgePhysics/Physics/Collision/Shapes/PhysicsBoxShape.h"
#include "EdgePhysics/Physics/Entity/PhysicsBodyFactory.h"

bool EdgeDemo::TestBoxStackCollisionDemo::initDemo()
{
	Edge::PhysicsBodyFactory::BodyCreationParam bodyCreationParam;

	Edge::PhysicsEntityFactory::EntityCollisionCreationParam collisionParam;
	collisionParam.m_shape = new Edge::PhysicsBoxShape(Edge::ComputeVector3(10.0, 1.0, 10.0));

	bodyCreationParam.m_collisionParam = &collisionParam;

	//floor
	{
		bodyCreationParam.m_position = Edge::ComputeVector3(0.0, -5.5, 0.0);

		const Edge::PhysicsBodyReference box = Edge::GetPhysics().createBody(&bodyCreationParam);

		m_physicsScene->addEntity(box);

		m_boxes.push_back(box);
	}

	Edge::PhysicsBodyFactory::BodyMotionCreationParam motionParams;
	bodyCreationParam.m_motionCreationParam = &motionParams;

	collisionParam.m_shape = new Edge::PhysicsBoxShape(Edge::ComputeVector3One);

	//dynamic cubes
	{
		constexpr Edge::ComputeValueType deltaY = 1.5;
		Edge::ComputeValueType positionY = bodyCreationParam.m_position.getY() + deltaY;

		for (uint32_t boxIndex = 0; boxIndex < 5; ++boxIndex)
		{
			bodyCreationParam.m_position = Edge::ComputeVector3(0.0, positionY, 0.0);

			const Edge::PhysicsBodyReference box = Edge::GetPhysics().createBody(&bodyCreationParam);

			m_physicsScene->addEntity(box);

			m_boxes.push_back(box);

			positionY += deltaY;
		}
	}

	return true;
}

void EdgeDemo::TestBoxStackCollisionDemo::releaseDemo()
{
	for (const auto& box : m_boxes)
	{
		m_physicsScene->removeEntity(box);
	}
}

void EdgeDemo::TestBoxStackCollisionDemo::updateDemoLogic(float deltaTime)
{
	m_debugVisualizationDataController->clear();

	for (const auto& box : m_boxes)
	{
		const Edge::Transform boxTransform = box->getTransform()->getWorldTransform();
		m_debugVisualizationDataController->addBox(
			boxTransform,
			box->getCollision()->getShape().getObjectCastRef<Edge::PhysicsBoxShape>().getSize().getFloatVector3()
		);
	}
}
