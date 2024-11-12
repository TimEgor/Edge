#include "TestKeepDistanceConstraintDemo.h"

#include "EdgePhysics/Physics/Physics.h"
#include "EdgePhysics/Physics/PhysicsCore.h"
#include "EdgePhysics/Physics/Collision/Shapes/PhysicsSphereShape.h"
#include "EdgePhysics/Physics/Constraint/Constraints/KeepDistanceConstraint.h"
#include "EdgePhysics/Physics/Utils/Body/MotionPropertyComputer.h"

void EdgeDemo::TestKeepDistanceConstraintDemo::drawSphere(const Edge::PhysicsBodyReference& body) const
{
	const Edge::Transform& transform = body->getTransform()->getWorldTransform();

	m_debugVisualizationDataController->addArrow(transform.getOrigin(), transform.getAxisX(), 0.2f, Edge::NormalizedColorRed);
	m_debugVisualizationDataController->addArrow(transform.getOrigin(), transform.getAxisY(), 0.2f, Edge::NormalizedColorGreen);
	m_debugVisualizationDataController->addArrow(transform.getOrigin(), transform.getAxisZ(), 0.2f, Edge::NormalizedColorBlue);

	m_debugVisualizationDataController->addSphere(transform.getOrigin(), Edge::FloatVector3UnitZ, Edge::FloatVector3UnitY, 0.5f);
}

bool EdgeDemo::TestKeepDistanceConstraintDemo::initDemo()
{
	Edge::PhysicsBodyFactory::BodyCreationParam bodyCreationParam;

	Edge::PhysicsBodyFactory::BodyMotionCreationParam bodyMotionCreationParam;
	bodyMotionCreationParam.m_mass = 1.0f;
	bodyMotionCreationParam.m_angularDamping = 0.2f;
	bodyMotionCreationParam.m_inertia = Edge::MotionPropertyComputer::CalcSphereInertiaTensor(bodyMotionCreationParam.m_mass, 1.0f);

	Edge::PhysicsBodyFactory::EntityCollisionCreationParam bodyCollisionCreationParam;
	bodyCollisionCreationParam.m_shape = new Edge::PhysicsSphereShape(0.5f);

	bodyCreationParam.m_motionCreationParam = &bodyMotionCreationParam;
	bodyCreationParam.m_collisionParam = &bodyCollisionCreationParam;

	bodyCreationParam.m_position.m_x = 5.0f;
	bodyCreationParam.m_position.m_y = 5.0f;

	m_dynamicBody = Edge::GetPhysics().createBody(&bodyCreationParam);

	m_physicsScene->addEntity(m_dynamicBody);

	bodyCreationParam.m_position.m_x = 0.0f;
	bodyCreationParam.m_position.m_y = 5.0f;
	bodyCreationParam.m_motionCreationParam = nullptr;

	m_staticBody = Edge::GetPhysics().createBody(&bodyCreationParam);

	m_physicsScene->addEntity(m_staticBody);

	m_constraint = new Edge::KeepDistanceConstraint(m_staticBody, m_dynamicBody, Edge::FloatVector3Zero, Edge::FloatVector3(-5.0f, 0.0f, 0.0f));

	m_physicsScene->addConstraint(m_constraint);

	return true;
}

void EdgeDemo::TestKeepDistanceConstraintDemo::releaseDemo()
{
	m_physicsScene->removeConstraint(m_constraint);

	m_physicsScene->removeEntity(m_dynamicBody.getObject());
	m_physicsScene->removeEntity(m_staticBody.getObject());
}

void EdgeDemo::TestKeepDistanceConstraintDemo::updateDemoLogic(float deltaTime)
{
	m_debugVisualizationDataController->clear();

	drawSphere(m_staticBody);
	drawSphere(m_dynamicBody);
}
