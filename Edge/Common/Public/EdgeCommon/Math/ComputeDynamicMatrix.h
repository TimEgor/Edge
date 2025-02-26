#pragma once

#include "DynamicMatrix.h"

namespace Edge
{
	void TransposeDynamicMatrix(const FloatDynamicMatrix& matrix, FloatDynamicMatrix& result);
	FloatDynamicMatrix TransposeDynamicMatrix(const FloatDynamicMatrix& matrix);

	void MultiplyDynamicMatrix(const FloatDynamicMatrix& matrix1, const FloatDynamicMatrix& matrix2, FloatDynamicMatrix& result);
	FloatDynamicMatrix MultiplyDynamicMatrix(const FloatDynamicMatrix& matrix1, const FloatDynamicMatrix& matrix2);

	void TransformDynamicVector(const FloatDynamicMatrix& matrix, const FloatDynamicVector& vector, FloatDynamicVector& result);
	FloatDynamicVector TransformDynamicVector(const FloatDynamicMatrix& matrix, const FloatDynamicVector& vector);

	void DynamicMatrixAddDiagonal(FloatDynamicMatrix& matrix, float value);
}
