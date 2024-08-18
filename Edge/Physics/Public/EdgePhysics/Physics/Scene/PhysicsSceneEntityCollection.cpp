#include "PhysicsSceneEntityCollection.h"

#include "EdgePhysics/Physics/Entity/PhysicsEntity.h"

#include "DefaultPhysicsEntitySceneContext.h"
#include "PhysicsScene.h"

bool Edge::DefaultPhysicsEntitySceneContextCollection::init()
{
	EDGE_CHECK_INITIALIZATION(m_pool.init());

	return true;
}

void Edge::DefaultPhysicsEntitySceneContextCollection::release()
{
	m_pool.release();
}

Edge::PhysicsEntitySceneContext* Edge::DefaultPhysicsEntitySceneContextCollection::createContext()
{
	return createDefaultContext();
}

void Edge::DefaultPhysicsEntitySceneContextCollection::destroyContext(PhysicsEntitySceneContext* context)
{
	if (!context || context->getType() != DefaultPhysicsEntitySceneContext::PhysicsEntitySceneContextType)
	{
		EDGE_ASSERT_FAIL_MESSAGE("Trying to destroying of an invalid context.");
		return;
	}

	destroyDefaultContext(static_cast<DefaultPhysicsEntitySceneContext*>(context));
}

Edge::DefaultPhysicsEntitySceneContext* Edge::DefaultPhysicsEntitySceneContextCollection::createDefaultContext()
{
	EntitySceneContextPool::NewElementInfo newContextInfo;
	m_pool.addElement(newContextInfo);

	DefaultPhysicsEntitySceneContext* context = newContextInfo.m_elementPtr;
	context->setContextCollection(this, newContextInfo.m_elementHandle.getKey());

	return context;
}

void Edge::DefaultPhysicsEntitySceneContextCollection::destroyDefaultContext(DefaultPhysicsEntitySceneContext* context)
{
	if (!context)
	{
		EDGE_ASSERT_FAIL_MESSAGE("Trying to destroying of an invalid context.");
		return;
	}

	m_pool.removeElement(context->getSceneContextID());
}

bool Edge::PhysicsSceneEntityCollection::init(const PhysicsSceneReference& scene)
{
	m_scene = scene;
	EDGE_CHECK_INITIALIZATION(m_scene);

	EDGE_CHECK_INITIALIZATION(m_entityPool.init());

	m_sceneContextManager = new DefaultPhysicsEntitySceneContextCollection();
	EDGE_CHECK_INITIALIZATION(m_sceneContextManager && m_sceneContextManager->init());

	return true;
}

void Edge::PhysicsSceneEntityCollection::release()
{
	m_scene.reset();

	m_sceneContextManager.reset();
	m_entityPool.release();
}

Edge::PhysicsSceneEntityID Edge::PhysicsSceneEntityCollection::addEntity(const PhysicsEntityReference& entity)
{
	if (!entity)
	{
		return InvalidPhysicsSceneEntityID;
	}

	const PhysicsSceneEntityID entityID = m_entityPool.addElement(entity).m_elementHandle.getKey();


	if (entityID != InvalidPhysicsSceneEntityID)
	{
		DefaultPhysicsEntitySceneContext* sceneContext = m_sceneContextManager->createDefaultContext();
		entity->setSceneContext(sceneContext);
		sceneContext->setScene(m_scene.getReference(), entityID);
	}

	return entityID;
}

void Edge::PhysicsSceneEntityCollection::removeEntity(const PhysicsEntityReference& entity)
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


	DefaultPhysicsEntitySceneContext& defaultSceneContext = sceneContext.getObjectCastRef<DefaultPhysicsEntitySceneContext>();
	const PhysicsSceneEntityID entityID = defaultSceneContext.getSceneEntityID();
	defaultSceneContext.setScene(nullptr, InvalidPhysicsSceneEntityID);

	entity->setSceneContext(nullptr);

	if (entityID == InvalidPhysicsSceneEntityID)
	{
		EDGE_ASSERT_FAIL_MESSAGE("Scene context has an invalid data.");
		return;
	}

	m_entityPool.removeElement(entityID);
}

Edge::PhysicsEntityReference Edge::PhysicsSceneEntityCollection::getEntity(PhysicsSceneEntityID entityID) const
{
	return *m_entityPool.getElement(EntityHandle(entityID));
}
