#pragma once
#include "EdgeCommon/CommonMacros.h"
#include "EdgeCommon/Assert/AssertCore.h"

namespace Edge
{
#pragma region Matrix2x2Base
	template <typename T>
	Matrix2x2Base<T>& Matrix2x2Base<T>::operator=(const Matrix2x2Base& matrix)
	{
		m_row1 = matrix.m_row1;
		m_row2 = matrix.m_row2;

		return *this;
	}

	template <typename T>
	typename Matrix2x2Base<T>::RowVectorType Matrix2x2Base<T>::operator[](size_t index) const
	{
		EDGE_ASSERT(index < 2);
		return m_rows[index];
	}

	template <typename T>
	typename Matrix2x2Base<T>::RowVectorType& Matrix2x2Base<T>::operator[](size_t index)
	{
		EDGE_ASSERT(index < 2);
		return m_rows[index];
	}

	template <typename T>
	typename Matrix2x2Base<T>::RowVectorType Matrix2x2Base<T>::getRow(size_t index) const
	{
		return operator[](index);
	}

	template <typename T>
	typename Matrix2x2Base<T>::RowVectorType& Matrix2x2Base<T>::getRow(size_t index)
	{
		return operator[](index);
	}

	template <typename T>
	typename Matrix2x2Base<T>::RowVectorType Matrix2x2Base<T>::getElement(size_t row, size_t column) const
	{
		EDGE_ASSERT(row < 2 && column < 2);
		return m_values[row * 2 + column];
	}

	template <typename T>
	typename Matrix2x2Base<T>::RowVectorType& Matrix2x2Base<T>::getElement(size_t row, size_t column)
	{
		EDGE_ASSERT(row < 2 && column < 2);
		return m_values[row * 2 + column];
	}

	template <typename T>
	void Matrix2x2Base<T>::setElement(size_t row, size_t column, ValueType value)
	{
		getElement(row, column) = value;
	}

#pragma endregion

#pragma region Matrix3x3Base
	template <typename T>
	Matrix3x3Base<T>& Matrix3x3Base<T>::operator=(const Matrix2x2Base<ValueType>& matrix)
	{
		m_row1 = matrix.m_row1;
		m_row2 = matrix.m_row2;
		m_row3 = RowVectorType(DefaultValue);

		return *this;
	}

	template <typename T>
	Matrix3x3Base<T>& Matrix3x3Base<T>::operator=(const Matrix3x3Base& matrix)
	{
		m_row1 = matrix.m_row1;
		m_row2 = matrix.m_row2;
		m_row3 = matrix.m_row3;

		return *this;
	}

	template <typename T>
	typename Matrix3x3Base<T>::RowVectorType Matrix3x3Base<T>::operator[](size_t index) const
	{
		EDGE_ASSERT(index < 3);
		return m_rows[index];
	}

	template <typename T>
	typename Matrix3x3Base<T>::RowVectorType& Matrix3x3Base<T>::operator[](size_t index)
	{
		EDGE_ASSERT(index < 3);
		return m_rows[index];
	}

	template <typename T>
	typename Matrix3x3Base<T>::RowVectorType Matrix3x3Base<T>::getRow(size_t index) const
	{
		return operator[](index);
	}

	template <typename T>
	typename Matrix3x3Base<T>::RowVectorType& Matrix3x3Base<T>::getRow(size_t index)
	{
		return operator[](index);
	}

	template <typename T>
	typename Matrix3x3Base<T>::RowVectorType Matrix3x3Base<T>::getElement(size_t row, size_t column) const
	{
		EDGE_ASSERT(row < 3 && column < 3);
		return m_values[row * 3 + column];
	}

	template <typename T>
	typename Matrix3x3Base<T>::RowVectorType& Matrix3x3Base<T>::getElement(size_t row, size_t column)
	{
		EDGE_ASSERT(row < 3 && column < 3);
		return m_values[row * 3 + column];
	}

	template <typename T>
	void Matrix3x3Base<T>::setElement(size_t row, size_t column, ValueType value)
	{
		getElement(row, column) = value;
	}
#pragma endregion

#pragma region Matrix4x4Base
	template <typename T>
	Matrix4x4Base<T>& Matrix4x4Base<T>::operator=(const Matrix2x2Base<ValueType>& matrix)
	{
		m_row1 = matrix.m_row1;
		m_row2 = matrix.m_row2;
		m_row3 = RowVectorType(DefaultValue);
		m_row4 = RowVectorType(DefaultValue);

		return *this;
	}

	template <typename T>
	Matrix4x4Base<T>& Matrix4x4Base<T>::operator=(const Matrix3x3Base<ValueType>& matrix)
	{
		m_row1 = matrix.m_row1;
		m_row2 = matrix.m_row2;
		m_row3 = matrix.m_row3;
		m_row4 = RowVectorType(DefaultValue);

		return *this;
	}

	template <typename T>
	Matrix4x4Base<T>& Matrix4x4Base<T>::operator=(const Matrix4x4Base& matrix)
	{
		m_row1 = matrix.m_row1;
		m_row2 = matrix.m_row2;
		m_row3 = matrix.m_row3;
		m_row4 = matrix.m_row4;

		return *this;
	}

	template <typename T>
	typename Matrix4x4Base<T>::RowVectorType Matrix4x4Base<T>::operator[](size_t index) const
	{
		EDGE_ASSERT(index < 4);
		return m_rows[index];
	}

	template <typename T>
	typename Matrix4x4Base<T>::RowVectorType& Matrix4x4Base<T>::operator[](size_t index)
	{
		EDGE_ASSERT(index < 4);
		return m_rows[index];
	}

	template <typename T>
	typename Matrix4x4Base<T>::RowVectorType Matrix4x4Base<T>::getRow(size_t index) const
	{
		return operator[](index);
	}

	template <typename T>
	typename Matrix4x4Base<T>::RowVectorType& Matrix4x4Base<T>::getRow(size_t index)
	{
		return operator[](index);
	}

	template <typename T>
	typename Matrix4x4Base<T>::RowVectorType Matrix4x4Base<T>::getElement(size_t row, size_t column) const
	{
		EDGE_ASSERT(row < 4 && column < 4);
		return m_values[row * 4 + column];
	}

	template <typename T>
	typename Matrix4x4Base<T>::RowVectorType& Matrix4x4Base<T>::getElement(size_t row, size_t column)
	{
		EDGE_ASSERT(row < 4 && column < 4);
		return m_values[row * 4 + column];
	}

	template <typename T>
	void Matrix4x4Base<T>::setElement(size_t row, size_t column, ValueType value)
	{
		getElement(row, column) = value;
	}
#pragma endregion
}
