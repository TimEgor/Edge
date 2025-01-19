#include "ContactFrictionAxleConstraintPart.h"

void Edge::ContactFrictionAxleConstraintPart::deactivate()
{
	m_totalLambda = 0.0f;
	m_invEffectiveMass = 0.0f;
}

void Edge::ContactFrictionAxleConstraintPart::applyVelocity(const FloatVector3& normal, float lambda)
{
	if (fabsf(lambda) <= Math::Epsilon)
	{
		return;
	}

	m_totalLambda += lambda;

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

void Edge::ContactFrictionAxleConstraintPart::preSolve(const FloatVector3& contactPosition, const FloatVector3& normal)
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

	float effectiveMass = 0.0f;

	if (motion1)
	{
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
		effectiveMass += motion2->getInverseMass();

		const ComputeVector r2 = CrossVector3(radius2, normal);
		r2.saveToFloatVector3(m_radiusNorm2);

		ComputeMatrix invInertia;
		motion2->getWorldInverseInertiaTensor(invInertia);

		const ComputeVector invInertiaR2 = invInertia * r2;
		invInertiaR2.saveToFloatVector3(m_invInerRadiusNorm2);

		effectiveMass += DotVector3(invInertiaR2, r2);
	}

	m_invEffectiveMass = 1.0f / effectiveMass;
}

void Edge::ContactFrictionAxleConstraintPart::warmUp(const FloatVector3& normal)
{
	applyVelocity(normal, m_totalLambda);
}

float Edge::ContactFrictionAxleConstraintPart::solveVelocity(const FloatVector3& normal)
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

		lambda = m_invEffectiveMass * JV;
	}

	return lambda;
}

bool Edge::ContactFrictionAxleConstraintPart::isActive() const
{
	return fabsf(m_invEffectiveMass) > Math::Epsilon;
}
