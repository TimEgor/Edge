#include "TestPrismaticConstraintDemo.h"

#include "EdgePhysics/Physics/Physics.h"
#include "EdgePhysics/Physics/PhysicsCore.h"
#include "EdgePhysics/Physics/Constraint/Constraints/PrismaticConstraint.h"
#include "EdgePhysics/Physics/Utils/Body/MotionPropertyComputer.h"

#include "EdgeDemoFramework/DemoApplication/DemoApplication.h"
#include "EdgeFramework/FrameworkCore.h"

void EdgeDemo::TestPrismaticConstraintDemo::drawBox(const Edge::PhysicsBodyReference& body, bool isDynamic) const
{
	const Edge::Transform& transform = body->getBodyTransform().getObjectRef().getWorldTransform();
	const Edge::PhysicsBodyMotionReference motion = body->getBodyMotion();

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

bool EdgeDemo::TestPrismaticConstraintDemo::initDemo()
{
	//Edge::FrameworkCore::getInstance().getApplication().setTimeScale(0.1f);

	Edge::PhysicsBodyFactory::BodyCreationParam bodyCreationParam;

	constexpr Edge::FloatVector3 size(2.0f);

	Edge::PhysicsBodyFactory::BodyMotionCreationParam bodyMotionCreationParam;
	bodyMotionCreationParam.m_mass = 1.0f;

	{
		m_staticBody = Edge::GetPhysics().createBody(&bodyCreationParam);
		m_physicsScene->addEntity(m_staticBody);
	}

	{
		//bodyMotionCreationParam.m_inertia = Edge::MotionPropertyComputer::CalcBoxInertiaTensor(bodyMotionCreationParam.m_mass, size);
		bodyMotionCreationParam.m_inertia = Edge::ComputeVector3One;
		bodyCreationParam.m_motionCreationParam = &bodyMotionCreationParam;

		bodyCreationParam.m_position.setZ(-2.5);

		m_dynamicBody = Edge::GetPhysics().createBody(&bodyCreationParam);
		m_physicsScene->addEntity(m_dynamicBody);
	}

	m_constraint = Edge::CreatePrismaticConstraintInWorldSpace(
		m_staticBody, m_dynamicBody,
		Edge::ComputeVector3Zero, Edge::ComputeVector3Zero,
		Edge::ComputeVector3UnitX, Edge::ComputeVector3UnitX);
	m_physicsScene->addConstraint(m_constraint);

	m_dynamicBody->getBodyMotion()->applyImpulse(Edge::FloatVector3(0.5f, 0.0f, 0.0f));

	return true;
}

void EdgeDemo::TestPrismaticConstraintDemo::releaseDemo()
{
	m_physicsScene->removeConstraint(m_constraint);

	m_physicsScene->removeEntity(m_staticBody.getObject());
	m_physicsScene->removeEntity(m_dynamicBody.getObject());
}

void EdgeDemo::TestPrismaticConstraintDemo::updateDemoLogic(float deltaTime)
{
	m_debugVisualizationDataController->clear();

	drawBox(m_staticBody, false);
	drawBox(m_dynamicBody, true);
}
