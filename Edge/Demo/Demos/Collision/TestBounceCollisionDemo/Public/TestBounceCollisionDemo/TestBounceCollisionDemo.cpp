#include "TestBounceCollisionDemo.h"

#include "EdgePhysics/Physics/Physics.h"
#include "EdgePhysics/Physics/PhysicsCore.h"
#include "EdgePhysics/Physics/Collision/PhysicsCollisionContact.h"
#include "EdgePhysics/Physics/Collision/Shapes/PhysicsBoxShape.h"
#include "EdgePhysics/Physics/Collision/Shapes/PhysicsSphereShape.h"
#include "EdgePhysics/Physics/Utils/Body/MotionPropertyComputer.h"

void EdgeDemo::TestBounceCollisionDemo::drawDynamicSphere(const Edge::PhysicsBodyReference& body) const
{
	const Edge::Transform& dynamicTransform = body->getTransform()->getWorldTransform();

	m_debugVisualizationDataController->addArrow(dynamicTransform.getOrigin().getFloatVector3(), dynamicTransform.getAxisX().getFloatVector3(), 0.2f, Edge::NormalizedColorRed);
	m_debugVisualizationDataController->addArrow(dynamicTransform.getOrigin().getFloatVector3(), dynamicTransform.getAxisY().getFloatVector3(), 0.2f, Edge::NormalizedColorGreen);
	m_debugVisualizationDataController->addArrow(dynamicTransform.getOrigin().getFloatVector3(), dynamicTransform.getAxisZ().getFloatVector3(), 0.2f, Edge::NormalizedColorBlue);

	m_debugVisualizationDataController->addWireframeSphere(dynamicTransform.getOrigin().getFloatVector3(), dynamicTransform.getAxisZ().getFloatVector3(), dynamicTransform.getAxisY().getFloatVector3(), 0.5f);
}

bool EdgeDemo::TestBounceCollisionDemo::initDemo()
{
	Edge::PhysicsBodyFactory::BodyCreationParam bodyCreationParam;

	Edge::PhysicsBodyFactory::BodyMotionCreationParam bodyMotionCreationParam;
	bodyMotionCreationParam.m_mass = 1.0f;
	bodyMotionCreationParam.m_angularDamping = 0.2f;
	bodyMotionCreationParam.m_inertia = Edge::MotionPropertyComputer::CalcSphereInertiaTensor(bodyMotionCreationParam.m_mass, 0.5f);
	bodyMotionCreationParam.m_gravityFactor = 0.0f;

	Edge::PhysicsBodyFactory::EntityCollisionCreationParam bodyCollisionCreationParam;
	bodyCollisionCreationParam.m_shape = new Edge::PhysicsSphereShape(0.5f);

	bodyCreationParam.m_motionCreationParam = &bodyMotionCreationParam;
	bodyCreationParam.m_collisionParam = &bodyCollisionCreationParam;

	//
	bodyCreationParam.m_position.setX(-3.0f);
	bodyCreationParam.m_position.setY(1.5f);

	m_dynamicBody1 = Edge::GetPhysics().createBody(&bodyCreationParam);

	m_physicsScene->addEntity(m_dynamicBody1);

	bodyCreationParam.m_position.setX(3.0f);
	bodyCreationParam.m_position.setY(1.5f);

	m_dynamicBody2 = Edge::GetPhysics().createBody(&bodyCreationParam);

	m_physicsScene->addEntity(m_dynamicBody2);

	bodyCreationParam.m_position.setX(-3.0f);
	bodyCreationParam.m_position.setY(3.5f);

	m_dynamicBody3 = Edge::GetPhysics().createBody(&bodyCreationParam);

	m_physicsScene->addEntity(m_dynamicBody3);

	bodyCreationParam.m_position.setX(3.0f);
	bodyCreationParam.m_position.setY(3.5f);

	m_dynamicBody4 = Edge::GetPhysics().createBody(&bodyCreationParam);

	m_physicsScene->addEntity(m_dynamicBody4);

	//
	bodyCreationParam.m_position.setX(0.0f);
	bodyCreationParam.m_position.setY(5.0f);
	bodyCreationParam.m_motionCreationParam = nullptr;

	bodyCollisionCreationParam.m_shape = new Edge::PhysicsSphereShape(5.0f);

	m_staticBody = Edge::GetPhysics().createBody(&bodyCreationParam);

	//m_physicsScene->addEntity(m_staticBody);

	//initial impulse
	m_dynamicBody1->getMotion()->applyImpulse(Edge::FloatVector3(0.5f, 0.0f, 0.0f));
	m_dynamicBody2->getMotion()->applyImpulse(Edge::FloatVector3(-0.5f, 0.0f, 0.0f));

	m_dynamicBody3->getMotion()->applyImpulse(Edge::FloatVector3(0.8f, 0.0f, 0.0f));
	m_dynamicBody4->getMotion()->applyImpulse(Edge::FloatVector3(-0.2f, 0.0f, 0.0f));

	return true;
}

void EdgeDemo::TestBounceCollisionDemo::releaseDemo()
{
	m_physicsScene->removeEntity(m_dynamicBody1);
	m_physicsScene->removeEntity(m_dynamicBody2);
	m_physicsScene->removeEntity(m_dynamicBody3);
	m_physicsScene->removeEntity(m_dynamicBody4);
	m_physicsScene->removeEntity(m_staticBody);

	m_dynamicBody1.reset();
	m_dynamicBody2.reset();
	m_dynamicBody3.reset();
	m_dynamicBody4.reset();
	m_staticBody.reset();
}

void EdgeDemo::TestBounceCollisionDemo::updateDemoLogic(float deltaTime)
{
	m_debugVisualizationDataController->clear();

	drawDynamicSphere(m_dynamicBody1);
	drawDynamicSphere(m_dynamicBody2);
	drawDynamicSphere(m_dynamicBody3);
	drawDynamicSphere(m_dynamicBody4);
}
