#include "IkPrismaticJoint.h"

#include "EdgeCommon/Math/ComputeMatrix44.h"

#include "IkLink.h"

EdgeDemo::IkPrismaticJoint::IkPrismaticJoint(IkLink* parentLink, IkLink* childLink, const Edge::ComputeVector3& localAxis)
	: IkJoint(parentLink, childLink),
	m_initialLocalTransform(childLink->getLocalTransform()), m_localAxis(localAxis)
{
}

void EdgeDemo::IkPrismaticJoint::updateLinks()
{
	const Edge::ComputeMatrix4x4 localJointOffset = Edge::TranslationComputeMatrix4x4(m_localAxis * m_value);
	const Edge::ComputeMatrix4x4 localJointTransform = localJointOffset * m_initialLocalTransform.m_matrix;

	getChildLink()->setLocalTransform(localJointTransform);
}

Edge::ComputeVector3 EdgeDemo::IkPrismaticJoint::calcDerivative(const Edge::ComputeVector3& effectorPosition) const
{
	const IkLink* childLink = getChildLink();
	const Edge::ComputeVector3 worldJointAxis = (childLink->getWorldTransform().m_matrix * Edge::ComputeVector4(m_localAxis)).getXYZ();

	return worldJointAxis;
}

void EdgeDemo::IkPrismaticJoint::applyValue(float value)
{
	setValue(value);
	updateLinks();
}
