#include "AxisPositionConstraintPart.h"

void Edge::AxisPositionConstraintPart::deactivate()
{
	m_invEffectiveMass = ComputeMatrix2x2Zero;
	m_totalLambda = ComputeVector2Zero;
}

void Edge::AxisPositionConstraintPart::applyVelocity(const ComputeVector2& lambda) const
{
	if (lambda == ComputeVector2Zero)
	{
		return;
	}

	const ComputeVector3 linearImpulse = m_n1 * lambda.getX() + m_n2 * lambda.getY();

	const PhysicsEntityMotionReference motion1 = m_entity1->getMotion();
	const PhysicsEntityMotionReference motion2 = m_entity2->getMotion();

	if (motion1)
	{
		const ComputeVector3 deltaVelocity = motion1->getInverseMass() * linearImpulse;

		const ComputeVector3 newLinVelocity = motion1->getLinearVelocity() - deltaVelocity;
		motion1->setLinearVelocity(newLinVelocity);

		ComputeMatrix3x3 invInertia;
		motion1->getWorldInverseInertiaTensor(invInertia);

		const ComputeVector3 inv_r1_u_n1 = invInertia * m_r1_u_n1;
		const ComputeVector3 inv_r1_u_n2 = invInertia * m_r1_u_n2;

		const ComputeVector3 angularVelocityDelta = inv_r1_u_n1 * lambda.getX() + inv_r1_u_n2 * lambda.getY();
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

		const ComputeVector3 inv_r2_n1 = invInertia * m_r2_n1;
		const ComputeVector3 inv_r2_n2 = invInertia * m_r2_n2;

		const ComputeVector3 angularVelocityDelta = inv_r2_n1 * lambda.getX() + inv_r2_n2 * lambda.getY();
		const ComputeVector3 newAngularVelocity = motion2->getAngularVelocity() + angularVelocityDelta;
		motion2->setAngularVelocity(newAngularVelocity);
	}
}

void Edge::AxisPositionConstraintPart::applyPosition(const ComputeVector2& lambda) const
{
	if (lambda == ComputeVector2Zero)
	{
		return;
	}

	const ComputeVector3 linearImpulse = m_n1 * lambda.getX() + m_n2 * lambda.getY();

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

		const ComputeVector3 inv_r1_u_n1 = invInertia * m_r1_u_n1;
		const ComputeVector3 inv_r1_u_n2 = invInertia * m_r1_u_n2;

		const ComputeVector3 rotationDelta = inv_r1_u_n1 * lambda.getX() + inv_r1_u_n2 * lambda.getY();
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

		const ComputeVector3 inv_r2_n1 = invInertia * m_r2_n1;
		const ComputeVector3 inv_r2_n2 = invInertia * m_r2_n2;

		const ComputeVector3 rotationDelta = inv_r2_n1 * lambda.getX() + inv_r2_n2 * lambda.getY();
		const ComputeValueType rotationDeltaLength = rotationDelta.getLength();
		if (rotationDeltaLength > Math::Epsilon)
		{
			const ComputeQuaternion newRotation = (ComputeQuaternion(rotationDelta, rotationDeltaLength) * transformAccessor2.getRotation()).normalize();
			transformAccessor2.setRotation(newRotation);
		}
	}
}

void Edge::AxisPositionConstraintPart::preSolve(
	const ComputeVector3& anchor1, const ComputeVector3& anchor2,
	const ComputeVector3& axis1, const ComputeVector3& axis2
)
{
	const PhysicsEntityMotionReference motion1 = m_entity1->getMotion();
	const PhysicsEntityMotionReference motion2 = m_entity2->getMotion();

	{
		const PhysicsEntityTransform& transform1 = m_entity1->getTransform().getObjectRef();
		const PhysicsEntityTransform& transform2 = m_entity2->getTransform().getObjectRef();

		const ComputeQuaternion rotation1 = transform1.getRotation();
		const ComputeQuaternion rotation2 = transform2.getRotation();

		const ComputeVector3 worldAnchor1 = rotation1.rotate(anchor1);
		const ComputeVector3 worldAnchor2 = rotation2.rotate(anchor2);

		const ComputeVector3 worldAxis1 = rotation1.rotate(axis1);

		m_n1 = worldAxis1.getOrthogonal();
		m_n2 = CrossComputeVector3(worldAxis1, m_n1);

		const ComputeVector3 position1 = motion1 ? motion1->getMassCenter() : transform1.getPosition();
		const ComputeVector3 position2 = motion2 ? motion2->getMassCenter() : transform2.getPosition();

		m_u = (position2 + worldAnchor2) - (position1 + worldAnchor1);
		const ComputeVector3 r1_u = worldAnchor1 + m_u;

		m_r1_u_n1 = CrossComputeVector3(r1_u, m_n1);
		m_r1_u_n2 = CrossComputeVector3(r1_u, m_n2);

		m_r2_n1 = CrossComputeVector3(worldAnchor2, m_n1);
		m_r2_n2 = CrossComputeVector3(worldAnchor2, m_n2);
	}

	if (!motion1 && !motion2)
	{
		deactivate();
		return;
	}

	ComputeMatrix2x2 effectiveMass = ComputeMatrix2x2Zero;

	if (motion1)
	{
		ComputeMatrix3x3 invInertia;
		motion1->getWorldInverseInertiaTensor(invInertia);

		const ComputeVector3 inv_r1_u_n1 = invInertia * m_r1_u_n1;
		const ComputeVector3 inv_r1_u_n2 = invInertia * m_r1_u_n2;

		effectiveMass.setElement(0, 0, effectiveMass.getElement(0, 0) + motion1->getInverseMass() + DotComputeVector3(m_r1_u_n1, inv_r1_u_n1));
		effectiveMass.setElement(0, 1, effectiveMass.getElement(0, 1) + DotComputeVector3(m_r1_u_n1, inv_r1_u_n2));
		effectiveMass.setElement(1, 0, effectiveMass.getElement(1, 0) + DotComputeVector3(m_r1_u_n2, inv_r1_u_n1));
		effectiveMass.setElement(1, 1, effectiveMass.getElement(1, 1) + motion1->getInverseMass() + DotComputeVector3(m_r1_u_n2, inv_r1_u_n2));
	}

	if (motion2)
	{
		ComputeMatrix3x3 invInertia;
		motion2->getWorldInverseInertiaTensor(invInertia);

		const ComputeVector3 inv_r2_n1 = invInertia * m_r2_n1;
		const ComputeVector3 inv_r2_n2 = invInertia * m_r2_n2;

		effectiveMass.setElement(0, 0, effectiveMass.getElement(0, 0) + motion2->getInverseMass() + DotComputeVector3(m_r2_n1, inv_r2_n1));
		effectiveMass.setElement(0, 1, effectiveMass.getElement(0, 1) + DotComputeVector3(m_r2_n1, inv_r2_n2));
		effectiveMass.setElement(1, 0, effectiveMass.getElement(1, 0) + DotComputeVector3(m_r2_n2, inv_r2_n1));
		effectiveMass.setElement(1, 1, effectiveMass.getElement(1, 1) + motion2->getInverseMass() + DotComputeVector3(m_r2_n2, inv_r2_n2));
	}

	m_invEffectiveMass = InvertComputeMatrix2x2(effectiveMass);
}

void Edge::AxisPositionConstraintPart::warmUp()
{
	applyVelocity(m_totalLambda);
}

void Edge::AxisPositionConstraintPart::solveVelocity()
{
	ComputeVector2 lambda = FloatVector2Zero;

	{
		const PhysicsEntityMotionReference motion1 = m_entity1->getMotion();
		const PhysicsEntityMotionReference motion2 = m_entity2->getMotion();

		const ComputeVector3 linearVelocity1 = motion1 ? motion1->getLinearVelocity() : ComputeVector3Zero;
		const ComputeVector3 linearVelocity2 = motion2 ? motion2->getLinearVelocity() : ComputeVector3Zero;

		const ComputeVector3 angularVelocity1 = motion1 ? motion1->getAngularVelocity() : ComputeVector3Zero;
		const ComputeVector3 angularVelocity2 = motion2 ? motion2->getAngularVelocity() : ComputeVector3Zero;

		const ComputeVector2 jv(
			-DotComputeVector3(m_n1, linearVelocity1) - DotComputeVector3(m_r1_u_n1, angularVelocity1) +
			DotComputeVector3(m_n1, linearVelocity2) + DotComputeVector3(m_r2_n1, angularVelocity2),
			-DotComputeVector3(m_n2, linearVelocity1) - DotComputeVector3(m_r1_u_n2, angularVelocity1) +
			DotComputeVector3(m_n2, linearVelocity2) + DotComputeVector3(m_r2_n2, angularVelocity2)
		);

		lambda = m_invEffectiveMass * -jv; //negate jv instead of m_invEffectiveMass
		m_totalLambda += lambda;
	}

	applyVelocity(lambda);
}

void Edge::AxisPositionConstraintPart::solvePosition()
{
	ComputeVector2 lambda = FloatVector2Zero;

	{
		static constexpr ComputeValueType baumgarteCoeff = 1.0;

		const ComputeVector2 jv(
			DotComputeVector3(m_u, m_n1),
			DotComputeVector3(m_u, m_n2)
		);

		lambda = m_invEffectiveMass * (jv * -baumgarteCoeff); //negate baumgarteCoeff instead of m_invEffectiveMass
	}

	applyPosition(lambda);
}

bool Edge::AxisPositionConstraintPart::isActive() const
{
	return true;
}
