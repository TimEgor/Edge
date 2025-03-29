#include "Transform.h"

Edge::ComputeMatrix3x3 Edge::Transform::getRotationMatrix() const
{
	ComputeMatrix3x3 rotation;
	getRotationMatrix(rotation);

	return rotation;
}

void Edge::Transform::getRotationMatrix(ComputeMatrix3x3& rotation) const
{
	rotation.setColumn(0, getAxisX());
	rotation.setColumn(1, getAxisY());
	rotation.setColumn(2, getAxisZ());
}

void Edge::Transform::setRotationMatrix(const ComputeMatrix3x3& rotation)
{
	m_matrix.getColumn(0).setXYZ(rotation.getColumn(0));
	m_matrix.getColumn(1).setXYZ(rotation.getColumn(1));
	m_matrix.getColumn(2).setXYZ(rotation.getColumn(2));
}

Edge::ComputeQuaternion Edge::Transform::getRotationQuaternion() const
{
	ComputeQuaternion quaternion;
	getRotationQuaternion(quaternion);

	return quaternion;
}

void Edge::Transform::getRotationQuaternion(ComputeQuaternion& rotation) const
{
	ComputeMatrix3x3 rotationMatrix;
	getRotationMatrix(rotationMatrix);
	rotation.setupFromRotationMatrix3x3(rotationMatrix);
}

void Edge::Transform::setRotationQuaternion(const ComputeQuaternion& rotation)
{
	setRotationMatrix(rotation.getRotationMatrix3x3());
}