#include "TestHingeConstraintDemo.h"

#include "EdgeDemoFramework/DemoApplication/DemoApplication.h"
#include "EdgeFramework/FrameworkCore.h"
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

	//const Edge::FloatVector3& size = body->getCollision()->getShape().getObjectCastRef<Edge::PhysicsBoxShape>().getSize();
	constexpr Edge::FloatVector3 size(2.0f);

	if (isDynamic)
	{
		m_debugVisualizationDataController->addArrow(transform.getOrigin().getFloatVector3(), transform.getAxisX().getFloatVector3(), 0.2f, Edge::NormalizedColorRed);
		m_debugVisualizationDataController->addArrow(transform.getOrigin().getFloatVector3(), transform.getAxisY().getFloatVector3(), 0.2f, Edge::NormalizedColorGreen);
		m_debugVisualizationDataController->addArrow(transform.getOrigin().getFloatVector3(), transform.getAxisZ().getFloatVector3(), 0.2f, Edge::NormalizedColorBlue);

		m_debugVisualizationDataController->addArrow(transform.getOrigin().getFloatVector3(), (transform.getAxisZ() * 2.5_ecv).getFloatVector3(), 0.2f, Edge::NormalizedColorMagneta);

		m_debugVisualizationDataController->addWireframeBox(transform, size);
	}
	else
	{
		m_debugVisualizationDataController->addWireframeBox(transform, size, Edge::NormalizedColorBlue);
	}
}

bool EdgeDemo::TestHingeConstraintDemo::initDemo()
{
	//Edge::FrameworkCore::getInstance().getApplication().setTimeScale(0.05f);

	m_cameraController->getTransform().setOrigin(Edge::FloatVector3(0.0f, 0.0f, -5.0f));

	//
	Edge::PhysicsBodyFactory::BodyCreationParam bodyCreationParam;

	constexpr Edge::FloatVector3 size(2.0f);

	Edge::PhysicsBodyFactory::BodyMotionCreationParam bodyMotionCreationParam;
	bodyMotionCreationParam.m_mass = 1.0f;

	Edge::PhysicsBodyFactory::EntityCollisionCreationParam bodyCollisionCreationParam;

	bodyCreationParam.m_collisionParam = &bodyCollisionCreationParam;

	{
		m_staticBody = Edge::GetPhysics().createBody(&bodyCreationParam);
		m_physicsScene->addEntity(m_staticBody);
	}

	{
		bodyMotionCreationParam.m_inertia = Edge::MotionPropertyComputer::CalcBoxInertiaTensor(bodyMotionCreationParam.m_mass, size);
		bodyCreationParam.m_motionCreationParam = &bodyMotionCreationParam;

		bodyCreationParam.m_position.setZ(-2.5);

		m_dynamicBody = Edge::GetPhysics().createBody(&bodyCreationParam);
		m_physicsScene->addEntity(m_dynamicBody);
	}

	m_constraint = new Edge::HingeConstraint(
		m_staticBody, m_dynamicBody,
		Edge::FloatVector3Zero, Edge::ComputeVector3(0.0, 0.0, 2.5),
		Edge::FloatVector3UnitZ, Edge::FloatVector3UnitZ);
	m_physicsScene->addConstraint(m_constraint);

	m_dynamicBody->getBodyMotion()->applyAngularImpulse(Edge::FloatVector3(0.0f, 0.0f, 3.5f));

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
		m_debugVisualizationDataController->addWireframeSphere(contactPoint.m_pointData.m_position1.getFloatVector3(), Edge::FloatVector3UnitZ, Edge::FloatVector3UnitY, 0.05f);
		m_debugVisualizationDataController->addLine(
			contactPoint.m_pointData.m_position1.getFloatVector3(),
			(contactPoint.m_pointData.m_position1 + contactPoint.m_pointData.m_normal).getFloatVector3()
		);
	}
}
