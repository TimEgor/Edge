#pragma once

#include "EdgeCommon/Patterns/NonCopyable.h"

#include "EdgePhysics/Physics/Collision/PhysicsGlobalCollisionQuery.h"
#include "EdgePhysics/Physics/Collision/PhysicsSceneCollisionManagerReference.h"

namespace Edge
{
	class DebugVisualizationDataController;

	using PhysicsSceneBroadPhaseEntityIndex = uint32_t;
	constexpr PhysicsSceneBroadPhaseEntityIndex InvalidPhysicsSceneBroadPhaseEntityIndex = -1;

	class PhysicsBroadPhase : public PhysicsGlobalCollisionQuery, public NonCopyable
	{
	public:
		PhysicsBroadPhase() = default;

		virtual bool init(const PhysicsSceneCollisionManagerReference& collisionManager) = 0;
		virtual void release() = 0;

		virtual void addCollision(const PhysicsEntityCollisionReference& collision) = 0;
		virtual void removeCollision(const PhysicsEntityCollisionReference& collision) = 0;
		virtual void notifyCollisionBoundChanged(const PhysicsEntityCollisionReference& collision) = 0;

		virtual void visualizeDebug(const DebugVisualizationDataController& data) const = 0;
	};
}
