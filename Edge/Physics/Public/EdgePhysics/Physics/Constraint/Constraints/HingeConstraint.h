#pragma once

#include "EdgePhysics/Physics/Constraint/TwoPhysicsEntityConstraint.h"
#include "EdgePhysics/Physics/Constraint/Parts/AxisRotationConstraintPart.h"
#include "EdgePhysics/Physics/Constraint/Parts/KeepPositionConstraintPart.h"

namespace Edge
{
	class HingeConstraint final : public TwoPhysicsEntityConstraint
	{
	private:
		KeepPositionConstraintPart m_positionPart;
		AxisRotationConstraintPart m_axisRotationPart;

		ComputeVector3 m_anchor1 = ComputeVector3Zero;
		ComputeVector3 m_anchor2 = ComputeVector3Zero;
		ComputeVector3 m_axis1 = ComputeVector3Zero;
		ComputeVector3 m_axis2 = ComputeVector3Zero;

	public:
		HingeConstraint(
			const PhysicsEntityReference& entity1, const PhysicsEntityReference& entity2,
			const ComputeVector3& anchor1, const ComputeVector3& anchor2,
			const ComputeVector3& axis1, const ComputeVector3& axis2
		);

		virtual void preSolve(float deltaTime) override;
		virtual void warmUp() override;
		virtual void solveVelocity() override;
		virtual void solvePosition() override;

		EDGE_PHYSICS_CONSTRAINT_TYPE(HINDGE)
	};
}
