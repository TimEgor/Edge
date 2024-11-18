#include "KeepRotationConstraintPart.h"

void Edge::KeepRotationConstraintPart::deactivate()
{
	m_invEffectiveMass = FloatMatrix4x4Zero;
	m_totalLambda = FloatVector3Zero;
}

void Edge::KeepRotationConstraintPart::applyVelocity(const FloatVector3& lambda) const
{
	if (IsVectorEqual(lambda, FloatVector3Zero))
	{
		return;
	}

	const PhysicsEntityMotionReference motion1 = m_entity1->getMotion();
	const PhysicsEntityMotionReference motion2 = m_entity2->getMotion();

	if (motion1)
	{
		const ComputeVector angularVelocityDelta = m_invIner1 * lambda;
		const FloatVector3 newAngularVelocity = (motion1->getAngularVelocity() - angularVelocityDelta).getFloatVector3();
		motion1->setAngularVelocity(newAngularVelocity);
	}

	if (motion2)
	{
		const ComputeVector angularVelocityDelta = m_invIner2 * lambda;
		const FloatVector3 newAngularVelocity = (motion2->getAngularVelocity() + angularVelocityDelta).getFloatVector3();
		motion2->setAngularVelocity(newAngularVelocity);
	}
}

void Edge::KeepRotationConstraintPart::applyPosition(const FloatVector3& lambda) const
{
	if (IsVectorEqual(lambda, FloatVector3Zero))
	{
		return;
	}

	const PhysicsEntityTransformReference transform1 = m_entity1->getTransform();
	const PhysicsEntityTransformReference transform2 = m_entity2->getTransform();

	const PhysicsEntityMotionReference motion1 = m_entity1->getMotion();
	const PhysicsEntityMotionReference motion2 = m_entity2->getMotion();

	if (motion1)
	{
		const ComputeVector angularVelocityDelta = m_invIner1 * lambda;
		const float angularVelocityDeltaLength = angularVelocityDelta.length3();
		if (angularVelocityDeltaLength > EDGE_EPSILON)
		{
			const ComputeQuaternion newRotation = (ComputeQuaternionFromRotationAxis(angularVelocityDelta, -angularVelocityDeltaLength) * transform1->getRotation()).normalize();
			transform1->setRotation(newRotation.getFloatQuaternion());
		}
	}

	if (motion2)
	{
		const ComputeVector angularVelocityDelta = m_invIner2 * lambda;
		const float angularVelocityDeltaLength = angularVelocityDelta.length3();
		if (angularVelocityDeltaLength > EDGE_EPSILON)
		{
			const ComputeQuaternion newRotation = (ComputeQuaternionFromRotationAxis(angularVelocityDelta, angularVelocityDeltaLength) * transform2->getRotation()).normalize();
			transform2->setRotation(newRotation.getFloatQuaternion());
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

	ComputeMatrix effectiveMass = FloatMatrix4x4Zero;

	if (motion1)
	{
		ComputeMatrix invInertia;
		motion1->getWorldInverseInertiaTensor(invInertia);
		invInertia.saveToMatrix4x4(m_invIner1);

		effectiveMass += invInertia;
	}

	if (motion2)
	{
		ComputeMatrix invInertia;
		motion2->getWorldInverseInertiaTensor(invInertia);
		invInertia.saveToMatrix4x4(m_invIner2);

		effectiveMass += invInertia;
	}

	effectiveMass.setElement(3, 3, 1.0f);

	InverseMatrix(effectiveMass).saveToMatrix4x4(m_invEffectiveMass);
}

void Edge::KeepRotationConstraintPart::warmUp()
{
	applyVelocity(m_totalLambda);
}

void Edge::KeepRotationConstraintPart::solveVelocity()
{
	FloatVector3 lambda = FloatVector3Zero;

	{
		const PhysicsEntityMotionReference motion1 = m_entity1->getMotion();
		const PhysicsEntityMotionReference motion2 = m_entity2->getMotion();

		const ComputeVector velocity1 = motion1 ? motion1->getAngularVelocity() : FloatVector3Zero;
		const ComputeVector velocity2 = motion2 ? motion2->getAngularVelocity() : FloatVector3Zero;
		const ComputeVector computeLambda = m_invEffectiveMass * (velocity1 - velocity2);

		computeLambda.saveToFloatVector3(lambda);
		(m_totalLambda + computeLambda).saveToFloatVector3(m_totalLambda);
	}

	applyVelocity(lambda);
}

void Edge::KeepRotationConstraintPart::solvePosition(const FloatQuaternion& invInitialDeltaOrientation)
{
	FloatVector3 lambda = FloatVector3Zero;

	{
		static constexpr float baumgarteCoeff = 1.0f;

		const ComputeQuaternion diffRotation = m_entity1->getTransform()->getRotation() * invInitialDeltaOrientation * ConjugateQuaternion(m_entity2->getTransform()->getRotation());
		const ComputeVector error = 2.0f * diffRotation.getVector();
		const ComputeVector computeLambda = m_invEffectiveMass * error * baumgarteCoeff;
		computeLambda.saveToFloatVector3(lambda);
	}

	applyPosition(lambda);
}

bool Edge::KeepRotationConstraintPart::isActive() const
{
	return m_invEffectiveMass[3][3] > EDGE_EPSILON;
}
