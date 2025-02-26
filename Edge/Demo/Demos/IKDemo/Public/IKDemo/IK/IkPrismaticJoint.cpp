#include "IkPrismaticJoint.h"

#include "EdgeCommon/Math/ComputeMatrix.h"

#include "IkLink.h"

EdgeDemo::IkPrismaticJoint::IkPrismaticJoint(IkLink* parentLink, IkLink* childLink, const Edge::FloatVector3& localAxis)
	: IkJoint(parentLink, childLink),
	m_initialLocalTransform(childLink->getLocalTransform()), m_localAxis(localAxis)
{
}

void EdgeDemo::IkPrismaticJoint::updateLinks()
{
	const Edge::ComputeMatrix localJointOffset = ComputeMatrixFromTranslation((m_localAxis * m_value).getFloatVector3());
	const Edge::ComputeMatrix localJointTransform = localJointOffset * m_initialLocalTransform.m_matrix;

	getChildLink()->setLocalTransform(localJointTransform.getMatrix4x4());
}

Edge::FloatVector3 EdgeDemo::IkPrismaticJoint::calcDerivative(const Edge::FloatVector3& effectorPosition) const
{
	const IkLink* childLink = getChildLink();
	const Edge::ComputeVector worldJointAxis = childLink->getWorldTransform().m_matrix * m_localAxis;

	return worldJointAxis.getFloatVector3();
}

void EdgeDemo::IkPrismaticJoint::applyValue(float value)
{
	setValue(value);
	updateLinks();
}
