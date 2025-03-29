#pragma once

#include <random>

namespace Edge
{
	template <typename T>
	T TypedRandom(T min, T max)
	{
		std::random_device rd;

		if constexpr (std::is_integral_v<T>)
		{
			std::uniform_int_distribution<T> range(min, max);
			return range(std::mt19937(rd()));
		}
		if constexpr (std::is_floating_point_v<T>) {
			std::uniform_real_distribution<T> range(min, max);
			return range(std::mt19937(rd()));
		}

		static_assert("Invalid randomization type");
		return T();
	}

	template <typename T>
	T TypedRandom(T max)
	{
		return TypedRandom<T>(T(0), max);
	}

	inline ComputeValueType Random(ComputeValueType max) { return TypedRandom<ComputeValueType>(max); }
	inline ComputeValueType Random(ComputeValueType min, ComputeValueType max) { return TypedRandom<ComputeValueType>(min, max); }
}
