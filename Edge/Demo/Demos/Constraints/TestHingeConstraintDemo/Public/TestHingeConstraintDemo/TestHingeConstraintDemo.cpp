#include "TestHingeConstraintDemo.h"

#include "EdgePhysics/Physics/Physics.h"
#include "EdgePhysics/Physics/PhysicsCore.h"
#include "EdgePhysics/Physics/Collision/Shapes/PhysicsBoxShape.h"
#include "EdgePhysics/Physics/Collision/Shapes/PhysicsSphereShape.h"
#include "EdgePhysics/Physics/Constraint/Constraints/HingeConstraint.h"
#include "EdgePhysics/Physics/Utils/Body/MotionPropertyComputer.h"

void EdgeDemo::TestHingeConstraintDemo::drawBox(const Edge::Transform& transform, const Edge::FloatVector3& size, bool isDynamic) const
{
	if (isDynamic)
	{
		m_debugVisualizationDataController->addArrow(transform.getOrigin(), transform.getAxisX(), 0.2f, Edge::NormalizedColorRed);
		m_debugVisualizationDataController->addArrow(transform.getOrigin(), transform.getAxisY(), 0.2f, Edge::NormalizedColorGreen);
		m_debugVisualizationDataController->addArrow(transform.getOrigin(), transform.getAxisZ(), 0.2f, Edge::NormalizedColorBlue);

		m_debugVisualizationDataController->addWireframeBox(transform, size);
	}
	else
	{
		m_debugVisualizationDataController->addBox(transform, size);
	}
}

bool EdgeDemo::TestHingeConstraintDemo::initDemo()
{
	Edge::PhysicsBodyFactory::BodyCreationParam bodyCreationParam;

	Edge::PhysicsBodyFactory::BodyMotionCreationParam bodyMotionCreationParam;
	bodyMotionCreationParam.m_mass = 1.0f;
	bodyMotionCreationParam.m_angularDamping = 0.2f;

	Edge::PhysicsBodyFactory::EntityCollisionCreationParam bodyCollisionCreationParam;

	bodyCreationParam.m_collisionParam = &bodyCollisionCreationParam;

	{
		bodyCollisionCreationParam.m_shape = new Edge::PhysicsBoxShape(Edge::FloatVector3(1.0f));

		m_staticBody = Edge::GetPhysics().createBody(&bodyCreationParam);
		m_physicsScene->addEntity(m_staticBody);
	}

	{
		bodyCollisionCreationParam.m_shape = new Edge::PhysicsBoxShape(Edge::FloatVector3(1.0f));

		bodyMotionCreationParam.m_inertia = Edge::MotionPropertyComputer::CalcBoxInertiaTensor(bodyMotionCreationParam.m_mass, 1.0f);
		bodyCreationParam.m_motionCreationParam = &bodyMotionCreationParam;

		bodyCreationParam.m_position.m_x = 1.0f;

		m_dynamicBody = Edge::GetPhysics().createBody(&bodyCreationParam);
		m_physicsScene->addEntity(m_dynamicBody);
	}

	m_constraint = new Edge::HingeConstraint(
		m_staticBody, m_dynamicBody,
		Edge::FloatVector3(0.5f, -0.5f, 0.0f), Edge::FloatVector3(-0.5f, 0.5f, 0.0f),
		Edge::FloatVector3UnitZ, Edge::FloatVector3UnitZ);
	m_physicsScene->addConstraint(m_constraint);

	//
	//m_dynamicBody->getMotion()->applyImpulse(Edge::FloatVector3(15.0f, 0.0f, 0.0f), Edge::FloatVector3(0.0f, 0.0f, 0.0f));
	//m_dynamicBody->getMotion()->applyAngularImpulse(Edge::FloatVector3(0.0f, 0.0f, 0.5f));

	return true;
}

void EdgeDemo::TestHingeConstraintDemo::releaseDemo()
{
	m_physicsScene->removeConstraint(m_constraint);

	m_physicsScene->removeEntity(m_staticBody.getObject());
	m_physicsScene->removeEntity(m_dynamicBody.getObject());
}

void EdgeDemo::TestHingeConstraintDemo::updateDemoLogic(float deltaTime)
{
	m_debugVisualizationDataController->clear();

	drawBox(m_staticBody->getBodyTransform()->getWorldTransform(), 1.0f, false);
	drawBox(m_dynamicBody->getBodyTransform()->getWorldTransform(), 1.0f, true);
}
