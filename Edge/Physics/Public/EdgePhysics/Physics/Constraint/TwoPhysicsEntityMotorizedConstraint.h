#pragma once

#include "PhysicsConstraintMotor.h"
#include "TwoPhysicsEntityConstraint.h"

namespace Edge
{
	class TwoPhysicsEntityMotorizedConstraint : public TwoPhysicsEntityConstraint
	{
	private:
		PhysicsConstraintMotorReference m_motor;

	protected:
		virtual bool validateMotorType(const PhysicsConstraintMotorReference& motor) const;

	public:
		TwoPhysicsEntityMotorizedConstraint(
			const PhysicsEntityReference& entity1,
			const PhysicsEntityReference& entity2,
			const PhysicsConstraintMotorReference& motor = nullptr
		);

		void setMotor(const PhysicsConstraintMotorReference& motor);
		PhysicsConstraintMotorReference getMotor() const;
	};
}
