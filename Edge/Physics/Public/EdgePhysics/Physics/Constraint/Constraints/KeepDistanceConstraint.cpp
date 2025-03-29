#include "KeepDistanceConstraint.h"

Edge::KeepDistanceConstraint::KeepDistanceConstraint(const PhysicsEntityReference& entity1,
	const PhysicsEntityReference& entity2, const ComputeVector3& anchor1, const ComputeVector3& anchor2)
	: TwoPhysicsEntityConstraint(entity1, entity2),
	m_positionPart(entity1, entity2),
	m_anchor1(anchor1), m_anchor2(anchor2)
{

}

void Edge::KeepDistanceConstraint::preSolve(float deltaTime)
{
	m_positionPart.preSolve(m_anchor1, m_anchor2);
}

void Edge::KeepDistanceConstraint::warmUp()
{
	if (m_positionPart.isActive())
	{
		m_positionPart.warmUp();
	}
}

void Edge::KeepDistanceConstraint::solveVelocity()
{
	if (m_positionPart.isActive())
	{
		m_positionPart.solveVelocity();
	}
}

void Edge::KeepDistanceConstraint::solvePosition()
{
	m_positionPart.preSolve(m_anchor1, m_anchor2);

	if (m_positionPart.isActive())
	{
		m_positionPart.solvePosition();
	}
}