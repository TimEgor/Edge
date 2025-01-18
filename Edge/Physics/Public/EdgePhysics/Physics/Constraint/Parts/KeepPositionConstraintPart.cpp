#include "KeepPositionConstraintPart.h"

#include "EdgeCommon/Math/ComputeMatrix.h"
#include "EdgeCommon/Math/Const.h"

#include "EdgePhysics/Physics/Entity/PhysicsEntity.h"

void Edge::KeepPositionConstraintPart::deactivate()
{
	m_invEffectiveMass = FloatMatrix4x4Zero;
	m_totalLambda = FloatVector3Zero;
}

void Edge::KeepPositionConstraintPart::applyVelocity(const FloatVector3& lambda) const
{
	if (IsVectorEqual(lambda, FloatVector3Zero))
	{
		return;
	}

	const PhysicsEntityMotionReference motion1 = m_entity1->getMotion();
	const PhysicsEntityMotionReference motion2 = m_entity2->getMotion();

	if (motion1)
	{
		const FloatVector3 newLinVelocity = (motion1->getLinearVelocity() - motion1->getInverseMass() * lambda).getFloatVector3();
		motion1->setLinearVelocity(newLinVelocity);

		const ComputeVector angularVelocityDelta = m_invInerR1 * lambda;
		const FloatVector3 newAngularVelocity = (motion1->getAngularVelocity() + angularVelocityDelta).getFloatVector3();
		motion1->setAngularVelocity(newAngularVelocity);
	}

	if (motion2)
	{
		const FloatVector3 newLinVelocity = (motion2->getLinearVelocity() + motion2->getInverseMass() * lambda).getFloatVector3();
		motion2->setLinearVelocity(newLinVelocity);

		const ComputeVector angularVelocityDelta = m_invInerR2 * lambda;
		const FloatVector3 newAngularVelocity = (motion2->getAngularVelocity() - angularVelocityDelta).getFloatVector3();
		motion2->setAngularVelocity(newAngularVelocity);
	}
}

void Edge::KeepPositionConstraintPart::applyPosition(const FloatVector3& lambda) const
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
		const FloatVector3 newPosition= (transformAccessor1.getPosition() - motion1->getInverseMass() * lambda).getFloatVector3();
		transformAccessor1.setPosition(newPosition);

		const ComputeVector angularVelocityDelta = m_invInerR1 * lambda;
		const float angularVelocityDeltaLength = angularVelocityDelta.getLength3();
		if (angularVelocityDeltaLength > EDGE_EPSILON)
		{
			const ComputeQuaternion newRotation = (ComputeQuaternionFromRotationAxis(angularVelocityDelta, angularVelocityDeltaLength) * transformAccessor1.getRotation()).normalize();
			transformAccessor1.setRotation(newRotation.getFloatQuaternion());
		}
	}

	if (motion2)
	{
		const FloatVector3 newPosition = (transformAccessor2.getPosition() + motion2->getInverseMass() * lambda).getFloatVector3();
		transformAccessor2.setPosition(newPosition);

		const ComputeVector angularVelocityDelta = m_invInerR2 * lambda;
		const float angularVelocityDeltaLength = angularVelocityDelta.getLength3();
		if (angularVelocityDeltaLength > EDGE_EPSILON)
		{
			const ComputeQuaternion newRotation = (ComputeQuaternionFromRotationAxis(angularVelocityDelta, -angularVelocityDeltaLength) * transformAccessor2.getRotation()).normalize();
			transformAccessor2.setRotation(newRotation.getFloatQuaternion());
		}
	}
}

void Edge::KeepPositionConstraintPart::preSolve(const FloatVector3& anchor1, const FloatVector3& anchor2)
{
	m_r1 = RotateVector(m_entity1->getTransform()->getRotation(), anchor1).getFloatVector3();
	m_r2 = RotateVector(m_entity2->getTransform()->getRotation(), anchor2).getFloatVector3();

	ComputeMatrix effectiveMass = FloatMatrix4x4Zero;
	float invTotalMass = 0.0f;

	const PhysicsEntityMotionReference motion1 = m_entity1->getMotion();
	const PhysicsEntityMotionReference motion2 = m_entity2->getMotion();

	if (!motion1 && !motion2)
	{
		deactivate();
		return;
	}

	if (motion1)
	{
		invTotalMass += motion1->getMass();

		ComputeMatrix invInertia;
		motion1->getWorldInverseInertiaTensor(invInertia);
		const ComputeMatrix r1x = ComputeSkewSymmetricMatrix4x4ForCrossProduct(m_r1);
		(invInertia * r1x).saveToMatrix4x4(m_invInerR1);
		effectiveMass += r1x * invInertia * TransposeMatrix(r1x);
	}

	if (motion2)
	{
		invTotalMass += motion2->getMass();

		ComputeMatrix invInertia;
		motion2->getWorldInverseInertiaTensor(invInertia);
		const ComputeMatrix r2x = ComputeSkewSymmetricMatrix4x4ForCrossProduct(m_r2);
		(invInertia * r2x).saveToMatrix4x4(m_invInerR2);
		effectiveMass += r2x * invInertia * TransposeMatrix(r2x);
	}

	effectiveMass += ComputeMatrixFromScale(invTotalMass);
	effectiveMass.setElement(3, 3, 1.0f);

	InverseMatrix(effectiveMass).saveToMatrix4x4(m_invEffectiveMass);
	m_invEffectiveMass.m_m44 = 1.0f;
}

void Edge::KeepPositionConstraintPart::warmUp()
{
	applyVelocity(m_totalLambda);
}

void Edge::KeepPositionConstraintPart::solveVelocity()
{
	FloatVector3 lambda = FloatVector3Zero;

	{
		const PhysicsEntityMotionReference motion1 = m_entity1->getMotion();
		const PhysicsEntityMotionReference motion2 = m_entity2->getMotion();

		const ComputeVector velocity1 = motion1 ? motion1->getLinearVelocity() - CrossVector3(m_r1, motion1->getAngularVelocity()) : FloatVector3Zero;
		const ComputeVector velocity2 = motion2 ? motion2->getLinearVelocity() - CrossVector3(m_r2, motion2->getAngularVelocity()) : FloatVector3Zero;
		const ComputeVector velocityDelta = velocity1 - velocity2;
		const ComputeVector computeLambda = m_invEffectiveMass * velocityDelta;

		computeLambda.saveToFloatVector3(lambda);
		(m_totalLambda + computeLambda).saveToFloatVector3(m_totalLambda);
	}

	applyVelocity(lambda);
}

void Edge::KeepPositionConstraintPart::solvePosition()
{
	FloatVector3 lambda = FloatVector3Zero;

	{
		static constexpr float baumgarteCoeff = 1.0f;

		const ComputeVector error = (m_entity2->getTransform()->getPosition() + m_r2) - (m_entity1->getTransform()->getPosition() + m_r1);
		const ComputeVector computeLambda = m_invEffectiveMass * error * -baumgarteCoeff;
		computeLambda.saveToFloatVector3(lambda);
	}

	applyPosition(lambda);
}

bool Edge::KeepPositionConstraintPart::isActive() const
{
	return m_invEffectiveMass.m_m44 > EDGE_EPSILON;
}
