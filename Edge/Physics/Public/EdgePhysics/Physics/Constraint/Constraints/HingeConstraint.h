#pragma once

#include "EdgeCommon/Math/Vector.h"

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

		FloatVector3 m_anchor1 = FloatVector3Zero;
		FloatVector3 m_anchor2 = FloatVector3Zero;
		FloatVector3 m_axis1 = FloatVector3Zero;
		FloatVector3 m_axis2 = FloatVector3Zero;

	public:
		HingeConstraint(const PhysicsEntityReference& entity1, const PhysicsEntityReference& entity2,
			const FloatVector3& anchor1, const FloatVector3& anchor2,
			const FloatVector3& axis1, const FloatVector3& axis2);

		virtual void preSolve(float deltaTime) override;
		virtual void warmUp() override;
		virtual void solveVelocity() override;
		virtual void solvePosition() override;

		EDGE_PHYSICS_CONSTRAINT_TYPE(HINDGE)
	};
}
