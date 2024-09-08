#include "PhysicsSceneCollisionCollection.h"

#include "PhysicsSceneCollisionManager.h"

bool Edge::DefaultPhysicsEntityCollisionSceneContextCollection::init()
{
	EDGE_CHECK_INITIALIZATION(m_pool.init());

	return true;
}

void Edge::DefaultPhysicsEntityCollisionSceneContextCollection::release()
{
	m_pool.release();
}

Edge::PhysicsEntityCollisionSceneContext* Edge::DefaultPhysicsEntityCollisionSceneContextCollection::createContext()
{
	return createDefaultContext();
}

void Edge::DefaultPhysicsEntityCollisionSceneContextCollection::destroyContext(PhysicsEntityCollisionSceneContext* context)
{
	if (!context || context->getType() != DefaultPhysicsEntityCollisionSceneContext::PhysicsEntityCollisionSceneContextType)
	{
		EDGE_ASSERT_FAIL_MESSAGE("Trying to destroying of an invalid context.");
		return;
	}

	destroyDefaultContext(static_cast<DefaultPhysicsEntityCollisionSceneContext*>(context));
}

Edge::DefaultPhysicsEntityCollisionSceneContext* Edge::DefaultPhysicsEntityCollisionSceneContextCollection::createDefaultContext()
{
	CollisionSceneContextPool::NewElementInfo newContextInfo;
	m_pool.addElement(newContextInfo);

	DefaultPhysicsEntityCollisionSceneContext* context = newContextInfo.m_elementPtr;
	context->setContextCollection(this, newContextInfo.m_elementHandle.getKey());

	return context;
}

void Edge::DefaultPhysicsEntityCollisionSceneContextCollection::destroyDefaultContext(DefaultPhysicsEntityCollisionSceneContext* context)
{
	if (!context)
	{
		EDGE_ASSERT_FAIL_MESSAGE("Trying to destroying of an invalid context.");
		return;
	}

	m_pool.removeElement(context->getCollisionContextID());
}

bool Edge::PhysicsSceneCollisionCollection::init(const PhysicsSceneCollisionManagerReference& collisionManager)
{
	m_collisionManager = collisionManager;

	m_collisionSceneContextManager = new DefaultPhysicsEntityCollisionSceneContextCollection();
	EDGE_CHECK_INITIALIZATION(m_collisionSceneContextManager && m_collisionSceneContextManager->init());

	EDGE_CHECK_INITIALIZATION(m_collisionPool.init());

	return true;
}

void Edge::PhysicsSceneCollisionCollection::release()
{
	m_collisionPool.release();

	m_collisionSceneContextManager.reset();

	m_collisionManager.reset();
}

Edge::PhysicsSceneCollisionID Edge::PhysicsSceneCollisionCollection::addCollision(const PhysicsEntityCollisionReference& collision)
{
	const PhysicsSceneEntityID collisionID = m_collisionPool.addElement(collision).m_elementHandle.getKey();

	if (collisionID != InvalidPhysicsSceneEntityID)
	{
		DefaultPhysicsEntityCollisionSceneContext* collisionSceneContext = m_collisionSceneContextManager->createDefaultContext();
		collision->setSceneContext(collisionSceneContext);
		collisionSceneContext->setCollisionManager(m_collisionManager.getReference(), collisionID);
	}

	return collisionID;
}

void Edge::PhysicsSceneCollisionCollection::removeCollision(const PhysicsEntityCollisionReference& collision)
{
	const DefaultPhysicsEntityCollisionSceneContextReference defaultSceneContext = CollisionUtil::GetDefaultCollisionSceneContext(collision);
	const PhysicsSceneEntityID collisionID = defaultSceneContext->getCollisionID();
	defaultSceneContext->setCollisionManager(nullptr, InvalidPhysicsSceneEntityID);

	collision->setSceneContext(nullptr);

	if (collisionID == InvalidPhysicsSceneEntityID)
	{
		EDGE_ASSERT_FAIL_MESSAGE("Scene context has an invalid data.");
		return;
	}

	m_collisionPool.removeElement(collisionID);
}

Edge::PhysicsEntityCollisionReference Edge::PhysicsSceneCollisionCollection::getCollision(PhysicsSceneCollisionID collisionID) const
{
	return *m_collisionPool.getElement(collisionID);
}
