#pragma once

#include "ComputeMath.h"
#include "Vector.h"

namespace Edge
{
	template <typename T>
	class ComputeVector2Base final
	{
	public:
		using ValueType = T;
		static_assert(std::is_arithmetic_v<ValueType>);

		using VectorType = Vector2Base<ValueType>;

	private:
		VectorType m_vector;

	public:
		constexpr ComputeVector2Base()
			: m_vector() {}
		constexpr ComputeVector2Base(ValueType value)
			: m_vector(value) {}
		constexpr ComputeVector2Base(ValueType x, ValueType y)
			: m_vector(x, y) {}
		constexpr ComputeVector2Base(const VectorType& vector)
			: m_vector(vector) {}
		constexpr ComputeVector2Base(const ComputeVector2Base& vector)
			: m_vector(vector.m_vector) {}

		ComputeVector2Base& operator=(const ComputeVector2Base& vector);

		ComputeVector2Base& operator+=(const ComputeVector2Base& vector);
		ComputeVector2Base& operator-=(const ComputeVector2Base& vector);
		ComputeVector2Base& operator*=(ValueType value);
		ComputeVector2Base& operator/=(ValueType value);

		bool operator==(const ComputeVector2Base& vector) const;
		bool operator!=(const ComputeVector2Base& vector) const;

		ValueType operator[](uint32_t index) const { return getElement(index); }
		ValueType& operator[](uint32_t index) { return getElement(index); }

		ValueType getElement(uint32_t index) const { return m_vector.getElement(index); }
		ValueType& getElement(uint32_t index) { return m_vector.getElement(index); }

		FloatVector2 getFloatVector2() const;
		void getFloatVector2(FloatVector2& out) const;

		ValueType getX() const { return m_vector.m_x; }
		ValueType getY() const { return m_vector.m_y; }
		ValueType& getX() { return m_vector.m_x; }
		ValueType& getY() { return m_vector.m_y; }
		void setX(ValueType value) { m_vector.m_x = value; }
		void setY(ValueType value) { m_vector.m_y = value; }

		ValueType getLength() const;
		ValueType getLengthSqr() const;

		ComputeVector2Base& negate();

		ComputeVector2Base getUnit() const;
		ComputeVector2Base& normalize();

		T dot(const ComputeVector2Base& vector) const;

		bool isEqual(const ComputeVector2Base& vector, ValueType epsilon = Math::TypedEpsilon<ValueType>()) const;
		bool isLess(const ComputeVector2Base& vector, ValueType epsilon = Math::TypedEpsilon<ValueType>()) const; // *this < vector
		bool isLessOrEqual(const ComputeVector2Base& vector, ValueType epsilon = Math::TypedEpsilon<ValueType>()) const; // *this <= vector
		bool isGreater(const ComputeVector2Base& vector, ValueType epsilon = Math::TypedEpsilon<ValueType>()) const; // *this > vector
		bool isGreaterOrEqual(const ComputeVector2Base& vector, ValueType epsilon = Math::TypedEpsilon<ValueType>()) const; // *this >= vector

		bool isUnit() const;
		bool isZero() const;
	};

	template <typename T>
	ComputeVector2Base<T> operator+(const ComputeVector2Base<T>& vector1, const ComputeVector2Base<T>& vector2);
	template <typename T>
	ComputeVector2Base<T> operator-(const ComputeVector2Base<T>& vector1, const ComputeVector2Base<T>& vector2);
	template <typename T>
	ComputeVector2Base<T> operator-(const ComputeVector2Base<T>& vector);
	template <typename T>
	ComputeVector2Base<T> operator*(const ComputeVector2Base<T>& vector, T value);
	template <typename T>
	ComputeVector2Base<T> operator*(T value, const ComputeVector2Base<T>& vector);
	template <typename T>
	ComputeVector2Base<T> operator/(const ComputeVector2Base<T>& vector, T value);
	template <typename T>
	ComputeVector2Base<T> operator/(T value, const ComputeVector2Base<T>& vector);

	template <typename T>
	T DotComputeVector2(const ComputeVector2Base<T>& vector1, const ComputeVector2Base<T>& vector2);

	using ComputeVector2 = ComputeVector2Base<ComputeValueType>;
	using FloatComputeVector2 = ComputeVector2Base<float>;
}

#include "ComputeVector2.hpp"