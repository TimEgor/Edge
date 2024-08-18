#include "PhysicsEntity.h"

#include "EdgeCommon/Assert/AssertCore.h"

#include "EdgePhysics/Physics/Collision/PhysicsSceneCollisionManager.h"
#include "EdgePhysics/Physics/Scene/PhysicsScene.h"

void Edge::PhysicsEntity::updateEntityLinks(PhysicsEntityWeakLinkObject* oldObject, PhysicsEntityWeakLinkObject* newObject)
{
	if (oldObject)
	{
		oldObject->setEntityLink(nullptr);
	}

	if (newObject)
	{
		newObject->setEntityLink(this);
	}
}

void Edge::PhysicsEntity::updateMotion(const PhysicsEntityMotionReference& newMotion)
{
	updateEntityLinks(m_motion.getObject(), newMotion.getObject());

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

void Edge::PhysicsEntity::setCollision(const PhysicsEntityCollisionReference& collision)
{
	if (m_collision && m_sceneContext)
	{
		m_sceneContext->getScene().getReference()->getCollisionManager()->removeCollision(m_collision);
	}

	updateEntityLinks(m_collision.getObject(), collision.getObject());

	m_collision = collision;

	if (m_collision && m_sceneContext)
	{
		m_sceneContext->getScene().getReference()->getCollisionManager()->addCollision(m_collision);
	}
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
