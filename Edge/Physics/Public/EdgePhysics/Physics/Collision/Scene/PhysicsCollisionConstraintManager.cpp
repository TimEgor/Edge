#include "PhysicsCollisionConstraintManager.h"

#include "EdgePhysics/Physics/Collision/PhysicsCollisionContact.h"

Edge::JobGraphReference Edge::PhysicsCollisionConstraintManager::getPreSolvingJobGraph(float deltaTime)
{
	JobGraphBuilder m_graphBuilder;

	const JobGraphBuilder::JobGraphJobID preSolvingJobID = m_graphBuilder.addJob(
		createLambdaJob([dt = deltaTime, this]()
			{
				preSolve(dt);
				warmUp();
			}, "Pre solve contact constraints")
	);

	return m_graphBuilder.getGraph();
}

Edge::JobGraphReference Edge::PhysicsCollisionConstraintManager::getVelocitySolvingJobGraph()
{
	JobGraphBuilder m_graphBuilder;

	const JobGraphBuilder::JobGraphJobID velocitySolvingJobID = m_graphBuilder.addJob(
		createLambdaJob([this]()
			{
				solveVelocity();
			}, "Solve contact constraints velocities")
	);

	return m_graphBuilder.getGraph();
}

Edge::JobGraphReference Edge::PhysicsCollisionConstraintManager::getPositionSolvingJobGraph()
{
	JobGraphBuilder m_graphBuilder;

	const JobGraphBuilder::JobGraphJobID positionSolvingJobID = m_graphBuilder.addJob(
		createLambdaJob([this]()
			{
				solvePosition();
			}, "Solve contact constraints positions")
	);

	return m_graphBuilder.getGraph();
}

void Edge::PhysicsCollisionConstraintManager::prepareCollection(uint32_t contactPointCount)
{
	m_constraintCollection.clear();
	m_constraintCollection.reserve(contactPointCount);
}

Edge::PhysicsCollisionConstraintManager::ContactConstraints::ContactConstraints(const PhysicsEntityReference& entity1,
	const PhysicsEntityReference& entity2, const PhysicsCollisionContactPoint& contactPoint)
	: m_entity1(entity1), m_entity2(entity2),
	m_frictionPart1(entity1, entity2), m_frictionPart2(entity1, entity2),
	m_penetrationPart(entity1, entity2), m_contactPoint(contactPoint) {}

void Edge::PhysicsCollisionConstraintManager::ContactConstraints::preSolve(float deltaTime)
{
	{
		m_frictionTangent1 = m_contactPoint.m_normal.getOrthogonal();
		m_frictionTangent2 = CrossComputeVector3(m_frictionTangent1, m_contactPoint.m_normal);

		m_contactPosition = (m_contactPoint.m_position1 + m_contactPoint.m_position2) * ComputeValueType(0.5);
	}

	preSolveFrictionParts();
	preSolvePenetrationPart();
}

void Edge::PhysicsCollisionConstraintManager::ContactConstraints::warmUp()
{
	m_penetrationPart.warmUp(m_contactPoint.m_normal);

	m_frictionPart1.warmUp(m_frictionTangent1);
	m_frictionPart2.warmUp(m_frictionTangent2);
}

void Edge::PhysicsCollisionConstraintManager::ContactConstraints::solvePenetrationPartVelocity()
{
	m_penetrationPart.solveVelocity(m_contactPoint.m_normal);
}

void Edge::PhysicsCollisionConstraintManager::ContactConstraints::solveFrictionPartsVelocity()
{
	const PhysicsEntityCollisionReference collision1 = m_entity1->getCollision();
	const PhysicsEntityCollisionReference collision2 = m_entity2->getCollision();
	const float friction = collision1->getFriction() * collision2->getFriction();

	const float limit = m_penetrationPart.getTotalLambda() * friction;

	const float lambda1 = m_frictionPart1.solveVelocity(m_frictionTangent1);
	const float lambda2 = m_frictionPart2.solveVelocity(m_frictionTangent2);

	m_frictionPart1.applyVelocity(m_frictionTangent1, lambda1 * friction);
	m_frictionPart2.applyVelocity(m_frictionTangent2, lambda2 * friction);
}

void Edge::PhysicsCollisionConstraintManager::ContactConstraints::solvePenetrationPartPosition()
{
	preSolvePenetrationPart();
	m_penetrationPart.solvePosition(m_contactPoint.m_normal, m_contactPoint.m_depth);
}

void Edge::PhysicsCollisionConstraintManager::ContactConstraints::preSolveFrictionParts()
{
	m_frictionPart1.preSolve(m_contactPosition, m_frictionTangent1);
	m_frictionPart2.preSolve(m_contactPosition, m_frictionTangent2);
}

void Edge::PhysicsCollisionConstraintManager::ContactConstraints::preSolvePenetrationPart()
{
	m_penetrationPart.preSolve(m_contactPosition, m_contactPoint.m_normal);
}

void Edge::PhysicsCollisionConstraintManager::preSolve(float deltaTime)
{
	for (ContactConstraints& contactContstains : m_constraintCollection)
	{
		contactContstains.preSolve(deltaTime);
	}
}

void Edge::PhysicsCollisionConstraintManager::warmUp()
{
	for (ContactConstraints& contactContstains : m_constraintCollection)
	{
		contactContstains.warmUp();
	}
}

void Edge::PhysicsCollisionConstraintManager::solveVelocity()
{
	for (ContactConstraints& contactContstains : m_constraintCollection)
	{
		contactContstains.solveFrictionPartsVelocity();
	}

	for (ContactConstraints& contactContstains : m_constraintCollection)
	{
		contactContstains.solvePenetrationPartVelocity();
	}
}

void Edge::PhysicsCollisionConstraintManager::solvePosition()
{
	for (ContactConstraints& contactContstains : m_constraintCollection)
	{
		contactContstains.solvePenetrationPartPosition();
	}
}

void Edge::PhysicsCollisionConstraintManager::addContact(
	const PhysicsEntityReference& entity1, const PhysicsEntityReference& entity2,
	const PhysicsCollisionContactPoint& contactPoint)
{
	m_constraintCollection.emplace_back(entity1, entity2, contactPoint);
}
