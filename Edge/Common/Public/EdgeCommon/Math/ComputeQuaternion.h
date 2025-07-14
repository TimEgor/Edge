#pragma once

#include "ComputeMatrix44.h"
#include "ComputeVector4.h"
#include "Quaternion.h"

namespace Edge
{
	template <typename T>
	class ComputeQuaternionBase final
	{
	public:
		using ValueType = T;
		static_assert(std::is_arithmetic_v<ValueType>);

		using QuaternionType = QuaternionBase<ValueType>;

	private:
		union
		{
			QuaternionType m_quaternion;

			ComputeVector4Base<ValueType> m_xyzw;

			ComputeVector3Base<ValueType> m_xyz;
		};


	public:
		constexpr ComputeQuaternionBase()
			: m_quaternion() {}
		constexpr ComputeQuaternionBase(ValueType x, ValueType y, ValueType z, ValueType w)
			: m_quaternion(x, y, z, w) {}
		constexpr ComputeQuaternionBase(const QuaternionType& quaternion)
			: m_quaternion(quaternion) {}
		constexpr ComputeQuaternionBase(const ComputeVector4Base<ValueType>& vector)
			: m_xyzw(vector) {}
		constexpr ComputeQuaternionBase(const ComputeQuaternionBase& quaternion)
			: m_quaternion(quaternion.m_quaternion) {}

		explicit ComputeQuaternionBase(const ComputeMatrix3x3Base<ValueType>& matrix);
		explicit ComputeQuaternionBase(const ComputeMatrix4x4Base<ValueType>& matrix);
		explicit ComputeQuaternionBase(const ComputeVector3Base<ValueType>& axis, ValueType angle);

		ComputeQuaternionBase& operator=(const ComputeQuaternionBase& quaternion);

		bool operator==(const ComputeQuaternionBase& quaternion) const;
		bool operator!=(const ComputeQuaternionBase& quaternion) const;

		ComputeQuaternionBase& operator*=(const ComputeQuaternionBase& quaternion);

		ValueType operator[](uint32_t index) const { return getElement(index); }
		ValueType& operator[](uint32_t index) { return getElement(index); }

		ValueType getElement(uint32_t index) const { return m_quaternion.m_elements.getElement(index); }
		ValueType& getElement(uint32_t index) { return m_quaternion.m_elements.getElement(index); }

		ComputeQuaternionBase& setupFromRotationMatrix3x3(const ComputeMatrix3x3Base<ValueType>& matrix);
		ComputeQuaternionBase& setupFromRotationMatrix4x4(const ComputeMatrix4x4Base<ValueType>& matrix);
		ComputeQuaternionBase& setupFromAxisAngle(const ComputeVector3Base<ValueType>& axis, ValueType angle);
		ComputeQuaternionBase& setupFromEulerAngles(const ComputeVector3Base<ValueType>& eulerAngles);
		ComputeQuaternionBase& setupFromRollPitchYaw(ValueType roll, ValueType pitch, ValueType yaw);

		ValueType getX() const { return m_quaternion.m_elements.m_x; }
		ValueType getY() const { return m_quaternion.m_elements.m_y; }
		ValueType getZ() const { return m_quaternion.m_elements.m_z; }
		ValueType getW() const { return m_quaternion.m_elements.m_w; }
		ValueType& getX() { return m_quaternion.m_elements.m_x; }
		ValueType& getY() { return m_quaternion.m_elements.m_y; }
		ValueType& getZ() { return m_quaternion.m_elements.m_z; }
		ValueType& getW() { return m_quaternion.m_elements.m_w; }
		void setX(ValueType value) { m_quaternion.m_elements.m_x = value; }
		void setY(ValueType value) { m_quaternion.m_elements.m_y = value; }
		void setZ(ValueType value) { m_quaternion.m_elements.m_z = value; }
		void setW(ValueType value) { m_quaternion.m_elements.m_w = value; }

		const ComputeVector4Base<ValueType>& getVector() const { return m_xyzw; }
		ComputeVector4Base<ValueType>& getVector() { return m_xyzw; }
		const ComputeVector3Base<ValueType>& getXYZ() const { return m_xyz; }
		ComputeVector3Base<ValueType>& getXYZ() { return m_xyz; }

		ValueType getLength() const;
		ValueType getLengthSqr() const;

		ValueType dot(const ComputeQuaternionBase& quaternion) const;

		ComputeQuaternionBase& normalize();
		ComputeQuaternionBase& conjugate();
		ComputeQuaternionBase& invert();

		ComputeVector3Base<ValueType> rotate(const ComputeVector3Base<ValueType>& vector) const;
		void rotate(const ComputeVector3Base<ValueType>& vector, ComputeVector3Base<ValueType>& out) const;

		bool isEqual(const ComputeQuaternionBase& quaternion, ValueType epsilon = Math::TypedEpsilon<ValueType>()) const;
		bool isUnit() const;
		bool isZero() const;

		ComputeMatrix3x3Base<ValueType> getRotationMatrix3x3() const;
		void getRotationMatrix3x3(ComputeMatrix3x3Base<ValueType>& matrix) const;
		ComputeMatrix4x4Base<ValueType> getRotationMatrix4x4() const;
		void getRotationMatrix4x4(ComputeMatrix4x4Base<ValueType>& matrix) const;

		ValueType getAxisAngle(const ComputeVector3Base<ValueType>& axis) const;

		ComputeVector3Base<ValueType> getEulerAngles() const;
		void getEulerAngles(ComputeVector3Base<ValueType>& angles) const;
	};

	template <typename T>
	ComputeQuaternionBase<T> operator*(const ComputeQuaternionBase<T>& quaternion1, const ComputeQuaternionBase<T>& quaternion2);

	template <typename T>
	ComputeQuaternionBase<T> ConjugateComputeQuaternion(const ComputeQuaternionBase<T>& quaternion);

	template <typename T>
	constexpr ComputeQuaternionBase<T> ComputeQuaternionZeroBase() { return ComputeQuaternionBase<T>(T(0.0), T(0.0), T(0.0), T(0.0)); }
	template <typename T>
	constexpr ComputeQuaternionBase<T> ComputeQuaternionIdentityBase() { return ComputeQuaternionBase<T>(T(0.0), T(0.0), T(0.0), T(1.0)); }

	template <typename T>
	ComputeVector3Base<T> EulerAnglesFromQuaternion(const ComputeQuaternionBase<T>& rotation) { return rotation.getEulerAngles(); }

	using ComputeQuaternion = ComputeQuaternionBase<ComputeValueType>;
	using FloatComputeQuaternion = ComputeQuaternionBase<float>;

	inline constexpr ComputeQuaternion ComputeQuaternionZero = ComputeQuaternionZeroBase<ComputeValueType>();
	inline constexpr ComputeQuaternion ComputeQuaternionIdentity = ComputeQuaternionIdentityBase<ComputeValueType>();
}

#include "ComputeQuaternion.hpp"