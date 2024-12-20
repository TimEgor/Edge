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

	bodyCreationParam.m_collisionParam = &bodyCollisionCreationParam;

	{
		bodyCreationParam.m_position.m_x = 0.0f;
		bodyCreationParam.m_position.m_y = 5.0f;

		const Edge::PhysicsBodyReference staticBody = Edge::GetPhysics().createBody(&bodyCreationParam);
		m_physicsScene->addEntity(staticBody);

		m_bodies.push_back(staticBody);
	}

	bodyCreationParam.m_motionCreationParam = &bodyMotionCreationParam;

	for (uint32_t i = 0; i < 5; ++i)
	{
		bodyCreationParam.m_position.m_x = 1.5f * static_cast<float>(i + 1);
		bodyCreationParam.m_position.m_y = 5.0f;

		const Edge::PhysicsBodyReference dynamicBody = Edge::GetPhysics().createBody(&bodyCreationParam);

		m_physicsScene->addEntity(dynamicBody);

		const Edge::PhysicsConstraintReference constraint = new Edge::KeepDistanceConstraint(m_bodies[m_bodies.size() - 1], dynamicBody, Edge::FloatVector3Zero, Edge::FloatVector3(-1.5f, 0.0f, 0.0f));


		m_physicsScene->addConstraint(constraint);

		m_bodies.push_back(dynamicBody);
		m_constraints.push_back(constraint);
	}

	return true;
}

void EdgeDemo::TestKeepDistanceConstraintDemo::releaseDemo()
{
	for (const auto& constraint : m_constraints)
	{
		m_physicsScene->removeConstraint(constraint);
	}

	for (const auto& body : m_bodies)
	{
		m_physicsScene->removeEntity(body.getObject());
	}
}

void EdgeDemo::TestKeepDistanceConstraintDemo::updateDemoLogic(float deltaTime)
{
	m_debugVisualizationDataController->clear();

	for (const auto& body : m_bodies)
	{
		drawSphere(body);
	}
}
