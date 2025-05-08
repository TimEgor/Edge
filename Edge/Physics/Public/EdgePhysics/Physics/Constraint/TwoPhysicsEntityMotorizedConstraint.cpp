#include "TwoPhysicsEntityMotorizedConstraint.h"

bool Edge::TwoPhysicsEntityMotorizedConstraint::validateMotorType(const PhysicsConstraintMotorReference& motor) const
{
	return true;
}

Edge::TwoPhysicsEntityMotorizedConstraint::TwoPhysicsEntityMotorizedConstraint(
	const PhysicsEntityReference& entity1,
	const PhysicsEntityReference& entity2,
	const PhysicsConstraintMotorReference& motor
)
	: TwoPhysicsEntityConstraint(entity1, entity2)
{
	setMotor(motor);
}

void Edge::TwoPhysicsEntityMotorizedConstraint::setMotor(const PhysicsConstraintMotorReference& motor)
{
	PhysicsConstraintMotor* setMotor = motor.getObject();

	if (!validateMotorType(motor))
	{
		setMotor = nullptr;
	}

	if (setMotor == m_motor)
	{
		return;
	}

	if (setMotor)
	{
		if (setMotor->getConstraintContext())
		{
			EDGE_ASSERT_FAIL_MESSAGE("Constraint motor has been already set.");
			return;
		}

		setMotor->setConstraintContext(this);
	}

	if (m_motor)
	{
		m_motor->setConstraintContext(nullptr);
	}

	m_motor = setMotor;
}

Edge::PhysicsConstraintMotorReference Edge::TwoPhysicsEntityMotorizedConstraint::getMotor() const
{
	return m_motor;
}
