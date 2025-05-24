#include "AngularAxisBiasConstraintMotor.h"

#include "EdgePhysics/Physics/Entity/PhysicsEntityMotion.h"

void Edge::AngularAxisBiasConstraintMotor::deactivate()
{
	m_invEffectiveMass = 0.0;
	m_currentBias = 0.0;
	m_totalLambda = 0.0;
}

void Edge::AngularAxisBiasConstraintMotor::applyVelocity(ComputeValueType lambda) const
{
	if (Math::IsApproxEqual(lambda, 0.0_ecv))
	{
		return;
	}

	const ComputeVector3 angularImpulse = lambda * m_a;

	TwoPhysicsEntityConstraint* constraint = getConstraintContext();

	const PhysicsEntityReference entity1 = constraint->getEntity1();
	const PhysicsEntityReference entity2 = constraint->getEntity2();

	const PhysicsEntityMotionReference motion1 = entity1->getMotion();
	const PhysicsEntityMotionReference motion2 = entity2->getMotion();

	if (motion1)
	{
		ComputeMatrix3x3 inertia;
		motion1->getWorldInverseInertiaTensor(inertia);

		const ComputeVector3 angularVelocityDelta = inertia * angularImpulse;
		const ComputeVector3 newAngularVelocity = motion1->getAngularVelocity() + angularVelocityDelta;
		motion1->setAngularVelocity(newAngularVelocity);
	}

	if (motion2)
	{
		ComputeMatrix3x3 inertia;
		motion2->getWorldInverseInertiaTensor(inertia);

		const ComputeVector3 angularVelocityDelta = inertia * angularImpulse;
		const ComputeVector3 newAngularVelocity = motion2->getAngularVelocity() + angularVelocityDelta;
		motion2->setAngularVelocity(newAngularVelocity);
	}
}

void Edge::AngularAxisBiasConstraintMotor::preSolve(
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
		ComputeMatrix3x3 inertia;
		motion1->getWorldInverseInertiaTensor(inertia);
		effectiveMass += m_a.dot(inertia * m_a);
	}

	if (motion2)
	{
		ComputeMatrix3x3 inertia;
		motion2->getWorldInverseInertiaTensor(inertia);
		effectiveMass += m_a.dot(inertia * m_a);
	}

	m_invEffectiveMass = 1.0_ecv / effectiveMass;
	m_currentBias = m_bias - offset;
}

void Edge::AngularAxisBiasConstraintMotor::warmUp()
{
	applyVelocity(m_totalLambda);
}

void Edge::AngularAxisBiasConstraintMotor::solveVelocity(ComputeValueType deltaTime)
{
	ComputeValueType lambda = 0.0;

	{
		TwoPhysicsEntityConstraint* constraint = getConstraintContext();

		const PhysicsEntityReference entity1 = constraint->getEntity1();
		const PhysicsEntityReference entity2 = constraint->getEntity2();

		const PhysicsEntityMotionReference motion1 = entity1->getMotion();
		const PhysicsEntityMotionReference motion2 = entity2->getMotion();

		const ComputeVector3 angularVelocity1 = motion1 ? motion1->getAngularVelocity() : ComputeVector3Zero;
		const ComputeVector3 angularVelocity2 = motion2 ? motion2->getAngularVelocity() : ComputeVector3Zero;

		const ComputeValueType jv = (angularVelocity2 - angularVelocity1).dot(m_a);

		const ComputeValueType impulseLimit = m_forceLimit * deltaTime;
		lambda = -m_invEffectiveMass * (jv + m_currentBias);

		const ComputeValueType totalLambda = Math::Clamp(m_totalLambda + lambda, -impulseLimit, impulseLimit);
		lambda = totalLambda - m_totalLambda;

		m_totalLambda += lambda;
	}

	applyVelocity(lambda);
}

bool Edge::AngularAxisBiasConstraintMotor::isActive() const
{
	return !Math::IsApproxEqual(m_invEffectiveMass, 0.0_ecv);
}
