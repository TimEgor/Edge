#pragma once

#include "EdgePhysics/Physics/Constraint/TwoPhysicsEntityConstraint.h"
#include "EdgePhysics/Physics/Constraint/Parts/AxisPositionConstraintPart.h"
#include "EdgePhysics/Physics/Constraint/Parts/KeepRotationConstraintPart.h"

namespace Edge
{
	class PrismaticConstraint final : public TwoPhysicsEntityConstraint
	{
	private:
		AxisPositionConstraintPart m_positionPart;
		KeepRotationConstraintPart m_rotationPart;

		ComputeQuaternion m_initialDeltaRotation = ComputeQuaternionIdentity;
		ComputeVector3 m_anchor1 = ComputeVector3Zero;
		ComputeVector3 m_anchor2 = ComputeVector3Zero;
		ComputeVector3 m_axis1 = ComputeVector3Zero;
		ComputeVector3 m_axis2 = ComputeVector3Zero;

	public:
		PrismaticConstraint(
			const PhysicsEntityReference& entity1, const PhysicsEntityReference& entity2,
			const ComputeVector3& anchor1, const ComputeVector3& anchor2,
			const ComputeVector3& axis1, const ComputeVector3& axis2,
			const ComputeQuaternion& deltaRotation = ComputeQuaternionIdentity
		);

		virtual void preSolve(float deltaTime) override;
		virtual void warmUp() override;
		virtual void solveVelocity() override;
		virtual void solvePosition() override;

		EDGE_PHYSICS_CONSTRAINT_TYPE(PRISMATIC)
	};

	EDGE_REFERENCE(PrismaticConstraint);

	PrismaticConstraintReference CreatePrismaticConstraintInWorldSpace(
		const PhysicsEntityReference& entity1, const PhysicsEntityReference& entity2,
		const ComputeVector3& anchor1, const ComputeVector3& anchor2,
		const ComputeVector3& axis1, const ComputeVector3& axis2
	);

	PrismaticConstraintReference CreatePrismaticConstraintInWorldSpace(
		const PhysicsEntityReference& entity1, const PhysicsEntityReference& entity2,
		const ComputeVector3& anchor1, const ComputeVector3& anchor2,
		const ComputeVector3& axis1, const ComputeVector3& axis2,
		const Transform& transform1, const Transform& transform2
	);

	PrismaticConstraintReference CreatePrismaticConstraintInWorldSpace(
		const PhysicsEntityReference& entity1, const PhysicsEntityReference& entity2,
		const ComputeVector3& anchor1, const ComputeVector3& anchor2,
		const ComputeVector3& axis1, const ComputeVector3& axis2,
		const ComputeVector3& dirX1, const ComputeVector3& dirX2,
		const ComputeVector3& dirY1, const ComputeVector3& dirY2
	);
}
