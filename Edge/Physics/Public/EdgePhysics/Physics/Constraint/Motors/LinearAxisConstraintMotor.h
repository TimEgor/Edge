#pragma once

#include "EdgeCommon/Math/ComputeVector3.h"

#include "EdgePhysics/Physics/Constraint/PhysicsConstraintMotor.h"

namespace Edge
{
	class LinearAxisConstraintMotor : public PhysicsConstraintMotor
	{
	private:
		ComputeValueType m_currentValue = 0.0;

	public:
		LinearAxisConstraintMotor() = default;

		void preSolve(const ComputeVector3& anchor1, const ComputeVector3& anchor2, const ComputeVector3& axis1, const ComputeVector3& axis2);
		void warmUp();
		void solveVelocity();
		void solvePosition();

		bool isActive() const;
	};

	EDGE_REFERENCE(LinearAxisConstraintMotor)
}

EDGE_RTTI(Edge::LinearAxisConstraintMotor, Edge::PhysicsConstraintMotor)