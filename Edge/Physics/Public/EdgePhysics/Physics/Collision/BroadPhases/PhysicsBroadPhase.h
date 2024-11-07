#pragma once

#include "EdgeCommon/Patterns/NonCopyable.h"

#include "EdgePhysics/Physics/Collision/PhysicsGlobalCollisionQuery.h"
#include "EdgePhysics/Physics/Collision/Scene/PhysicsCollisionSceneContextTypes.h"
#include "EdgePhysics/Physics/Collision/Scene/PhysicsSceneCollisionManagerReference.h"

#include <vector>

namespace Edge
{
	class DebugVisualizationDataController;

	using PhysicsSceneBroadPhaseEntityIndex = uint32_t;
	constexpr PhysicsSceneBroadPhaseEntityIndex InvalidPhysicsSceneBroadPhaseEntityIndex = -1;

	class PhysicsBroadPhase : public PhysicsGlobalCollisionQuery, public NonCopyable
	{
	public:
		struct CollisionPair final
		{
			PhysicsSceneCollisionID m_collision1 = InvalidPhysicsSceneCollisionID;
			PhysicsSceneCollisionID m_collision2 = InvalidPhysicsSceneCollisionID;

			CollisionPair() = default;
			CollisionPair(PhysicsSceneCollisionID collision1, PhysicsSceneCollisionID collision2)
				: m_collision1(collision1), m_collision2(collision2) {}
		};

		using PhysicsSceneCollisionPairCollection = std::vector<CollisionPair>;

		PhysicsBroadPhase() = default;

		virtual bool init(const PhysicsSceneCollisionManagerReference& collisionManager) = 0;
		virtual void release() = 0;

		virtual void addCollision(const PhysicsEntityCollisionReference& collision) = 0;
		virtual void removeCollision(const PhysicsEntityCollisionReference& collision) = 0;
		virtual void updateCollisionBoundChanged(const PhysicsEntityCollisionReference& collision) = 0;

		virtual void findCollidingPairs(const PhysicsEntityCollisionReference& collision, PhysicsSceneCollisionPairCollection& result) = 0;

		virtual void visualizeDebug(const DebugVisualizationDataController& data) const = 0;
	};
}
