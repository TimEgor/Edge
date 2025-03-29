#include "KeepRotationConstraintPart.h"

void Edge::KeepRotationConstraintPart::deactivate()
{
	m_invEffectiveMass = ComputeMatrix3x3Zero;
	m_totalLambda = ComputeVector3Zero;
}

void Edge::KeepRotationConstraintPart::applyVelocity(const ComputeVector3& lambda) const
{
	if (lambda == ComputeVector3Zero)
	{
		return;
	}

	const PhysicsEntityMotionReference motion1 = m_entity1->getMotion();
	const PhysicsEntityMotionReference motion2 = m_entity2->getMotion();

	if (motion1)
	{
		const ComputeVector3 angularVelocityDelta = m_invIner1 * lambda;
		const ComputeVector3 newAngularVelocity = motion1->getAngularVelocity() - angularVelocityDelta;
		motion1->setAngularVelocity(newAngularVelocity);
	}

	if (motion2)
	{
		const ComputeVector3 angularVelocityDelta = m_invIner2 * lambda;
		const ComputeVector3 newAngularVelocity = motion2->getAngularVelocity() + angularVelocityDelta;
		motion2->setAngularVelocity(newAngularVelocity);
	}
}

void Edge::KeepRotationConstraintPart::applyPosition(const ComputeVector3& lambda) const
{
	if (lambda == FloatVector3Zero)
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
		const ComputeVector3 angularVelocityDelta = m_invIner1 * lambda;
		const ComputeValueType angularVelocityDeltaLength = angularVelocityDelta.getLength();
		if (angularVelocityDeltaLength > Math::Epsilon)
		{
			const ComputeQuaternion newRotation = (ComputeQuaternion(angularVelocityDelta, -angularVelocityDeltaLength) * transformAccessor1.getRotation()).normalize();
			transformAccessor1.setRotation(newRotation);
		}
	}

	if (motion2)
	{
		const ComputeVector3 angularVelocityDelta = m_invIner2 * lambda;
		const ComputeValueType angularVelocityDeltaLength = angularVelocityDelta.getLength();
		if (angularVelocityDeltaLength > Math::Epsilon)
		{
			const ComputeQuaternion newRotation = (ComputeQuaternion(angularVelocityDelta, angularVelocityDeltaLength) * transformAccessor2.getRotation()).normalize();
			transformAccessor2.setRotation(newRotation);
		}
	}
}

void Edge::KeepRotationConstraintPart::preSolve()
{
	const PhysicsEntityMotionReference motion1 = m_entity1->getMotion();
	const PhysicsEntityMotionReference motion2 = m_entity2->getMotion();

	if (!motion1 && !motion2)
	{
		deactivate();
		return;
	}

	ComputeMatrix3x3 effectiveMass = ComputeMatrix3x3Zero;

	if (motion1)
	{
		motion1->getWorldInverseInertiaTensor(m_invIner1);
		effectiveMass += m_invIner1;
	}

	if (motion2)
	{
		motion2->getWorldInverseInertiaTensor(m_invIner2);
		effectiveMass += m_invIner2;
	}

	m_invEffectiveMass = InvertComputeMatrix3x3(effectiveMass);
}

void Edge::KeepRotationConstraintPart::warmUp()
{
	applyVelocity(m_totalLambda);
}

void Edge::KeepRotationConstraintPart::solveVelocity()
{
	ComputeVector3 lambda = ComputeVector3Zero;

	{
		const PhysicsEntityMotionReference motion1 = m_entity1->getMotion();
		const PhysicsEntityMotionReference motion2 = m_entity2->getMotion();

		const ComputeVector3 velocity1 = motion1 ? motion1->getAngularVelocity() : FloatVector3Zero;
		const ComputeVector3 velocity2 = motion2 ? motion2->getAngularVelocity() : FloatVector3Zero;
		lambda = m_invEffectiveMass * (velocity1 - velocity2);

		m_totalLambda += lambda;
	}

	applyVelocity(lambda);
}

void Edge::KeepRotationConstraintPart::solvePosition(const ComputeQuaternion& invInitialDeltaOrientation)
{
	ComputeVector3 lambda = ComputeVector3Zero;

	{
		static constexpr ComputeValueType baumgarteCoeff = ComputeValueType(1.0);

		const ComputeQuaternion diffRotation = m_entity1->getTransform()->getRotation() * invInitialDeltaOrientation * ConjugateComputeQuaternion(m_entity2->getTransform()->getRotation());
		const ComputeVector3 error = ComputeValueType(2.0) * diffRotation.getXYZ();
		lambda = m_invEffectiveMass * (error * baumgarteCoeff);
	}

	applyPosition(lambda);
}

bool Edge::KeepRotationConstraintPart::isActive() const
{
	//return m_invEffectiveMass.getElement(2, 2) > Math::Epsilon;
	return true;
}
