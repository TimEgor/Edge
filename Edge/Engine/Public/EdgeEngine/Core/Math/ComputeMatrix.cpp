#include "ComputeMatrix.h"

#include "ComputeQuaternion.h"

TS::ComputeMatrix::ComputeMatrix(const ComputeMath::Matrix& matrix) : m_matrix(matrix) {}

TS::ComputeMatrix::ComputeMatrix(const FloatMatrix2x2& matrix)
{
	loadFromMatrix2x2(matrix);
}

TS::ComputeMatrix::ComputeMatrix(const FloatMatrix3x3& matrix)
{
	loadFromMatrix3x3(matrix);
}

TS::ComputeMatrix::ComputeMatrix(const FloatMatrix4x4& matrix)
{
	loadFromMatrix4x4(matrix);
}

void TS::ComputeMatrix::setupFromRotationQuaternion(const ComputeQuaternion& quaternion)
{
	m_matrix = ComputeMath::matrixRotationQuaternion(quaternion.m_quaternion);
}

TS::ComputeMatrix& TS::ComputeMatrix::operator*=(const ComputeMatrix& matrix)
{
	m_matrix = ComputeMath::matrixMultiply(m_matrix, matrix.m_matrix);
	return *this;
}

TS::ComputeMatrix& TS::ComputeMatrix::transpose()
{
	m_matrix = ComputeMath::matrixTranspose(m_matrix);
	return *this;
}

TS::ComputeMatrix& TS::ComputeMatrix::inverse()
{
	m_matrix = ComputeMath::matrixInverse(m_matrix);
	return *this;
}

void TS::ComputeMatrix::loadFromMatrix2x2(const FloatMatrix2x2& matrix)
{
	m_matrix = ComputeMath::loadMatrix2x2(matrix);
}

void TS::ComputeMatrix::loadFromMatrix3x3(const FloatMatrix3x3& matrix)
{
	m_matrix = ComputeMath::loadMatrix3x3(matrix);
}

void TS::ComputeMatrix::loadFromMatrix4x4(const FloatMatrix4x4& matrix)
{
	m_matrix = ComputeMath::loadMatrix4x4(matrix);
}

void TS::ComputeMatrix::saveToMatrix2x2(FloatMatrix2x2& matrix) const
{
	ComputeMath::saveMatrix2x2(m_matrix, matrix);
}

void TS::ComputeMatrix::saveToMatrix3x3(FloatMatrix3x3& matrix) const
{
	ComputeMath::saveMatrix3x3(m_matrix, matrix);
}

void TS::ComputeMatrix::saveToMatrix4x4(FloatMatrix4x4& matrix) const
{
	ComputeMath::saveMatrix4x4(m_matrix, matrix);
}

TS::FloatMatrix2x2 TS::ComputeMatrix::getToMatrix2x2() const
{
	return ComputeMath::saveMatrix2x2(m_matrix);;
}

TS::FloatMatrix3x3 TS::ComputeMatrix::getToMatrix3x3() const
{
	return ComputeMath::saveMatrix3x3(m_matrix);
}

TS::FloatMatrix4x4 TS::ComputeMatrix::getToMatrix4x4() const
{
	return ComputeMath::saveMatrix4x4(m_matrix);
}

TS::ComputeMatrix TS::computeMatrixFromRotationQuaternion(const ComputeQuaternion& quaternion)
{
	return ComputeMath::matrixRotationQuaternion(quaternion.m_quaternion);
}

TS::ComputeMatrix TS::operator*(const ComputeMatrix& matrix1, const ComputeMatrix& matrix2)
{
	ComputeMatrix result(matrix1);
	return result *= matrix2;
}

TS::ComputeVector TS::operator*(const ComputeMatrix& matrix, const ComputeVector& vector)
{
	return ComputeMath::transformVector(vector.m_vector, matrix.m_matrix);
}

TS::ComputeMatrix TS::transposeMatrix(const ComputeMatrix& matrix)
{
	return ComputeMath::matrixTranspose(matrix.m_matrix);
}

TS::ComputeMatrix TS::inverseMatrix(const ComputeMatrix& matrix)
{
	return ComputeMath::matrixInverse(matrix.m_matrix);
}
