#include "PhysicsSceneActiveEntityCollection.h"

#include "EdgeCommon/UtilsMacros.h"

#include "DefaultPhysicsEntitySceneContext.h"
#include "PhysicsSceneEntityManager.h"

bool Edge::PhysicsSceneActiveEntityCollection::init(const PhysicsSceneEntityManagerReference& manager)
{
	EDGE_CHECK_INITIALIZATION(m_ids.empty());
	EDGE_CHECK_INITIALIZATION(manager);

	m_ids.reserve(4096);

	m_manager = manager;

	return true;
}

void Edge::PhysicsSceneActiveEntityCollection::release()
{
	m_ids = EntityCollection();
}

void Edge::PhysicsSceneActiveEntityCollection::addEntity(const PhysicsEntityReference& entity)
{
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

	m_ids.push_back(defaultSceneContext.getSceneEntityID());

	defaultSceneContext.setActivationContextIndex(m_ids.size() - 1);
}

void Edge::PhysicsSceneActiveEntityCollection::removeEntity(const PhysicsEntityReference& entity)
{
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

	defaultSceneContext.setActivationContextIndex(InvalidPhysicsSceneActivationContextEntityIndex);

	const size_t entityCount = m_ids.size();
	if (currentEntityIndex < entityCount - 1)
	{
		const PhysicsSceneEntityID exchangeEntityID = m_ids[entityCount - 1];
		m_ids[currentEntityIndex] = exchangeEntityID;
		m_manager.getReference()->getEntity(exchangeEntityID)->getSceneContext().getObjectCastRef<DefaultPhysicsEntitySceneContext>().setActivationContextIndex(currentEntityIndex);
	}

	m_ids.pop_back();
}
