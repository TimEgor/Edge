#include "TestCollisionDemo.h"

#include "EdgePhysics/Physics/Physics.h"
#include "EdgePhysics/Physics/PhysicsCore.h"
#include "EdgePhysics/Physics/Collision/PhysicsCollisionContactManager.h"
#include "EdgePhysics/Physics/Collision/Shapes/PhysicsBoxShape.h"
#include "EdgePhysics/Physics/Collision/Shapes/PhysicsSphereShape.h"
#include "EdgePhysics/Physics/Utils/Body/MotionPropertyComputer.h"

void EdgeDemo::TestCollisionDemo::drawDynamicSphere(const Edge::PhysicsBodyReference& body) const
{
	const Edge::Transform& dynamicTransform = body->getTransform()->getWorldTransform();

	m_debugVisualizationDataController->addArrow(dynamicTransform.getOrigin(), dynamicTransform.getAxisX(), 0.2f, Edge::NormalizedColorRed);
	m_debugVisualizationDataController->addArrow(dynamicTransform.getOrigin(), dynamicTransform.getAxisY(), 0.2f, Edge::NormalizedColorGreen);
	m_debugVisualizationDataController->addArrow(dynamicTransform.getOrigin(), dynamicTransform.getAxisZ(), 0.2f, Edge::NormalizedColorBlue);

	m_debugVisualizationDataController->addSphere(dynamicTransform.getOrigin(), Edge::FloatVector3UnitZ, Edge::FloatVector3UnitY, 0.5f);
}

bool EdgeDemo::TestCollisionDemo::initDemo()
{
	Edge::PhysicsBodyFactory::BodyCreationParam bodyCreationParam;

	Edge::PhysicsBodyFactory::BodyMotionCreationParam bodyMotionCreationParam;
	bodyMotionCreationParam.m_mass = 1.0f;
	bodyMotionCreationParam.m_angularDamping = 0.2f;
	bodyMotionCreationParam.m_inertia = Edge::MotionPropertyComputer::CalcSphereInertiaTensor(bodyMotionCreationParam.m_mass, 0.5f);

	Edge::PhysicsBodyFactory::EntityCollisionCreationParam bodyCollisionCreationParam;
	bodyCollisionCreationParam.m_shape = new Edge::PhysicsSphereShape(0.5f);

	bodyCreationParam.m_motionCreationParam = &bodyMotionCreationParam;
	bodyCreationParam.m_collisionParam = &bodyCollisionCreationParam;

	bodyCreationParam.m_position.m_x = 0.0f;
	bodyCreationParam.m_position.m_y = 1.5f;

	m_dynamicBody1 = Edge::GetPhysics().createBody(&bodyCreationParam);

	m_physicsScene->addEntity(m_dynamicBody1);

	bodyCreationParam.m_position.m_x = 1.1f;
	bodyCreationParam.m_position.m_y = 1.5f;

	m_dynamicBody2 = Edge::GetPhysics().createBody(&bodyCreationParam);

	m_physicsScene->addEntity(m_dynamicBody2);

	bodyCreationParam.m_position.m_x = 0.0f;
	bodyCreationParam.m_position.m_y = -5.0f;
	bodyCreationParam.m_motionCreationParam = nullptr;

	bodyCollisionCreationParam.m_shape = new Edge::PhysicsSphereShape(5.0f);

	m_staticBody = Edge::GetPhysics().createBody(&bodyCreationParam);

	m_physicsScene->addEntity(m_staticBody);

	return true;
}

void EdgeDemo::TestCollisionDemo::releaseDemo()
{
	m_physicsScene->removeEntity(m_dynamicBody1.getObject());
	m_physicsScene->removeEntity(m_dynamicBody2.getObject());
	m_physicsScene->removeEntity(m_staticBody.getObject());

	m_dynamicBody1.reset();
	m_dynamicBody2.reset();
	m_staticBody.reset();
}

void EdgeDemo::TestCollisionDemo::updateDemoLogic(float deltaTime)
{
	m_debugVisualizationDataController->clear();

	drawDynamicSphere(m_dynamicBody1);
	drawDynamicSphere(m_dynamicBody2);
		
	m_debugVisualizationDataController->addSphere(m_staticBody->getTransform()->getPosition(), Edge::FloatVector3UnitZ, Edge::FloatVector3UnitY, 5.0f);

	
	const Edge::PhysicsCollisionContactManager& contactManager = m_physicsScene->getCollisionManager()->getContactManager();
	const Edge::PhysicsCollisionContact* contact = contactManager.getContact(m_dynamicBody1->getCollision(), m_staticBody->getCollision());
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
