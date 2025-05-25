#include "PhysicsEntity.h"

#include "EdgeCommon/Assert/AssertCore.h"

#include "EdgePhysics/Physics/Collision/Scene/PhysicsSceneCollisionManager.h"
#include "EdgePhysics/Physics/Scene/PhysicsScene.h"

#include "Scene/PhysicsSceneEntityManager.h"

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
	EDGE_ASSERT(m_sceneContext.isNull());

	m_transform->setEntityLink(nullptr);
	updateMotion(nullptr);
	setCollision(nullptr);
}

void Edge::PhysicsEntity::setCollision(const PhysicsEntityCollisionReference& collision)
{
	if (m_collision && m_sceneContext)
	{
		getScene()->getCollisionManager()->removeCollision(m_collision);
	}

	updateEntityLinks(m_collision.getObject(), collision.getObject());

	m_collision = collision;

	if (m_collision && m_sceneContext)
	{
		getScene()->getCollisionManager()->addCollision(m_collision);
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

void Edge::PhysicsEntity::makeTransformChangingNotification()
{
	const PhysicsSceneReference scene = getScene();
	if (scene)
	{
		scene->makeTransformChangingNotification(this);
	}
}

Edge::PhysicsSceneReference Edge::PhysicsEntity::getScene() const
{
	PhysicsSceneEntityManagerReference manager = getManager();
	return manager ? manager->getScene().getReference() : nullptr;
}

Edge::PhysicsSceneEntityManagerReference Edge::PhysicsEntity::getManager() const
{
	return m_sceneContext ? m_sceneContext->getManager().getReference() : nullptr;
}

bool Edge::PhysicsEntity::isActive() const
{
	return m_sceneContext && m_sceneContext->isActive();
}
