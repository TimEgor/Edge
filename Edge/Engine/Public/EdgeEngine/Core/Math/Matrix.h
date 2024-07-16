#pragma once

#include "Vector.h"

namespace Edge
{
	template <typename T>
	struct Matrix2x2Base final
	{
		using ValueType = T;
		static_assert(std::is_arithmetic_v<ValueType>);

		static constexpr ValueType DefaultValue = 0;

		using RowVectorType = Vector2Base<ValueType>;

		union
		{
			ValueType m_values[2][2];

			struct
			{
				ValueType m_m11, m_m12;
				ValueType m_m21, m_m22;
			};

			RowVectorType m_rows[2];

			struct
			{
				RowVectorType m_row1;
				RowVectorType m_row2;
			};
		};

		constexpr Matrix2x2Base() = default;
		constexpr Matrix2x2Base(
			ValueType m11, ValueType m12,
			ValueType m21, ValueType m22)
			: m_m11(m11), m_m12(m12),
			m_m21(m21), m_m22(m22) {}

		constexpr Matrix2x2Base(const RowVectorType& row1, const RowVectorType& row2)
			: m_row1(row1), m_row2(row2) {}

		constexpr Matrix2x2Base(const Matrix2x2Base& matrix)
			: m_row1(matrix.m_row1), m_row2(matrix.m_row2) {}

		Matrix2x2Base& operator=(const Matrix2x2Base& matrix);
		RowVectorType operator[](size_t index) const;
		RowVectorType& operator[](size_t index);

		RowVectorType getRow(size_t index) const;
		RowVectorType& getRow(size_t index);

		RowVectorType getElement(size_t row, size_t column) const;
		RowVectorType& getElement(size_t row, size_t column);

		void setElement(size_t row, size_t column, ValueType value);
	};

	template <typename T>
	struct Matrix3x3Base final
	{
		using ValueType = T;
		static_assert(std::is_arithmetic_v<ValueType>);

		static constexpr ValueType DefaultValue = 0;

		using RowVectorType = Vector3Base<ValueType>;

		union
		{
			ValueType m_values[3][3];

			struct
			{
				ValueType m_m11, m_m12, m_m13;
				ValueType m_m21, m_m22, m_m23;
				ValueType m_m31, m_m32, m_m33;
			};

			RowVectorType m_rows[3];

			struct
			{
				RowVectorType m_row1;
				RowVectorType m_row2;
				RowVectorType m_row3;
			};

		};

		constexpr Matrix3x3Base() = default;
		constexpr Matrix3x3Base(
			ValueType m11, ValueType m12, ValueType m13,
			ValueType m21, ValueType m22, ValueType m23,
			ValueType m31, ValueType m32, ValueType m33)
			: m_m11(m11), m_m12(m12), m_m13(m13),
			m_m21(m21), m_m22(m22), m_m23(m23),
			m_m31(m31), m_m32(m32), m_m33(m33) {}

		constexpr Matrix3x3Base(const RowVectorType& row1, const RowVectorType& row2, const RowVectorType& row3)
			: m_row1(row1), m_row2(row2), m_row3(row3) {}

		constexpr Matrix3x3Base(const Matrix2x2Base<ValueType>& matrix)
			: m_row1(matrix.m_row1), m_row2(matrix.m_row2) {}

		constexpr Matrix3x3Base(const Matrix3x3Base& matrix)
			: m_row1(matrix.m_row1), m_row2(matrix.m_row2), m_row3(matrix.m_row3) {}

		Matrix3x3Base& operator=(const Matrix2x2Base<ValueType>& matrix);
		Matrix3x3Base& operator=(const Matrix3x3Base& matrix);
		RowVectorType operator[](size_t index) const;
		RowVectorType& operator[](size_t index);

		RowVectorType getRow(size_t index) const;
		RowVectorType& getRow(size_t index);

		RowVectorType getElement(size_t row, size_t column) const;
		RowVectorType& getElement(size_t row, size_t column);

		void setElement(size_t row, size_t column, ValueType value);
	};

	template <typename T>
	struct Matrix4x4Base final
	{
		using ValueType = T;
		static_assert(std::is_arithmetic_v<ValueType>);

		static constexpr ValueType DefaultValue = 0;

		using RowVectorType = Vector4Base<ValueType>;

		union
		{
			ValueType m_values[4][4];

			struct
			{
				ValueType m_m11, m_m12, m_m13, m_m14;
				ValueType m_m21, m_m22, m_m23, m_m24;
				ValueType m_m31, m_m32, m_m33, m_m34;
				ValueType m_m41, m_m42, m_m43, m_m44;
			};

			RowVectorType m_rows[4];

			struct
			{
				RowVectorType m_row1;
				RowVectorType m_row2;
				RowVectorType m_row3;
				RowVectorType m_row4;
			};
		};

		constexpr Matrix4x4Base() = default;
		constexpr Matrix4x4Base(
			ValueType m11, ValueType m12, ValueType m13, ValueType m14,
			ValueType m21, ValueType m22, ValueType m23, ValueType m24,
			ValueType m31, ValueType m32, ValueType m33, ValueType m34,
			ValueType m41, ValueType m42, ValueType m43, ValueType m44)
			: m_m11(m11), m_m12(m12), m_m13(m13), m_m14(m14),
			m_m21(m21), m_m22(m22), m_m23(m23), m_m24(m24),
			m_m31(m31), m_m32(m32), m_m33(m33), m_m34(m34),
			m_m41(m41), m_m42(m42), m_m43(m43), m_m44(m44) {}

		constexpr Matrix4x4Base(const RowVectorType& row1, const RowVectorType& row2,
			const RowVectorType& row3, const RowVectorType& row4)
			: m_row1(row1), m_row2(row2), m_row3(row3), m_row4(row4) {}

		constexpr Matrix4x4Base(const Matrix2x2Base<ValueType>& matrix)
			: m_row1(matrix.m_row1), m_row2(matrix.m_row2) {}

		constexpr Matrix4x4Base(const Matrix3x3Base<ValueType>& matrix)
			: m_row1(matrix.m_row1), m_row2(matrix.m_row2), m_row3(matrix.m_row3) {}

		constexpr Matrix4x4Base(const Matrix4x4Base& matrix)
			: m_row1(matrix.m_row1), m_row2(matrix.m_row2), m_row3(matrix.m_row3), m_row4(matrix.m_row4) {}

		Matrix4x4Base& operator=(const Matrix2x2Base<ValueType>& matrix);
		Matrix4x4Base& operator=(const Matrix3x3Base<ValueType>& matrix);
		Matrix4x4Base& operator=(const Matrix4x4Base& matrix);
		RowVectorType operator[](size_t index) const;
		RowVectorType& operator[](size_t index);

		RowVectorType getRow(size_t index) const;
		RowVectorType& getRow(size_t index);

		RowVectorType getElement(size_t row, size_t column) const;
		RowVectorType& getElement(size_t row, size_t column);

		void setElement(size_t row, size_t column, ValueType value);
	};

	using FloatMatrix2x2 = Matrix2x2Base<float>;
	using FloatMatrix3x3 = Matrix3x3Base<float>;
	using FloatMatrix4x4 = Matrix4x4Base<float>;

	constexpr FloatMatrix4x4 FloatMatrix4x4Identity = FloatMatrix4x4(
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f);
}

#include "Matrix.hpp"