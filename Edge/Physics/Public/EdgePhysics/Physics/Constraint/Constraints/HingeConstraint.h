#pragma once

#include "EdgePhysics/Physics/Constraint/TwoPhysicsEntityConstraint.h"
#include "EdgePhysics/Physics/Constraint/Motors/AngularAxisConstraintMotor.h"
#include "EdgePhysics/Physics/Constraint/Parts/AxisRotationConstraintPart.h"
#include "EdgePhysics/Physics/Constraint/Parts/KeepPositionConstraintPart.h"

namespace Edge
{
	class HingeConstraint : public TwoPhysicsEntityConstraint
	{
	private:
		AngularAxisConstraintMotorReference m_motor;

		KeepPositionConstraintPart m_positionPart;
		AxisRotationConstraintPart m_rotationPart;

	protected:
		ComputeQuaternion m_initialRotationDelta = ComputeQuaternionIdentity;

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

		virtual void preSolve(ComputeValueType deltaTime) override;
		virtual void warmUp() override;
		virtual void solveVelocity(ComputeValueType deltaTime) override;
		virtual void solvePosition(ComputeValueType deltaTime) override;

		void setMotor(const AngularAxisConstraintMotorReference& motor);
		AngularAxisConstraintMotorReference getMotor() const;

		ComputeValueType getCurrentAngle() const;

		EDGE_RTTI_VIRTUAL(HingeConstraint, TwoPhysicsEntityConstraint)
	};

	EDGE_REFERENCE(HingeConstraint);

	HingeConstraintReference CreateHingeConstraintInWorldSpace(
		const PhysicsEntityReference& entity1, const PhysicsEntityReference& entity2,
		const ComputeVector3& anchor1, const ComputeVector3& anchor2,
		const ComputeVector3& axis1, const ComputeVector3& axis2
	);
}