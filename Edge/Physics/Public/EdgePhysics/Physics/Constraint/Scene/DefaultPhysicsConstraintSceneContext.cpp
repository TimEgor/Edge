#include "DefaultPhysicsConstraintSceneContext.h"

#include "EdgeCommon/Assert/AssertCore.h"

#include "PhysicsSceneConstraintManager.h"

void Edge::DefaultPhysicsConstraintSceneContext::selfDestroy()
{
	m_collection->destroyContext(this);
}
Edge::PhysicsSceneConstraintManagerWeakReference Edge::DefaultPhysicsConstraintSceneContext::getConstraintManager() const
{
	return m_constraintManager;
}

void Edge::DefaultPhysicsConstraintSceneContext::setConstraintManager(const PhysicsSceneConstraintManagerReference& manager, PhysicsSceneConstraintID id)
{
	if (manager && id == InvalidPhysicsSceneConstraintID || !manager && id != InvalidPhysicsSceneConstraintID)
	{
		EDGE_ASSERT_FAIL_MESSAGE("Trying to set an invalid constraint scene context data.");
		return;
	}

	m_constraintManager = manager;
	m_sceneConstraintID = id;
}

void Edge::DefaultPhysicsConstraintSceneContext::setContextCollection(const PhysicsConstraintSceneContextCollectionReference& collection, PhysicsSceneConstraintID id)
{
	if (collection && id == InvalidPhysicsSceneConstraintID || !collection && id != InvalidPhysicsSceneConstraintID)
	{
		EDGE_ASSERT_FAIL_MESSAGE("Trying to set an invalid entity constraint context collection.");
		return;
	}

	m_collection = collection;
	m_sceneContextID = id;
}

bool Edge::DefaultPhysicsConstraintSceneContext::isActive() const
{
	return m_activationContextIndex != InvalidPhysicsSceneActivationContextConstraintIndex;
}
