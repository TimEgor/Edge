#include "PhysicsSceneEntityManager.h"

#include "EdgePhysics/Physics/Entity/PhysicsEntity.h"

bool Edge::EntityManager::init(const PhysicsSceneReference& scene)
{
	m_scene = scene;
	EDGE_CHECK_INITIALIZATION(m_scene);

	{
		LockGuard locker(m_entityPoolMutex);
		EDGE_CHECK_INITIALIZATION(m_entityPool.init());
		EDGE_CHECK_INITIALIZATION(m_sceneContextPool.init());
	}

	return true;
}

void Edge::EntityManager::release()
{
	m_scene.reset();

	{
		LockGuard locker(m_entityPoolMutex);
		m_entityPool.release();
		m_sceneContextPool.release();
	}
}

Edge::PhysicsSceneEntityID Edge::EntityManager::addEntity(const PhysicsEntityReference& entity)
{
	if (!entity)
	{
		return InvalidPhysicsSceneEntityID;
	}

	PhysicsSceneEntityID entityID = InvalidPhysicsSceneEntityID;

	DefaultPhysicsEntitySceneContext* sceneContext = nullptr;

	{
		LockGuard locker(m_entityPoolMutex);
		entityID = m_entityPool.addElement(entity).m_elementHandle.getKey();

		EntitySceneContextPool::NewElementInfo newContextInfo;
		m_sceneContextPool.addElement(newContextInfo, entity.getObjectRef());

		EDGE_ASSERT(entityID == newContextInfo.m_elementHandle.getKey());

		sceneContext = newContextInfo.m_elementPtr;
	}

	if (entityID != InvalidPhysicsSceneEntityID)
	{
		entity->setSceneContext(sceneContext);
		sceneContext->setScene(m_scene.getReference(), entityID);
	}

	return entityID;
}

void Edge::EntityManager::removeEntity(const PhysicsEntityReference& entity)
{
	if (!entity)
	{
		return;
	}

	PhysicsEntitySceneContextReference sceneContext = entity->getSceneContext();
	if (sceneContext->getType() != DefaultPhysicsEntitySceneContext::getPhysicsEntitySceneContextType())
	{
		EDGE_ASSERT_FAIL_MESSAGE("Entity scene context has an invalid type.");
		return;
	}

	PhysicsSceneEntityID entityID = InvalidPhysicsSceneEntityID;

	{
		DefaultPhysicsEntitySceneContext& defaultSceneContext = sceneContext.getObjectCastRef<DefaultPhysicsEntitySceneContext>();
		entityID = defaultSceneContext.getSceneEntityID();
		defaultSceneContext.setScene(nullptr, InvalidPhysicsSceneEntityID);
	}

	if (entityID == InvalidPhysicsSceneEntityID)
	{
		EDGE_ASSERT_FAIL_MESSAGE("Scene context has an invalid data.");
		return;
	}

	removeEntity(entityID);
}

void Edge::EntityManager::removeEntity(PhysicsSceneEntityID entityID)
{
	if (entityID == InvalidPhysicsSceneEntityID)
	{
		return;
	}

	LockGuard locker(m_entityPoolMutex);
	m_entityPool.removeElement(entityID);
	m_sceneContextPool.removeElement(entityID);
}

Edge::PhysicsEntityReference Edge::EntityManager::getEntity(PhysicsSceneEntityID entityID) const
{
	SharedLockGuard locker(m_entityPoolMutex);
	return *m_entityPool.getElement(EntityHandle(entityID));
}
