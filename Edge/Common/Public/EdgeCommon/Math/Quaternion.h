#pragma once

#include "Vector.h"

namespace Edge
{
	template <typename T>
	struct QuaternionBase final
	{
		using VectorType = Vector4Base<T>;

		VectorType m_elements;

		constexpr QuaternionBase() = default;
		constexpr QuaternionBase(T x, T y, T z, T w) : m_elements(x, y, z, w) {}
		constexpr QuaternionBase(const VectorType& elements) : m_elements(elements) {}
		constexpr QuaternionBase(const QuaternionBase& quaternion) = default;

		QuaternionBase& operator=(const QuaternionBase& quaternion) = default;
	};

	using FloatQuaternion = QuaternionBase<float>;

	constexpr FloatQuaternion FloatQuaternionZero = FloatQuaternion(0.0f, 0.0f, 0.0f, 0.0f);
	constexpr FloatQuaternion FloatQuaternionIdentity = FloatQuaternion(0.0f, 0.0f, 0.0f, 1.0f);
}