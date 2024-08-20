#pragma once

#include "BroadPhases/PhysicsBroadPhase.h"

#include "PhysicsEntityCollision.h"
#include "PhysicsEntityCollisionSceneContextCollection.h"

namespace Edge
{
	class DefaultPhysicsEntityCollisionSceneContext final : public PhysicsEntityCollisionSceneContext
	{
	private:
		PhysicsSceneCollisionManagerWeakReference m_collisionManager;
		PhysicsEntityCollisionSceneContextCollectionReference m_collection;

		PhysicsSceneCollisionID m_sceneCollisionID = InvalidPhysicsSceneCollisionID;
		PhysicsSceneCollisionID m_collisionContextID = InvalidPhysicsSceneCollisionID;

		PhysicsSceneBroadPhaseEntityIndex m_broadPhaseEntityIndex = InvalidPhysicsSceneBroadPhaseEntityIndex;

		virtual void selfDestroy() override;

	public:
		DefaultPhysicsEntityCollisionSceneContext() = default;

		virtual PhysicsSceneCollisionManagerWeakReference getCollisionManager() const override { return m_collisionManager; }
		PhysicsSceneCollisionID getCollisionID() const { return m_collisionContextID; }
		void setCollisionManager(const PhysicsSceneCollisionManagerReference& manager, PhysicsSceneCollisionID id);

		PhysicsSceneCollisionID getCollisionContextID() const { return m_collisionContextID; }
		void setContextCollection(const PhysicsEntityCollisionSceneContextCollectionReference& collection, PhysicsSceneCollisionID id);

		PhysicsSceneBroadPhaseEntityIndex getBroadPhaseEntityIndex() const { return m_broadPhaseEntityIndex; }
		void setBroadPhaseEntityIndex(PhysicsSceneBroadPhaseEntityIndex index);

		EDGE_PHYSICS_ENTITY_COLLISION_SCENE_CONTEXT_TYPE(DEFAULT);
	};
}
