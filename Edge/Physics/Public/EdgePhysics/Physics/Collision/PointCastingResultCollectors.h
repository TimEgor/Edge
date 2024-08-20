#pragma once

#include "PhysicsGlobalCollisionQuery.h"

namespace Edge
{
	class ClosestPointCastingResultCollector final : public PhysicsGlobalCollisionQuery::PointCastingResultCollector
	{
	public:
		using PointInstanceCastingResult = PhysicsGlobalCollisionQuery::PointInstanceCastingResult;

	private:
		PointInstanceCastingResult m_hitResult;
		bool m_hasHit = false;

	public:
		ClosestPointCastingResultCollector() = default;

		virtual void addHit(const PointInstanceCastingResult& result) override;
		virtual bool hasHit() const override { return m_hasHit; }

		virtual void reset() override;

		virtual bool shouldStopCollecting() const override;

		virtual float getMaxHitDistance() const override { return m_hitResult.m_result.m_distance; }

		const PointInstanceCastingResult& getHitResult() const { return m_hitResult; }
	};
}
