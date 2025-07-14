#include "ContactFrictionAxleConstraintPart.h"

void Edge::ContactFrictionAxleConstraintPart::deactivate()
{
	m_totalLambda = ComputeValueType(0.0);
	m_invEffectiveMass = ComputeValueType(0.0);
}

void Edge::ContactFrictionAxleConstraintPart::applyVelocity(const ComputeVector3& normal, ComputeValueType lambda)
{
	if (abs(lambda) <= Math::Epsilon)
	{
		return;
	}

	m_totalLambda += lambda;

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

Edge::ComputeValueType Edge::ContactFrictionAxleConstraintPart::getTotalLambda() const
{
	return m_totalLambda;
}

void Edge::ContactFrictionAxleConstraintPart::setTotalLambda(ComputeValueType lambda)
{
	m_totalLambda = lambda;
}

void Edge::ContactFrictionAxleConstraintPart::preSolve(const ComputeVector3& contactPosition, const ComputeVector3& normal)
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

	ComputeValueType effectiveMass = ComputeValueType(0.0);

	if (motion1)
	{
		effectiveMass += motion1->getInverseMass();

		m_radiusNorm1 = CrossComputeVector3(radius1, normal);

		ComputeMatrix3x3 invInertia;
		motion1->getWorldInverseInertiaTensor(invInertia);

		m_invInerRadiusNorm1 = invInertia * m_radiusNorm1;

		effectiveMass += DotComputeVector3(m_invInerRadiusNorm1, m_radiusNorm1);
	}

	if (motion2)
	{
		effectiveMass += motion2->getInverseMass();

		m_radiusNorm2 = CrossComputeVector3(radius2, normal);

		ComputeMatrix3x3 invInertia;
		motion2->getWorldInverseInertiaTensor(invInertia);

		m_invInerRadiusNorm2 = invInertia * m_radiusNorm2;

		effectiveMass += DotComputeVector3(m_invInerRadiusNorm2, m_radiusNorm2);
	}

	m_invEffectiveMass = ComputeValueType(1.0) / effectiveMass;
}

void Edge::ContactFrictionAxleConstraintPart::warmUp(const ComputeVector3& normal)
{
	applyVelocity(normal, m_totalLambda);
}

Edge::ComputeValueType Edge::ContactFrictionAxleConstraintPart::solveVelocity(const ComputeVector3& normal)
{
	ComputeValueType lambda = ComputeValueType(0.0);

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

		lambda = m_invEffectiveMass * JV;
	}

	return lambda;
}

bool Edge::ContactFrictionAxleConstraintPart::isActive() const
{
	return abs(m_invEffectiveMass) > Math::Epsilon;
}
