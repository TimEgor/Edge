#pragma once

#include "LinearAxisBiasConstraintMotor.h"

namespace Edge
{
	class LinearAxisVelocityConstraintMotor : public LinearAxisBiasConstraintMotor
	{
	public:
		LinearAxisVelocityConstraintMotor() = default;

		virtual void preSolve(
			ComputeValueType offset,
			const ComputeVector3& anchor1,
			const ComputeVector3& anchor2,
			const ComputeVector3& axis1,
			const ComputeVector3& axis2
		) override
		{
			LinearAxisBiasConstraintMotor::preSolve(
				0.0,
				anchor1,
				anchor2,
				axis1,
				axis2
			);
		}

		void setTargetVelocity(ComputeValueType velocity)
		{
			setBias(velocity);
		}

		ComputeValueType getTargetVelocity() const
		{
			return getBias();
		}

		EDGE_RTTI_VIRTUAL(LinearAxisVelocityConstraintMotor, LinearAxisBiasConstraintMotor)
	};

	EDGE_REFERENCE(LinearAxisVelocityConstraintMotor)
}
