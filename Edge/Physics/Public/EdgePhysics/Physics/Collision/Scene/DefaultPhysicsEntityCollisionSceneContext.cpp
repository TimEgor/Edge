#include "DefaultPhysicsEntityCollisionSceneContext.h"

#include "EdgePhysics/Physics/Collision/Scene/PhysicsSceneCollisionManager.h"

void Edge::DefaultPhysicsEntityCollisionSceneContext::selfDestroy()
{
	m_collection->destroyContext(this);
}

Edge::PhysicsSceneCollisionManagerWeakReference Edge::DefaultPhysicsEntityCollisionSceneContext::getCollisionManager() const
{
	return m_collisionManager;
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

Edge::DefaultPhysicsEntityCollisionSceneContextReference Edge::CollisionUtil::TryToGetDefaultCollisionSceneContext(const PhysicsEntityCollisionReference& collision)
{
	if (!collision)
	{
		return nullptr;
	}

	const PhysicsEntityCollisionSceneContextReference sceneContext = collision->getSceneContext();
	if (sceneContext->getType() != DefaultPhysicsEntityCollisionSceneContext::getPhysicsEntityCollisionSceneContextType())
	{
		return nullptr;
	}


	return sceneContext.getObjectCast<DefaultPhysicsEntityCollisionSceneContext>();
}

Edge::DefaultPhysicsEntityCollisionSceneContextReference Edge::CollisionUtil::GetDefaultCollisionSceneContext(const PhysicsEntityCollisionReference& collision)
{
	const DefaultPhysicsEntityCollisionSceneContextReference defaultSceneContext = TryToGetDefaultCollisionSceneContext(collision);
	EDGE_ASSERT_MESSAGE(defaultSceneContext, "Collision scene context is null or has an invalid type.");

	return defaultSceneContext;
}
