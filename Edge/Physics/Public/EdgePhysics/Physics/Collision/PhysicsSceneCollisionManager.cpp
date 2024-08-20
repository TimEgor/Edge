#include "PhysicsSceneCollisionManager.h"

#include "EdgePhysics/Physics/Entity/PhysicsEntity.h"
#include "EdgePhysics/Physics/Scene/PhysicsScene.h"

#include "PhysicsSceneCollisionCollection.h"
#include "BroadPhases/BruteforcePhysicsBroadPhase.h"

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

	m_broadPhase = new BruteforcePhysicsBroadPhase();
	EDGE_CHECK_INITIALIZATION(m_broadPhase && m_broadPhase->init(this));

	return true;
}

void Edge::PhysicsSceneCollisionManager::release()
{
	EDGE_SAFE_DESTROY_WITH_RELEASING(m_broadPhase);
	EDGE_SAFE_DESTROY_WITH_RELEASING(m_collisionCollection);
}

void Edge::PhysicsSceneCollisionManager::addCollision(const PhysicsEntityCollisionReference& collision)
{
	if (!checkCollisionOwning(collision))
	{
		return;
	}

	m_collisionCollection->addCollision(collision);

	m_broadPhase->addCollision(collision);
}

void Edge::PhysicsSceneCollisionManager::removeCollision(const PhysicsEntityCollisionReference& collision)
{
	if (!checkCollisionOwning(collision))
	{
		return;
	}

	m_broadPhase->removeCollision(collision);

	m_collisionCollection->removeCollision(collision);
}

Edge::PhysicsEntityCollisionReference Edge::PhysicsSceneCollisionManager::getCollision(PhysicsSceneCollisionID id)
{
	return m_collisionCollection->getCollision(id);
}

void Edge::PhysicsSceneCollisionManager::rayCast(const FloatVector3& origin, const FloatVector3& end, PointCastingResultCollector& resultCollector) const
{
	m_broadPhase->rayCast(origin, end, resultCollector);
}
