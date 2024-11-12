#pragma once

#include "EdgeCommon/Math/Vector.h"

#include "EdgePhysics/Physics/Constraint/TwoPhysicsEntityConstraint.h"
#include "EdgePhysics/Physics/Constraint/Parts/PositionConstraintPart.h"

namespace Edge
{
	class KeepDistanceConstraint final : public TwoPhysicsEntityConstraint
	{
	private:
		PositionConstraintPart m_positionPart;

		FloatVector3 m_anchor1 = FloatVector3Zero;
		FloatVector3 m_anchor2 = FloatVector3Zero;

	public:
		KeepDistanceConstraint(const PhysicsEntityReference& entity1, const PhysicsEntityReference& entity2,
			const FloatVector3& anchor1, const FloatVector3& anchor2);

		virtual void preSolve(float deltaTime) override;
		virtual void solveVelocity() override;
		virtual void solvePosition() override;

		EDGE_PHYSICS_CONSTRAINT_TYPE(KEEP_DISTANCE)
	};
}
