#pragma once

#include "DynamicVector.h"

namespace Edge
{
	template <typename T>
	class DynamicMatrixBase final
	{
	public:
		using ValueType = T;
		using RowType = DynamicVectorBase<ValueType>;
		using RowContainer = std::vector<RowType>;

		static_assert(std::is_arithmetic_v<ValueType>);

		static constexpr ValueType DefaultValue = 0;

	private:
		RowContainer m_values;

	public:
		DynamicMatrixBase() = default;
		DynamicMatrixBase(size_t dimensionRow, size_t dimensionColumn);
		DynamicMatrixBase(RowContainer&& values);
		DynamicMatrixBase(const DynamicMatrixBase& matrix);
		DynamicMatrixBase(DynamicMatrixBase&& matrix);

		DynamicMatrixBase& operator=(const DynamicMatrixBase& matrix);
		DynamicMatrixBase& operator=(DynamicMatrixBase&& matrix);
		const RowType& operator[](size_t index) const;
		RowType& operator[](size_t index);

		const RowType& getRow(size_t index) const;
		RowType& getRow(size_t index);

		const ValueType& getElement(size_t row, size_t column) const;
		ValueType& getElement(size_t row, size_t column);

		void setElement(size_t row, size_t column, ValueType value);

		void reset();

		uint32_t getRowCount() const;
		uint32_t getColumnCount() const;
	};

	using FloatDynamicMatrix = DynamicMatrixBase<float>;
}

#include "DynamicMatrix.hpp"