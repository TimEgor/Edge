#pragma once

#include <chrono>

namespace Edge
{
	using ClockCounter = std::chrono::high_resolution_clock;
	using ClockTimePoint = ClockCounter::time_point;
	using Millisecond = std::chrono::milliseconds;

	class Clock final
	{
	public:
		Clock() = default;

		inline static ClockTimePoint getCurrentTime() { return ClockCounter::now(); }
		inline static float calcTimePointDelta(const ClockTimePoint& t1, const ClockTimePoint& t2) { return std::chrono::duration<float>(t1 - t2).count(); }
	};
}