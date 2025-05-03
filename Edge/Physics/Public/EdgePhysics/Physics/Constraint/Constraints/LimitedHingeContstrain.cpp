#include "LimitedHingeContstrain.h"

#include "EdgeCommon/UtilsMacros.h"

Edge::LimitedHingeConstraint::LimitedHingeConstraint(
	const PhysicsEntityReference& entity1,
	const PhysicsEntityReference& entity2,
	const ComputeVector3& anchor1,
	const ComputeVector3& anchor2,
	const ComputeVector3& axis1,
	const ComputeVector3& axis2,
	ComputeValueType minLimit,
	ComputeValueType maxLimit
)
	: HingeConstraint(
		entity1, entity2,
		anchor1, anchor2,
		axis1, axis2
	),
	m_limitPart(entity1, entity2)
{
	setLimits(minLimit, maxLimit);
}

void Edge::LimitedHingeConstraint::preSolve(float deltaTime)
{
	HingeConstraint::preSolve(deltaTime);

	m_limitPart.preSolve(m_axis1, getCurrentAngle(), m_minLimitValue, m_maxLimitValue);
}

void Edge::LimitedHingeConstraint::warmUp()
{
	HingeConstraint::warmUp();

	m_limitPart.warmUp();
}

void Edge::LimitedHingeConstraint::solveVelocity()
{
	HingeConstraint::solveVelocity();

	if (m_limitPart.isActive())
	{
		m_limitPart.solveVelocity();
	}
}

void Edge::LimitedHingeConstraint::solvePosition()
{
	HingeConstraint::solvePosition();

	const ComputeValueType angle = getCurrentAngle();

	m_limitPart.preSolve(m_axis1, angle, m_minLimitValue, m_maxLimitValue);

	if (m_limitPart.isActive())
	{
		m_limitPart.solvePosition(angle, m_minLimitValue, m_maxLimitValue);
	}
}

void Edge::LimitedHingeConstraint::setLimits(ComputeValueType min, ComputeValueType max)
{
	if (min > max)
	{
		EDGE_ASSERT_FAIL_MESSAGE("Constraint min limit value should be less or equal than max value.");
		return;
	}

	setMinLimit(min);
	setMaxLimit(max);
}

void Edge::LimitedHingeConstraint::setMinLimit(ComputeValueType min)
{
	if (-Math::Pi > min && min > Math::Pi)
	{
		EDGE_ASSERT_FAIL_MESSAGE("Constraint limit should be in range [-pi; pi]");
		return;
	}

	m_minLimitValue = min;
}

void Edge::LimitedHingeConstraint::setMaxLimit(ComputeValueType max)
{
	if (-Math::Pi > max && max > Math::Pi)
	{
		EDGE_ASSERT_FAIL_MESSAGE("Constraint limit should be in range [-pi; pi]");
		return;
	}

	m_maxLimitValue = max;
}

Edge::HingeConstraintReference Edge::CreateLimitedHingeConstraintInWorldSpace(
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

	return new LimitedHingeConstraint(
		entity1,
		entity2,
		localAnchor1,
		localAnchor2,
		localAxis1,
		localAxis2,
		minLimit,
		maxLimit
	);
}
