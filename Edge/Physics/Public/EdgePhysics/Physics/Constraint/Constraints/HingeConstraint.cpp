#include "HingeConstraint.h"

#include "EdgeCommon/UtilsMacros.h"

Edge::HingeConstraint::HingeConstraint(
	const PhysicsEntityReference& entity1,
	const PhysicsEntityReference& entity2,
	const ComputeVector3& anchor1,
	const ComputeVector3& anchor2,
	const ComputeVector3& axis1,
	const ComputeVector3& axis2
)
	: TwoPhysicsEntityConstraint(entity1, entity2),
	  m_positionPart(entity1, entity2),
	  m_rotationPart(entity1, entity2),
	  m_anchor1(anchor1),
	  m_anchor2(anchor2),
	  m_axis1(axis1),
	  m_axis2(axis2)
{
	m_initialRotationDelta =
		ComputeQuaternion(getEntity1()->getTransform()->getRotation()) *
		ComputeQuaternion(getEntity2()->getTransform()->getRotation()).conjugate();
}

void Edge::HingeConstraint::preSolve(ComputeValueType deltaTime)
{
	if (m_motor && m_motor->isEnabled())
	{
		m_motor->preSolve(getCurrentAngle(), m_anchor1, m_anchor2, m_axis1, m_axis2);
	}

	m_positionPart.preSolve(m_anchor1, m_anchor2);
	m_rotationPart.preSolve(m_axis1, m_axis2);
}

void Edge::HingeConstraint::warmUp()
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

void Edge::HingeConstraint::solveVelocity(ComputeValueType deltaTime)
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

void Edge::HingeConstraint::solvePosition(ComputeValueType deltaTime)
{
	if (m_motor && m_motor->isEnabled() && m_motor->isActive())
	{
		m_motor->solvePosition();
	}

	m_positionPart.preSolve(m_anchor1, m_anchor2);

	if (m_positionPart.isActive())
	{
		m_positionPart.solvePosition();
	}

	m_rotationPart.preSolve(m_axis1, m_axis2);

	if (m_rotationPart.isActive())
	{
		m_rotationPart.solvePosition();
	}
}

void Edge::HingeConstraint::setMotor(const AngularAxisConstraintMotorReference& motor)
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

Edge::AngularAxisConstraintMotorReference Edge::HingeConstraint::getMotor() const
{
	return m_motor;
}

Edge::ComputeValueType Edge::HingeConstraint::getCurrentAngle() const
{
	const ComputeQuaternion rotation1 = getEntity1()->getTransform()->getRotation();
	const ComputeQuaternion rotation2 = getEntity2()->getTransform()->getRotation();
	const ComputeVector3 worldAxis2 = rotation2.rotate(m_axis2);

	const ComputeQuaternion diffRotation = rotation1 * m_initialRotationDelta * ConjugateComputeQuaternion(rotation2);
	return diffRotation.getAxisAngle(worldAxis2);
}

Edge::HingeConstraintReference Edge::CreateHingeConstraintInWorldSpace(
	const PhysicsEntityReference& entity1,
	const PhysicsEntityReference& entity2,
	const ComputeVector3& anchor1,
	const ComputeVector3& anchor2,
	const ComputeVector3& axis1,
	const ComputeVector3& axis2
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

	return new HingeConstraint(
		entity1,
		entity2,
		localAnchor1,
		localAnchor2,
		localAxis1,
		localAxis2
	);
}
