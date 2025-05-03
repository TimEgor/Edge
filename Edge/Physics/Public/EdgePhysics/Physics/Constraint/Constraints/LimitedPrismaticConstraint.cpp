#include "LimitedPrismaticConstraint.h"

#include "EdgeCommon/UtilsMacros.h"

Edge::LimitedPrismaticConstraint::LimitedPrismaticConstraint(
	const PhysicsEntityReference& entity1,
	const PhysicsEntityReference& entity2,
	const ComputeVector3& anchor1,
	const ComputeVector3& anchor2,
	const ComputeVector3& axis1,
	const ComputeVector3& axis2,
	ComputeValueType minLimit,
	ComputeValueType maxLimit,
	const ComputeQuaternion& deltaRotation
)
	: PrismaticConstraint(
		  entity1,
		  entity2,
		  anchor1,
		  anchor2,
		  axis1,
		  axis2,
		  deltaRotation
	  ),
	  m_limitPart(entity1, entity2)
{
	setLimits(minLimit, maxLimit);
}

void Edge::LimitedPrismaticConstraint::preSolve(float deltaTime)
{
	PrismaticConstraint::preSolve(deltaTime);

	m_limitPart.preSolve(m_anchor1, m_anchor2, m_axis1, m_axis2, getCurrentOffset(), m_minLimitValue, m_maxLimitValue);
}

void Edge::LimitedPrismaticConstraint::warmUp()
{
	PrismaticConstraint::warmUp();

	m_limitPart.warmUp();
}

void Edge::LimitedPrismaticConstraint::solveVelocity()
{
	PrismaticConstraint::solveVelocity();

	if (m_limitPart.isActive())
	{
		m_limitPart.solveVelocity();
	}
}

void Edge::LimitedPrismaticConstraint::solvePosition()
{
	PrismaticConstraint::solvePosition();

	const ComputeValueType offset = getCurrentOffset();

	m_limitPart.preSolve(m_anchor1, m_anchor2, m_axis1, m_axis2, offset, m_minLimitValue, m_maxLimitValue);

	if (m_limitPart.isActive())
	{
		m_limitPart.solvePosition(offset, m_minLimitValue, m_maxLimitValue);
	}
}

void Edge::LimitedPrismaticConstraint::setLimits(ComputeValueType min, ComputeValueType max)
{
	if (min > max)
	{
		EDGE_ASSERT_FAIL_MESSAGE("Constraint min limit value should be less or equal than max value.");
		return;
	}

	m_minLimitValue = min;
	m_maxLimitValue = max;
}

Edge::LimitedPrismaticConstraintReference Edge::CreateLimitedPrismaticConstraintInWorldSpace(
	const PhysicsEntityReference& entity1,
	const PhysicsEntityReference& entity2,
	const ComputeVector3& anchor1,
	const ComputeVector3& anchor2,
	const ComputeVector3& axis1,
	const ComputeVector3& axis2,
	ComputeValueType minLimit,
	ComputeValueType maxLimit
)
{
	EDGE_CHECK_RETURN_NULL(entity1 && entity2);

	return CreateLimitedPrismaticConstraintInWorldSpace(
		entity1, entity2,
		anchor1, anchor2,
		axis1, axis2,
		entity1->getTransform()->getWorldTransform(), entity2->getTransform()->getWorldTransform(),
		minLimit, maxLimit
	);
}

Edge::LimitedPrismaticConstraintReference Edge::CreateLimitedPrismaticConstraintInWorldSpace(
	const PhysicsEntityReference& entity1,
	const PhysicsEntityReference& entity2,
	const ComputeVector3& anchor1,
	const ComputeVector3& anchor2,
	const ComputeVector3& axis1,
	const ComputeVector3& axis2,
	const Transform& transform1,
	const Transform& transform2,
	ComputeValueType minLimit,
	ComputeValueType maxLimit
)
{
	EDGE_CHECK_RETURN_NULL(entity1 && entity2);

	return CreateLimitedPrismaticConstraintInWorldSpace(
		entity1, entity2,
		anchor1, anchor2,
		axis1, axis2,
		transform1.getAxisX(), transform2.getAxisX(),
		transform1.getAxisY(), transform2.getAxisY(),
		minLimit, maxLimit
	);
}

Edge::LimitedPrismaticConstraintReference Edge::CreateLimitedPrismaticConstraintInWorldSpace(
	const PhysicsEntityReference& entity1,
	const PhysicsEntityReference& entity2,
	const ComputeVector3& anchor1,
	const ComputeVector3& anchor2,
	const ComputeVector3& axis1,
	const ComputeVector3& axis2,
	const ComputeVector3& dirX1,
	const ComputeVector3& dirX2,
	const ComputeVector3& dirY1,
	const ComputeVector3& dirY2,
	ComputeValueType minLimit,
	ComputeValueType maxLimit
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

	return new LimitedPrismaticConstraint(
		entity1, entity2,
		localAnchor1, localAnchor2,
		localAxis1, localAxis2,
		minLimit, maxLimit,
		rotationDelta
	);
}
