#include "ContactPenetrationAxleConstraintPart.h"

void Edge::ContactPenetrationAxleConstraintPart::deactivate()
{
	m_totalLambda = 0.0f;
	m_invEffectiveMass = 0.0f;
}

void Edge::ContactPenetrationAxleConstraintPart::applyVelocity(const FloatVector3& normal, float lambda) const
{
	if (fabsf(lambda) <= Math::Epsilon)
	{
		return;
	}

	const PhysicsEntityMotionReference motion1 = m_entity1->getMotion();
	const PhysicsEntityMotionReference motion2 = m_entity2->getMotion();

	if (motion1)
	{
		const ComputeVector linearVelocityDelta = (motion1->getInverseMass() * lambda) * normal;
		const FloatVector3 newLinVelocity = (motion1->getLinearVelocity() - linearVelocityDelta).getFloatVector3();
		motion1->setLinearVelocity(newLinVelocity);

		const ComputeVector angularVelocityDelta = m_invInerRadiusNorm1 * lambda;
		const FloatVector3 newAngularVelocity = (motion1->getAngularVelocity() - angularVelocityDelta).getFloatVector3();
		motion1->setAngularVelocity(newAngularVelocity);
	}

	if (motion2)
	{
		const ComputeVector linearVelocityDelta = (motion2->getInverseMass() * lambda) * normal;
		const FloatVector3 newLinVelocity = (motion2->getLinearVelocity() + linearVelocityDelta).getFloatVector3();
		motion2->setLinearVelocity(newLinVelocity);

		const ComputeVector angularVelocityDelta = m_invInerRadiusNorm2 * lambda;
		const FloatVector3 newAngularVelocity = (motion2->getAngularVelocity() + angularVelocityDelta).getFloatVector3();
		motion2->setAngularVelocity(newAngularVelocity);
	}
}

void Edge::ContactPenetrationAxleConstraintPart::applyPosition(const FloatVector3& normal, float lambda) const
{
	if (fabsf(lambda) <= Math::Epsilon)
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
		const ComputeVector positionDelta = (motion1->getInverseMass() * lambda) * normal;
		const FloatVector3 newPosition = (transformAccessor1.getPosition() - positionDelta).getFloatVector3();
		transformAccessor1.setPosition(newPosition);

		const ComputeVector angularVelocityDelta = m_invInerRadiusNorm1 * lambda;
		const float angularVelocityDeltaLength = angularVelocityDelta.getLength3();
		if (angularVelocityDeltaLength > Math::Epsilon)
		{
			const ComputeQuaternion newRotation = (ComputeQuaternionFromRotationAxis(angularVelocityDelta, angularVelocityDeltaLength) * transformAccessor1.getRotation()).normalize();
			transformAccessor1.setRotation(newRotation.getFloatQuaternion());
		}
	}

	if (motion2)
	{
		const ComputeVector positionDelta = (motion1->getInverseMass() * lambda) * normal;
		const FloatVector3 newPosition = (transformAccessor2.getPosition() + positionDelta).getFloatVector3();
		transformAccessor2.setPosition(newPosition);

		const ComputeVector angularVelocityDelta = m_invInerRadiusNorm2 * lambda;
		const float angularVelocityDeltaLength = angularVelocityDelta.getLength3();
		if (angularVelocityDeltaLength > Math::Epsilon)
		{
			const ComputeQuaternion newRotation = (ComputeQuaternionFromRotationAxis(angularVelocityDelta, -angularVelocityDeltaLength) * transformAccessor2.getRotation()).normalize();
			transformAccessor2.setRotation(newRotation.getFloatQuaternion());
		}
	}
}

void Edge::ContactPenetrationAxleConstraintPart::preSolve(const FloatVector3& contactPosition, const FloatVector3& normal)
{
	const PhysicsEntityTransformReference transform1 = m_entity1->getTransform();
	const PhysicsEntityTransformReference transform2 = m_entity2->getTransform();

	const ComputeVector radius1 = contactPosition - transform1->getPosition();
	const ComputeVector radius2 = contactPosition - transform2->getPosition();

	const PhysicsEntityMotionReference motion1 = m_entity1->getMotion();
	const PhysicsEntityMotionReference motion2 = m_entity2->getMotion();

	if (!motion1 && !motion2)
	{
		deactivate();
		return;
	}

	const PhysicsEntityCollisionReference collision1 = m_entity1->getCollision();
	const PhysicsEntityCollisionReference collision2 = m_entity2->getCollision();

	const float elasticity1 = collision1->getElasticity();
	const float elasticity2 = collision2->getElasticity();
	const float elasticity = std::max(elasticity1, elasticity2);

	ComputeVector relativeVelocity;
	float effectiveMass = 0.0f;

	if (motion1)
	{
		relativeVelocity -= motion1->getLocalPointLinearVelocity(radius1.getFloatVector3());

		effectiveMass += motion1->getInverseMass();

		const ComputeVector r1 = CrossVector3(radius1, normal);
		r1.saveToFloatVector3(m_radiusNorm1);

		ComputeMatrix invInertia;
		motion1->getWorldInverseInertiaTensor(invInertia);

		const ComputeVector invInertiaR1 = invInertia * r1;
		invInertiaR1.saveToFloatVector3(m_invInerRadiusNorm1);

		effectiveMass += DotVector3(invInertiaR1, r1);
	}

	if (motion2)
	{
		relativeVelocity += motion2->getLocalPointLinearVelocity(radius2.getFloatVector3());

		effectiveMass += motion2->getInverseMass();

		const ComputeVector r2 = CrossVector3(radius2, normal);
		r2.saveToFloatVector3(m_radiusNorm2);

		ComputeMatrix invInertia;
		motion2->getWorldInverseInertiaTensor(invInertia);

		const ComputeVector invInertiaR2 = invInertia * r2;
		invInertiaR2.saveToFloatVector3(m_invInerRadiusNorm2);

		effectiveMass += DotVector3(invInertiaR2, r2);
	}

	const float relativeSpeed = DotVector3(relativeVelocity, normal);
	m_restitution = elasticity * relativeSpeed;

	m_invEffectiveMass = 1.0f / effectiveMass;
}

void Edge::ContactPenetrationAxleConstraintPart::warmUp(const FloatVector3& normal)
{
	applyVelocity(normal, m_totalLambda);
}

void Edge::ContactPenetrationAxleConstraintPart::solveVelocity(const FloatVector3& normal)
{
	float lambda = 0.0f;

	{
		const PhysicsEntityMotionReference motion1 = m_entity1->getMotion();
		const PhysicsEntityMotionReference motion2 = m_entity2->getMotion();

		const ComputeVector linearVelocity1 = motion1 ? motion1->getLinearVelocity() : FloatVector3Zero;
		const ComputeVector linearVelocity2 = motion2 ? motion2->getLinearVelocity() : FloatVector3Zero;
		const ComputeVector linearVelocityDelta = linearVelocity1 - linearVelocity2;

		const ComputeVector angularVelocity1 = motion1 ? motion1->getAngularVelocity() : FloatVector3Zero;
		const ComputeVector angularVelocity2 = motion2 ? motion2->getAngularVelocity() : FloatVector3Zero;

		float JV = DotVector3(normal, linearVelocityDelta);
		JV += DotVector3(m_radiusNorm1, angularVelocity1);
		JV -= DotVector3(m_radiusNorm2, angularVelocity2);

		lambda = m_invEffectiveMass * (JV - m_restitution);

		m_totalLambda += lambda;
	}

	applyVelocity(normal, lambda);
}

void Edge::ContactPenetrationAxleConstraintPart::solvePosition(const FloatVector3& normal, float depth)
{
	static constexpr float baumgarteCoeff = 1.0f;
	const float lambda = m_invEffectiveMass * depth * baumgarteCoeff;

	applyPosition(normal, lambda);
}

bool Edge::ContactPenetrationAxleConstraintPart::isActive() const
{
	return fabsf(m_invEffectiveMass) > Math::Epsilon;
}
