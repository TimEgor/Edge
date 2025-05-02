#include "AxisRotationLimitConstaintPart.h"

void Edge::AxisRotationLimitConstraintPart::deactivate()
{
	m_invEffectiveMass = 0.0;
	m_totalLambda = 0.0;
}

void Edge::AxisRotationLimitConstraintPart::applyVelocity(const ComputeVector3& lambda) const
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

void Edge::AxisRotationLimitConstraintPart::applyPosition(const ComputeVector3& lambda) const
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

void Edge::AxisRotationLimitConstraintPart::solveLimitPosition(ComputeValueType delta)
{
	ComputeVector3 lambda = FloatVector3Zero;

	{
		static constexpr float baumgarteCoeff = 1.0f;

		const ComputeValueType computeLambdaValue = -m_invEffectiveMass * delta * baumgarteCoeff;

		lambda = computeLambdaValue * m_axis1;
	}

	applyPosition(lambda);
}

void Edge::AxisRotationLimitConstraintPart::preSolve(const ComputeVector3& axis1, ComputeValueType deltaAngle, ComputeValueType minLimit, ComputeValueType maxLimit)
{
	const ComputeVector3 worldAxis1 = m_entity1->getTransform()->getRotation().rotate(axis1);
	m_axis1 = worldAxis1;

	m_minLambdaLimit = 0.0;
	m_maxLambdaLimit = 0.0;

	if ((deltaAngle - minLimit) <= 0.0)
	{
		m_minLambdaLimit = -Math::Max;
	}
	if ((maxLimit - deltaAngle) <= 0.0)
	{
		m_maxLambdaLimit = Math::Max;
	}

	const PhysicsEntityMotionReference motion1 = m_entity1->getMotion();
	const PhysicsEntityMotionReference motion2 = m_entity2->getMotion();

	if (!motion1 && !motion2)
	{
		deactivate();
		return;
	}

	ComputeValueType effectiveMass = 0.0;

	if (motion1)
	{
		ComputeMatrix3x3 inertia;
		motion1->getWorldInverseInertiaTensor(inertia);
		effectiveMass += m_axis1.dot(inertia * m_axis1);
	}

	if (motion2)
	{
		ComputeMatrix3x3 inertia;
		motion2->getWorldInverseInertiaTensor(inertia);
		effectiveMass += m_axis1.dot(inertia * m_axis1);
	}

	m_invEffectiveMass = 1.0_ecv / effectiveMass;
}

void Edge::AxisRotationLimitConstraintPart::warmUp()
{
	applyVelocity(m_totalLambda * m_axis1);
}

void Edge::AxisRotationLimitConstraintPart::solveVelocity()
{
	ComputeVector3 lambda = FloatVector3Zero;

	{
		const PhysicsEntityMotionReference motion1 = m_entity1->getMotion();
		const PhysicsEntityMotionReference motion2 = m_entity2->getMotion();

		const ComputeVector3 velocity1 = motion1 ? motion1->getAngularVelocity() : ComputeVector3Zero;
		const ComputeVector3 velocity2 = motion2 ? motion2->getAngularVelocity() : ComputeVector3Zero;

		const ComputeValueType jv = (velocity2 - velocity1).dot(m_axis1);

		const ComputeValueType computeLambdaValue = m_invEffectiveMass * -jv; //negate jv instead of m_invEffectiveMass

		const ComputeValueType totalLambda = Math::Clamp(m_totalLambda + computeLambdaValue, m_minLambdaLimit, m_maxLambdaLimit);
		const ComputeValueType deltaLambda = totalLambda - m_totalLambda;

		m_totalLambda += deltaLambda;
		
		lambda = deltaLambda * m_axis1;
	}

	applyVelocity(lambda);
}

void Edge::AxisRotationLimitConstraintPart::solvePosition(ComputeValueType deltaAngle, ComputeValueType minLimit, ComputeValueType maxLimit)
{
	const ComputeValueType minDelta = deltaAngle - minLimit;
	if (minDelta < 0.0)
	{
		solveLimitPosition(-minDelta);
	}

	const ComputeValueType maxDelta = maxLimit - deltaAngle;
	if (maxDelta < 0.0)
	{
		solveLimitPosition(maxDelta);
	}
}

bool Edge::AxisRotationLimitConstraintPart::isActive() const
{
	return m_invEffectiveMass != 0.0_ecv;
}
