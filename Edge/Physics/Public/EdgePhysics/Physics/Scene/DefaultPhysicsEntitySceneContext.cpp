#include "DefaultPhysicsEntitySceneContext.h"

#include "PhysicsScene.h"

void Edge::DefaultPhysicsEntitySceneContext::selfDestroy()
{
	m_collection->destroyContext(this);
}

void Edge::DefaultPhysicsEntitySceneContext::setActivationContextIndex(PhysicsSceneActivationContextEntityIndex index)
{
	if (index != InvalidPhysicsSceneActivationContextEntityIndex && !getEntity()->getMotion())
	{
		EDGE_ASSERT_FAIL_MESSAGE("Entity witch was set as active doesn't have a motion.");
		return;
	}

	m_activationContextIndex = index;
}

bool Edge::DefaultPhysicsEntitySceneContext::isActive() const
{
	return m_activationContextIndex != InvalidPhysicsSceneActivationContextEntityIndex;
}

void Edge::DefaultPhysicsEntitySceneContext::setScene(const PhysicsSceneReference& scene, PhysicsSceneEntityID id)
{
	if (scene && id == InvalidPhysicsSceneEntityID || !scene && id != InvalidPhysicsSceneEntityID)
	{
		EDGE_ASSERT_FAIL_MESSAGE("Trying to set an invalid entity scene context data.");
		return;
	}

	m_scene = scene;
	m_sceneEntityID = id;
}

void Edge::DefaultPhysicsEntitySceneContext::setContextCollection(const PhysicsEntitySceneContextCollectionReference& collection, PhysicsSceneEntityID id)
{
	if (collection && id == InvalidPhysicsSceneEntityID || !collection && id != InvalidPhysicsSceneEntityID)
	{
		EDGE_ASSERT_FAIL_MESSAGE("Trying to set an invalid entity scene context collection.");
		return;
	}

	m_collection = collection;
	m_sceneContextID = id;
}
