#include "FixedConstraint.h"

Edge::FixedConstraint::FixedConstraint(const PhysicsEntityReference& entity1, const PhysicsEntityReference& entity2,
	const FloatVector3& anchor1, const FloatVector3& anchor2, FloatQuaternion deltaRotation)
	: TwoPhysicsEntityConstraint(entity1, entity2),
	m_positionPart(entity1, entity2), m_rotationPart(entity1, entity2),
	m_anchor1(anchor1), m_anchor2(anchor2),
	m_initialDeltaRotation(deltaRotation)
{
}

void Edge::FixedConstraint::preSolve(float deltaTime)
{
	m_positionPart.preSolve(m_anchor1, m_anchor2);
	m_rotationPart.preSolve();
}

void Edge::FixedConstraint::warmUp()
{
	if (m_rotationPart.isActive())
	{
		m_rotationPart.warmUp();
	}

	if (m_positionPart.isActive())
	{
		m_positionPart.warmUp();
	}
}

void Edge::FixedConstraint::solveVelocity()
{
	if (m_rotationPart.isActive())
	{
		m_rotationPart.solveVelocity();
	}

	if (m_positionPart.isActive())
	{
		m_positionPart.solveVelocity();
	}
}

void Edge::FixedConstraint::solvePosition()
{
	m_rotationPart.preSolve();

	if (m_rotationPart.isActive())
	{
		m_rotationPart.solvePosition(m_initialDeltaRotation);
	}

	m_positionPart.preSolve(m_anchor1, m_anchor2);

	if (m_positionPart.isActive())
	{
		m_positionPart.solvePosition();
	}
}
