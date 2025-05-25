#include "IkHingeJoint.h"

#include "EdgeCommon/Math/ComputeMatrix44.h"

#include "IkLink.h"

EdgeDemo::IkHingeJoint::IkHingeJoint(IkLink* parentLink, IkLink* childLink, const Edge::ComputeVector3& localAxis)
	: IkJoint(parentLink, childLink),
	m_initialLocalTransform(childLink->getLocalTransform()), m_localAxis(localAxis)
{
}

void EdgeDemo::IkHingeJoint::updateLinks()
{
	const Edge::ComputeQuaternion localJointRotation = Edge::ComputeQuaternion(m_localAxis, m_value);
	const Edge::ComputeMatrix4x4 localJointTransform = localJointRotation.getRotationMatrix4x4() * m_initialLocalTransform.m_matrix;

	getChildLink()->setLocalTransform(localJointTransform);
}

Edge::ComputeVector3 EdgeDemo::IkHingeJoint::calcDerivative(const Edge::ComputeVector3& effectorPosition) const
{
	const IkLink* childLink = getChildLink();
	const Edge::ComputeVector3 worldJointAxis = (childLink->getWorldTransform().m_matrix * Edge::ComputeVector4(m_localAxis)).getXYZ();
	const Edge::ComputeVector3 worldDelta = effectorPosition - childLink->getWorldTransform().getOrigin();
	const Edge::ComputeVector3 translationAxis = Edge::CrossComputeVector3(worldJointAxis, worldDelta);

	return translationAxis;
}

void EdgeDemo::IkHingeJoint::applyValue(float value)
{
	setValue(value);
	updateLinks();
}
