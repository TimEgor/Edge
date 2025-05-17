#pragma once

#include "LinearAxisConstraintMotor.h"

namespace Edge
{
	class LinearAxisVelocityConstraintMotor : public LinearAxisConstraintMotor
	{
	private:
		ComputeVector3 m_a = ComputeVector3Zero;

		ComputeValueType m_invEffectiveMass = 0.0;
		ComputeValueType m_impulseLimit = 0.0;

		ComputeValueType m_totalLambda = 0.0;

		ComputeValueType m_targetVelocity = 0.0;
		ComputeValueType m_forceLimit = Math::Max;

		void deactivate();

		void applyVelocity(ComputeValueType lambda) const;

	public:
		LinearAxisVelocityConstraintMotor() = default;

		virtual void preSolve(
			ComputeValueType deltaTime,
			const ComputeVector3& anchor1,
			const ComputeVector3& anchor2,
			const ComputeVector3& axis1,
			const ComputeVector3& axis2
		) override;
		virtual void warmUp() override;
		virtual void solveVelocity() override;
		virtual void solvePosition() override {}

		virtual bool isActive() const override;

		void setTargetVelocity(ComputeValueType velocity)
		{
			m_targetVelocity = velocity;
		}

		ComputeValueType getTargetVelocity() const
		{
			return m_targetVelocity;
		}

		EDGE_RTTI_VIRTUAL(LinearAxisVelocityConstraintMotor, LinearAxisConstraintMotor)
	};

	EDGE_REFERENCE(LinearAxisVelocityConstraintMotor)
}
