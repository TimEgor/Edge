#pragma once

#include "ComputeVector2.h"
#include "Matrix.h"

namespace Edge
{
	template <typename T>
	class ComputeMatrix2x2Base final
	{
	public:
		using ValueType = T;
		static_assert(std::is_arithmetic_v<ValueType>);

		using MatrixType = Matrix2x2Base<ValueType>;

	private:
		union
		{
			MatrixType m_matrix; // store values in a transposed form (column-major)

			ComputeVector2Base<ValueType> m_columns[2];

			struct
			{
				ComputeVector2Base<ValueType> m_column1;
				ComputeVector2Base<ValueType> m_column2;
			};
		};

	public:
		constexpr ComputeMatrix2x2Base()
			: m_matrix() {}
		constexpr ComputeMatrix2x2Base(
			ValueType m11, ValueType m12,
			ValueType m21, ValueType m22
		)
			: m_matrix(
				m11, m12,
				m21, m22
			)
		{}

		constexpr ComputeMatrix2x2Base(const MatrixType& matrix)
			: m_matrix(matrix) {}

		constexpr ComputeMatrix2x2Base(
			const ComputeVector2Base<ValueType>& column1,
			const ComputeVector2Base<ValueType>& column2
		)
			: m_column1(column1),
			m_column2(column2)
		{}

		constexpr ComputeMatrix2x2Base(const ComputeMatrix2x2Base& matrix)
			: m_matrix(matrix.m_matrix) {}

		ComputeMatrix2x2Base& operator=(const ComputeMatrix2x2Base& matrix);

		ComputeMatrix2x2Base& operator+=(const ComputeMatrix2x2Base& matrix);
		ComputeMatrix2x2Base& operator-=(const ComputeMatrix2x2Base& matrix);
		ComputeMatrix2x2Base& operator*=(const ComputeMatrix2x2Base& matrix);
		ComputeMatrix2x2Base& operator*=(ValueType value);
		ComputeMatrix2x2Base& operator/=(ValueType value);

		bool operator==(const ComputeMatrix2x2Base& matrix) const;
		bool operator!=(const ComputeMatrix2x2Base& matrix) const;

		FloatMatrix2x2 getFloatMatrix2x2() const;
		void getFloatMatrix2x2(FloatMatrix2x2& out) const { out = m_matrix; }

		ValueType getElement(uint32_t row, uint32_t column) const { return m_matrix.getElement(column, row); }
		ValueType& getElement(uint32_t row, uint32_t column) { return m_matrix.getElement(column, row); }
		void setElement(uint32_t row, uint32_t column, ValueType value) { return m_matrix.setElement(column, row, value); }

		const ComputeVector2Base<ValueType>& getColumn(uint32_t index) const;
		ComputeVector2Base<ValueType>& getColumn(uint32_t index);
		ComputeVector2Base<ValueType> getRow(uint32_t index) const;

		void setColumn(uint32_t index, const ComputeVector2Base<ValueType>& column);
		void setRow(uint32_t index, const ComputeVector2Base<ValueType>& row);

		ComputeMatrix2x2Base& negate();

		ComputeMatrix2x2Base& transpose();

		ValueType getDeterminant() const;
		ComputeMatrix2x2Base& invert();

		ComputeVector2Base<ValueType> transform(const ComputeVector2Base<ValueType>& vector) const;
		void transform(const ComputeVector2Base<ValueType>& vector, ComputeVector2Base<ValueType>& out) const;

		bool isEqual(const ComputeMatrix2x2Base& matrix, ValueType epsilon = Math::TypedEpsilon<ValueType>()) const;
	};

	template <typename T>
	ComputeMatrix2x2Base<T> operator+(const ComputeMatrix2x2Base<T>& matrix1, const ComputeMatrix2x2Base<T>& matrix2);
	template <typename T>
	ComputeMatrix2x2Base<T> operator-(const ComputeMatrix2x2Base<T>& matrix1, const ComputeMatrix2x2Base<T>& matrix2);
	template <typename T>
	ComputeMatrix2x2Base<T> operator-(const ComputeMatrix2x2Base<T>& matrix);
	template <typename T>
	ComputeMatrix2x2Base<T> operator*(const ComputeMatrix2x2Base<T>& matrix1, const ComputeMatrix2x2Base<T>& matrix2);
	template <typename T>
	ComputeMatrix2x2Base<T> operator*(const ComputeMatrix2x2Base<T>& matrix, T value);
	template <typename T>
	ComputeMatrix2x2Base<T> operator*(T value, const ComputeMatrix2x2Base<T>& matrix);
	template <typename T>
	ComputeMatrix2x2Base<T> operator/(const ComputeMatrix2x2Base<T>& matrix, T value);
	template <typename T>
	ComputeMatrix2x2Base<T> operator/(T value, const ComputeMatrix2x2Base<T>& matrix);

	template <typename T>
	ComputeVector2Base<T> operator*(const ComputeMatrix2x2Base<T>& matrix, const ComputeVector2Base<T>& vector);

	template <typename T>
	ComputeMatrix2x2Base<T> InvertComputeMatrix2x2(const ComputeMatrix2x2Base<T>& matrix);
	template <typename T>
	ComputeMatrix2x2Base<T> TransposeComputeMatrix2x2(const ComputeMatrix2x2Base<T>& matrix);

	template <typename T>
	constexpr ComputeMatrix2x2Base<T> ComputeMatrix2x2ZeroBase()
	{
		return ComputeMatrix2x2Base<T>(
			T(0.0), T(0.0),
			T(0.0), T(0.0)
		);
	}

	template <typename T>
	constexpr ComputeMatrix2x2Base<T> ComputeMatrix2x2IdentityBase()
	{
		return ComputeMatrix2x2Base<T>(
			T(1.0), T(0.0),
			T(0.0), T(1.0)
		);
	}

	using ComputeMatrix2x2 = ComputeMatrix2x2Base<ComputeValueType>;
	using FloatComputeMatrix2x2 = ComputeMatrix2x2Base<float>;

	constexpr ComputeMatrix2x2 ComputeMatrix2x2Zero = ComputeMatrix2x2ZeroBase<ComputeValueType>();
	constexpr ComputeMatrix2x2 ComputeMatrix2x2Identity = ComputeMatrix2x2IdentityBase<ComputeValueType>();

	constexpr FloatComputeMatrix2x2 FloatComputeMatrix2x2Zero = ComputeMatrix2x2ZeroBase<float>();
	constexpr FloatComputeMatrix2x2 FloatComputeMatrix2x2Identity = ComputeMatrix2x2IdentityBase<float>();
}

#include "ComputeMatrix22.hpp"