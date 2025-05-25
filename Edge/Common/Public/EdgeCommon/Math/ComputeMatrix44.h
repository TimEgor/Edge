#pragma once

#include "ComputeMatrix33.h"
#include "ComputeVector4.h"
#include "Matrix.h"

namespace Edge
{
	template <typename T>
	class ComputeMatrix4x4Base final
	{
	public:
		using ValueType = T;
		static_assert(std::is_arithmetic_v<ValueType>);

		using MatrixType = Matrix4x4Base<ValueType>;

	private:
		union
		{
			MatrixType m_matrix; // store values in a transposed form (column-major)

			ComputeVector4Base<ValueType> m_columns[4];

			struct
			{
				ComputeVector4Base<ValueType> m_column1;
				ComputeVector4Base<ValueType> m_column2;
				ComputeVector4Base<ValueType> m_column3;
				ComputeVector4Base<ValueType> m_column4;
			};
		};

	public:
		constexpr ComputeMatrix4x4Base()
			: m_matrix()
		{}
		constexpr ComputeMatrix4x4Base(
			ValueType m11, ValueType m12, ValueType m13, ValueType m14,
			ValueType m21, ValueType m22, ValueType m23, ValueType m24,
			ValueType m31, ValueType m32, ValueType m33, ValueType m34,
			ValueType m41, ValueType m42, ValueType m43, ValueType m44
		)
			: m_matrix(
				m11, m12, m13, m14,
				m21, m22, m23, m24,
				m31, m32, m33, m34,
				m41, m42, m43, m44
			)
		{}

		constexpr ComputeMatrix4x4Base(const MatrixType& matrix)
			: m_matrix(matrix) {}

		constexpr ComputeMatrix4x4Base(
			const ComputeVector4Base<ValueType>& column1,
			const ComputeVector4Base<ValueType>& column2,
			const ComputeVector4Base<ValueType>& column3,
			const ComputeVector4Base<ValueType>& column4
		)
			: m_column1(column1),
			m_column2(column2),
			m_column3(column3),
			m_column4(column4)
		{}

		constexpr ComputeMatrix4x4Base(const ComputeMatrix2x2Base<ValueType>& matrix)
			: m_column1(matrix.getColumn(0)),
			m_column2(matrix.getColumn(1)),
			m_column3(ValueType(0.0)),
			m_column4(ValueType(0.0))
		{}

		constexpr ComputeMatrix4x4Base(const ComputeMatrix3x3Base<ValueType>& matrix)
			: m_column1(matrix.getColumn(0)),
			m_column2(matrix.getColumn(1)),
			m_column3(matrix.getColumn(2)),
			m_column4(ValueType(0.0))
		{}

		constexpr ComputeMatrix4x4Base(const ComputeMatrix4x4Base& matrix)
			: m_matrix(matrix.m_matrix)
		{}

		ComputeMatrix4x4Base& operator=(const ComputeMatrix4x4Base& matrix);

		ComputeMatrix4x4Base& operator+=(const ComputeMatrix4x4Base& matrix);
		ComputeMatrix4x4Base& operator-=(const ComputeMatrix4x4Base& matrix);
		ComputeMatrix4x4Base& operator*=(const ComputeMatrix4x4Base& matrix);
		ComputeMatrix4x4Base& operator*=(ValueType value);
		ComputeMatrix4x4Base& operator/=(ValueType value);

		bool operator==(const ComputeMatrix4x4Base& matrix) const;
		bool operator!=(const ComputeMatrix4x4Base& matrix) const;

		FloatMatrix4x4 getFloatMatrix4x4() const;
		void getFloatMatrix4x4(FloatMatrix4x4& out) const { out = m_matrix; }

		ValueType getElement(uint32_t row, uint32_t column) const { return m_matrix.getElement(column, row); }
		ValueType& getElement(uint32_t row, uint32_t column) { return m_matrix.getElement(column, row); }
		void setElement(uint32_t row, uint32_t column, ValueType value) { return m_matrix.setElement(column, row, value); }

		const ComputeVector4Base<ValueType>& getColumn(uint32_t index) const;
		ComputeVector4Base<ValueType> getRow(uint32_t index) const;
		ComputeVector4Base<ValueType>& getColumn(uint32_t index);

		void setColumn(uint32_t index, const ComputeVector4Base<ValueType>& column);
		void setRow(uint32_t index, const ComputeVector4Base<ValueType>& row);

		ComputeMatrix4x4Base& negate();

		ComputeMatrix4x4Base& transpose();

		ValueType getDeterminant() const;
		ComputeMatrix4x4Base& invert();

		ComputeVector4Base<ValueType> transform(const ComputeVector4Base<ValueType>& vector) const;
		void transform(const ComputeVector4Base<ValueType>& vector, ComputeVector4Base<ValueType>& out) const;

		bool isEqual(const ComputeMatrix4x4Base& matrix, ValueType epsilon = Math::TypedEpsilon<ValueType>()) const;
	};

	template <typename T>
	ComputeMatrix4x4Base<T> operator+(const ComputeMatrix4x4Base<T>& matrix1, const ComputeMatrix4x4Base<T>& matrix2);
	template <typename T>
	ComputeMatrix4x4Base<T> operator-(const ComputeMatrix4x4Base<T>& matrix1, const ComputeMatrix4x4Base<T>& matrix2);
	template <typename T>
	ComputeMatrix4x4Base<T> operator-(const ComputeMatrix4x4Base<T>& matrix);
	template <typename T>
	ComputeMatrix4x4Base<T> operator*(const ComputeMatrix4x4Base<T>& matrix1, const ComputeMatrix4x4Base<T>& matrix2);
	template <typename T>
	ComputeMatrix4x4Base<T> operator*(const ComputeMatrix4x4Base<T>& matrix, T value);
	template <typename T>
	ComputeMatrix4x4Base<T> operator*(T value, const ComputeMatrix4x4Base<T>& matrix);
	template <typename T>
	ComputeMatrix4x4Base<T> operator/(const ComputeMatrix4x4Base<T>& matrix, T value);
	template <typename T>
	ComputeMatrix4x4Base<T> operator/(T value, const ComputeMatrix4x4Base<T>& matrix);

	template <typename T>
	ComputeVector4Base<T> operator*(const ComputeMatrix4x4Base<T>& matrix, const ComputeVector4Base<T>& vector);

	template <typename T>
	ComputeMatrix4x4Base<T> CrossProductSkewSymmetricComputeMatrix4x4(const ComputeVector4Base<T>& vector);
	template <typename T>
	ComputeMatrix4x4Base<T> TranslationComputeMatrix4x4(const ComputeVector3Base<T>& vector);
	template <typename T>
	ComputeMatrix4x4Base<T> RotationEulerComputeMatrix4x4(const ComputeVector3Base<T>& vector);
	template <typename T>
	ComputeMatrix4x4Base<T> RotationEulerComputeMatrix4x4(T pitch, T yaw, T roll);
	template <typename T>
	ComputeMatrix4x4Base<T> ScaleComputeMatrix4x4(const ComputeVector3Base<T>& scale);

	template <typename T>
	ComputeMatrix4x4Base<T> InvertComputeMatrix4x4(const ComputeMatrix4x4Base<T>& matrix);

	template <typename T>
	constexpr ComputeMatrix4x4Base<T> ComputeMatrix4x4ZeroBase() {
		return ComputeMatrix4x4Base<T>(
			T(0.0), T(0.0), T(0.0), T(0.0),
			T(0.0), T(0.0), T(0.0), T(0.0),
			T(0.0), T(0.0), T(0.0), T(0.0),
			T(0.0), T(0.0), T(0.0), T(0.0)
		);
	}

	template <typename T>
	constexpr ComputeMatrix4x4Base<T> ComputeMatrix4x4IdentityBase() {
		return ComputeMatrix4x4Base<T>(
			T(1.0), T(0.0), T(0.0), T(0.0),
			T(0.0), T(1.0), T(0.0), T(0.0),
			T(0.0), T(0.0), T(1.0), T(0.0),
			T(0.0), T(0.0), T(0.0), T(1.0)
		);
	}

	template <typename T>
	constexpr ComputeMatrix4x4Base<T> ComputeMatrix4x4ZeroIdentityBase() {
		return ComputeMatrix4x4Base<T>(
			T(0.0), T(0.0), T(0.0), T(0.0),
			T(0.0), T(0.0), T(0.0), T(0.0),
			T(0.0), T(0.0), T(0.0), T(0.0),
			T(0.0), T(0.0), T(0.0), T(1.0)
		);
	}

	using ComputeMatrix4x4 = ComputeMatrix4x4Base<ComputeValueType>;
	using FloatComputeMatrix4x4 = ComputeMatrix4x4Base<float>;

	inline constexpr ComputeMatrix4x4 ComputeMatrix4x4Zero = ComputeMatrix4x4ZeroBase<ComputeValueType>();
	inline constexpr ComputeMatrix4x4 ComputeMatrix4x4Identity = ComputeMatrix4x4IdentityBase<ComputeValueType>();
	inline constexpr ComputeMatrix4x4 ComputeMatrix4x4ZeroIdentity = ComputeMatrix4x4ZeroIdentityBase<ComputeValueType>();

	inline constexpr FloatComputeMatrix4x4 FloatComputeMatrix4x4Zero = ComputeMatrix4x4ZeroBase<float>();
	inline constexpr FloatComputeMatrix4x4 FloatComputeMatrix4x4Identity = ComputeMatrix4x4IdentityBase<float>();
	inline constexpr FloatComputeMatrix4x4 FloatComputeMatrix4x4ZeroIdentity = ComputeMatrix4x4ZeroIdentityBase<float>();
}

#include "ComputeMatrix44.hpp"