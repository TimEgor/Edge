#include "HingeConstraint.h"

Edge::HingeConstraint::HingeConstraint(const PhysicsEntityReference& entity1, const PhysicsEntityReference& entity2,
	const FloatVector3& anchor1, const FloatVector3& anchor2, const FloatVector3& axis1, const FloatVector3& axis2)
	: TwoPhysicsEntityConstraint(entity1, entity2),
	m_positionPart(entity1, entity2), m_axisRotationPart(entity1, entity2),
	m_anchor1(anchor1), m_anchor2(anchor2),
	m_axis1(axis1), m_axis2(axis2)
{
}

void Edge::HingeConstraint::preSolve(float deltaTime)
{
	m_positionPart.preSolve(m_anchor1, m_anchor2);
	m_axisRotationPart.preSolve(m_axis1, m_axis2);
}

void Edge::HingeConstraint::warmUp()
{
	if (m_positionPart.isActive())
	{
		m_positionPart.warmUp();
	}

	if (m_axisRotationPart.isActive())
	{
		m_axisRotationPart.warmUp();
	}
}

void Edge::HingeConstraint::solveVelocity()
{
	if (m_positionPart.isActive())
	{
		m_positionPart.solveVelocity();
	}

	if (m_axisRotationPart.isActive())
	{
		m_axisRotationPart.solveVelocity();
	}
}

void Edge::HingeConstraint::solvePosition()
{
	m_positionPart.preSolve(m_anchor1, m_anchor2);

	if (m_positionPart.isActive())
	{
		m_positionPart.solvePosition();
	}

	m_axisRotationPart.preSolve(m_axis1, m_axis2);

	if (m_axisRotationPart.isActive())
	{
		m_axisRotationPart.solvePosition();
	}
}