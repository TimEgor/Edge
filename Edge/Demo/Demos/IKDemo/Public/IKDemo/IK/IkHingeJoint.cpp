#include "IkHingeJoint.h"

#include "EdgeCommon/Math/ComputeMatrix.h"

#include "IkLink.h"

EdgeDemo::IkHingeJoint::IkHingeJoint(IkLink* parentLink, IkLink* childLink, const Edge::FloatVector3& localAxis)
	: IkJoint(parentLink, childLink),
	m_initialLocalTransform(childLink->getLocalTransform()), m_localAxis(localAxis)
{
}

void EdgeDemo::IkHingeJoint::updateLinks()
{
	const Edge::ComputeQuaternion localJointRotation = ComputeQuaternionFromRotationAxis(m_localAxis, m_value);
	const Edge::ComputeMatrix localJointTransform = ComputeMatrixFromRotationQuaternion(localJointRotation)* m_initialLocalTransform.m_matrix;

	getChildLink()->setLocalTransform(localJointTransform.getMatrix4x4());
}

Edge::FloatVector3 EdgeDemo::IkHingeJoint::calcDerivative(const Edge::FloatVector3& effectorPosition) const
{
	const IkLink* childLink = getChildLink();
	const Edge::ComputeVector worldJointAxis = childLink->getWorldTransform().m_matrix * m_localAxis;
	const Edge::ComputeVector worldDelta = effectorPosition - childLink->getWorldTransform().getOrigin();
	const Edge::ComputeVector translationAxis = CrossVector3(worldJointAxis, worldDelta);

	return translationAxis.getFloatVector3();
}

void EdgeDemo::IkHingeJoint::applyValue(float value)
{
	setValue(value);
	updateLinks();
}
