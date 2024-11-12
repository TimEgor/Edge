#include "PhysicsSceneActiveConstraintCollection.h"

#include "EdgeCommon/UtilsMacros.h"
#include "EdgeCommon/Assert/AssertCore.h"

#include "DefaultPhysicsConstraintSceneContext.h"
#include "PhysicsSceneConstraintManager.h"

bool Edge::PhysicsSceneActiveConstraintCollection::init(const PhysicsSceneConstraintManagerReference& manager)
{
	EDGE_CHECK_INITIALIZATION(m_ids.empty());
	EDGE_CHECK_INITIALIZATION(manager);

	m_ids.reserve(4096);

	m_manager = manager;

	return true;
}

void Edge::PhysicsSceneActiveConstraintCollection::release()
{
	m_ids = ConstraintCollection();
}

void Edge::PhysicsSceneActiveConstraintCollection::addConstraint(const PhysicsConstraintReference& constraint)
{
	if (!constraint)
	{
		EDGE_ASSERT_FAIL_MESSAGE("Trying to activate an invalid constraint.");
		return;
	}

	PhysicsConstraintSceneContextReference sceneContext = constraint->getSceneContext();
	if (sceneContext->getType() != DefaultPhysicsConstraintSceneContext::getPhysicsConstraintSceneContextType())
	{
		EDGE_ASSERT_FAIL_MESSAGE("Constraint scene context has an invalid type.");
		return;
	}

	DefaultPhysicsConstraintSceneContext& defaultSceneContext = sceneContext.getObjectCastRef<DefaultPhysicsConstraintSceneContext>();

	if (defaultSceneContext.getActivationContextIndex() != InvalidPhysicsSceneActivationContextConstraintIndex)
	{
		EDGE_ASSERT_FAIL_MESSAGE("Trying to activate an already activated constraint.");
		return;
	}

	m_ids.push_back(defaultSceneContext.getSceneConstraintID());

	defaultSceneContext.setActivationContextIndex(m_ids.size() - 1);
}

void Edge::PhysicsSceneActiveConstraintCollection::removeConstraint(const PhysicsConstraintReference& constraint)
{
	if (!constraint)
	{
		EDGE_ASSERT_FAIL_MESSAGE("Trying to deactivate an invalid constraint.");
		return;
	}

	PhysicsConstraintSceneContextReference sceneContext = constraint->getSceneContext();
	if (sceneContext->getType() != DefaultPhysicsConstraintSceneContext::getPhysicsConstraintSceneContextType())
	{
		EDGE_ASSERT_FAIL_MESSAGE("Constraint scene context has an invalid type.");
		return;
	}

	DefaultPhysicsConstraintSceneContext& defaultSceneContext = sceneContext.getObjectCastRef<DefaultPhysicsConstraintSceneContext>();

	const PhysicsSceneActivationContextConstraintIndex currentEntityIndex = defaultSceneContext.getActivationContextIndex();
	if (currentEntityIndex == InvalidPhysicsSceneActivationContextConstraintIndex)
	{
		EDGE_ASSERT_FAIL_MESSAGE("Trying to deactivate an inactive constraint.");
		return;
	}

	defaultSceneContext.setActivationContextIndex(InvalidPhysicsSceneActivationContextConstraintIndex);

	const size_t entityCount = m_ids.size();
	if (currentEntityIndex < entityCount - 1)
	{
		const PhysicsSceneConstraintID exchangeEntityID = m_ids[entityCount - 1];
		m_ids[currentEntityIndex] = exchangeEntityID;
		m_manager.getReference()->getConstraint(exchangeEntityID)->getSceneContext().getObjectCastRef<DefaultPhysicsConstraintSceneContext>().setActivationContextIndex(currentEntityIndex);
	}

	m_ids.pop_back();
}
