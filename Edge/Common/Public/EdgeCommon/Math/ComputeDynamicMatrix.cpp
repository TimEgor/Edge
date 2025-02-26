#include "ComputeDynamicMatrix.h"

void Edge::TransposeDynamicMatrix(const FloatDynamicMatrix& matrix, FloatDynamicMatrix& result)
{
	result = TransposeDynamicMatrix(matrix);
}

Edge::FloatDynamicMatrix Edge::TransposeDynamicMatrix(const FloatDynamicMatrix& matrix)
{
	const uint32_t rowCount = matrix.getRowCount();
	const uint32_t columnCount = matrix.getColumnCount();

	FloatDynamicMatrix result = FloatDynamicMatrix(columnCount, rowCount);

	for (uint32_t rowIndex = 0; rowIndex < rowCount; ++rowIndex)
	{
		for (uint32_t columnIndex = 0; columnIndex < columnCount; ++columnIndex)
		{
			result.setElement(columnIndex, rowIndex, matrix.getElement(rowIndex, columnIndex));
		}
	}

	return result;
}

void Edge::MultiplyDynamicMatrix(const FloatDynamicMatrix& matrix1, const FloatDynamicMatrix& matrix2, FloatDynamicMatrix& result)
{
	result = MultiplyDynamicMatrix(matrix1, matrix2);
}

Edge::FloatDynamicMatrix Edge::MultiplyDynamicMatrix(const FloatDynamicMatrix& matrix1, const FloatDynamicMatrix& matrix2)
{
	const uint32_t rowCount1 = matrix1.getRowCount();
	const uint32_t columnCount1 = matrix1.getColumnCount();

	const uint32_t rowCount2 = matrix2.getRowCount();
	const uint32_t columnCount2 = matrix2.getColumnCount();

	EDGE_ASSERT(columnCount1 == rowCount2);

	FloatDynamicMatrix result = FloatDynamicMatrix(rowCount1, columnCount2);

	for (uint32_t rowIndex = 0; rowIndex < rowCount1; ++rowIndex)
	{
		for (uint32_t columnIndex = 0; columnIndex < columnCount2; ++columnIndex)
		{
			float value = 0.0f;

			for (uint32_t elementIndex = 0; elementIndex < columnCount1; ++elementIndex)
			{
				value += matrix1.getElement(rowIndex, elementIndex) * matrix2.getElement(elementIndex, columnIndex);
			}

			result.setElement(rowIndex, columnIndex, value);
		}
	}

	return result;
}

void Edge::TransformDynamicVector(const FloatDynamicMatrix& matrix, const FloatDynamicVector& vector, FloatDynamicVector& result)
{
	result = TransformDynamicVector(matrix, vector);
}

Edge::FloatDynamicVector Edge::TransformDynamicVector(const FloatDynamicMatrix& matrix, const FloatDynamicVector& vector)
{
	const uint32_t rowCount = matrix.getRowCount();
	const uint32_t columnCount = matrix.getColumnCount();

	EDGE_ASSERT(vector.getElementCount() == columnCount);

	FloatDynamicVector result = FloatDynamicVector(rowCount);

	for (uint32_t rowIndex = 0; rowIndex < rowCount; ++rowIndex)
	{
		float value = 0.0f;

		for (uint32_t columnIndex = 0; columnIndex < columnCount; ++columnIndex)
		{
			value += matrix.getElement(rowIndex, columnIndex) * vector.getElement(columnIndex);
		}

		result.setElement(rowIndex, value);
	}

	return result;
}

void Edge::DynamicMatrixAddDiagonal(FloatDynamicMatrix& matrix, float value)
{
	const uint32_t rowCount = matrix.getRowCount();
	const uint32_t columnCount = matrix.getColumnCount();

	EDGE_ASSERT(rowCount == columnCount);

	for (uint32_t elementIndex = 0; elementIndex < rowCount; ++elementIndex)
	{
		matrix[elementIndex][elementIndex] += value;
	}
}
