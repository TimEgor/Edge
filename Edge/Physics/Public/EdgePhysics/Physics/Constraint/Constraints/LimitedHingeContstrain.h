#pragma once

#include "EdgePhysics/Physics/Constraint/Parts/AxisRotationLimitConstaintPart.h"

#include "HingeConstraint.h"

namespace Edge
{
	class LimitedHingeConstraint final : public HingeConstraint
	{
	private:
		AxisRotationLimitConstraintPart m_limitPart;

	protected:
		ComputeValueType m_minLimitValue = 0.0;
		ComputeValueType m_maxLimitValue = 0.0;

		void setMinLimit(ComputeValueType min);
		void setMaxLimit(ComputeValueType max);

	public:
		LimitedHingeConstraint(
			const PhysicsEntityReference& entity1, const PhysicsEntityReference& entity2,
			const ComputeVector3& anchor1, const ComputeVector3& anchor2,
			const ComputeVector3& axis1, const ComputeVector3& axis2,
			ComputeValueType minLimit, ComputeValueType maxLimit
		);

		virtual void preSolve(float deltaTime) override;
		virtual void warmUp() override;
		virtual void solveVelocity() override;
		virtual void solvePosition() override;

		void setLimits(ComputeValueType min, ComputeValueType max);

		ComputeValueType getMinLimit() const { return m_minLimitValue; }
		ComputeValueType getMaxLimit() const { return m_maxLimitValue; }

		EDGE_PHYSICS_CONSTRAINT_TYPE(LIMITED_HINDGE)
	};

	EDGE_REFERENCE(LimitedHingeConstraint);

	HingeConstraintReference CreateLimitedHingeConstraintInWorldSpace(
		const PhysicsEntityReference& entity1, const PhysicsEntityReference& entity2,
		const ComputeVector3& anchor1, const ComputeVector3& anchor2,
		const ComputeVector3& axis1, const ComputeVector3& axis2,
		ComputeValueType minLimit, ComputeValueType maxLimit
	);
}
