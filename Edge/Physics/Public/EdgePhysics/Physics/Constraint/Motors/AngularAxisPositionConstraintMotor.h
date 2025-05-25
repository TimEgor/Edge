#pragma once

#include "AngularAxisBiasConstraintMotor.h"

namespace Edge
{
	class AngularAxisPositionConstraintMotor : public AngularAxisBiasConstraintMotor
	{
	public:
		AngularAxisPositionConstraintMotor() = default;

		void setTargetAngle(ComputeValueType angle)
		{
			setBias(angle);
		}

		ComputeValueType getTargetAngle() const
		{
			return getBias();
		}

		EDGE_RTTI_VIRTUAL(AngularAxisPositionConstraintMotor, AngularAxisBiasConstraintMotor)
	};

	EDGE_REFERENCE(AngularAxisPositionConstraintMotor)
}
