#include "TestFrictionDemo.h"

#include "EdgeCommon/Random/Random.h"

#include "EdgePhysics/Physics/Physics.h"
#include "EdgePhysics/Physics/PhysicsCore.h"
#include "EdgePhysics/Physics/Collision/Shapes/PhysicsBoxShape.h"
#include "EdgePhysics/Physics/Collision/Shapes/PhysicsSphereShape.h"
#include "EdgePhysics/Physics/Utils/Body/MotionPropertyComputer.h"

bool EdgeDemo::TestFrictionDemo::initDemo()
{
	Edge::PhysicsBodyFactory::BodyCreationParam bodyCreationParam;

	Edge::PhysicsBodyFactory::EntityCollisionCreationParam bodyCollisionCreationParam;
	Edge::PhysicsBodyFactory::BodyMotionCreationParam bodyMotionCreationParam;

	bodyCreationParam.m_collisionParam = &bodyCollisionCreationParam;

	//

	bodyCreationParam.m_position = Edge::FloatVector3(0.0f, 0.0f, 0.0f);
	bodyCollisionCreationParam.m_shape = new Edge::PhysicsBoxShape(Edge::FloatVector3(10.0f, 1.0f, 3.0f));

	m_staticBox = Edge::GetPhysics().createBody(&bodyCreationParam);

	m_physicsScene->addEntity(m_staticBox);

	//

	bodyCreationParam.m_position = Edge::FloatVector3(0.0f, 1.5f, 0.0f);
	bodyCreationParam.m_motionCreationParam = &bodyMotionCreationParam;
	bodyMotionCreationParam.m_inertia = Edge::MotionPropertyComputer::CalcSphereInertiaTensor(bodyMotionCreationParam.m_mass, 1.0f);
	bodyCollisionCreationParam.m_shape = new Edge::PhysicsSphereShape(1.0f);

	m_dynamicBody = Edge::GetPhysics().createBody(&bodyCreationParam);

	m_physicsScene->addEntity(m_dynamicBody);

	//

	//m_dynamicBody->getMotion()->applyImpulse(Edge::FloatVector3UnitX);

	return true;
}

void EdgeDemo::TestFrictionDemo::releaseDemo()
{
	m_physicsScene->removeEntity(m_staticBox);
	m_physicsScene->removeEntity(m_dynamicBody);

	m_staticBox.reset();
	m_dynamicBody.reset();
}

void EdgeDemo::TestFrictionDemo::updateDemoLogic(float deltaTime)
{
	m_debugVisualizationDataController->clear();

	m_debugVisualizationDataController->addBox(m_staticBox->getTransform()->getWorldTransform(),
		m_staticBox->getCollision()->getShape().getObjectCastRef<Edge::PhysicsBoxShape>().getSize().getFloatVector3());

	const Edge::Transform& dynamicTransform = m_dynamicBody->getTransform()->getWorldTransform();

	m_debugVisualizationDataController->addArrow(dynamicTransform.getOrigin().getFloatVector3(), dynamicTransform.getAxisX().getFloatVector3(), 0.2f, Edge::NormalizedColorRed);
	m_debugVisualizationDataController->addArrow(dynamicTransform.getOrigin().getFloatVector3(), dynamicTransform.getAxisY().getFloatVector3(), 0.2f, Edge::NormalizedColorGreen);
	m_debugVisualizationDataController->addArrow(dynamicTransform.getOrigin().getFloatVector3(), dynamicTransform.getAxisZ().getFloatVector3(), 0.2f, Edge::NormalizedColorBlue);

	m_debugVisualizationDataController->addSphere(dynamicTransform,
		m_dynamicBody->getCollision()->getShape().getObjectCastRef<Edge::PhysicsSphereShape>().getRadius());
}
