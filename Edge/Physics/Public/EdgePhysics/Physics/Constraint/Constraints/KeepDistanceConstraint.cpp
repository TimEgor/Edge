#include "KeepDistanceConstraint.h"

#include "EdgeCommon/UtilsMacros.h"

Edge::KeepDistanceConstraint::KeepDistanceConstraint(const PhysicsEntityReference& entity1,
                                                     const PhysicsEntityReference& entity2, const ComputeVector3& anchor1, const ComputeVector3& anchor2)
	: TwoPhysicsEntityConstraint(entity1, entity2),
	m_positionPart(entity1, entity2),
	m_anchor1(anchor1), m_anchor2(anchor2)
{

}

void Edge::KeepDistanceConstraint::preSolve(float deltaTime)
{
	m_positionPart.preSolve(m_anchor1, m_anchor2);
}

void Edge::KeepDistanceConstraint::warmUp()
{
	if (m_positionPart.isActive())
	{
		m_positionPart.warmUp();
	}
}

void Edge::KeepDistanceConstraint::solveVelocity(ComputeValueType deltaTime)
{
	if (m_positionPart.isActive())
	{
		m_positionPart.solveVelocity();
	}
}

void Edge::KeepDistanceConstraint::solvePosition(ComputeValueType deltaTime)
{
	m_positionPart.preSolve(m_anchor1, m_anchor2);

	if (m_positionPart.isActive())
	{
		m_positionPart.solvePosition();
	}
}

Edge::KeepDistanceConstraintReference Edge::CreateKeepDistanceConstraintInWorldSpace(
	const PhysicsEntityReference& entity1, const PhysicsEntityReference& entity2,
	const ComputeVector3& anchor1, const ComputeVector3& anchor2
)
{
	EDGE_CHECK_RETURN_NULL(entity1 && entity2);

	const ComputeVector3 localAnchor1 = (InvertComputeMatrix4x4(entity1->getTransform()->getWorldTransform().m_matrix) * ComputeVector4FromPoint(anchor1)).getXYZ();
	const ComputeVector3 localAnchor2 = (InvertComputeMatrix4x4(entity2->getTransform()->getWorldTransform().m_matrix) * ComputeVector4FromPoint(anchor2)).getXYZ();

	return new KeepDistanceConstraint(entity1, entity2, localAnchor1, localAnchor2);
}
