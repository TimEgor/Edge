#pragma once

#include "ComputeMatrix22.h"
#include "ComputeVector3.h"

namespace Edge
{
	template <typename T>
	class ComputeMatrix3x3Base final
	{
	public:
		using ValueType = T;
		static_assert(std::is_arithmetic_v<ValueType>);

		using MatrixType = Matrix3x3Base<ValueType>;

	private:
		union
		{
			MatrixType m_matrix; // store values in a transposed form (column-major)

			ComputeVector3Base<ValueType> m_columns[3];

			struct
			{
				ComputeVector3Base<ValueType> m_column1;
				ComputeVector3Base<ValueType> m_column2;
				ComputeVector3Base<ValueType> m_column3;
			};
		};

	public:
		constexpr ComputeMatrix3x3Base()
			: m_matrix()
		{}
		constexpr ComputeMatrix3x3Base(
			ValueType m11, ValueType m12, ValueType m13,
			ValueType m21, ValueType m22, ValueType m23,
			ValueType m31, ValueType m32, ValueType m33
		)
			: m_matrix(
				m11, m12, m13,
				m21, m22, m23,
				m31, m32, m33
			)
		{}

		constexpr ComputeMatrix3x3Base(const MatrixType& matrix)
			: m_matrix(matrix) {}

		constexpr ComputeMatrix3x3Base(
			const ComputeVector3Base<ValueType>& column1,
			const ComputeVector3Base<ValueType>& column2,
			const ComputeVector3Base<ValueType>& column3
		)
			: m_column1(column1),
			m_column2(column2),
			m_column3(column3)
		{}

		constexpr ComputeMatrix3x3Base(const ComputeMatrix2x2Base<ValueType>& matrix)
			: m_column1(matrix.getColumn(0)),
			m_column2(matrix.getColumn(1)),
			m_column3(ValueType(0.0))
		{}

		constexpr ComputeMatrix3x3Base(const ComputeMatrix3x3Base& matrix)
			: m_matrix(matrix.m_matrix) {}

		ComputeMatrix3x3Base& operator=(const ComputeMatrix3x3Base& matrix);

		ComputeMatrix3x3Base& operator+=(const ComputeMatrix3x3Base& matrix);
		ComputeMatrix3x3Base& operator-=(const ComputeMatrix3x3Base& matrix);
		ComputeMatrix3x3Base& operator*=(const ComputeMatrix3x3Base& matrix);
		ComputeMatrix3x3Base& operator*=(ValueType value);
		ComputeMatrix3x3Base& operator/=(ValueType value);

		bool operator==(const ComputeMatrix3x3Base& matrix) const;
		bool operator!=(const ComputeMatrix3x3Base& matrix) const;

		FloatMatrix3x3 getFloatMatrix3x3() const;
		void getFloatMatrix3x3(FloatMatrix3x3& out) const { out = m_matrix; }

		ValueType getElement(uint32_t row, uint32_t column) const { return m_matrix.getElement(column, row); }
		ValueType& getElement(uint32_t row, uint32_t column) { return m_matrix.getElement(column, row); }
		void setElement(uint32_t row, uint32_t column, ValueType value) { return m_matrix.setElement(column, row, value); }

		const ComputeVector3Base<ValueType>& getColumn(uint32_t index) const;
		ComputeVector3Base<ValueType>& getColumn(uint32_t index);
		ComputeVector3Base<ValueType> getRow(uint32_t index) const;

		void setColumn(uint32_t index, const ComputeVector3Base<ValueType>& column);
		void setRow(uint32_t index, const ComputeVector3Base<ValueType>& row);

		ComputeMatrix3x3Base& negate();

		ComputeMatrix3x3Base& transpose();

		ValueType getDeterminant() const;
		ComputeMatrix3x3Base& invert();

		ComputeVector3Base<ValueType> transform(const ComputeVector3Base<ValueType>& vector) const;
		void transform(const ComputeVector3Base<ValueType>& vector, ComputeVector3Base<ValueType>& out) const;

		bool isEqual(const ComputeMatrix3x3Base& matrix, ValueType epsilon = Math::TypedEpsilon<ValueType>()) const;
	};

	template <typename T>
	ComputeMatrix3x3Base<T> operator+(const ComputeMatrix3x3Base<T>& matrix1, const ComputeMatrix3x3Base<T>& matrix2);
	template <typename T>
	ComputeMatrix3x3Base<T> operator-(const ComputeMatrix3x3Base<T>& matrix1, const ComputeMatrix3x3Base<T>& matrix2);
	template <typename T>
	ComputeMatrix3x3Base<T> operator-(const ComputeMatrix3x3Base<T>& matrix);
	template <typename T>
	ComputeMatrix3x3Base<T> operator*(const ComputeMatrix3x3Base<T>& matrix1, const ComputeMatrix3x3Base<T>& matrix2);
	template <typename T>
	ComputeMatrix3x3Base<T> operator*(const ComputeMatrix3x3Base<T>& matrix, T value);
	template <typename T>
	ComputeMatrix3x3Base<T> operator*(T value, const ComputeMatrix3x3Base<T>& matrix);
	template <typename T>
	ComputeMatrix3x3Base<T> operator/(const ComputeMatrix3x3Base<T>& matrix, T value);
	template <typename T>
	ComputeMatrix3x3Base<T> operator/(T value, const ComputeMatrix3x3Base<T>& matrix);

	template <typename T>
	ComputeVector3Base<T> operator*(const ComputeMatrix3x3Base<T>& matrix, const ComputeVector3Base<T>& vector);

	template <typename T>
	ComputeMatrix3x3Base<T> CrossProductSkewSymmetricComputeMatrix3x3(const ComputeVector3Base<T>& vector);
	template <typename T>
	ComputeMatrix3x3Base<T> RotationEulerComputeMatrix3x3(const ComputeVector3Base<T>& vector);
	template <typename T>
	ComputeMatrix3x3Base<T> RotationEulerComputeMatrix3x3(T roll, T pitch, T yaw);
	template <typename T>
	ComputeVector3Base<T> EulerAnglesFromRotationComputeMatrix3x3(const ComputeMatrix3x3Base<T>& rotation);
	template <typename T>
	ComputeMatrix3x3Base<T> ScaleComputeMatrix3x3(const ComputeVector3Base<T>& scale);

	template <typename T>
	ComputeMatrix3x3Base<T> InvertComputeMatrix3x3(const ComputeMatrix3x3Base<T>& matrix);
	template <typename T>
	ComputeMatrix3x3Base<T> TransposeComputeMatrix3x3(const ComputeMatrix3x3Base<T>& matrix);

	template <typename T>
	constexpr ComputeMatrix3x3Base<T> ComputeMatrix3x3ZeroBase() {
		return ComputeMatrix3x3Base<T>(
			T(0.0), T(0.0), T(0.0),
			T(0.0), T(0.0), T(0.0),
			T(0.0), T(0.0), T(0.0)
		);
	}

	template <typename T>
	constexpr ComputeMatrix3x3Base<T> ComputeMatrix3x3IdentityBase() {
		return ComputeMatrix3x3Base<T>(
			T(1.0), T(0.0), T(0.0),
			T(0.0), T(1.0), T(0.0),
			T(0.0), T(0.0), T(1.0)
		);
	}

	using ComputeMatrix3x3 = ComputeMatrix3x3Base<ComputeValueType>;
	using FloatComputeMatrix3x3 = ComputeMatrix3x3Base<float>;

	constexpr ComputeMatrix3x3 ComputeMatrix3x3Zero = ComputeMatrix3x3ZeroBase<ComputeValueType>();
	constexpr ComputeMatrix3x3 ComputeMatrix3x3Identity = ComputeMatrix3x3IdentityBase<ComputeValueType>();

	constexpr FloatComputeMatrix3x3 FloatComputeMatrix3x3Zero = ComputeMatrix3x3ZeroBase<float>();
	constexpr FloatComputeMatrix3x3 FloatComputeMatrix3x3Identity = ComputeMatrix3x3IdentityBase<float>();
}

#include "ComputeMatrix33.hpp"