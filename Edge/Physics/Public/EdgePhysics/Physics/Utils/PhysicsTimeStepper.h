#pragma once

#include <cstdint>

namespace Edge
{
	class PhysicsFixedTimeStepper final
	{
	private:
		float m_stepTime = 0.0f;
		float m_timeAccumulator = 0.0f;

	public:
		PhysicsFixedTimeStepper() = default;

		void setStepFrequency(uint32_t frequency);

		void addTime(float time);
		bool makeStep();

		float getStepTime() const;
	};

	class PhysicsSemiFixedTimeStepper final
	{
	private:
		float m_stepTime = 0.0f;

		float m_maxAvailableStepTime = 0.0f;
		float m_timeAccumulator = 0.0f;

	public:
		PhysicsSemiFixedTimeStepper() = default;

		void setStepFrequency(uint32_t frequency);

		void addTime(float time);
		bool makeStep();

		float getStepTime() const;
	};
}
