#include "PrismaticConstraint.h"

#include "EdgeCommon/UtilsMacros.h"

Edge::PrismaticConstraint::PrismaticConstraint(
	const PhysicsEntityReference& entity1, const PhysicsEntityReference& entity2,
	const ComputeVector3& anchor1, const ComputeVector3& anchor2,
	const ComputeVector3& axis1, const ComputeVector3& axis2,
	const ComputeQuaternion& deltaRotation
)
	: TwoPhysicsEntityConstraint(entity1, entity2),
	m_positionPart(entity1, entity2), m_rotationPart(entity1, entity2),
	m_anchor1(anchor1), m_anchor2(anchor2),
	m_axis1(axis1), m_axis2(axis2),
	m_initialDeltaRotation(deltaRotation)
{
}

void Edge::PrismaticConstraint::preSolve(ComputeValueType deltaTime)
{
	if (m_motor && m_motor->isEnabled())
	{
		m_motor->preSolve(getCurrentOffset(), m_anchor1, m_anchor2, m_axis1, m_axis2);
	}

	m_positionPart.preSolve(m_anchor1, m_anchor2, m_axis1, m_axis2);
	m_rotationPart.preSolve();
}

void Edge::PrismaticConstraint::warmUp()
{
	if (m_motor && m_motor->isEnabled() && m_motor->isActive())
	{
		m_motor->warmUp();
	}

	if (m_positionPart.isActive())
	{
		m_positionPart.warmUp();
	}

	if (m_rotationPart.isActive())
	{
		m_rotationPart.warmUp();
	}
}

void Edge::PrismaticConstraint::solveVelocity(ComputeValueType deltaTime)
{
	if (m_motor && m_motor->isEnabled() && m_motor->isActive())
	{
		m_motor->solveVelocity(deltaTime);
	}

	if (m_positionPart.isActive())
	{
		m_positionPart.solveVelocity();
	}

	if (m_rotationPart.isActive())
	{
		m_rotationPart.solveVelocity();
	}
}

void Edge::PrismaticConstraint::solvePosition(ComputeValueType deltaTime)
{
	if (m_motor && m_motor->isEnabled() && m_motor->isActive())
	{
		m_motor->solvePosition();
	}

	m_positionPart.preSolve(m_anchor1, m_anchor2, m_axis1, m_axis2);

	if (m_positionPart.isActive())
	{
		m_positionPart.solvePosition();
	}

	m_rotationPart.preSolve();

	if (m_rotationPart.isActive())
	{
		m_rotationPart.solvePosition(m_initialDeltaRotation);
	}
}

void Edge::PrismaticConstraint::setMotor(const LinearAxisConstraintMotorReference& motor)
{
	if (m_motor == motor)
	{
		return;
	}

	if (motor)
	{
		if (motor->getConstraintContext())
		{
			EDGE_ASSERT_FAIL_MESSAGE("Constraint motor has been already set.");
			return;
		}

		motor->setConstraintContext(this);
	}

	if (m_motor)
	{
		m_motor->setConstraintContext(nullptr);
	}

	m_motor = motor;
}

Edge::LinearAxisConstraintMotorReference Edge::PrismaticConstraint::getMotor() const
{
	return m_motor;
}

Edge::ComputeValueType Edge::PrismaticConstraint::getCurrentOffset() const
{
	const PhysicsEntityTransformReference& transform1 = getEntity1()->getTransform();
	const PhysicsEntityTransformReference& transform2 = getEntity2()->getTransform();

	const ComputeVector3 position1 = transform1->getPosition();
	const ComputeVector3 position2 = transform2->getPosition();

	const ComputeQuaternion rotation1 = transform1->getRotation();
	const ComputeQuaternion rotation2 = transform2->getRotation();

	const ComputeVector3 anchor1 = rotation1.rotate(m_anchor1);
	const ComputeVector3 anchor2 = rotation2.rotate(m_anchor2);

	const ComputeVector3 delta = (position2 + anchor2) - (position1 + anchor1);
	const ComputeVector3 axis1 = rotation1.rotate(m_axis1);

	return axis1.dot(delta);
}

Edge::PrismaticConstraintReference Edge::CreatePrismaticConstraintInWorldSpace(
	const PhysicsEntityReference& entity1, const PhysicsEntityReference& entity2,
	const ComputeVector3& anchor1, const ComputeVector3& anchor2,
	const ComputeVector3& axis1, const ComputeVector3& axis2
)
{
	EDGE_CHECK_RETURN_NULL(entity1 && entity2);

	return CreatePrismaticConstraintInWorldSpace(
		entity1, entity2,
		anchor1, anchor2,
		axis1, axis2,
		entity1->getTransform()->getWorldTransform(), entity2->getTransform()->getWorldTransform()
	);
}

Edge::PrismaticConstraintReference Edge::CreatePrismaticConstraintInWorldSpace(
	const PhysicsEntityReference& entity1, const PhysicsEntityReference& entity2,
	const ComputeVector3& anchor1, const ComputeVector3& anchor2,
	const ComputeVector3& axis1, const ComputeVector3& axis2,
	const Transform& transform1, const Transform& transform2
)
{
	EDGE_CHECK_RETURN_NULL(entity1 && entity2);

	return CreatePrismaticConstraintInWorldSpace(
		entity1, entity2,
		anchor1, anchor2,
		axis1, axis2,
		transform1.getAxisX(), transform2.getAxisX(),
		transform1.getAxisY(), transform2.getAxisY()
	);
}

Edge::PrismaticConstraintReference Edge::CreatePrismaticConstraintInWorldSpace(
	const PhysicsEntityReference& entity1, const PhysicsEntityReference& entity2,
	const ComputeVector3& anchor1, const ComputeVector3& anchor2,
	const ComputeVector3& axis1, const ComputeVector3& axis2,
	const ComputeVector3& dirX1, const ComputeVector3& dirX2,
	const ComputeVector3& dirY1, const ComputeVector3& dirY2
)
{
	EDGE_CHECK_RETURN_NULL(entity1 && entity2);

	ComputeVector3 localAnchor1;
	ComputeVector3 localAnchor2;

	ComputeVector3 localAxis1;
	ComputeVector3 localAxis2;

	{
		const ComputeMatrix4x4 invertTransform1 = InvertComputeMatrix4x4(entity1->getTransform()->getWorldTransform().m_matrix);
		const ComputeMatrix4x4 invertTransform2 = InvertComputeMatrix4x4(entity2->getTransform()->getWorldTransform().m_matrix);

		localAnchor1 = (invertTransform1 * ComputeVector4FromPoint(anchor1)).getXYZ();
		localAnchor2 = (invertTransform2 * ComputeVector4FromPoint(anchor2)).getXYZ();

		localAxis1 = (invertTransform1 * ComputeVector4(axis1)).getXYZ();
		localAxis2 = (invertTransform2 * ComputeVector4(axis2)).getXYZ();
	}

	ComputeQuaternion rotationDelta;

	{
		const ComputeMatrix3x3 rotation1(
			dirX1,
			dirY1,
			CrossComputeVector3(dirX1, dirY1)
		);

		const ComputeMatrix3x3 rotation2(
			dirX2,
			dirY2,
			CrossComputeVector3(dirX2, dirY2)
		);

		rotationDelta = ComputeQuaternion(rotation1) * ComputeQuaternion(rotation2).conjugate();
	}

	return new PrismaticConstraint(
		entity1, entity2,
		localAnchor1, localAnchor2,
		localAxis1, localAxis2,
		rotationDelta
	);
}
