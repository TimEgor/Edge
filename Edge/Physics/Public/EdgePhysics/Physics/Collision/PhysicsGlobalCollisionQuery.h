#pragma once

#include "EdgeCommon/Math/Vector.h"

#include "EdgePhysics/Physics/Entity/PhysicsEntity.h"

namespace Edge
{
	class PhysicsGlobalCollisionQuery
	{
	public:

		struct PointInstanceCastingResult final
		{
			PhysicsEntityCollisionReference m_collision;
			PhysicsCollisionQuery::PointCastingResult m_result;
		};

		class PointCastingResultCollector
		{
		public:
			using PointCastingResult = PointInstanceCastingResult;

			PointCastingResultCollector() = default;
			virtual ~PointCastingResultCollector() = default;

			virtual void addHit(const PointCastingResult& result) = 0;
			virtual bool hasHit() const = 0;

			virtual void reset() = 0;

			virtual bool shouldStopCollecting() const = 0;

			virtual float getMaxHitDistance() const = 0;
		};

		PhysicsGlobalCollisionQuery() = default;
		virtual ~PhysicsGlobalCollisionQuery() = default;

		virtual void rayCast(const FloatVector3& origin, const FloatVector3& end, PointCastingResultCollector& resultCollector) const = 0;
	};
}
