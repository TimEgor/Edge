#include "TestCollisionDemo.h"

#include "EdgePhysics/Physics/Physics.h"
#include "EdgePhysics/Physics/PhysicsCore.h"
#include "EdgePhysics/Physics/Collision/PhysicsCollisionContactManager.h"
#include "EdgePhysics/Physics/Collision/Shapes/PhysicsBoxShape.h"
#include "EdgePhysics/Physics/Collision/Shapes/PhysicsSphereShape.h"

bool EdgeDemo::TestCollisionDemo::initDemo()
{
	Edge::PhysicsBodyFactory::BodyCreationParam bodyCreationParam;

	Edge::PhysicsBodyFactory::BodyMotionCreationParam bodyMotionCreationParam;
	bodyMotionCreationParam.m_mass = 1.0f;
	bodyMotionCreationParam.m_angularDamping = 0.2f;

	Edge::PhysicsBodyFactory::EntityCollisionCreationParam bodyCollisionCreationParam;
	bodyCollisionCreationParam.m_shape = new Edge::PhysicsSphereShape(0.5f);

	bodyCreationParam.m_motionCreationParam = &bodyMotionCreationParam;
	bodyCreationParam.m_collisionParam = &bodyCollisionCreationParam;

	bodyCreationParam.m_position.m_y = 10.0f;

	m_dynamicBody = Edge::GetPhysics().createBody(&bodyCreationParam);

	m_physicsScene->addEntity(m_dynamicBody);

	bodyCreationParam.m_position.m_y = -5.0f;
	//bodyCreationParam.m_motionCreationParam = nullptr;
	bodyCreationParam.m_motionCreationParam->m_gravityFactor = 0.0f;

	bodyCollisionCreationParam.m_shape = new Edge::PhysicsSphereShape(5.0f);

	m_staticBody = Edge::GetPhysics().createBody(&bodyCreationParam);

	m_physicsScene->addEntity(m_staticBody);

	return true;
}

void EdgeDemo::TestCollisionDemo::releaseDemo()
{
	m_physicsScene->removeEntity(m_dynamicBody.getObject());
	m_physicsScene->removeEntity(m_staticBody.getObject());

	m_dynamicBody.reset();
	m_staticBody.reset();
}

void EdgeDemo::TestCollisionDemo::updateDemoLogic(float deltaTime)
{
	m_debugVisualizationDataController->clear();

	m_debugVisualizationDataController->addSphere(m_dynamicBody->getTransform()->getPosition(), Edge::FloatVector3UnitZ, Edge::FloatVector3UnitY, 0.5f);
	m_debugVisualizationDataController->addSphere(m_staticBody->getTransform()->getPosition(), Edge::FloatVector3UnitZ, Edge::FloatVector3UnitY, 5.0f);

	
	const Edge::PhysicsCollisionContactManager& contactManager = m_physicsScene->getCollisionManager()->getContactManager();
	const Edge::PhysicsCollisionContact* contact = contactManager.getContact(m_dynamicBody->getCollision(), m_staticBody->getCollision());
	if (contact)
	{
		const Edge::PhysicsCollisionContactPoint* contactPoint = contactManager.getContactPoint(contact->getCollisionPointBaseIndex());
		if (contactPoint)
		{
			m_debugVisualizationDataController->addArrow(contactPoint->m_position, contactPoint->m_normal, 0.5f, Edge::NormalizedColorBlue);
			m_debugVisualizationDataController->addPoint(contactPoint->m_position, Edge::NormalizedColorCyan);
		}
	}
}
