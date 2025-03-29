#include "KeepPositionConstraintPart.h"

#include "EdgePhysics/Physics/Entity/PhysicsEntity.h"

void Edge::KeepPositionConstraintPart::deactivate()
{
	m_invEffectiveMass = ComputeMatrix3x3Zero;
	m_totalLambda = ComputeVector3Zero;
}

void Edge::KeepPositionConstraintPart::applyVelocity(const ComputeVector3& lambda) const
{
	if (lambda == ComputeVector3Zero)
	{
		return;
	}

	const PhysicsEntityMotionReference motion1 = m_entity1->getMotion();
	const PhysicsEntityMotionReference motion2 = m_entity2->getMotion();

	if (motion1)
	{
		const ComputeVector3 newLinVelocity = motion1->getLinearVelocity() - motion1->getInverseMass() * lambda;
		motion1->setLinearVelocity(newLinVelocity);

		ComputeMatrix3x3 invInertia;
		motion1->getWorldInverseInertiaTensor(invInertia);

		const ComputeVector3 angularVelocityDelta = invInertia * CrossComputeVector3(m_r1, lambda);
		const ComputeVector3 newAngularVelocity = motion1->getAngularVelocity() - angularVelocityDelta;
		motion1->setAngularVelocity(newAngularVelocity);
	}

	if (motion2)
	{
		const ComputeVector3 deltaVelocity = motion2->getInverseMass() * lambda;

		const ComputeVector3 newLinVelocity = motion2->getLinearVelocity() + deltaVelocity;
		motion2->setLinearVelocity(newLinVelocity);

		//const ComputeVector angularVelocityDelta = m_invInerR2 * lambda;

		ComputeMatrix3x3 invInertia;
		motion2->getWorldInverseInertiaTensor(invInertia);

		const ComputeVector3 angularVelocityDelta = invInertia * CrossComputeVector3(m_r2, lambda);
		const ComputeVector3 newAngularVelocity = motion2->getAngularVelocity() + angularVelocityDelta;
		motion2->setAngularVelocity(newAngularVelocity);
	}
}

void Edge::KeepPositionConstraintPart::applyPosition(const ComputeVector3& lambda) const
{
	if (lambda == ComputeVector3Zero)
	{
		return;
	}

	const PhysicsEntityTransformReference transform1 = m_entity1->getTransform();
	const PhysicsEntityTransformReference transform2 = m_entity2->getTransform();

	PhysicsEntityTransformNotificationFreeAccessor transformAccessor1(transform1);
	PhysicsEntityTransformNotificationFreeAccessor transformAccessor2(transform2);

	const PhysicsEntityMotionReference motion1 = m_entity1->getMotion();
	const PhysicsEntityMotionReference motion2 = m_entity2->getMotion();

	if (motion1)
	{
		const ComputeVector3 newPosition = transformAccessor1.getPosition() - motion1->getInverseMass() * lambda;
		transformAccessor1.setPosition(newPosition);

		ComputeMatrix3x3 invInertia;
		motion1->getWorldInverseInertiaTensor(invInertia);

		const ComputeVector3 rotationDelta = invInertia * CrossComputeVector3(m_r1, lambda);
		const ComputeValueType rotationDeltaLength = rotationDelta.getLength();
		if (rotationDeltaLength > Math::Epsilon)
		{
			const ComputeQuaternion newRotation = (ComputeQuaternion(rotationDelta, -rotationDeltaLength) * transformAccessor1.getRotation()).normalize();
			transformAccessor1.setRotation(newRotation);
		}
	}

	if (motion2)
	{
		const ComputeVector3 deltaPosition = motion2->getInverseMass() * lambda;

		const ComputeVector3 newPosition = transformAccessor2.getPosition() + deltaPosition;
		transformAccessor2.setPosition(newPosition);

		ComputeMatrix3x3 invInertia;
		motion2->getWorldInverseInertiaTensor(invInertia);

		const ComputeVector3 rotationDelta = invInertia * CrossComputeVector3(m_r2, lambda);
		const ComputeValueType rotationDeltaLength = rotationDelta.getLength();
		if (rotationDeltaLength > Math::Epsilon)
		{
			const ComputeQuaternion newRotation = (ComputeQuaternion(rotationDelta, rotationDeltaLength) * transformAccessor2.getRotation()).normalize();
			transformAccessor2.setRotation(newRotation);
		}
	}
}

void Edge::KeepPositionConstraintPart::preSolve(const ComputeVector3& anchor1, const ComputeVector3& anchor2)
{
	m_r1 = m_entity1->getTransform()->getRotation().rotate(anchor1);
	m_r2 = m_entity2->getTransform()->getRotation().rotate(anchor2);

	ComputeMatrix3x3 effectiveMass = ComputeMatrix3x3Zero;
	ComputeValueType invTotalMass = ComputeValueType(0.0);

	const PhysicsEntityMotionReference motion1 = m_entity1->getMotion();
	const PhysicsEntityMotionReference motion2 = m_entity2->getMotion();

	if (!motion1 && !motion2)
	{
		deactivate();
		return;
	}

	if (motion1)
	{
		invTotalMass += motion1->getInverseMass();

		ComputeMatrix3x3 invInertia;
		motion1->getWorldInverseInertiaTensor(invInertia);
		const ComputeMatrix3x3 r1x = CrossProductSkewSymmetricComputeMatrix3x3(m_r1);
		//(invInertia * r1x).saveToMatrix4x4(m_invInerR1);
		effectiveMass += r1x * invInertia * TransposeComputeMatrix3x3(r1x);
	}

	if (motion2)
	{
		invTotalMass += motion2->getInverseMass();

		ComputeMatrix3x3 invInertia;
		motion2->getWorldInverseInertiaTensor(invInertia);
		const ComputeMatrix3x3 r2x = CrossProductSkewSymmetricComputeMatrix3x3(m_r2);
		//(invInertia * r2x).saveToMatrix4x4(m_invInerR2);
		effectiveMass += r2x * invInertia * TransposeComputeMatrix3x3(r2x);
	}

	effectiveMass += ScaleComputeMatrix3x3(ComputeVector3(invTotalMass));

	m_invEffectiveMass = InvertComputeMatrix3x3(effectiveMass);
}

void Edge::KeepPositionConstraintPart::warmUp()
{
	applyVelocity(m_totalLambda);
}

void Edge::KeepPositionConstraintPart::solveVelocity()
{
	ComputeVector3 lambda = FloatVector3Zero;

	{
		const PhysicsEntityMotionReference motion1 = m_entity1->getMotion();
		const PhysicsEntityMotionReference motion2 = m_entity2->getMotion();

		const ComputeVector3 velocity1 = motion1 ? motion1->getLinearVelocity() + CrossComputeVector3(motion1->getAngularVelocity(), m_r1) : ComputeVector3Zero;
		const ComputeVector3 velocity2 = motion2 ? motion2->getLinearVelocity() + CrossComputeVector3(motion2->getAngularVelocity(), m_r2) : ComputeVector3Zero;
		const ComputeVector3 velocityDelta = velocity2 - velocity1;
		lambda = m_invEffectiveMass * -velocityDelta; //negate velocityDelta instead of m_invEffectiveMass

		m_totalLambda += lambda;
	}

	applyVelocity(lambda);
}

void Edge::KeepPositionConstraintPart::solvePosition()
{
	ComputeVector3 lambda = ComputeVector3Zero;

	{
		static constexpr ComputeValueType baumgarteCoeff = 1.0f;

		const ComputeVector3 error = (m_entity2->getTransform()->getPosition() + m_r2) - (m_entity1->getTransform()->getPosition() + m_r1);
		lambda = m_invEffectiveMass * (error * -baumgarteCoeff); //negate baumgarteCoeff instead of m_invEffectiveMass
	}

	applyPosition(lambda);
}

bool Edge::KeepPositionConstraintPart::isActive() const
{
	//return m_invEffectiveMass.getElement(3, 3) > Math::Epsilon;
	return true;
}
