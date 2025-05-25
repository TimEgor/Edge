#pragma once

#include "AngularAxisBiasConstraintMotor.h"

namespace Edge
{
	class AngularAxisVelocityConstraintMotor : public AngularAxisBiasConstraintMotor
	{
	public:
		AngularAxisVelocityConstraintMotor() = default;

		virtual void preSolve(
			ComputeValueType offset,
			const ComputeVector3& anchor1,
			const ComputeVector3& anchor2,
			const ComputeVector3& axis1,
			const ComputeVector3& axis2
		) override
		{
			AngularAxisBiasConstraintMotor::preSolve(
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

		EDGE_RTTI_VIRTUAL(AngularAxisVelocityConstraintMotor, AngularAxisBiasConstraintMotor)
	};

	EDGE_REFERENCE(AngularAxisVelocityConstraintMotor)
}
