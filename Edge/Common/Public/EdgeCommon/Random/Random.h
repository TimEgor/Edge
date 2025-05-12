#pragma once

#include <random>

namespace Edge
{
	template <typename T, typename Enabled = void>
	struct TypedRandomizer final
	{
		T random(T min, T max)
		{
			static_assert(false && "Invalid randomization type");
			return T();
		}
	};

	template <typename T>
	struct TypedRandomizer<T, std::enable_if_t<std::is_integral_v<T>>> final
	{
		T random(T min, T max)
		{
			std::random_device rd;
			std::uniform_int_distribution<T> range(min, max);
			return range(std::mt19937(rd()));
		}
	};

	template <typename T>
	struct TypedRandomizer<T, std::enable_if_t<std::is_floating_point_v<T>>> final
	{
		T random(T min, T max)
		{
			std::random_device rd;
			std::uniform_real_distribution<T> range(min, max);
			return range(std::mt19937(rd()));
		}
	};

	template <typename T>
	T TypedRandom(T min, T max)
	{
		static TypedRandomizer<T> randomizer;
		return randomizer.random(min, max);
	}

	template <typename T>
	T TypedRandom(T max)
	{
		return TypedRandom<T>(T(0), max);
	}

	inline ComputeValueType Random(ComputeValueType max) { return TypedRandom<ComputeValueType>(max); }
	inline ComputeValueType Random(ComputeValueType min, ComputeValueType max) { return TypedRandom<ComputeValueType>(min, max); }
}
