#include "AxisPositionLimitConstraintPart.h"

void Edge::AxisPositionLimitConstraintPart::deactivate()
{
	m_invEffectiveMass = 0.0;
	m_totalLambda = 0.0;
}

void Edge::AxisPositionLimitConstraintPart::applyVelocity(ComputeValueType lambda) const
{
	if (Math::IsApproxEqual(lambda, 0.0_ecv))
	{
		return;
	}

	const ComputeVector3 linearImpulse = lambda * m_a;

	const PhysicsEntityMotionReference motion1 = m_entity1->getMotion();
	const PhysicsEntityMotionReference motion2 = m_entity2->getMotion();

	if (motion1)
	{
		const ComputeVector3 deltaVelocity = motion1->getInverseMass() * linearImpulse;

		const ComputeVector3 newLinVelocity = motion1->getLinearVelocity() - deltaVelocity;
		motion1->setLinearVelocity(newLinVelocity);

		ComputeMatrix3x3 invInertia;
		motion1->getWorldInverseInertiaTensor(invInertia);

		const ComputeVector3 inv_r1_u_a = invInertia * m_r1_u_a;

		const ComputeVector3 angularVelocityDelta = inv_r1_u_a * lambda;
		const ComputeVector3 newAngularVelocity = motion1->getAngularVelocity() - angularVelocityDelta;
		motion1->setAngularVelocity(newAngularVelocity);
	}

	if (motion2)
	{
		const ComputeVector3 deltaVelocity = motion2->getInverseMass() * linearImpulse;

		const ComputeVector3 newLinVelocity = motion2->getLinearVelocity() + deltaVelocity;
		motion2->setLinearVelocity(newLinVelocity);

		ComputeMatrix3x3 invInertia;
		motion2->getWorldInverseInertiaTensor(invInertia);

		const ComputeVector3 inv_r2_a = invInertia * m_r2_a;

		const ComputeVector3 angularVelocityDelta = inv_r2_a * lambda;
		const ComputeVector3 newAngularVelocity = motion2->getAngularVelocity() + angularVelocityDelta;
		motion2->setAngularVelocity(newAngularVelocity);
	}
}

void Edge::AxisPositionLimitConstraintPart::applyPosition(ComputeValueType lambda) const
{
	if (Math::IsApproxEqual(lambda, 0.0_ecv))
	{
		return;
	}

	const ComputeVector3 linearImpulse = lambda * m_a;

	const PhysicsEntityTransformReference transform1 = m_entity1->getTransform();
	const PhysicsEntityTransformReference transform2 = m_entity2->getTransform();

	PhysicsEntityTransformNotificationFreeAccessor transformAccessor1(transform1);
	PhysicsEntityTransformNotificationFreeAccessor transformAccessor2(transform2);

	const PhysicsEntityMotionReference motion1 = m_entity1->getMotion();
	const PhysicsEntityMotionReference motion2 = m_entity2->getMotion();

	if (motion1)
	{
		const ComputeVector3 deltaPosition = motion1->getInverseMass() * linearImpulse;

		const ComputeVector3 newPosition = transformAccessor1.getPosition() - deltaPosition;
		transformAccessor1.setPosition(newPosition);

		ComputeMatrix3x3 invInertia;
		motion1->getWorldInverseInertiaTensor(invInertia);

		const ComputeVector3 inv_r1_u_a = invInertia * m_r1_u_a;

		const ComputeVector3 rotationDelta = inv_r1_u_a * lambda;
		const ComputeValueType rotationDeltaLength = rotationDelta.getLength();
		if (rotationDeltaLength > Math::Epsilon)
		{
			const ComputeQuaternion newRotation = (ComputeQuaternion(rotationDelta, -rotationDeltaLength) * transformAccessor1.getRotation()).normalize();
			transformAccessor1.setRotation(newRotation);
		}
	}

	if (motion2)
	{
		const ComputeVector3 deltaPosition = motion2->getInverseMass() * linearImpulse;

		const ComputeVector3 newPosition = transformAccessor2.getPosition() + deltaPosition;
		transformAccessor2.setPosition(newPosition);

		ComputeMatrix3x3 invInertia;
		motion2->getWorldInverseInertiaTensor(invInertia);

		const ComputeVector3 inv_r2_a = invInertia * m_r2_a;

		const ComputeVector3 rotationDelta = inv_r2_a * lambda;
		const ComputeValueType rotationDeltaLength = rotationDelta.getLength();
		if (rotationDeltaLength > Math::Epsilon)
		{
			const ComputeQuaternion newRotation = (ComputeQuaternion(rotationDelta, rotationDeltaLength) * transformAccessor2.getRotation()).normalize();
			transformAccessor2.setRotation(newRotation);
		}
	}
}

void Edge::AxisPositionLimitConstraintPart::solveLimitPosition(ComputeValueType delta)
{
	ComputeValueType lambda = 0.0;

	{
		static constexpr float baumgarteCoeff = 1.0f;

		lambda = -m_invEffectiveMass * delta * baumgarteCoeff;
	}

	applyPosition(lambda);
}

void Edge::AxisPositionLimitConstraintPart::preSolve(
	const ComputeVector3& anchor1,
	const ComputeVector3& anchor2,
	const ComputeVector3& axis1,
	const ComputeVector3& axis2,
	ComputeValueType deltaOffset,
	ComputeValueType minLimit,
	ComputeValueType maxLimit
)
{
	m_minLambdaLimit = 0.0;
	m_maxLambdaLimit = 0.0;

	if ((deltaOffset - minLimit) <= 0.0)
	{
		m_minLambdaLimit = -Math::Max;
	}
	if ((maxLimit - deltaOffset) <= 0.0)
	{
		m_maxLambdaLimit = Math::Max;
	}

	const PhysicsEntityMotionReference motion1 = m_entity1->getMotion();
	const PhysicsEntityMotionReference motion2 = m_entity2->getMotion();

	{
		const PhysicsEntityTransform& transform1 = m_entity1->getTransform().getObjectRef();
		const PhysicsEntityTransform& transform2 = m_entity2->getTransform().getObjectRef();

		const ComputeQuaternion rotation1 = transform1.getRotation();
		const ComputeQuaternion rotation2 = transform2.getRotation();

		const ComputeVector3 worldAnchor1 = rotation1.rotate(anchor1);
		const ComputeVector3 worldAnchor2 = rotation2.rotate(anchor2);

		m_a = rotation1.rotate(axis1);

		const ComputeVector3 position1 = motion1 ? motion1->getMassCenter() : transform1.getPosition();
		const ComputeVector3 position2 = motion2 ? motion2->getMassCenter() : transform2.getPosition();

		const ComputeVector3 u = (position2 + worldAnchor2) - (position1 + worldAnchor1);

		const ComputeVector3 r1_u = worldAnchor1 + u;

		m_r1_u_a = CrossComputeVector3(r1_u, m_a);
		m_r2_a = CrossComputeVector3(worldAnchor2, m_a);
	}

	if (!motion1 && !motion2)
	{
		deactivate();
		return;
	}

	ComputeValueType effectiveMass = 0.0;

	if (motion1)
	{
		effectiveMass += motion1->getInverseMass();

		ComputeMatrix3x3 inertia;
		motion1->getWorldInverseInertiaTensor(inertia);
		effectiveMass += m_r1_u_a.dot(inertia * m_r1_u_a);
	}

	if (motion2)
	{
		effectiveMass += motion2->getInverseMass();

		ComputeMatrix3x3 inertia;
		motion2->getWorldInverseInertiaTensor(inertia);
		effectiveMass += m_r2_a.dot(inertia * m_r2_a);
	}

	m_invEffectiveMass = 1.0_ecv / effectiveMass;
}

void Edge::AxisPositionLimitConstraintPart::warmUp()
{
	applyVelocity(m_totalLambda);
}

void Edge::AxisPositionLimitConstraintPart::solveVelocity()
{
	ComputeValueType lambda = 0.0;

	{
		const PhysicsEntityMotionReference motion1 = m_entity1->getMotion();
		const PhysicsEntityMotionReference motion2 = m_entity2->getMotion();

		const ComputeVector3 linearVelocity1 = motion1 ? motion1->getLinearVelocity() : ComputeVector3Zero;
		const ComputeVector3 linearVelocity2 = motion2 ? motion2->getLinearVelocity() : ComputeVector3Zero;

		const ComputeVector3 angularVelocity1 = motion1 ? motion1->getAngularVelocity() : ComputeVector3Zero;
		const ComputeVector3 angularVelocity2 = motion2 ? motion2->getAngularVelocity() : ComputeVector3Zero;

		const ComputeValueType jv =
			(linearVelocity2 - linearVelocity1).dot(m_a) +
			angularVelocity1.dot(m_r1_u_a) -
			angularVelocity2.dot(m_r2_a);

		lambda = -m_invEffectiveMass * jv;

		const ComputeValueType totalLambda = Math::Clamp(m_totalLambda + lambda, m_minLambdaLimit, m_maxLambdaLimit);
		lambda = totalLambda - m_totalLambda;

		m_totalLambda += lambda;
	}

	applyVelocity(lambda);
}

void Edge::AxisPositionLimitConstraintPart::solvePosition(ComputeValueType deltaOffset, ComputeValueType minLimit, ComputeValueType maxLimit)
{
	const ComputeValueType minDelta = deltaOffset - minLimit;
	if (minDelta < 0.0)
	{
		solveLimitPosition(minDelta);
	}

	const ComputeValueType maxDelta = maxLimit - deltaOffset;
	if (maxDelta < 0.0)
	{
		solveLimitPosition(-maxDelta);
	}
}

bool Edge::AxisPositionLimitConstraintPart::isActive() const
{
	return !Math::IsApproxEqual(m_invEffectiveMass, 0.0_ecv);
}
