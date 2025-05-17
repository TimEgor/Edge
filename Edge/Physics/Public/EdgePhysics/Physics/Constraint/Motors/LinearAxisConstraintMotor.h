#pragma once

#include "EdgeCommon/Math/ComputeVector3.h"

#include "EdgePhysics/Physics/Constraint/PhysicsConstraintMotor.h"

namespace Edge
{
	class LinearAxisConstraintMotor : public PhysicsConstraintMotor
	{
	public:
		LinearAxisConstraintMotor() = default;

		virtual void preSolve(
			ComputeValueType deltaTime,
			const ComputeVector3& anchor1,
			const ComputeVector3& anchor2,
			const ComputeVector3& axis1,
			const ComputeVector3& axis2
		) = 0;
		virtual void warmUp() = 0;
		virtual void solveVelocity() = 0;
		virtual void solvePosition() = 0;

		virtual bool isActive() const = 0;

		EDGE_RTTI_VIRTUAL(LinearAxisConstraintMotor, PhysicsConstraintMotor)
	};

	EDGE_REFERENCE(LinearAxisConstraintMotor)
}
