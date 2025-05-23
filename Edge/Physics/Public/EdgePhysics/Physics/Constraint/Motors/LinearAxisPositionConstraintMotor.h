#pragma once

#include "LinearAxisBiasConstraintMotor.h"

namespace Edge
{
	class LinearAxisPositionConstraintMotor : public LinearAxisBiasConstraintMotor
	{
	public:
		LinearAxisPositionConstraintMotor() = default;

		void setTargetOffset(ComputeValueType offset)
		{
			setBias(offset);
		}

		ComputeValueType getTargetOffset() const
		{
			return getTargetOffset();
		}

		EDGE_RTTI_VIRTUAL(LinearAxisPositionConstraintMotor, LinearAxisConstraintMotor)
	};

	EDGE_REFERENCE(LinearAxisPositionConstraintMotor)
}
