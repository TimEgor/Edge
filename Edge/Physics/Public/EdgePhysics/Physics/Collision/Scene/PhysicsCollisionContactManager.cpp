#include "PhysicsCollisionContactManager.h"

#include "EdgeCommon/UtilsMacros.h"
#include "EdgeCommon/Profile/Profile.h"

#include "EdgePhysics/Physics/Collision/Dispatchers/GJKCollisionDispatcher.h"
#include "EdgePhysics/Physics/Collision/Dispatchers/SphereVsSphereCollisionDispatcher.h"
#include "EdgePhysics/Physics/Collision/Scene/DefaultPhysicsEntityCollisionSceneContext.h"
#include "EdgePhysics/Physics/Collision/Shapes/PhysicsSphereShape.h"

#include "PhysicsCollisionConstraintManager.h"
#include "PhysicsSceneCollisionManager.h"

bool Edge::PhysicsCollisionContactManager::DispatcherContext::init()
{
#define GET_SHAPE_TYPE_ID(TYPE) (RTTI::GetTypeMetaInfoID<TYPE>())
#define CREATE_AND_ADD_DISPATCHER(DISPATCHER_TYPE, SHAPE_TYPE1, SHAPE_TYPE2)			\
	{																					\
		PhysicsCollisionDispatcher* newDispatcher = new DISPATCHER_TYPE();				\
		m_dispatchers.push_back(newDispatcher);											\
		m_dispatcherCollection->addDispatcher(SHAPE_TYPE1, SHAPE_TYPE2, newDispatcher);	\
	}

	m_dispatcherCollection = new PhysicsCollisionDispatcherCollection();
	EDGE_CHECK_INITIALIZATION(m_dispatcherCollection);

	CREATE_AND_ADD_DISPATCHER(SphereVsSphereCollisionDispatcher, GET_SHAPE_TYPE_ID(PhysicsSphereShape), GET_SHAPE_TYPE_ID(PhysicsSphereShape));

	PhysicsCollisionDispatcher* gjkDispatcher = new GJKCollisionDispatcher();
	m_dispatchers.push_back(gjkDispatcher);
	m_dispatcherCollection->setDefaultDispatcher(gjkDispatcher);

	return true;
}

void Edge::PhysicsCollisionContactManager::DispatcherContext::release()
{
	for (const auto dispatcher : m_dispatchers)
	{
		delete dispatcher;
	}

	EDGE_SAFE_DESTROY(m_dispatcherCollection);
}

Edge::PhysicsCollisionDispatcher* Edge::PhysicsCollisionContactManager::DispatcherContext::getDispatcher(
	PhysicsEntityCollisionShapeType type1,
	PhysicsEntityCollisionShapeType type2
) const
{
	EDGE_ASSERT(m_dispatcherCollection);
	return m_dispatcherCollection->getDispatcher(type1, type2);
}

uint32_t Edge::PhysicsCollisionContactManager::ContactCache::getNextContainerIndex() const
{
	return (m_writingContainerIndex + 1) % CacheContainerCount;
}

void Edge::PhysicsCollisionContactManager::ContactCache::prepareCache(uint32_t manifoldCount)
{
	m_writingContainerIndex = getNextContainerIndex();

	ContactCollection& collection = m_cacheCollection[m_writingContainerIndex];
	collection.reserve(manifoldCount);
	collection.clear();
}

Edge::PhysicsCollisionContactManager::ContactCache::ContactCollection& Edge::PhysicsCollisionContactManager::ContactCache::getWritingCollection()
{
	return m_cacheCollection[m_writingContainerIndex];
}

const Edge::PhysicsCollisionContactManager::ContactCache::ContactCollection& Edge::PhysicsCollisionContactManager::ContactCache::getReadingCollection() const
{
	const uint32_t readingContainerIndex = getNextContainerIndex();
	return m_cacheCollection[readingContainerIndex];
}

bool Edge::PhysicsCollisionContactManager::init(const PhysicsSceneCollisionManagerReference& collisionManager)
{
	m_collisionManager = collisionManager;
	EDGE_CHECK_INITIALIZATION(m_collisionManager);

	m_dispatcherContext = new DispatcherContext();
	EDGE_CHECK_INITIALIZATION(m_dispatcherContext && m_dispatcherContext->init());

	m_contactConstraintManager = new PhysicsCollisionConstraintManager();
	EDGE_CHECK_INITIALIZATION(m_contactConstraintManager);

	m_contactCache = new ContactCache();
	EDGE_CHECK_INITIALIZATION(m_contactCache);

	return true;
}

void Edge::PhysicsCollisionContactManager::release()
{
	EDGE_SAFE_DESTROY(m_contactCache);

	EDGE_SAFE_DESTROY(m_contactConstraintManager);
	EDGE_SAFE_DESTROY_WITH_RELEASING(m_dispatcherContext);

	m_collisionManager.reset();
}

Edge::JobGraphReference Edge::PhysicsCollisionContactManager::getPreSolvingJobGraph(ComputeValueType deltaTime)
{
	return m_contactConstraintManager->getPreSolvingJobGraph(deltaTime);
}

Edge::JobGraphReference Edge::PhysicsCollisionContactManager::getVelocitySolvingJobGraph(ComputeValueType deltaTime)
{
	return m_contactConstraintManager->getVelocitySolvingJobGraph(deltaTime);
}

Edge::JobGraphReference Edge::PhysicsCollisionContactManager::getPositionSolvingJobGraph(ComputeValueType deltaTime)
{
	return m_contactConstraintManager->getPositionSolvingJobGraph(deltaTime);
}

void Edge::PhysicsCollisionContactManager::prepareContacts(uint32_t manifoldCount, uint32_t pointCount)
{
	m_contactCache->prepareCache(manifoldCount);
	m_contactConstraintManager->prepareCollection(pointCount);
}

void Edge::PhysicsCollisionContactManager::addManifold(
	PhysicsCollisionContactID contactID,
	const PhysicsContactManifold& manifold,
	const PhysicsEntityReference& entity1,
	const PhysicsEntityReference& entity2
)
{
	const ContactCache::ContactCollection& readingCache = m_contactCache->getReadingCollection();
	ContactCache::ContactCollection& writingCache = m_contactCache->getWritingCollection();

	const ContactCache::ContactPointCollection* prevContactCacheData = nullptr;
	const auto prevContactCacheDataIter = readingCache.find(contactID);
	if (prevContactCacheDataIter != readingCache.end())
	{
		prevContactCacheData = &prevContactCacheDataIter->second;
	}

	const uint32_t contactPointCount = manifold.getContactPointCount();

	ContactCache::ContactPointCollection& contactCacheData = writingCache[contactID];
	contactCacheData.reserve(contactPointCount);

	for (uint32_t contactPointIndex = 0; contactPointIndex < contactPointCount; ++contactPointIndex)
	{
		const ComputeVector3& position1 = manifold.m_positions1[contactPointIndex];
		const ComputeVector3& position2 = manifold.m_positions2[contactPointIndex];

		PhysicsCollisionContactPoint& contactPoint = contactCacheData.emplace_back();
		contactPoint.m_position1 = position1;
		contactPoint.m_position2 = position2;
		contactPoint.m_normal = manifold.m_normal;
		contactPoint.m_depth = manifold.m_depth;

		if (prevContactCacheData)
		{
			const uint32_t prevContactPointCount = prevContactCacheData->size();

			for (uint32_t prevContactPointIndex = 0; prevContactPointIndex < prevContactPointCount; ++prevContactPointIndex)
			{
				const PhysicsCollisionContactPoint& prevContactPointData = (*prevContactCacheData)[prevContactPointIndex];

				const ComputeVector3& prevPosition1 = prevContactPointData.m_position1;
				const ComputeVector3& prevPosition2 = prevContactPointData.m_position2;

				if (position1.isEqual(prevPosition1, 0.001) && position2.isEqual(prevPosition2, 0.001))
				{
					contactPoint.m_cachedData = prevContactPointData.m_cachedData;
					break;
				}
			}
		}

		m_contactConstraintManager->addContact(entity1, entity2, contactPoint);
	}
}

void Edge::PhysicsCollisionContactManager::cacheConstraintDatas()
{
	m_contactConstraintManager->cacheApplyingData();
}

uint32_t Edge::PhysicsCollisionContactManager::dispatchCollision(
	const PhysicsEntityCollisionReference& collision1,
	const PhysicsEntityCollisionReference& collision2,
	CollisionManifoldCollection& result
) const
{
	const PhysicsEntityCollisionShapeType shapeType1 = collision1->getShape()->GetObjectTypeMetaInfoID();
	const PhysicsEntityCollisionShapeType shapeType2 = collision2->getShape()->GetObjectTypeMetaInfoID();

	PhysicsCollisionDispatcher* dispatcher = m_dispatcherContext->getDispatcher(shapeType1, shapeType2);
	if (!dispatcher)
	{
		return 0;
	}

	return dispatcher->dispatch(collision1, collision2, result);
}
