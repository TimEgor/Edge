#pragma once

#include <cstdint>

namespace Edge::Math
{
	constexpr float Pi = 3.1415927f;
	constexpr float Pi2 = Pi * 2.0f;
	constexpr float HalfPi = 3.1415927f * 0.5f;

	constexpr float DegToRad = Pi / 180.0f;
	constexpr float RadToDeg = 180.0f / Pi;

	constexpr float Epsilon = 1.192093e-07f;
	constexpr float EpsilonSqr = Epsilon * Epsilon;

	constexpr float FltMax = 3.402823466e+38f;
	constexpr float FltMin = 1.175494351e-38f;

	inline bool IsNan(float val) { return (*(const uint32_t*)&(val) & 0x7F800000) == 0x7F800000 && (*(const uint32_t*)&(val) & 0x7FFFFF) != 0; }
	inline bool IsInf(float val) { return (*(const uint32_t*)&(val) & 0x7FFFFFFF) == 0x7F800000; }
}