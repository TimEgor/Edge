#pragma once

#include "PhysicsBroadPhase.h"

#include <vector>

namespace Edge
{
	class BruteforcePhysicsBroadPhase final : public PhysicsBroadPhase
	{
	private:
		using EntityPageCollection = std::vector<PhysicsSceneCollisionID>;

		EntityPageCollection m_ids;

		PhysicsSceneCollisionManagerWeakReference m_collisionManager;

	public:
		BruteforcePhysicsBroadPhase() = default;

		virtual bool init(const PhysicsSceneCollisionManagerReference& collisionManager) override;
		virtual void release() override;

		virtual void addCollision(const PhysicsEntityCollisionReference& collision) override;
		virtual void removeCollision(const PhysicsEntityCollisionReference& collision) override;
		virtual void updateCollisionBoundChanged(const PhysicsEntityCollisionReference& collision) override {}

		virtual void findCollidingPairs(const PhysicsEntityCollisionReference& collision, PhysicsSceneCollisionPairCollection& result) override;

		virtual void rayCast(const ComputeVector3& origin, const ComputeVector3& end, PointCastingResultCollector& resultCollector) const override;
	};
}
