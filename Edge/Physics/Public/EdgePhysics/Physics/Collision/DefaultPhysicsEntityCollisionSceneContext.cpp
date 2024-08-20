#include "DefaultPhysicsEntityCollisionSceneContext.h"

#include "PhysicsSceneCollisionManager.h"

void Edge::DefaultPhysicsEntityCollisionSceneContext::selfDestroy()
{
	m_collection->destroyContext(this);
}

void Edge::DefaultPhysicsEntityCollisionSceneContext::setCollisionManager(const PhysicsSceneCollisionManagerReference& manager, PhysicsSceneCollisionID id)
{
	if (manager && id == InvalidPhysicsSceneCollisionID || !manager && id != InvalidPhysicsSceneCollisionID)
	{
		EDGE_ASSERT_FAIL_MESSAGE("Trying to set an invalid collision scene context data.");
		return;
	}

	m_collisionManager = manager;
	m_sceneCollisionID = id;
}

void Edge::DefaultPhysicsEntityCollisionSceneContext::setContextCollection(const PhysicsEntityCollisionSceneContextCollectionReference& collection, PhysicsSceneCollisionID id)
{
	if (collection && id == InvalidPhysicsSceneCollisionID || !collection && id != InvalidPhysicsSceneCollisionID)
	{
		EDGE_ASSERT_FAIL_MESSAGE("Trying to set an invalid collision scene context collection.");
		return;
	}

	m_collection = collection;
	m_collisionContextID = id;
}

void Edge::DefaultPhysicsEntityCollisionSceneContext::setBroadPhaseEntityIndex(PhysicsSceneBroadPhaseEntityIndex index)
{
	m_broadPhaseEntityIndex = index;
}
