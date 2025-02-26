#include "Transform.h"

Edge::FloatMatrix3x3 Edge::Transform::getRotationMatrix() const
{
	FloatMatrix3x3 rotation;
	getRotationMatrix(rotation);

	return rotation;
}

void Edge::Transform::getRotationMatrix(FloatMatrix3x3& rotation) const
{
	rotation.m_row1 = getAxisX();
	rotation.m_row2 = getAxisY();
	rotation.m_row3 = getAxisZ();
}

Edge::ComputeMatrix Edge::Transform::getRotationComputeMatrix() const
{
	ComputeMatrix matrix;
	getRotationComputeMatrix(matrix);

	return matrix;
}

void Edge::Transform::getRotationComputeMatrix(ComputeMatrix& rotation) const
{
	FloatMatrix3x3 rotationMatrix;
	getRotationMatrix(rotationMatrix);

	rotation = rotationMatrix;
}

void Edge::Transform::setRotationMatrix(const FloatMatrix3x3& rotation)
{
	m_matrix.m_row1.m_xyz = rotation.m_row1;
	m_matrix.m_row2.m_xyz = rotation.m_row2;
	m_matrix.m_row3.m_xyz = rotation.m_row3;
}

Edge::FloatQuaternion Edge::Transform::getRotationQuaternion() const
{
	FloatQuaternion quaternion;
	getRotationQuaternion(quaternion);

	return quaternion;
}

void Edge::Transform::getRotationQuaternion(FloatQuaternion& rotation) const
{
	ComputeQuaternion quaternion;
	getRotationComputeQuaternion(quaternion);
	quaternion.saveToFloatQuaternion(rotation);
}

Edge::ComputeQuaternion Edge::Transform::getRotationComputeQuaternion() const
{
	ComputeQuaternion quaternion;
	getRotationComputeQuaternion(quaternion);

	return quaternion;
}

void Edge::Transform::getRotationComputeQuaternion(ComputeQuaternion& rotation) const
{
	ComputeMatrix rotationMatrix;
	getRotationComputeMatrix(rotationMatrix);
	rotation = ComputeQuaternionFromRotationMatrix(rotationMatrix);
}

void Edge::Transform::setRotationQuaternion(const FloatQuaternion& rotation)
{
	setRotationMatrix(ComputeMatrixFromRotationQuaternion(rotation).getMatrix3x3());
}
