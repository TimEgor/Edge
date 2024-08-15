#include "PhysicsEntity.h"

#include "EdgeCommon/Assert/AssertCore.h"

#include "EdgePhysics/Physics/Scene/PhysicsScene.h"

void Edge::PhysicsEntity::updateMotion(const PhysicsEntityMotionReference& newMotion)
{
	if (m_motion)
	{
		m_motion->setEntityLink(nullptr);
	}

	if (newMotion)
	{
		newMotion->setEntityLink(this);
	}

	m_motion = newMotion;
}

Edge::PhysicsEntity::PhysicsEntity(const PhysicsEntityTransformReference& transform)
	: m_transform(transform)
{
	EDGE_ASSERT(transform);
	transform->setEntityLink(this);
}

Edge::PhysicsEntity::~PhysicsEntity()
{
	EDGE_ASSERT(m_sceneContext == nullptr);

	m_transform->setEntityLink(nullptr);
	updateMotion(nullptr);
}

void Edge::PhysicsEntity::setSceneContext(const PhysicsEntitySceneContextReference& context)
{
	if (context && m_sceneContext)
	{
		EDGE_ASSERT_FAIL_MESSAGE("Entity scene context has been already set.");
		return;
	}

	if (m_sceneContext)
	{
		m_sceneContext->setEntityLink(nullptr);
	}

	if (context)
	{
		context->setEntityLink(this);
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
