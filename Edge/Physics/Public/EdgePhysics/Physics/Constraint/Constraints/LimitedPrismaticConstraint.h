#pragma once

#include "EdgePhysics/Physics/Constraint/Parts/AxisPositionLimitConstraintPart.h"

#include "PrismaticConstraint.h"

namespace Edge
{
	class LimitedPrismaticConstraint final : public PrismaticConstraint
	{
	private:
		AxisPositionLimitConstraintPart m_limitPart;

	protected:
		ComputeValueType m_minLimitValue = 0.0;
		ComputeValueType m_maxLimitValue = 0.0;

	public:
		LimitedPrismaticConstraint(
			const PhysicsEntityReference& entity1, const PhysicsEntityReference& entity2,
			const ComputeVector3& anchor1, const ComputeVector3& anchor2,
			const ComputeVector3& axis1, const ComputeVector3& axis2,
			ComputeValueType minLimit, ComputeValueType maxLimit,
			const ComputeQuaternion& deltaRotation = ComputeQuaternionIdentity
		);

		virtual void preSolve(float deltaTime) override;
		virtual void warmUp() override;
		virtual void solveVelocity() override;
		virtual void solvePosition() override;

		void setLimits(ComputeValueType min, ComputeValueType max);

		ComputeValueType getMinLimit() const { return m_minLimitValue; }
		ComputeValueType getMaxLimit() const { return m_maxLimitValue; }

		EDGE_RTTI_VIRTUAL(LimitedPrismaticConstraint, PrismaticConstraint)
	};

	EDGE_REFERENCE(LimitedPrismaticConstraint);

	LimitedPrismaticConstraintReference CreateLimitedPrismaticConstraintInWorldSpace(
		const PhysicsEntityReference& entity1, const PhysicsEntityReference& entity2,
		const ComputeVector3& anchor1, const ComputeVector3& anchor2,
		const ComputeVector3& axis1, const ComputeVector3& axis2,
		ComputeValueType minLimit, ComputeValueType maxLimit
	);

	LimitedPrismaticConstraintReference CreateLimitedPrismaticConstraintInWorldSpace(
		const PhysicsEntityReference& entity1, const PhysicsEntityReference& entity2,
		const ComputeVector3& anchor1, const ComputeVector3& anchor2,
		const ComputeVector3& axis1, const ComputeVector3& axis2,
		const Transform& transform1, const Transform& transform2,
		ComputeValueType minLimit, ComputeValueType maxLimit
	);

	LimitedPrismaticConstraintReference CreateLimitedPrismaticConstraintInWorldSpace(
		const PhysicsEntityReference& entity1, const PhysicsEntityReference& entity2,
		const ComputeVector3& anchor1, const ComputeVector3& anchor2,
		const ComputeVector3& axis1, const ComputeVector3& axis2,
		const ComputeVector3& dirX1, const ComputeVector3& dirX2,
		const ComputeVector3& dirY1, const ComputeVector3& dirY2,
		ComputeValueType minLimit, ComputeValueType maxLimit
	);
}