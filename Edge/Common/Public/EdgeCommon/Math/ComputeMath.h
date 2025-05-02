#pragma once

#include "EdgeCommon/Assert/AssertCore.h"

#include <cmath>
#include <limits>
#include <utility>

#define EDGE_PI 3.14159265358979323846

namespace Edge
{
#if defined(EDGE_COMPUTE_TYPE_DOUBLE)
	using ComputeValueType = double;
#else
	using ComputeValueType = float;
#ifndef EDGE_COMPUTE_TYPE_FLOAT
#define EDGE_COMPUTE_TYPE_FLOAT
#endif
#endif

	namespace Literals
	{
		constexpr ComputeValueType operator ""_ecv(long double value) { return static_cast<ComputeValueType>(value); }
	}

	namespace Math
	{
		template <typename T>
		constexpr T TypedPi() { return T(EDGE_PI); }
		template <typename T>
		constexpr T TypedPi2() { return TypedPi<T>() * T(2.0); }
		template <typename T>
		constexpr T TypedHalfPi() { return TypedPi<T>() * T(0.5); }

		template <typename T>
		constexpr T TypedDegToRad() { return TypedPi<T>() / T(180.0); }
		template <typename T>
		constexpr T TypedRadToDeg() { return T(180.0) / TypedPi<T>(); }

		template <typename T>
		constexpr T TypedEpsilon() { return std::numeric_limits<T>::epsilon(); }
		template <typename T>
		constexpr T TypedEpsilonSqr() { return TypedEpsilon<T>() * TypedEpsilon<T>(); }

		template <typename T>
		constexpr T TypedMax() { return std::numeric_limits<T>::max(); }
		template <typename T>
		constexpr T TypedMin() { return std::numeric_limits<T>::min(); }

		constexpr ComputeValueType Pi = TypedPi<ComputeValueType>();
		constexpr ComputeValueType Pi2 = TypedPi2<ComputeValueType>();
		constexpr ComputeValueType HalfPi = TypedHalfPi<ComputeValueType>();

		constexpr ComputeValueType DegToRad = TypedDegToRad<ComputeValueType>();
		constexpr ComputeValueType RadToDeg = TypedRadToDeg<ComputeValueType>();

		constexpr ComputeValueType Epsilon = TypedEpsilon<ComputeValueType>();
		constexpr ComputeValueType EpsilonSqr = TypedEpsilonSqr<ComputeValueType>();

		constexpr ComputeValueType Max = TypedMax<ComputeValueType>();
		constexpr ComputeValueType Min = TypedMin<ComputeValueType>();

		template <typename T>
		T ConvertDegToRad(T angle) { return angle * TypedDegToRad<T>(); }
		template <typename T>
		T ConvertRadToDeg(T angle) { return angle * TypedRadToDeg<T>(); }

		template <typename T>
		bool IsApproxEqual(T value1, T value2, T epsilon = TypedEpsilon<T>())
		{
			EDGE_ASSERT(epsilon > T(0.0));
			return std::abs(value1 - value2) < epsilon;
		}

		template <typename T>
		bool IsApproxLess(T value1, T value2, T epsilon = TypedEpsilon<T>()) // is value1 less than value2
		{
			EDGE_ASSERT(epsilon > T(0.0));
			return (value2 - value1) > epsilon;
		}

		template <typename T>
		bool IsApproxLessOrEqual(T value1, T value2, T epsilon = TypedEpsilon<T>()) // is value1 less or equal than value2
		{
			EDGE_ASSERT(epsilon > T(0.0));
			return (value2 - value1) >= epsilon;
		}

		template <typename T>
		bool IsApproxGreater(T value1, T value2, T epsilon = TypedEpsilon<T>()) // is value1 greater than value2
		{
			EDGE_ASSERT(epsilon > T(0.0));
			return (value1 - value2) > epsilon;
		}

		template <typename T>
		bool IsApproxGreaterOrEqual(T value1, T value2, T epsilon = TypedEpsilon<T>()) // is value1 greater or equal than value2
		{
			EDGE_ASSERT(epsilon > T(0.0));
			return (value1 - value2) >= epsilon;
		}

		template <typename T>
		T Clamp(T val, T minVal, T maxVal)
		{
			return std::min(std::max(val, minVal), maxVal);
		}
	}
}

using namespace Edge::Literals;