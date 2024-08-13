#include "DefaultPhysicsEntitySceneContext.h"

Edge::DefaultPhysicsEntitySceneContext::DefaultPhysicsEntitySceneContext(PhysicsEntity& entity)
	: m_entity(entity) {}

Edge::DefaultPhysicsEntitySceneContext::~DefaultPhysicsEntitySceneContext()
{
	m_entity.setSceneContext(nullptr);

	EDGE_ASSERT(getReferenceCount() == 1);
	releaseReferenceObject();
}

void Edge::DefaultPhysicsEntitySceneContext::setActivationContextIndex(PhysicsSceneActivationContextEntityIndex index)
{
	if (index != InvalidPhysicsSceneActivationContextEntityIndex && !m_entity.getMotion())
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
