#include "AxisRotationConstraintPart.h"

void Edge::AxisRotationConstraintPart::deactivate()
{
	m_invEffectiveMass = FloatMatrix2x2Zero;
	m_totalLambda = FloatVector2Zero;
}

void Edge::AxisRotationConstraintPart::applyVelocity(const FloatVector3& lambda) const
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

void Edge::AxisRotationConstraintPart::applyPosition(const FloatVector3& lambda) const
{
	if (IsVectorEqual(lambda, FloatVector3Zero))
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
		const ComputeVector angularVelocityDelta = m_invIner1 * lambda;
		const float angularVelocityDeltaLength = angularVelocityDelta.getLength3();
		if (angularVelocityDeltaLength > EDGE_EPSILON)
		{
			const ComputeQuaternion newRotation = (ComputeQuaternionFromRotationAxis(angularVelocityDelta, -angularVelocityDeltaLength) * transformAccessor1.getRotation()).normalize();
			transformAccessor1.setRotation(newRotation.getFloatQuaternion());
		}
	}

	if (motion2)
	{
		const ComputeVector angularVelocityDelta = m_invIner2 * lambda;
		const float angularVelocityDeltaLength = angularVelocityDelta.getLength3();
		if (angularVelocityDeltaLength > EDGE_EPSILON)
		{
			const ComputeQuaternion newRotation = (ComputeQuaternionFromRotationAxis(angularVelocityDelta, angularVelocityDeltaLength) * transformAccessor2.getRotation()).normalize();
			transformAccessor2.setRotation(newRotation.getFloatQuaternion());
		}
	}
}

void Edge::AxisRotationConstraintPart::preSolve(const FloatVector3& axis1, const FloatVector3& axis2)
{
	const ComputeVector worldAxis1 = RotateVector(m_entity1->getTransform()->getRotation(), axis1);
	const ComputeVector worldAxis2 = RotateVector(m_entity2->getTransform()->getRotation(), axis2);

	m_axis1 = worldAxis1.getFloatVector3();

	const ComputeVector b2 = Vector3Orthogonal(worldAxis2);
	const ComputeVector c2 = CrossVector3(worldAxis2, b2);

	b2.saveToFloatVector3(m_axisOrtho1);
	c2.saveToFloatVector3(m_axisOrtho2);

	const PhysicsEntityMotionReference motion1 = m_entity1->getMotion();
	const PhysicsEntityMotionReference motion2 = m_entity2->getMotion();

	if (!motion1 && !motion2)
	{
		deactivate();
		return;
	}

	ComputeMatrix totalInvInertia = FloatMatrix4x4Zero;

	if (motion1)
	{
		ComputeMatrix invInertia;
		motion1->getWorldInverseInertiaTensor(invInertia);
		invInertia.saveToMatrix4x4(m_invIner1);

		totalInvInertia += invInertia;
	}

	if (motion2)
	{
		ComputeMatrix invInertia;
		motion2->getWorldInverseInertiaTensor(invInertia);
		invInertia.saveToMatrix4x4(m_invIner2);

		totalInvInertia += invInertia;
	}

	totalInvInertia.setElement(3, 3, 1.0f);

	const ComputeVector a1b2 = CrossVector3(b2, worldAxis1);
	const ComputeVector a1c2 = CrossVector3(c2, worldAxis1);

	FloatMatrix4x4 invEffectiveMass = FloatMatrix4x4Identity;
	invEffectiveMass.m_m11 = DotVector3(a1b2, TransformVector(totalInvInertia, a1b2));
	invEffectiveMass.m_m12 = DotVector3(a1b2, TransformVector(totalInvInertia, a1c2));
	invEffectiveMass.m_m21 = DotVector3(a1c2, TransformVector(totalInvInertia, a1b2));
	invEffectiveMass.m_m22 = DotVector3(a1c2, TransformVector(totalInvInertia, a1c2));

	InverseMatrix(invEffectiveMass).saveToMatrix2x2(m_invEffectiveMass);
}

void Edge::AxisRotationConstraintPart::warmUp()
{
	applyVelocity(m_totalLambda);
}

void Edge::AxisRotationConstraintPart::solveVelocity()
{
	FloatVector3 lambda = FloatVector3Zero;

	{
		const PhysicsEntityMotionReference motion1 = m_entity1->getMotion();
		const PhysicsEntityMotionReference motion2 = m_entity2->getMotion();

		const ComputeVector velocity1 = motion1 ? motion1->getAngularVelocity() : FloatVector3Zero;
		const ComputeVector velocity2 = motion2 ? motion2->getAngularVelocity() : FloatVector3Zero;

		const ComputeVector delta = velocity1 - velocity2;

		const ComputeVector a1b2 = CrossVector3(m_axisOrtho1, m_axis1);
		const ComputeVector a1c2 = CrossVector3(m_axisOrtho2, m_axis1);

		FloatVector2 jv(
			DotVector3(a1b2, delta),
			DotVector3(a1c2, delta)
		);

		ComputeVector computeLambda = m_invEffectiveMass * jv;
		computeLambda = a1b2 * computeLambda.getX() + a1c2 * computeLambda.getY();

		computeLambda.saveToFloatVector3(lambda);
		(m_totalLambda + computeLambda).saveToFloatVector3(m_totalLambda);
	}

	applyVelocity(lambda);
}

void Edge::AxisRotationConstraintPart::solvePosition()
{
	FloatVector3 lambda = FloatVector3Zero;

	{
		static constexpr float baumgarteCoeff = 1.0f;

		const ComputeVector a1b2 = CrossVector3(m_axisOrtho1, m_axis1);
		const ComputeVector a1c2 = CrossVector3(m_axisOrtho2, m_axis1);

		FloatVector2 jv(
			DotVector3(m_axis1, m_axisOrtho1),
			DotVector3(m_axis1, m_axisOrtho2)
		);

		ComputeVector computeLambda = m_invEffectiveMass * jv * -baumgarteCoeff;
		computeLambda = a1b2 * computeLambda.getX() + a1c2 * computeLambda.getY();

		computeLambda.saveToFloatVector3(lambda);
	}

	applyPosition(lambda);
}

bool Edge::AxisRotationConstraintPart::isActive() const
{
	return m_invEffectiveMass.m_m22 > EDGE_EPSILON;
}
