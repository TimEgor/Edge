#include "PhysicsSceneActiveEntityManager.h"

#include "EdgeCommon/UtilsMacros.h"

#include "DefaultPhysicsEntitySceneContext.h"

bool Edge::PhysicsSceneActiveEntityCollection::init(PhysicsSceneActivationContextEntityIndex pageSize,
	PhysicsSceneActivationContextEntityIndex maxFreePageCount)
{
	LockGuard locker(m_mutex);

	EDGE_CHECK_INITIALIZATION(m_entityPages.empty());
	EDGE_CHECK_INITIALIZATION(pageSize > 0);

	m_pageSize = pageSize;
	m_maxFreePageCount = maxFreePageCount;

	return true;
}

void Edge::PhysicsSceneActiveEntityCollection::release()
{
	LockGuard locker(m_mutex);

	for (EntityPage& page : m_entityPages)
	{
		EDGE_SAFE_DESTROY_ARRAY(page.m_entities);
	}

	m_entityPages = EntityPageCollection();

	m_currentPage = 0;
}

void Edge::PhysicsSceneActiveEntityCollection::addEntity(const PhysicsEntityReference& entity)
{
	LockGuard locker(m_mutex);

	if (!entity)
	{
		EDGE_ASSERT_FAIL_MESSAGE("Trying to activate an invalid entity.");
		return;
	}

	PhysicsEntitySceneContextReference sceneContext = entity->getSceneContext();
	if (sceneContext->getType() != DefaultPhysicsEntitySceneContext::getPhysicsEntitySceneContextType())
	{
		EDGE_ASSERT_FAIL_MESSAGE("Entity scene context has an invalid type.");
		return;
	}

	DefaultPhysicsEntitySceneContext& defaultSceneContext = sceneContext.getObjectCastRef<DefaultPhysicsEntitySceneContext>();

	if (defaultSceneContext.getActivationContextIndex() != InvalidPhysicsSceneActivationContextEntityIndex)
	{
		EDGE_ASSERT_FAIL_MESSAGE("Trying to activate an already activated entity.");
		return;
	}

	if (m_currentPage == m_entityPages.size())
	{
		EntityPage newPage;
		newPage.m_entities = new PhysicsEntityReference[m_pageSize];

		m_entityPages.push_back(newPage);
	}

	EntityPage& page = m_entityPages[m_currentPage];

	page.m_entities[page.m_size] = entity;

	defaultSceneContext.setActivationContextIndex(m_currentPage * m_pageSize + page.m_size);

	++page.m_size;

	if (page.m_size == m_pageSize)
	{
		++m_currentPage;
	}
}

void Edge::PhysicsSceneActiveEntityCollection::removeEntity(const PhysicsEntityReference& entity)
{
	LockGuard locker(m_mutex);

	if (!entity)
	{
		EDGE_ASSERT_FAIL_MESSAGE("Trying to deactivate an invalid entity.");
		return;
	}

	PhysicsEntitySceneContextReference sceneContext = entity->getSceneContext();
	if (sceneContext->getType() != DefaultPhysicsEntitySceneContext::getPhysicsEntitySceneContextType())
	{
		EDGE_ASSERT_FAIL_MESSAGE("Entity scene context has an invalid type.");
		return;
	}

	DefaultPhysicsEntitySceneContext& defaultSceneContext = sceneContext.getObjectCastRef<DefaultPhysicsEntitySceneContext>();

	const PhysicsSceneActivationContextEntityIndex currentEntityIndex = defaultSceneContext.getActivationContextIndex();
	if (currentEntityIndex == InvalidPhysicsSceneActivationContextEntityIndex)
	{
		EDGE_ASSERT_FAIL_MESSAGE("Trying to deactivate an inactive entity.");
		return;
	}

	const PhysicsSceneActivationContextEntityIndex pageIndex = currentEntityIndex / m_pageSize;
	const PhysicsSceneActivationContextEntityIndex index = currentEntityIndex % m_pageSize;

	EntityPage& page = m_entityPages[pageIndex];
	EntityPage& lastPage = m_entityPages[m_currentPage];

	PhysicsEntityReference* exchangedEntityPtr = &page.m_entities[index];
	(*exchangedEntityPtr)->getSceneContext().getObjectCastRef<DefaultPhysicsEntitySceneContext>().setActivationContextIndex(
		InvalidPhysicsSceneActivationContextEntityIndex);

	if (pageIndex != m_currentPage || index < page.m_size - 1)
	{
		*exchangedEntityPtr = lastPage.m_entities[lastPage.m_size - 1];
		(*exchangedEntityPtr)->getSceneContext().getObjectCastRef<DefaultPhysicsEntitySceneContext>().setActivationContextIndex(
			currentEntityIndex);
		--lastPage.m_size;
	}
	else
	{
		--page.m_size;
	}

	if (lastPage.m_size == 0 && m_currentPage != 0)
	{
		--m_currentPage;

		const size_t pageCount = m_entityPages.size();
		if (pageCount - m_currentPage > m_maxFreePageCount)
		{
			EDGE_SAFE_DESTROY_ARRAY(m_entityPages[pageCount - 1].m_entities);
			m_entityPages.pop_back();
		}
	}
}

Edge::PhysicsSceneActiveEntityCollectionIterator::PhysicsSceneActiveEntityCollectionIterator(
	const PhysicsSceneActiveEntityCollection& collection)
	: m_collection(collection)
{
	next();
}

Edge::PhysicsSceneActiveEntityCollectionIterator::operator bool() const
{
	return m_currentEntity;
}

Edge::PhysicsEntityReference Edge::PhysicsSceneActiveEntityCollectionIterator::getCurrentEntity() const
{
	return m_currentEntity;
}

bool Edge::PhysicsSceneActiveEntityCollectionIterator::next()
{
	SharedLockGuard locker(m_collection.m_mutex);

	++m_currentEntityIndex;

	if (m_currentPageIndex >= m_collection.m_entityPages.size())
	{
		m_currentEntity = nullptr;
		return false;
	}

	if (m_collection.m_pageSize <= m_currentEntityIndex || m_collection.m_entityPages[m_currentPageIndex].m_size <= m_currentEntityIndex)
	{
		m_currentEntity = nullptr;

		++m_currentPageIndex;
		m_currentEntityIndex = 0;
	}

	if (m_currentPageIndex < m_collection.m_entityPages.size() && m_collection.m_entityPages[m_currentPageIndex].m_size > m_currentEntityIndex)
	{
		m_currentEntity = m_collection.m_entityPages[m_currentPageIndex].m_entities[m_currentEntityIndex];
	}

	return m_currentEntity != nullptr;
}
