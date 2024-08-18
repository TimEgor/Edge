#include "PhysicsSceneCollisionManager.h"

#include "EdgePhysics/Physics/Entity/PhysicsEntity.h"
#include "EdgePhysics/Physics/Scene/PhysicsScene.h"

#include "PhysicsSceneCollisionCollection.h"

bool Edge::PhysicsSceneCollisionManager::checkCollisionOwning(const PhysicsEntityCollisionReference& collision) const
{
	EDGE_CHECK_RETURN_FALSE(collision);
	EDGE_CHECK_RETURN_FALSE(collision->getShape());

	const PhysicsEntityReference entity = collision->getEntity();
	EDGE_CHECK_RETURN_FALSE(entity);

	const PhysicsSceneReference entityScene = entity->getScene();
	EDGE_CHECK_RETURN_FALSE(entityScene && entityScene == m_scene.getReference());

	return true;
}

bool Edge::PhysicsSceneCollisionManager::init(const PhysicsSceneReference& scene)
{
	m_scene = scene;

	m_collisionCollection = new PhysicsSceneCollisionCollection();
	EDGE_CHECK_INITIALIZATION(m_collisionCollection && m_collisionCollection->init(this));

	return true;
}

void Edge::PhysicsSceneCollisionManager::release()
{
	EDGE_SAFE_DESTROY_WITH_RELEASING(m_collisionCollection);
}

void Edge::PhysicsSceneCollisionManager::addCollision(const PhysicsEntityCollisionReference& collision)
{
	if (!checkCollisionOwning(collision))
	{
		return;
	}

	m_collisionCollection->addCollision(collision);
}

void Edge::PhysicsSceneCollisionManager::removeCollision(const PhysicsEntityCollisionReference& collision)
{
	if (!checkCollisionOwning(collision))
	{
		return;
	}

	m_collisionCollection->removeCollision(collision);
}
