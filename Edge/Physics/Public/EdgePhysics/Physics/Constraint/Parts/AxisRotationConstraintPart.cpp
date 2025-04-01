#include "AxisRotationConstraintPart.h"

void Edge::AxisRotationConstraintPart::deactivate()
{
	m_invEffectiveMass = ComputeMatrix2x2Zero;
	m_totalLambda = ComputeVector3Zero;
}

void Edge::AxisRotationConstraintPart::applyVelocity(const ComputeVector3& lambda) const
{
	if (lambda == ComputeVector3Zero)
	{
		return;
	}

	const PhysicsEntityMotionReference motion1 = m_entity1->getMotion();
	const PhysicsEntityMotionReference motion2 = m_entity2->getMotion();

	if (motion1)
	{
		ComputeMatrix3x3 inertia;
		motion1->getWorldInverseInertiaTensor(inertia);

		const ComputeVector3 angularVelocityDelta = inertia * lambda;
		const ComputeVector3 newAngularVelocity = motion1->getAngularVelocity() - angularVelocityDelta;
		motion1->setAngularVelocity(newAngularVelocity);
	}

	if (motion2)
	{
		ComputeMatrix3x3 inertia;
		motion2->getWorldInverseInertiaTensor(inertia);

		const ComputeVector3 angularVelocityDelta = inertia * lambda;
		const ComputeVector3 newAngularVelocity = motion2->getAngularVelocity() + angularVelocityDelta;
		motion2->setAngularVelocity(newAngularVelocity);
	}
}

void Edge::AxisRotationConstraintPart::applyPosition(const ComputeVector3& lambda) const
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
		ComputeMatrix3x3 inertia;
		motion1->getWorldInverseInertiaTensor(inertia);

		const ComputeVector3 angularVelocityDelta = inertia * lambda;
		const ComputeValueType angularVelocityDeltaLength = angularVelocityDelta.getLength();
		if (angularVelocityDeltaLength > Math::Epsilon)
		{
			const ComputeQuaternion newRotation = (ComputeQuaternion(angularVelocityDelta, -angularVelocityDeltaLength) * transformAccessor1.getRotation()).normalize();
			transformAccessor1.setRotation(newRotation);
		}
	}

	if (motion2)
	{
		ComputeMatrix3x3 inertia;
		motion2->getWorldInverseInertiaTensor(inertia);

		const ComputeVector3 angularVelocityDelta = inertia * lambda;
		const ComputeValueType angularVelocityDeltaLength = angularVelocityDelta.getLength();
		if (angularVelocityDeltaLength > Math::Epsilon)
		{
			const ComputeQuaternion newRotation = (ComputeQuaternion(angularVelocityDelta, angularVelocityDeltaLength) * transformAccessor2.getRotation()).normalize();
			transformAccessor2.setRotation(newRotation);
		}
	}
}

void Edge::AxisRotationConstraintPart::preSolve(const ComputeVector3& axis1, const ComputeVector3& axis2)
{
	const ComputeVector3 worldAxis1 = m_entity1->getTransform()->getRotation().rotate(axis1);
	const ComputeVector3 worldAxis2 = m_entity2->getTransform()->getRotation().rotate(axis2);

	m_axis1 = worldAxis1;

	m_axisOrtho1 = worldAxis2.getOrthogonal();
	m_axisOrtho2 = CrossComputeVector3(worldAxis2, m_axisOrtho1);

	const PhysicsEntityMotionReference motion1 = m_entity1->getMotion();
	const PhysicsEntityMotionReference motion2 = m_entity2->getMotion();

	if (!motion1 && !motion2)
	{
		deactivate();
		return;
	}

	ComputeMatrix3x3 totalInvInertia = ComputeMatrix3x3Zero;

	if (motion1)
	{
		ComputeMatrix3x3 inertia;
		motion1->getWorldInverseInertiaTensor(inertia);
		totalInvInertia += inertia;
	}

	if (motion2)
	{
		ComputeMatrix3x3 inertia;
		motion2->getWorldInverseInertiaTensor(inertia);
		totalInvInertia += inertia;
	}

	const ComputeVector3 a1b2 = CrossComputeVector3(m_axisOrtho1, worldAxis1);
	const ComputeVector3 a1c2 = CrossComputeVector3(m_axisOrtho2, worldAxis1);

	const ComputeMatrix2x2 effectiveMass(
		DotComputeVector3(a1b2, totalInvInertia * a1b2), DotComputeVector3(a1c2, totalInvInertia * a1b2),
		DotComputeVector3(a1b2, totalInvInertia * a1c2), DotComputeVector3(a1c2, totalInvInertia * a1c2)
	);

	m_invEffectiveMass = InvertComputeMatrix2x2(effectiveMass);
}

void Edge::AxisRotationConstraintPart::warmUp()
{
	applyVelocity(m_totalLambda);
}

void Edge::AxisRotationConstraintPart::solveVelocity()
{
	ComputeVector3 lambda = FloatVector3Zero;

	{
		const PhysicsEntityMotionReference motion1 = m_entity1->getMotion();
		const PhysicsEntityMotionReference motion2 = m_entity2->getMotion();

		const ComputeVector3 velocity1 = motion1 ? motion1->getAngularVelocity() : ComputeVector3Zero;
		const ComputeVector3 velocity2 = motion2 ? motion2->getAngularVelocity() : ComputeVector3Zero;

		const ComputeVector3 angularVelocityDelta = velocity2 - velocity1;

		const ComputeVector3 a1b2 = CrossComputeVector3(m_axisOrtho1, m_axis1);
		const ComputeVector3 a1c2 = CrossComputeVector3(m_axisOrtho2, m_axis1);

		const ComputeVector2 jv(
			DotComputeVector3(a1b2, angularVelocityDelta),
			DotComputeVector3(a1c2, angularVelocityDelta)
		);

		ComputeVector2 computeLambda = m_invEffectiveMass * -jv; //negate jv instead of m_invEffectiveMass
		lambda = a1b2 * computeLambda.getX() + a1c2 * computeLambda.getY();

		m_totalLambda += lambda;
	}

	applyVelocity(lambda);
}

void Edge::AxisRotationConstraintPart::solvePosition()
{
	ComputeVector3 lambda = FloatVector3Zero;

	{
		static constexpr float baumgarteCoeff = 1.0f;

		const ComputeVector3 a1b2 = CrossComputeVector3(m_axisOrtho1, m_axis1);
		const ComputeVector3 a1c2 = CrossComputeVector3(m_axisOrtho2, m_axis1);

		const ComputeVector2 jv(
			DotComputeVector3(m_axis1, m_axisOrtho1),
			DotComputeVector3(m_axis1, m_axisOrtho2)
		);

		const ComputeVector2 computeLambda = m_invEffectiveMass * (jv * -baumgarteCoeff); //negate baumgarteCoeff instead of m_invEffectiveMass
		lambda = a1b2 * computeLambda.getX() + a1c2 * computeLambda.getY();
	}

	applyPosition(lambda);
}

bool Edge::AxisRotationConstraintPart::isActive() const
{
	//return m_invEffectiveMass.getElement(1, 1) > Math::Epsilon;
	return true;
}
