#pragma once

#include "ComputeVector3.h"

namespace Edge
{
	template <typename T>
	class ComputeVector4Base final
	{
	public:
		using ValueType = T;
		static_assert(std::is_arithmetic_v<ValueType>);

		using VectorType = Vector4Base<ValueType>;

	private:
		union
		{
			VectorType m_vector;

			struct
			{
				ComputeVector2Base<ValueType> m_vectorXY;
				ComputeVector2Base<ValueType> m_vectorZW;
			};

			ComputeVector3Base<ValueType> m_vectorXYZ;
		};

	public:
		constexpr ComputeVector4Base()
			: m_vector() {}
		constexpr ComputeVector4Base(ValueType value)
			: m_vector(value) {}
		constexpr ComputeVector4Base(ValueType x, ValueType y, ValueType z, ValueType w)
			: m_vector(x, y, z, w) {}
		constexpr ComputeVector4Base(const VectorType& vector)
			: m_vector(vector) {}
		constexpr ComputeVector4Base(const ComputeVector2Base<ValueType>& vector)
			: m_vector(vector.getX(), vector.getY(), VectorType::DefaultValue, VectorType::DefaultValue) {}
		constexpr ComputeVector4Base(const ComputeVector3Base<ValueType>& vector)
			: m_vector(vector.getX(), vector.getY(), vector.getZ(), VectorType::DefaultValue) {}
		constexpr ComputeVector4Base(const ComputeVector2Base<ValueType>& vector, ValueType z, ValueType w)
			: m_vector(vector.getX(), vector.getY(), z, w) {}
		constexpr ComputeVector4Base(const ComputeVector3Base<ValueType>& vector, ValueType w)
			: m_vector(vector.getX(), vector.getY(), vector.getZ(), w) {}
		constexpr ComputeVector4Base(const ComputeVector4Base& vector)
			: m_vector(vector.m_vector) {}

		ComputeVector4Base& operator=(const ComputeVector4Base& vector);

		ComputeVector4Base& operator+=(const ComputeVector4Base& vector);
		ComputeVector4Base& operator-=(const ComputeVector4Base& vector);
		ComputeVector4Base& operator*=(T value);
		ComputeVector4Base& operator/=(T value);

		bool operator==(const ComputeVector4Base& vector) const;
		bool operator!=(const ComputeVector4Base& vector) const;

		FloatVector4 getFloatVector4() const;
		void getFloatVector4(FloatVector4& out) const;

		ValueType operator[](uint32_t index) const { return getElement(index); }
		ValueType& operator[](uint32_t index) { return getElement(index); }

		ValueType getElement(uint32_t index) const { return m_vector.getElement(index); }
		ValueType& getElement(uint32_t index) { return m_vector.getElement(index); }

		ValueType getX() const { return m_vector.m_x; }
		ValueType getY() const { return m_vector.m_y; }
		ValueType getZ() const { return m_vector.m_z; }
		ValueType getW() const { return m_vector.m_w; }
		ValueType& getX() { return m_vector.m_x; }
		ValueType& getY() { return m_vector.m_y; }
		ValueType& getZ() { return m_vector.m_z; }
		ValueType& getW() { return m_vector.m_w; }
		void setX(ValueType value) { m_vector.m_x = value; }
		void setY(ValueType value) { m_vector.m_y = value; }
		void setZ(ValueType value) { m_vector.m_z = value; }
		void setW(ValueType value) { m_vector.m_w = value; }

		const ComputeVector2Base<ValueType>& getXY() const { return m_vectorXY; }
		const ComputeVector2Base<ValueType>& getZW() const { return m_vectorZW; }
		ComputeVector2Base<ValueType>& getXY() { return m_vectorXY; }
		ComputeVector2Base<ValueType>& getZW() { return m_vectorZW; }
		void setXY(const ComputeVector2Base<ValueType>& vector) { m_vectorXY = vector; }
		void setZW(const ComputeVector2Base<ValueType>& vector) { m_vectorZW = vector; }

		const ComputeVector3Base<ValueType>& getXYZ() const { return m_vectorXYZ; }
		ComputeVector3Base<ValueType>& getXYZ() { return m_vectorXYZ; }
		void setXYZ(const ComputeVector3Base<ValueType>& vector) { m_vectorXYZ = vector; }

		ValueType getLength() const;
		ValueType getLengthSqr() const;

		ComputeVector4Base& negate();

		ComputeVector4Base getUnit() const;
		ComputeVector4Base& normalize();

		ValueType dot(const ComputeVector4Base& vector) const;

		bool isEqual(const ComputeVector4Base& vector, ValueType epsilon = Math::TypedEpsilon<ValueType>()) const;
		bool isLess(const ComputeVector4Base& vector, ValueType epsilon = Math::TypedEpsilon<ValueType>()) const; // *this < vector
		bool isLessOrEqual(const ComputeVector4Base& vector, ValueType epsilon = Math::TypedEpsilon<ValueType>()) const; // *this <= vector
		bool isGreater(const ComputeVector4Base& vector, ValueType epsilon = Math::TypedEpsilon<ValueType>()) const; // *this > vector
		bool isGreaterOrEqual(const ComputeVector4Base& vector, ValueType epsilon = Math::TypedEpsilon<ValueType>()) const; // *this >= vector

		bool isUnit() const;
		bool isZero() const;
	};

	template <typename T>
	ComputeVector4Base<T> operator+(const ComputeVector4Base<T>& vector1, const ComputeVector4Base<T>& vector2);
	template <typename T>
	ComputeVector4Base<T> operator-(const ComputeVector4Base<T>& vector1, const ComputeVector4Base<T>& vector2);
	template <typename T>
	ComputeVector4Base<T> operator-(const ComputeVector4Base<T>& vector);
	template <typename T>
	ComputeVector4Base<T> operator*(const ComputeVector4Base<T>& vector, T value);
	template <typename T>
	ComputeVector4Base<T> operator*(T value, const ComputeVector4Base<T>& vector);
	template <typename T>
	ComputeVector4Base<T> operator/(const ComputeVector4Base<T>& vector, T value);
	template <typename T>
	ComputeVector4Base<T> operator/(T value, const ComputeVector4Base<T>& vector);

	template <typename T>
	ComputeVector4Base<T> ComputeVector4FromPoint(const ComputeVector3Base<T>& vector);

	template <typename T>
	T DotComputeVector4(const ComputeVector4Base<T>& vector1, const ComputeVector4Base<T>& vector2);

	using ComputeVector4 = ComputeVector4Base<ComputeValueType>;
	using FloatComputeVector4 = ComputeVector4Base<float>;
}

#include "ComputeVector4.hpp"