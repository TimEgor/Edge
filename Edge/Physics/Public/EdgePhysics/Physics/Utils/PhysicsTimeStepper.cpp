#include "PhysicsTimeStepper.h"

#include <algorithm>

void Edge::PhysicsFixedTimeStepper::setStepFrequency(uint32_t frequency)
{
	m_stepTime = 1.0f / frequency;
}

void Edge::PhysicsFixedTimeStepper::addTime(float time)
{
	m_timeAccumulator += time;
}

bool Edge::PhysicsFixedTimeStepper::makeStep()
{
	if (m_timeAccumulator >= m_stepTime)
	{
		m_timeAccumulator -= m_stepTime;

		return true;
	}

	return false;
}

float Edge::PhysicsFixedTimeStepper::getStepTime() const
{
	return m_stepTime;
}

void Edge::PhysicsSemiFixedTimeStepper::setStepFrequency(uint32_t frequency)
{
	m_maxAvailableStepTime = 1.0f / frequency;
}

void Edge::PhysicsSemiFixedTimeStepper::addTime(float time)
{
	m_timeAccumulator += time;
}

bool Edge::PhysicsSemiFixedTimeStepper::makeStep()
{
	if (m_timeAccumulator > 0.0f)
	{
		m_stepTime = std::min(m_timeAccumulator, m_maxAvailableStepTime);
		m_timeAccumulator -= m_stepTime;

		return true;
	}

	return false;
}

float Edge::PhysicsSemiFixedTimeStepper::getStepTime() const
{
	return m_stepTime;
}
