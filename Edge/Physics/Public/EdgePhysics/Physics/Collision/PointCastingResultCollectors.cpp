#include "PointCastingResultCollectors.h"

void Edge::ClosestPointCastingResultCollector::addHit(const PointInstanceCastingResult& result)
{
	if (!m_hasHit || result.m_result.m_distance < m_hitResult.m_result.m_distance)
	{
		m_hitResult = result;
		m_hasHit = true;
	}
}

void Edge::ClosestPointCastingResultCollector::reset()
{
	m_hitResult.m_result.m_distance = Math::Max;
	m_hasHit = false;
}

bool Edge::ClosestPointCastingResultCollector::shouldStopCollecting() const
{
	return m_hasHit && m_hitResult.m_result.m_distance <= Math::Epsilon;
}
