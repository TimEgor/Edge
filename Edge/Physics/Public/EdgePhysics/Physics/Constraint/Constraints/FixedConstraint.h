#pragma once

#include "EdgeCommon/Math/Vector.h"

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

		FloatQuaternion m_initialDeltaRotation = FloatQuaternionIdentity;
		FloatVector3 m_anchor1 = FloatVector3Zero;
		FloatVector3 m_anchor2 = FloatVector3Zero;

	public:
		FixedConstraint(const PhysicsEntityReference& entity1, const PhysicsEntityReference& entity2,
			const FloatVector3& anchor1, const FloatVector3& anchor2, FloatQuaternion deltaRotation = FloatQuaternionIdentity);

		virtual void preSolve(float deltaTime) override;
		virtual void warmUp() override;
		virtual void solveVelocity() override;
		virtual void solvePosition() override;

		EDGE_PHYSICS_CONSTRAINT_TYPE(FIXED)
	};
}
