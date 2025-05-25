#pragma once

#include "AngularAxisConstraintMotor.h"

namespace Edge
{
	class AngularAxisBiasConstraintMotor : public AngularAxisConstraintMotor
	{
	private:
		ComputeVector3 m_a = ComputeVector3Zero;

		ComputeValueType m_invEffectiveMass = 0.0;

		ComputeValueType m_currentBias = 0.0;
		ComputeValueType m_totalLambda = 0.0;

		ComputeValueType m_bias = 0.0;
		ComputeValueType m_forceLimit = Math::Max;

		void deactivate();

		void applyVelocity(ComputeValueType lambda) const;

	public:
		AngularAxisBiasConstraintMotor() = default;

		virtual void preSolve(
			ComputeValueType angle,
			const ComputeVector3& anchor1,
			const ComputeVector3& anchor2,
			const ComputeVector3& axis1,
			const ComputeVector3& axis2
		) override;
		virtual void warmUp() override;
		virtual void solveVelocity(ComputeValueType deltaTime) override;
		virtual void solvePosition() override {}

		virtual bool isActive() const override;

		void setBias(ComputeValueType bias)
		{
			m_bias = bias;
		}

		ComputeValueType getBias() const
		{
			return m_bias;
		}

		EDGE_RTTI_VIRTUAL(AngularAxisBiasConstraintMotor, AngularAxisConstraintMotor)
	};

	EDGE_REFERENCE(AngularAxisBiasConstraintMotor)
}
