#pragma once

#include "ComputeVector2.h"

namespace Edge
{
	template <typename T>
	class ComputeVector3Base final
	{
		using ValueType = T;
		static_assert(std::is_arithmetic_v<ValueType>);

		using VectorType = Vector3Base<ValueType>;

	private:
		union
		{
			VectorType m_vector;

			ComputeVector2Base<ValueType> m_vectorXY;
		};

	public:
		constexpr ComputeVector3Base()
			: m_vector() {}
		constexpr ComputeVector3Base(ValueType value)
			: m_vector(value) {}
		constexpr ComputeVector3Base(ValueType x, ValueType y, ValueType z)
			: m_vector(x, y, z) {}
		constexpr ComputeVector3Base(const VectorType& vector)
			: m_vector(vector) {}
		constexpr ComputeVector3Base(const ComputeVector2Base<ValueType>& vector)
			: m_vector(vector.getX(), vector.getY(), VectorType::DefaultValue) {}
		constexpr ComputeVector3Base(const ComputeVector2Base<ValueType>& vector, ValueType z)
			: m_vector(vector.getX(), vector.getY(), z) {}
		constexpr ComputeVector3Base(const ComputeVector3Base& vector)
			: m_vector(vector.m_vector) {}

		ComputeVector3Base& operator=(const ComputeVector3Base& vector);

		ComputeVector3Base& operator+=(const ComputeVector3Base& vector);
		ComputeVector3Base& operator-=(const ComputeVector3Base& vector);
		ComputeVector3Base& operator*=(T value);
		ComputeVector3Base& operator/=(T value);

		bool operator==(const ComputeVector3Base& vector) const;
		bool operator!=(const ComputeVector3Base& vector) const;

		ValueType operator[](uint32_t index) const { return getElement(index); }
		ValueType& operator[](uint32_t index) { return getElement(index); }

		ValueType getElement(uint32_t index) const { return m_vector.getElement(index); }
		ValueType& getElement(uint32_t index) { return m_vector.getElement(index); }

		FloatVector3 getFloatVector3() const;
		void getFloatVector3(FloatVector3& out) const;

		ValueType getX() const { return m_vector.m_x; }
		ValueType getY() const { return m_vector.m_y; }
		ValueType getZ() const { return m_vector.m_z; }
		ValueType& getX() { return m_vector.m_x; }
		ValueType& getY() { return m_vector.m_y; }
		ValueType& getZ() { return m_vector.m_z; }
		void setX(ValueType value) { m_vector.m_x = value; }
		void setY(ValueType value) { m_vector.m_y = value; }
		void setZ(ValueType value) { m_vector.m_z = value; }

		const ComputeVector2Base<ValueType>& getXY() const { return m_vectorXY; }
		ComputeVector2Base<ValueType>& getXY() { return m_vectorXY; }
		void setXY(const ComputeVector2Base<ValueType>& vector) { m_vectorXY = vector; }

		ValueType getLength() const;
		ValueType getLengthSqr() const;

		ComputeVector3Base& negate();
		ComputeVector3Base& computeReciprocal();

		ComputeVector3Base& multiplyElements(const ComputeVector3Base& vector);

		ComputeVector3Base getUnit() const;
		void getUnit(ComputeVector3Base& out) const;
		ComputeVector3Base& normalize();

		ComputeVector3Base getOrthogonal() const;
		void getOrthogonal(ComputeVector3Base& out) const;

		ComputeVector3Base getAbs() const;
		void getAbs(ComputeVector3Base& out) const;

		uint32_t getMinElementIndex() const;
		uint32_t getMaxElementIndex() const;

		ValueType dot(const ComputeVector3Base& vector) const;
		ComputeVector3Base cross(const ComputeVector3Base& vector) const;

		ComputeVector3Base swizzle(uint32_t index1, uint32_t index2, uint32_t index3) const;

		bool isEqual(const ComputeVector3Base& vector, ValueType epsilon = Math::TypedEpsilon<ValueType>()) const;
		bool isLess(const ComputeVector3Base& vector, ValueType epsilon = Math::TypedEpsilon<ValueType>()) const; // *this < vector
		bool isLessOrEqual(const ComputeVector3Base& vector, ValueType epsilon = Math::TypedEpsilon<ValueType>()) const; // *this <= vector
		bool isGreater(const ComputeVector3Base& vector, ValueType epsilon = Math::TypedEpsilon<ValueType>()) const; // *this > vector
		bool isGreaterOrEqual(const ComputeVector3Base& vector, ValueType epsilon = Math::TypedEpsilon<ValueType>()) const; // *this >= vector
		bool isAnyLess(const ComputeVector3Base& vector, ValueType epsilon = Math::TypedEpsilon<ValueType>()) const; // *this < vector
		bool isAnyLessOrEqual(const ComputeVector3Base& vector, ValueType epsilon = Math::TypedEpsilon<ValueType>()) const; // *this <= vector
		bool isAnyGreater(const ComputeVector3Base& vector, ValueType epsilon = Math::TypedEpsilon<ValueType>()) const; // *this > vector
		bool isAnyGreaterOrEqual(const ComputeVector3Base& vector, ValueType epsilon = Math::TypedEpsilon<ValueType>()) const; // *this >= vector

		bool isUnit() const;
		bool isZero() const;
	};

	template <typename T>
	ComputeVector3Base<T> operator+(const ComputeVector3Base<T>& vector1, const ComputeVector3Base<T>& vector2);
	template <typename T>
	ComputeVector3Base<T> operator-(const ComputeVector3Base<T>& vector1, const ComputeVector3Base<T>& vector2);
	template <typename T>
	ComputeVector3Base<T> operator-(const ComputeVector3Base<T>& vector);
	template <typename T>
	ComputeVector3Base<T> operator*(const ComputeVector3Base<T>& vector, T value);
	template <typename T>
	ComputeVector3Base<T> operator*(T value, const ComputeVector3Base<T>& vector);
	template <typename T>
	ComputeVector3Base<T> operator/(const ComputeVector3Base<T>& vector, T value);
	template <typename T>
	ComputeVector3Base<T> operator/(T value, const ComputeVector3Base<T>& vector);

	template <typename T>
	T DotComputeVector3(const ComputeVector3Base<T>& vector1, const ComputeVector3Base<T>& vector2);
	template <typename T>
	ComputeVector3Base<T> CrossComputeVector3(const ComputeVector3Base<T>& vector1, const ComputeVector3Base<T>& vector2);

	template <typename T>
	ComputeVector3Base<T> NegateComputeVector3(const ComputeVector3Base<T>& vector);
	template <typename T>
	ComputeVector3Base<T> ComputeReciprocalComputeVector3(const ComputeVector3Base<T>& vector);
	template <typename T>
	ComputeVector3Base<T> NormalizeComputeVector3(const ComputeVector3Base<T>& vector);

	template <typename T>
	ComputeVector3Base<T> MultiplyComputeVector3Elements(const ComputeVector3Base<T>& vector1, const ComputeVector3Base<T>& vector2);

	template <typename T>
	ComputeVector3Base<T> MinComputeVector3(const ComputeVector3Base<T>& vector1, const ComputeVector3Base<T>& vector2);
	template <typename T>
	ComputeVector3Base<T> MaxComputeVector3(const ComputeVector3Base<T>& vector1, const ComputeVector3Base<T>& vector2);

	template <typename T>
	constexpr ComputeVector3Base<T> ComputeVector3ZeroBase() { return ComputeVector3Base<T>(0.0); }
	template <typename T>
	constexpr ComputeVector3Base<T> ComputeVector3OneBase() { return ComputeVector3Base<T>(1.0); }
	template <typename T>
	constexpr ComputeVector3Base<T> ComputeVector3NegativeOneBase() { return ComputeVector3Base<T>(-1.0); }

	template <typename T>
	constexpr ComputeVector3Base<T> ComputeVector3EpsilonBase() { return ComputeVector3Base<T>(Math::TypedEpsilon<T>()); }

	template <typename T>
	constexpr ComputeVector3Base<T> ComputeVector3UnitXBase() { return ComputeVector3Base<T>(1.0, 0.0, 0.0); }
	template <typename T>
	constexpr ComputeVector3Base<T> ComputeVector3UnitYBase() { return ComputeVector3Base<T>(0.0, 1.0, 0.0); }
	template <typename T>
	constexpr ComputeVector3Base<T> ComputeVector3UnitZBase() { return ComputeVector3Base<T>(0.0, 0.0, 1.0); }
	template <typename T>
	constexpr ComputeVector3Base<T> ComputeVector3NegativeUnitXBase() { return ComputeVector3Base<T>(-1.0, 0.0, 0.0); }
	template <typename T>
	constexpr ComputeVector3Base<T> ComputeVector3NegativeUnitYBase() { return ComputeVector3Base<T>(0.0, -1.0, 0.0); }
	template <typename T>
	constexpr ComputeVector3Base<T> ComputeVector3NegativeUnitZBase() { return ComputeVector3Base<T>(0.0, 0.0, -1.0); }

	using ComputeVector3 = ComputeVector3Base<ComputeValueType>;
	using FloatComputeVector3 = ComputeVector3Base<float>;

	constexpr ComputeVector3 ComputeVector3Zero = ComputeVector3ZeroBase<ComputeValueType>();
	constexpr ComputeVector3 ComputeVector3One = ComputeVector3OneBase<ComputeValueType>();
	constexpr ComputeVector3 ComputeVector3NegativeOne = ComputeVector3NegativeOneBase<ComputeValueType>();

	constexpr ComputeVector3 ComputeVector3Epsilon = ComputeVector3EpsilonBase<ComputeValueType>();

	constexpr ComputeVector3 ComputeVector3UnitX = ComputeVector3UnitXBase<ComputeValueType>();
	constexpr ComputeVector3 ComputeVector3UnitY = ComputeVector3UnitYBase<ComputeValueType>();
	constexpr ComputeVector3 ComputeVector3UnitZ = ComputeVector3UnitZBase<ComputeValueType>();
	constexpr ComputeVector3 ComputeVector3NegativeUnitX = ComputeVector3NegativeUnitXBase<ComputeValueType>();
	constexpr ComputeVector3 ComputeVector3NegativeUnitY = ComputeVector3NegativeUnitYBase<ComputeValueType>();
	constexpr ComputeVector3 ComputeVector3NegativeUnitZ = ComputeVector3NegativeUnitZBase<ComputeValueType>();

	constexpr FloatComputeVector3 FloatComputeVector3Zero = ComputeVector3ZeroBase<float>();
	constexpr FloatComputeVector3 FloatComputeVector3One = ComputeVector3OneBase<float>();
	constexpr FloatComputeVector3 FloatComputeVector3NegativeOne = ComputeVector3NegativeOneBase<float>();

	constexpr FloatComputeVector3 FloatComputeVector3Epsilon = ComputeVector3EpsilonBase<float>();

	constexpr FloatComputeVector3 FloatComputeVector3UnitX = ComputeVector3UnitXBase<float>();
	constexpr FloatComputeVector3 FloatComputeVector3UnitY = ComputeVector3UnitYBase<float>();
	constexpr FloatComputeVector3 FloatComputeVector3UnitZ = ComputeVector3UnitZBase<float>();
	constexpr FloatComputeVector3 FloatComputeVector3NegativeUnitX = ComputeVector3NegativeUnitXBase<float>();
	constexpr FloatComputeVector3 FloatComputeVector3NegativeUnitY = ComputeVector3NegativeUnitYBase<float>();
	constexpr FloatComputeVector3 FloatComputeVector3NegativeUnitZ = ComputeVector3NegativeUnitZBase<float>();
}

#include "ComputeVector3.hpp"