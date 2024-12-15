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

void Edge::PhysicsCollisionConstraintManager::ContactConstraints::preSolve(float deltaTime)
{
	preSolvePenetrationPart();
}

void Edge::PhysicsCollisionConstraintManager::ContactConstraints::warmUp()
{
	m_penetrationPart.warmUp(m_contactPoint.m_normal);
}

void Edge::PhysicsCollisionConstraintManager::ContactConstraints::solveVelocity()
{
	m_penetrationPart.solveVelocity(m_contactPoint.m_normal);
}

void Edge::PhysicsCollisionConstraintManager::ContactConstraints::solvePosition()
{
	preSolvePenetrationPart();
	m_penetrationPart.solvePosition(m_contactPoint.m_normal, m_contactPoint.m_depth);
}

void Edge::PhysicsCollisionConstraintManager::ContactConstraints::preSolvePenetrationPart()
{
	const ComputeVector contactPosition = (m_contactPoint.m_position1 + m_contactPoint.m_position2) * 0.5f;
	m_penetrationPart.preSolve(contactPosition.getFloatVector3(), m_contactPoint.m_normal);
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
		contactContstains.solveVelocity();
	}
}

void Edge::PhysicsCollisionConstraintManager::solvePosition()
{
	for (ContactConstraints& contactContstains : m_constraintCollection)
	{
		contactContstains.solvePosition();
	}
}

void Edge::PhysicsCollisionConstraintManager::addContact(
	const PhysicsEntityReference& entity1, const PhysicsEntityReference& entity2,
	const PhysicsCollisionContactPoint& contactPoint)
{
	m_constraintCollection.emplace_back(entity1, entity2, contactPoint);
}
