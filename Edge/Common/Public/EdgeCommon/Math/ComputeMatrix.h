#pragma once

#include "ComputeVector.h"
#include "ComputeMath/ComputeMatrix.h"

namespace Edge
{
	class ComputeQuaternion;

	class ComputeMatrix final
	{
	public:
		ComputeMath::Matrix m_matrix;

		ComputeMatrix() = default;
		ComputeMatrix(const ComputeMath::Matrix& matrix);
		ComputeMatrix(const FloatMatrix2x2& matrix);
		ComputeMatrix(const FloatMatrix3x3& matrix);
		ComputeMatrix(const FloatMatrix4x4& matrix);
		ComputeMatrix(const ComputeMatrix& matrix) = default;

		void setupFromRotationQuaternion(const ComputeQuaternion& quaternion);

		ComputeMatrix& operator=(const ComputeMatrix& matrix) = default;

		ComputeMatrix& operator*=(const ComputeMatrix& matrix);

		ComputeMatrix& transpose();
		ComputeMatrix& inverse();

		void loadFromMatrix2x2(const FloatMatrix2x2& matrix);
		void loadFromMatrix3x3(const FloatMatrix3x3& matrix);
		void loadFromMatrix4x4(const FloatMatrix4x4& matrix);

		void saveToMatrix2x2(FloatMatrix2x2& matrix) const;
		void saveToMatrix3x3(FloatMatrix3x3& matrix) const;
		void saveToMatrix4x4(FloatMatrix4x4& matrix) const;

		FloatMatrix2x2 getToMatrix2x2() const;
		FloatMatrix3x3 getToMatrix3x3() const;
		FloatMatrix4x4 getToMatrix4x4() const;
	};

	ComputeMatrix ComputeMatrixFromRotationQuaternion(const ComputeQuaternion& quaternion);
	void GetAnglesFromRotationMatrix(const ComputeMatrix& rotationMatrix, float& pitch, float& yaw, float& roll);

	ComputeMatrix operator*(const ComputeMatrix& matrix1, const ComputeMatrix& matrix2);
	ComputeVector operator*(const ComputeMatrix& matrix, const ComputeVector& vector);

	ComputeMatrix TransposeMatrix(const ComputeMatrix& matrix);
	ComputeMatrix InverseMatrix(const ComputeMatrix& matrix);
}
