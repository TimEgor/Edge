#include "ComputeMatrix.h"

#include "ComputeQuaternion.h"

Edge::ComputeMatrix::ComputeMatrix(const ComputeMath::Matrix& matrix) : m_matrix(matrix) {}

Edge::ComputeMatrix::ComputeMatrix(const FloatMatrix2x2& matrix)
{
	loadFromMatrix2x2(matrix);
}

Edge::ComputeMatrix::ComputeMatrix(const FloatMatrix3x3& matrix)
{
	loadFromMatrix3x3(matrix);
}

Edge::ComputeMatrix::ComputeMatrix(const FloatMatrix4x4& matrix)
{
	loadFromMatrix4x4(matrix);
}

void Edge::ComputeMatrix::setupFromRotationQuaternion(const ComputeQuaternion& quaternion)
{
	m_matrix = ComputeMath::matrixRotationQuaternion(quaternion.m_quaternion);
}

Edge::ComputeMatrix& Edge::ComputeMatrix::operator*=(const ComputeMatrix& matrix)
{
	m_matrix = ComputeMath::matrixMultiply(m_matrix, matrix.m_matrix);
	return *this;
}

Edge::ComputeMatrix& Edge::ComputeMatrix::operator+=(const ComputeMatrix& matrix)
{
	m_matrix = ComputeMath::matrixSum(m_matrix, matrix.m_matrix);
	return *this;
}

Edge::ComputeMatrix& Edge::ComputeMatrix::transpose()
{
	m_matrix = ComputeMath::matrixTranspose(m_matrix);
	return *this;
}

Edge::ComputeMatrix& Edge::ComputeMatrix::inverse()
{
	m_matrix = ComputeMath::matrixInverse(m_matrix);
	return *this;
}

void Edge::ComputeMatrix::setElement(uint32_t i, uint32_t j, float val)
{
	ComputeMath::matrixSetElement(m_matrix, i, j, val);
}

void Edge::ComputeMatrix::loadFromMatrix2x2(const FloatMatrix2x2& matrix)
{
	m_matrix = ComputeMath::matrix2x2Load(matrix);
}

void Edge::ComputeMatrix::loadFromMatrix3x3(const FloatMatrix3x3& matrix)
{
	m_matrix = ComputeMath::matrix3x3Load(matrix);
}

void Edge::ComputeMatrix::loadFromMatrix4x4(const FloatMatrix4x4& matrix)
{
	m_matrix = ComputeMath::matrix4x4Load(matrix);
}

void Edge::ComputeMatrix::saveToMatrix2x2(FloatMatrix2x2& matrix) const
{
	ComputeMath::matrix2x2Save(m_matrix, matrix);
}

void Edge::ComputeMatrix::saveToMatrix3x3(FloatMatrix3x3& matrix) const
{
	ComputeMath::matrix3x3Save(m_matrix, matrix);
}

void Edge::ComputeMatrix::saveToMatrix4x4(FloatMatrix4x4& matrix) const
{
	ComputeMath::matrix4x4Save(m_matrix, matrix);
}

Edge::FloatMatrix2x2 Edge::ComputeMatrix::getToMatrix2x2() const
{
	return ComputeMath::matrix2x2Save(m_matrix);;
}

Edge::FloatMatrix3x3 Edge::ComputeMatrix::getToMatrix3x3() const
{
	return ComputeMath::matrix3x3Save(m_matrix);
}

Edge::FloatMatrix4x4 Edge::ComputeMatrix::getToMatrix4x4() const
{
	return ComputeMath::matrix4x4Save(m_matrix);
}

Edge::FloatMatrix3x3 Edge::ComputeSkewSymmetricMatrix3x3ForCrossProduct(const FloatVector3& vector)
{
	return FloatMatrix3x3(
		0.0f, -vector.m_z, vector.m_y,
		vector.m_z, 0.0f, -vector.m_x,
		-vector.m_y, vector.m_x, 0.0);
}

Edge::FloatMatrix4x4 Edge::ComputeSkewSymmetricMatrix4x4ForCrossProduct(const FloatVector3& vector)
{
	return FloatMatrix4x4(
		0.0f, -vector.m_z, vector.m_y, 0.0f,
		vector.m_z, 0.0f, -vector.m_x, 0.0f,
		-vector.m_y, vector.m_x, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f);
}

Edge::ComputeMatrix Edge::ComputeMatrixFromRotationQuaternion(const ComputeQuaternion& quaternion)
{
	return ComputeMath::matrixRotationQuaternion(quaternion.m_quaternion);
}

Edge::ComputeMatrix Edge::ComputeMatrixFromScale(float scale)
{
	return ComputeMath::matrixScaling(scale, scale, scale);
}

Edge::ComputeMatrix Edge::ComputeMatrixFromScale(const FloatVector3& scale)
{
	return ComputeMath::matrixScaling(scale);
}

void Edge::GetAnglesFromRotationMatrix(const ComputeMatrix& rotationMatrix, float& pitch, float& yaw, float& roll)
{
	ComputeMath::anglesFromMatrixRotation(rotationMatrix.m_matrix, pitch, yaw, roll);
}

Edge::ComputeVector Edge::TransformVector(const ComputeMatrix& matrix, const ComputeVector& vector)
{
	return matrix * vector;
}

Edge::ComputeMatrix Edge::operator*(const ComputeMatrix& matrix1, const ComputeMatrix& matrix2)
{
	ComputeMatrix result(matrix1);
	return result *= matrix2;
}

Edge::ComputeVector Edge::operator*(const ComputeMatrix& matrix, const ComputeVector& vector)
{
	return ComputeMath::transformVector(vector.m_vector, matrix.m_matrix);
}

Edge::ComputeMatrix Edge::operator+(const ComputeMatrix& matrix1, const ComputeMatrix& matrix2)
{
	ComputeMatrix result(matrix1);
	return result += matrix2;
}

Edge::ComputeMatrix Edge::TransposeMatrix(const ComputeMatrix& matrix)
{
	return ComputeMath::matrixTranspose(matrix.m_matrix);
}

Edge::ComputeMatrix Edge::InverseMatrix(const ComputeMatrix& matrix)
{
	return ComputeMath::matrixInverse(matrix.m_matrix);
}
