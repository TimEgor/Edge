#include "LinearAxisBiasConstraintMotor.h"

#include "EdgePhysics/Physics/Entity/PhysicsEntityMotion.h"

void Edge::LinearAxisBiasConstraintMotor::deactivate()
{
	m_invEffectiveMass = 0.0;
	m_currentBias = 0.0;
	m_totalLambda = 0.0;
}

void Edge::LinearAxisBiasConstraintMotor::applyVelocity(ComputeValueType lambda) const
{
	if (Math::IsApproxEqual(lambda, 0.0_ecv))
	{
		return;
	}

	const ComputeVector3 linearImpulse = lambda * m_a;

	TwoPhysicsEntityConstraint* constraint = getConstraintContext();

	const PhysicsEntityReference entity1 = constraint->getEntity1();
	const PhysicsEntityReference entity2 = constraint->getEntity2();

	const PhysicsEntityMotionReference motion1 = entity1->getMotion();
	const PhysicsEntityMotionReference motion2 = entity2->getMotion();

	if (motion1)
	{
		const ComputeVector3 deltaVelocity = motion1->getInverseMass() * linearImpulse;

		const ComputeVector3 newLinVelocity = motion1->getLinearVelocity() + deltaVelocity;
		motion1->setLinearVelocity(newLinVelocity);
	}

	if (motion2)
	{
		const ComputeVector3 deltaVelocity = motion2->getInverseMass() * linearImpulse;

		const ComputeVector3 newLinVelocity = motion2->getLinearVelocity() - deltaVelocity;
		motion2->setLinearVelocity(newLinVelocity);
	}
}

void Edge::LinearAxisBiasConstraintMotor::preSolve(
	ComputeValueType offset,
	const ComputeVector3& anchor1,
	const ComputeVector3& anchor2,
	const ComputeVector3& axis1,
	const ComputeVector3& axis2
)
{
	TwoPhysicsEntityConstraint* constraint = getConstraintContext();

	const PhysicsEntityReference entity1 = constraint->getEntity1();
	const PhysicsEntityReference entity2 = constraint->getEntity2();

	const PhysicsEntityMotionReference motion1 = entity1->getMotion();
	const PhysicsEntityMotionReference motion2 = entity2->getMotion();

	{
		const PhysicsEntityTransform& transform1 = entity1->getTransform().getObjectRef();
		const ComputeQuaternion rotation1 = transform1.getRotation();

		m_a = rotation1.rotate(axis1);
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
	}

	if (motion2)
	{
		effectiveMass += motion2->getInverseMass();
	}

	m_invEffectiveMass = 1.0_ecv / effectiveMass;
	m_currentBias = m_bias - offset;
}

void Edge::LinearAxisBiasConstraintMotor::warmUp()
{
	applyVelocity(m_totalLambda);
}

void Edge::LinearAxisBiasConstraintMotor::solveVelocity(ComputeValueType deltaTime)
{
	ComputeValueType lambda = 0.0;

	{
		TwoPhysicsEntityConstraint* constraint = getConstraintContext();

		const PhysicsEntityReference entity1 = constraint->getEntity1();
		const PhysicsEntityReference entity2 = constraint->getEntity2();

		const PhysicsEntityMotionReference motion1 = entity1->getMotion();
		const PhysicsEntityMotionReference motion2 = entity2->getMotion();

		const ComputeVector3 linearVelocity1 = motion1 ? motion1->getLinearVelocity() : ComputeVector3Zero;
		const ComputeVector3 linearVelocity2 = motion2 ? motion2->getLinearVelocity() : ComputeVector3Zero;

		const ComputeValueType jv = (linearVelocity1 - linearVelocity2).dot(m_a);

		const ComputeValueType impulseLimit = m_forceLimit * deltaTime;
		lambda = -m_invEffectiveMass * (jv + m_currentBias);

		const ComputeValueType totalLambda = Math::Clamp(m_totalLambda + lambda, -impulseLimit, impulseLimit);
		lambda = totalLambda - m_totalLambda;

		m_totalLambda += lambda;
	}

	applyVelocity(lambda);
}

bool Edge::LinearAxisBiasConstraintMotor::isActive() const
{
	return !Math::IsApproxEqual(m_invEffectiveMass, 0.0_ecv);
}
