#pragma once

#include "EdgeCommon/CommonMacros.h"
#include "EdgeCommon/Assert/AssertCore.h"

namespace Edge
{
#pragma region DynamicMatrixBase
	template <typename T>
	DynamicMatrixBase<T>::DynamicMatrixBase(size_t dimensionRow, size_t dimensionColumn)
	{
		EDGE_ASSERT(dimensionRow > 0);
		EDGE_ASSERT(dimensionColumn > 0);

		m_values = std::vector<RowType>(dimensionRow);

		for (size_t rowIndex = 0; rowIndex < dimensionRow; ++rowIndex)
		{
			m_values[rowIndex] = RowType(dimensionColumn);
		}

		reset();
	}

	template <typename T>
	DynamicMatrixBase<T>::DynamicMatrixBase(RowContainer&& values)
		: m_values(std::move(values))
	{
		const size_t rowCount = m_values.size();
		EDGE_ASSERT(rowCount > 0);

		const size_t columnCheckSize = m_values[0].getElementCount();

		for (size_t rowIndex = 1; rowIndex < rowCount; ++rowIndex)
		{
			EDGE_ASSERT(columnCheckSize == m_values[rowIndex].getElementCount());
		}
	}


	template <typename T>
	DynamicMatrixBase<T>::DynamicMatrixBase(const DynamicMatrixBase& matrix)
		: m_values(matrix.m_values)
	{
	}

	template <typename T>
	DynamicMatrixBase<T>::DynamicMatrixBase(DynamicMatrixBase&& matrix)
		: m_values(std::move(matrix.m_values))
	{
	}

	template <typename T>
	DynamicMatrixBase<T>& DynamicMatrixBase<T>::operator=(const DynamicMatrixBase& matrix)
	{
		m_values = matrix.m_values;
		return *this;
	}

	template <typename T>
	DynamicMatrixBase<T>& DynamicMatrixBase<T>::operator=(DynamicMatrixBase&& matrix)
	{
		m_values = std::move(matrix.m_values);
		return *this;
	}

	template <typename T>
	const typename DynamicMatrixBase<T>::RowType& DynamicMatrixBase<T>::operator[](size_t index) const
	{
		return getRow(index);
	}

	template <typename T>
	typename DynamicMatrixBase<T>::RowType& DynamicMatrixBase<T>::operator[](size_t index)
	{
		return getRow(index);
	}


	template <typename T>
	const typename DynamicMatrixBase<T>::RowType& DynamicMatrixBase<T>::getRow(size_t index) const
	{
		//EDGE_ASSERT(index < m_values.size());
		return m_values[index];
	}

	template <typename T>
	typename DynamicMatrixBase<T>::RowType& DynamicMatrixBase<T>::getRow(size_t index)
	{
		//EDGE_ASSERT(index < m_values.size());
		return m_values[index];
	}

	template <typename T>
	const typename DynamicMatrixBase<T>::ValueType& DynamicMatrixBase<T>::getElement(size_t row, size_t column) const
	{
		//EDGE_ASSERT(row < m_values.size());
		//EDGE_ASSERT(column < m_values[row].size());
		return m_values[row][column];
	}

	template <typename T>
	typename DynamicMatrixBase<T>::ValueType& DynamicMatrixBase<T>::getElement(size_t row, size_t column)
	{
		//EDGE_ASSERT(row < m_values.size());
		//EDGE_ASSERT(column < m_values[row].size());
		return m_values[row][column];
	}

	template <typename T>
	void DynamicMatrixBase<T>::setElement(size_t row, size_t column, ValueType value)
	{
		//EDGE_ASSERT(row < m_values.size());
		//EDGE_ASSERT(column < m_values[row].size());
		m_values[row][column] = value;
	}

	template <typename T>
	void DynamicMatrixBase<T>::reset()
	{
		const size_t rows = m_values.size();
		for (size_t rowIndex = 0; rowIndex < rows; ++rowIndex)
		{
			m_values[rowIndex].reset();
		}
	}

	template <typename T>
	uint32_t DynamicMatrixBase<T>::getRowCount() const
	{
		return m_values.size();
	}

	template <typename T>
	uint32_t DynamicMatrixBase<T>::getColumnCount() const
	{
		return m_values.empty() ? 0 : m_values[0].getElementCount();
	}

#pragma endregion
}
