#include "FixedConstraint.h"

#include "EdgeCommon/UtilsMacros.h"

Edge::FixedConstraint::FixedConstraint(const PhysicsEntityReference& entity1, const PhysicsEntityReference& entity2,
	const ComputeVector3& anchor1, const ComputeVector3& anchor2, const ComputeQuaternion& deltaRotation)
	: TwoPhysicsEntityConstraint(entity1, entity2),
	m_positionPart(entity1, entity2), m_rotationPart(entity1, entity2),
	m_anchor1(anchor1), m_anchor2(anchor2),
	m_initialDeltaRotation(deltaRotation)
{
}

void Edge::FixedConstraint::preSolve(float deltaTime)
{
	m_positionPart.preSolve(m_anchor1, m_anchor2);
	m_rotationPart.preSolve();
}

void Edge::FixedConstraint::warmUp()
{
	if (m_positionPart.isActive())
	{
		m_positionPart.warmUp();
	}

	if (m_rotationPart.isActive())
	{
		m_rotationPart.warmUp();
	}
}

void Edge::FixedConstraint::solveVelocity(ComputeValueType deltaTime)
{
	if (m_positionPart.isActive())
	{
		m_positionPart.solveVelocity();
	}

	if (m_rotationPart.isActive())
	{
		m_rotationPart.solveVelocity();
	}
}

void Edge::FixedConstraint::solvePosition(ComputeValueType deltaTime)
{
	m_positionPart.preSolve(m_anchor1, m_anchor2);

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

Edge::FixedConstraintReference Edge::CreateFixedConstraintInWorldSpace(
	const PhysicsEntityReference& entity1, const PhysicsEntityReference& entity2,
	const ComputeVector3& anchor1, const ComputeVector3& anchor2
)
{
	EDGE_CHECK_RETURN_NULL(entity1 && entity2);

	return CreateFixedConstraintInWorldSpace(
		entity1, entity2,
		anchor1, anchor2,
		entity1->getTransform()->getWorldTransform(), entity2->getTransform()->getWorldTransform()
	);
}

Edge::FixedConstraintReference Edge::CreateFixedConstraintInWorldSpace(
	const PhysicsEntityReference& entity1, const PhysicsEntityReference& entity2,
	const ComputeVector3& anchor1, const ComputeVector3& anchor2,
	const Transform& transform1, const Transform& transform2
)
{
	EDGE_CHECK_RETURN_NULL(entity1 && entity2);

	return CreateFixedConstraintInWorldSpace(
		entity1, entity2,
		anchor1, anchor2,
		transform1.getAxisX(), transform2.getAxisX(),
		transform1.getAxisY(), transform2.getAxisY()
	);
}

Edge::FixedConstraintReference Edge::CreateFixedConstraintInWorldSpace(
	const PhysicsEntityReference& entity1, const PhysicsEntityReference& entity2,
	const ComputeVector3& anchor1, const ComputeVector3& anchor2,
	const ComputeVector3& dirX1, const ComputeVector3& dirX2,
	const ComputeVector3& dirY1, const ComputeVector3& dirY2
)
{
	EDGE_CHECK_RETURN_NULL(entity1 && entity2);

	const ComputeVector3 localAnchor1 = (InvertComputeMatrix4x4(entity1->getTransform()->getWorldTransform().m_matrix) * ComputeVector4FromPoint(anchor1)).getXYZ();
	const ComputeVector3 localAnchor2 = (InvertComputeMatrix4x4(entity2->getTransform()->getWorldTransform().m_matrix) * ComputeVector4FromPoint(anchor2)).getXYZ();

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

	return new FixedConstraint(
		entity1, entity2,
		localAnchor1, localAnchor2,
		rotationDelta
	);
}
