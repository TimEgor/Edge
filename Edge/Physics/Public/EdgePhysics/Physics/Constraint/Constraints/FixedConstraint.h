#pragma once

#include "EdgePhysics/Physics/Constraint/TwoPhysicsEntityConstraint.h"
#include "EdgePhysics/Physics/Constraint/Parts/KeepPositionConstraintPart.h"
#include "EdgePhysics/Physics/Constraint/Parts/KeepRotationConstraintPart.h"

namespace Edge
{
	class FixedConstraint final : public TwoPhysicsEntityConstraint
	{
	private:
		KeepPositionConstraintPart m_positionPart;
		KeepRotationConstraintPart m_rotationPart;

		ComputeQuaternion m_initialDeltaRotation = ComputeQuaternionIdentity;
		ComputeVector3 m_anchor1 = ComputeVector3Zero;
		ComputeVector3 m_anchor2 = ComputeVector3Zero;

	public:
		FixedConstraint(
			const PhysicsEntityReference& entity1, const PhysicsEntityReference& entity2,
			const ComputeVector3& anchor1, const ComputeVector3& anchor2,
			ComputeQuaternion deltaRotation = ComputeQuaternionIdentity
		);

		virtual void preSolve(float deltaTime) override;
		virtual void warmUp() override;
		virtual void solveVelocity() override;
		virtual void solvePosition() override;

		EDGE_PHYSICS_CONSTRAINT_TYPE(FIXED)
	};
}
