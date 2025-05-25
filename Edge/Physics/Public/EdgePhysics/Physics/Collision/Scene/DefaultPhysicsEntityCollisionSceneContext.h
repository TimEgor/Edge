#pragma once

#include "EdgePhysics/Physics/Collision/BroadPhases/PhysicsBroadPhase.h"
#include "EdgePhysics/Physics/Collision/Scene/PhysicsSceneCollisionManagerReference.h"

#include "PhysicsCollisionSceneContextTypes.h"
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

		virtual PhysicsSceneCollisionManagerWeakReference getCollisionManager() const override;
		PhysicsSceneCollisionID getCollisionID() const { return m_collisionContextID; }
		void setCollisionManager(const PhysicsSceneCollisionManagerReference& manager, PhysicsSceneCollisionID id);

		PhysicsSceneCollisionID getCollisionContextID() const { return m_collisionContextID; }
		void setContextCollection(const PhysicsEntityCollisionSceneContextCollectionReference& collection, PhysicsSceneCollisionID id);

		PhysicsSceneBroadPhaseEntityIndex getBroadPhaseEntityIndex() const { return m_broadPhaseEntityIndex; }
		void setBroadPhaseEntityIndex(PhysicsSceneBroadPhaseEntityIndex index);

		EDGE_RTTI_VIRTUAL(DefaultPhysicsEntityCollisionSceneContext)
	};

	EDGE_REFERENCE(DefaultPhysicsEntityCollisionSceneContext);

	namespace CollisionUtil
	{
		DefaultPhysicsEntityCollisionSceneContextReference TryToGetDefaultCollisionSceneContext(const PhysicsEntityCollisionReference& collision);
		DefaultPhysicsEntityCollisionSceneContextReference GetDefaultCollisionSceneContext(const PhysicsEntityCollisionReference& collision);
	}
}

EDGE_RTTI(Edge::DefaultPhysicsEntityCollisionSceneContext)