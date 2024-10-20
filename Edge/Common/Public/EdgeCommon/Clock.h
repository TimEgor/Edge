#pragma once

#include <chrono>

namespace Edge
{
	using ClockCounter = std::chrono::high_resolution_clock;
	using ClockTimePoint = ClockCounter::time_point;
	using Millisecond = std::chrono::milliseconds;

	namespace Clock
	{
		inline ClockTimePoint GetCurrentTimePoint() { return ClockCounter::now(); }
		inline float CalcTimePointDelta(const ClockTimePoint& t1, const ClockTimePoint& t2) { return std::chrono::duration<float>(t1 - t2).count(); }
	};
}