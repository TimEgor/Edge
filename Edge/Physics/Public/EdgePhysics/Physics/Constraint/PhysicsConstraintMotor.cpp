#include "PhysicsConstraintMotor.h"

bool Edge::PhysicsConstraintMotor::isEnabled() const
{
	return m_isEnabled;
}

void Edge::PhysicsConstraintMotor::setEnabled(bool isEnabled)
{
	m_isEnabled = isEnabled;
}

void Edge::PhysicsConstraintMotor::setConstraintContext(const TwoPhysicsEntityConstraintReference& constraint)
{
	m_constraint = constraint.getObject();
}

Edge::TwoPhysicsEntityConstraint* Edge::PhysicsConstraintMotor::getConstraintContext() const
{
	return m_constraint;
}
