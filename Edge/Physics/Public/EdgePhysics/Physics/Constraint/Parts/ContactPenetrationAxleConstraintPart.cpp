#include "ContactPenetrationAxleConstraintPart.h"

void Edge::ContactPenetrationAxleConstraintPart::deactivate()
{
	m_totalLambda = 0.0f;
	m_invEffectiveMass = 0.0f;
}

void Edge::ContactPenetrationAxleConstraintPart::applyVelocity(const ComputeVector3& normal, ComputeValueType lambda) const
{
	if (abs(lambda) <= Math::Epsilon)
	{
		return;
	}

	const PhysicsEntityMotionReference motion1 = m_entity1->getMotion();
	const PhysicsEntityMotionReference motion2 = m_entity2->getMotion();

	if (motion1)
	{
		const ComputeVector3 linearVelocityDelta = (motion1->getInverseMass() * lambda) * normal;
		const ComputeVector3 newLinVelocity = motion1->getLinearVelocity() - linearVelocityDelta;
		motion1->setLinearVelocity(newLinVelocity);

		const ComputeVector3 angularVelocityDelta = m_invInerRadiusNorm1 * lambda;
		const ComputeVector3 newAngularVelocity = motion1->getAngularVelocity() - angularVelocityDelta;
		motion1->setAngularVelocity(newAngularVelocity);
	}

	if (motion2)
	{
		const ComputeVector3 linearVelocityDelta = (motion2->getInverseMass() * lambda) * normal;
		const ComputeVector3 newLinVelocity = motion2->getLinearVelocity() + linearVelocityDelta;
		motion2->setLinearVelocity(newLinVelocity);

		const ComputeVector3 angularVelocityDelta = m_invInerRadiusNorm2 * lambda;
		const ComputeVector3 newAngularVelocity = motion2->getAngularVelocity() + angularVelocityDelta;
		motion2->setAngularVelocity(newAngularVelocity);
	}
}

void Edge::ContactPenetrationAxleConstraintPart::applyPosition(const ComputeVector3& normal, ComputeValueType lambda) const
{
	if (abs(lambda) <= Math::Epsilon)
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
		const ComputeVector3 positionDelta = (motion1->getInverseMass() * lambda) * normal;
		const ComputeVector3 newPosition = transformAccessor1.getPosition() - positionDelta;
		transformAccessor1.setPosition(newPosition);

		const ComputeVector3 angularVelocityDelta = m_invInerRadiusNorm1 * lambda;
		const ComputeValueType angularVelocityDeltaLength = angularVelocityDelta.getLength();
		if (angularVelocityDeltaLength > Math::Epsilon)
		{
			const ComputeQuaternion newRotation = (ComputeQuaternion(angularVelocityDelta, angularVelocityDeltaLength) * transformAccessor1.getRotation()).normalize();
			transformAccessor1.setRotation(newRotation);
		}
	}

	if (motion2)
	{
		const ComputeVector3 positionDelta = (motion1->getInverseMass() * lambda) * normal;
		const ComputeVector3 newPosition = transformAccessor2.getPosition() + positionDelta;
		transformAccessor2.setPosition(newPosition);

		const ComputeVector3 angularVelocityDelta = m_invInerRadiusNorm2 * lambda;
		const ComputeValueType angularVelocityDeltaLength = angularVelocityDelta.getLength();
		if (angularVelocityDeltaLength > Math::Epsilon)
		{
			const ComputeQuaternion newRotation = (ComputeQuaternion(angularVelocityDelta, -angularVelocityDeltaLength) * transformAccessor2.getRotation()).normalize();
			transformAccessor2.setRotation(newRotation);
		}
	}
}

void Edge::ContactPenetrationAxleConstraintPart::preSolve(const ComputeVector3& contactPosition, const ComputeVector3& normal)
{
	const PhysicsEntityTransformReference transform1 = m_entity1->getTransform();
	const PhysicsEntityTransformReference transform2 = m_entity2->getTransform();

	const ComputeVector3 radius1 = contactPosition - transform1->getPosition();
	const ComputeVector3 radius2 = contactPosition - transform2->getPosition();

	const PhysicsEntityMotionReference motion1 = m_entity1->getMotion();
	const PhysicsEntityMotionReference motion2 = m_entity2->getMotion();

	if (!motion1 && !motion2)
	{
		deactivate();
		return;
	}

	const PhysicsEntityCollisionReference collision1 = m_entity1->getCollision();
	const PhysicsEntityCollisionReference collision2 = m_entity2->getCollision();

	const ComputeValueType elasticity1 = collision1->getElasticity();
	const ComputeValueType elasticity2 = collision2->getElasticity();
	const ComputeValueType elasticity = std::max(elasticity1, elasticity2);

	ComputeVector3 relativeVelocity;
	ComputeValueType effectiveMass = ComputeValueType(0.0);

	if (motion1)
	{
		relativeVelocity -= motion1->getLocalPointLinearVelocity(radius1);

		effectiveMass += motion1->getInverseMass();

		m_radiusNorm1 = CrossComputeVector3(radius1, normal);

		ComputeMatrix3x3 invInertia;
		motion1->getWorldInverseInertiaTensor(invInertia);

		m_invInerRadiusNorm1 = invInertia * m_radiusNorm1;

		effectiveMass += DotComputeVector3(m_invInerRadiusNorm1, m_radiusNorm1);
	}

	if (motion2)
	{
		relativeVelocity += motion2->getLocalPointLinearVelocity(radius2);

		effectiveMass += motion2->getInverseMass();

		m_radiusNorm2 = CrossComputeVector3(radius2, normal);

		ComputeMatrix3x3 invInertia;
		motion2->getWorldInverseInertiaTensor(invInertia);

		m_invInerRadiusNorm2 = invInertia * m_radiusNorm2;

		effectiveMass += DotComputeVector3(m_invInerRadiusNorm2, m_radiusNorm2);
	}

	const ComputeValueType relativeSpeed = DotComputeVector3(relativeVelocity, normal);
	m_restitution = elasticity * relativeSpeed;

	m_invEffectiveMass = ComputeValueType(1.0) / effectiveMass;
}

void Edge::ContactPenetrationAxleConstraintPart::warmUp(const ComputeVector3& normal)
{
	applyVelocity(normal, m_totalLambda);
}

void Edge::ContactPenetrationAxleConstraintPart::solveVelocity(const ComputeVector3& normal)
{
	ComputeValueType lambda = 0.0f;

	{
		const PhysicsEntityMotionReference motion1 = m_entity1->getMotion();
		const PhysicsEntityMotionReference motion2 = m_entity2->getMotion();

		const ComputeVector3 linearVelocity1 = motion1 ? motion1->getLinearVelocity() : ComputeVector3Zero;
		const ComputeVector3 linearVelocity2 = motion2 ? motion2->getLinearVelocity() : ComputeVector3Zero;
		const ComputeVector3 linearVelocityDelta = linearVelocity1 - linearVelocity2;

		const ComputeVector3 angularVelocity1 = motion1 ? motion1->getAngularVelocity() : ComputeVector3Zero;
		const ComputeVector3 angularVelocity2 = motion2 ? motion2->getAngularVelocity() : ComputeVector3Zero;

		ComputeValueType JV = DotComputeVector3(normal, linearVelocityDelta);
		JV += DotComputeVector3(m_radiusNorm1, angularVelocity1);
		JV -= DotComputeVector3(m_radiusNorm2, angularVelocity2);

		lambda = m_invEffectiveMass * (JV - m_restitution);

		m_totalLambda += lambda;
	}

	applyVelocity(normal, lambda);
}

void Edge::ContactPenetrationAxleConstraintPart::solvePosition(const ComputeVector3& normal, ComputeValueType depth)
{
	static constexpr ComputeValueType baumgarteCoeff = ComputeValueType(1.0);
	const ComputeValueType lambda = m_invEffectiveMass * depth * baumgarteCoeff;

	applyPosition(normal, lambda);
}

bool Edge::ContactPenetrationAxleConstraintPart::isActive() const
{
	return abs(m_invEffectiveMass) > Math::Epsilon;
}
