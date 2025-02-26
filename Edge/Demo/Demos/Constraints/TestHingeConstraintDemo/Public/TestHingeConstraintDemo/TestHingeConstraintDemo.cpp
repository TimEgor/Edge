#include "TestHingeConstraintDemo.h"

#include "EdgePhysics/Physics/Physics.h"
#include "EdgePhysics/Physics/PhysicsCore.h"
#include "EdgePhysics/Physics/Collision/Scene/PhysicsCollisionContactManager.h"
#include "EdgePhysics/Physics/Collision/Shapes/PhysicsBoxShape.h"
#include "EdgePhysics/Physics/Constraint/Constraints/HingeConstraint.h"
#include "EdgePhysics/Physics/Utils/Body/MotionPropertyComputer.h"

void EdgeDemo::TestHingeConstraintDemo::drawBox(const Edge::PhysicsBodyReference& body, bool isDynamic) const
{
	const Edge::Transform& transform = body->getBodyTransform().getObjectRef().getWorldTransform();
	const Edge::PhysicsBodyMotionReference motion = body->getBodyMotion();

	const Edge::FloatVector3& size = body->getCollision()->getShape().getObjectCastRef<Edge::PhysicsBoxShape>().getSize();

	if (isDynamic)
	{
		//m_debugVisualizationDataController->addArrow(transform.getOrigin(), transform.getAxisX(), 0.2f, Edge::NormalizedColorRed);
		//m_debugVisualizationDataController->addArrow(transform.getOrigin(), transform.getAxisY(), 0.2f, Edge::NormalizedColorGreen);
		//m_debugVisualizationDataController->addArrow(transform.getOrigin(), transform.getAxisZ(), 0.2f, Edge::NormalizedColorBlue);

		m_debugVisualizationDataController->addLine(transform.getOrigin(), (transform.getOrigin() + motion->getLinearVelocity()).getFloatVector3(), Edge::NormalizedColorYellow);
		m_debugVisualizationDataController->addLine(transform.getOrigin(), (transform.getOrigin() + motion->getAngularVelocity()).getFloatVector3(), Edge::NormalizedColorGreen);

		m_debugVisualizationDataController->addWireframeBox(transform, size);
	}
	else
	{
		m_debugVisualizationDataController->addBox(transform, size);
	}
}

bool EdgeDemo::TestHingeConstraintDemo::initDemo()
{
	m_cameraController->getTransform().setOrigin(Edge::FloatVector3(0.0f, 0.0f, -3.0f));

	//
	Edge::PhysicsBodyFactory::BodyCreationParam bodyCreationParam;

	constexpr Edge::FloatVector3 size(2.0f);

	Edge::PhysicsBodyFactory::BodyMotionCreationParam bodyMotionCreationParam;
	bodyMotionCreationParam.m_mass = Edge::MotionPropertyComputer::CalcBoxMass(size, 1.0f);
	bodyMotionCreationParam.m_angularDamping = 0.2f;

	Edge::PhysicsBodyFactory::EntityCollisionCreationParam bodyCollisionCreationParam;

	bodyCreationParam.m_collisionParam = &bodyCollisionCreationParam;

	{
		bodyCollisionCreationParam.m_shape = new Edge::PhysicsBoxShape(size);

		m_staticBody = Edge::GetPhysics().createBody(&bodyCreationParam);
		m_physicsScene->addEntity(m_staticBody);
	}

	{
		bodyCollisionCreationParam.m_shape = new Edge::PhysicsBoxShape(size);

		bodyMotionCreationParam.m_inertia = Edge::MotionPropertyComputer::CalcBoxInertiaTensor(bodyMotionCreationParam.m_mass, size);
		bodyCreationParam.m_motionCreationParam = &bodyMotionCreationParam;

		bodyCreationParam.m_position.m_z = -2.5f;

		m_dynamicBody = Edge::GetPhysics().createBody(&bodyCreationParam);
		m_physicsScene->addEntity(m_dynamicBody);
	}

	m_constraint = new Edge::HingeConstraint(
		m_staticBody, m_dynamicBody,
		Edge::FloatVector3Zero, Edge::FloatVector3(0.0f, 0.0f, 2.5f),
		Edge::FloatVector3UnitZ, Edge::FloatVector3UnitZ);
	m_physicsScene->addConstraint(m_constraint);

	m_dynamicBody->getBodyMotion()->applyAngularImpulse(Edge::FloatVector3(0.0f, 0.0f, 1.5f));

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

	drawBox(m_staticBody, false);
	drawBox(m_dynamicBody, true);

	const Edge::PhysicsCollisionContactManager::ContactPointCollection& contactPoints =
		m_physicsScene->getCollisionManager()->getContactManager().getContactPoints();

	for (const Edge::PhysicsInstancedCollisionContactPoint& contactPoint : contactPoints)
	{
		m_debugVisualizationDataController->addWireframeSphere(contactPoint.m_pointData.m_position1, Edge::FloatVector3UnitZ, Edge::FloatVector3UnitY, 0.05f);
		m_debugVisualizationDataController->addLine(
			contactPoint.m_pointData.m_position1,
			(contactPoint.m_pointData.m_position1 + contactPoint.m_pointData.m_normal).getFloatVector3()
		);
	}
}
