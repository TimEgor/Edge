#include "TestHingeConstraintDemo.h"

#include "EdgeCommon/String/Format.h"
#include "EdgePhysics/Physics/Physics.h"
#include "EdgePhysics/Physics/PhysicsCore.h"
#include "EdgePhysics/Physics/Constraint/Constraints/HingeConstraint.h"
#include "EdgePhysics/Physics/Utils/Body/MotionPropertyComputer.h"

#include "EdgeDemoFramework/DemoApplication/DemoApplication.h"

void EdgeDemo::TestHingeConstraintDemo::drawBox(const Edge::PhysicsBodyReference& body, bool isDynamic) const
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

bool EdgeDemo::TestHingeConstraintDemo::initDemo()
{
	m_cameraController->getTransform().setOrigin(Edge::FloatVector3(0.0f, 0.0f, -5.0f));

	//
	Edge::PhysicsBodyFactory::BodyCreationParam bodyCreationParam;

	constexpr Edge::FloatVector3 size(2.0f);

	Edge::PhysicsBodyFactory::BodyMotionCreationParam bodyMotionCreationParam;
	bodyMotionCreationParam.m_mass = 1.0f;

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

	m_dynamicBody->getBodyMotion()->applyAngularImpulse(Edge::FloatVector3(0.0f, 0.0f, 0.5f));

	return true;
}

void EdgeDemo::TestHingeConstraintDemo::releaseDemo()
{
	m_physicsScene->removeConstraint(m_constraint);

	m_physicsScene->removeEntity(m_staticBody);
	m_physicsScene->removeEntity(m_dynamicBody);
}

void EdgeDemo::TestHingeConstraintDemo::updateDemoLogic(float deltaTime)
{
	m_debugVisualizationDataController->clear();

	drawBox(m_staticBody, false);
	drawBox(m_dynamicBody, true);

	m_debugVisualizationDataController->addScreenText(Edge::UInt32Vector2Zero, Edge::StringFormat("%.3f", Edge::Math::ConvertRadToDeg(m_constraint->getCurrentAngle())), 20);
}
