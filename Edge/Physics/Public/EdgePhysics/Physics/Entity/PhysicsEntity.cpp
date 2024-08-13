#include "PhysicsEntity.h"

#include "EdgeCommon/Assert/AssertCore.h"

#include "EdgePhysics/Physics/Scene/PhysicsScene.h"

Edge::PhysicsEntity::PhysicsEntity(const PhysicsEntityTransformReference& transform)
	: m_transform(transform)
{
	EDGE_ASSERT(transform);
}

void Edge::PhysicsEntity::setSceneContext(const PhysicsEntitySceneContextReference& context)
{
	if (context && m_sceneContext)
	{
		EDGE_ASSERT_FAIL_MESSAGE("Entity scene context has been already set.");
		return;
	}

	m_sceneContext = context;
}

Edge::PhysicsSceneReference Edge::PhysicsEntity::getScene() const
{
	return m_sceneContext ? m_sceneContext->getScene().getReference() : nullptr;
}

bool Edge::PhysicsEntity::isActive() const
{
	return m_sceneContext && m_sceneContext->isActive();
}
