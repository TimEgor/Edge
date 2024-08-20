#include "BruteforcePhysicsBroadPhase.h"

#include "EdgePhysics/Physics/Collision/DefaultPhysicsEntityCollisionSceneContext.h"

#include "EdgeCommon/UtilsMacros.h"
#include "EdgePhysics/Physics/Collision/PhysicsSceneCollisionManager.h"

bool Edge::BruteforcePhysicsBroadPhase::init(const PhysicsSceneCollisionManagerReference& collisionManager)
{
	EDGE_CHECK_INITIALIZATION(!m_collisionManager);
	EDGE_CHECK_INITIALIZATION(m_ids.empty());

	m_collisionManager = collisionManager;

	m_ids.reserve(4096);

	return true;
}

void Edge::BruteforcePhysicsBroadPhase::release()
{
	m_ids = EntityPageCollection();

	m_collisionManager.reset();
}

void Edge::BruteforcePhysicsBroadPhase::addCollision(const PhysicsEntityCollisionReference& collision)
{
	if (!collision)
	{
		EDGE_ASSERT_FAIL_MESSAGE("Trying to add an invalid collision into broad phase.");
		return;
	}

	const PhysicsEntityCollisionSceneContextReference sceneContext = collision->getSceneContext();
	if (sceneContext->getType() != DefaultPhysicsEntityCollisionSceneContext::PhysicsEntityCollisionSceneContextType)
	{
		EDGE_ASSERT_FAIL_MESSAGE("Collision scene context has an invalid type.");
		return;
	}

	DefaultPhysicsEntityCollisionSceneContext& defaultSceneContext = sceneContext.getObjectCastRef<DefaultPhysicsEntityCollisionSceneContext>();

	if (defaultSceneContext.getBroadPhaseEntityIndex() != InvalidPhysicsSceneBroadPhaseEntityIndex)
	{
		EDGE_ASSERT_FAIL_MESSAGE("Trying to add an already added collision into broad phase.");
		return;
	}

	const PhysicsSceneCollisionID collisionID = defaultSceneContext.getCollisionID();

	m_ids.push_back(collisionID);
}

void Edge::BruteforcePhysicsBroadPhase::removeCollision(const PhysicsEntityCollisionReference& collision)
{
	if (!collision)
	{
		EDGE_ASSERT_FAIL_MESSAGE("Trying to remove an invalid collision from broad phase.");
		return;
	}

	const PhysicsEntityCollisionSceneContextReference sceneContext = collision->getSceneContext();
	if (sceneContext->getType() != DefaultPhysicsEntityCollisionSceneContext::PhysicsEntityCollisionSceneContextType)
	{
		EDGE_ASSERT_FAIL_MESSAGE("Collision scene context has an invalid type.");
		return;
	}

	DefaultPhysicsEntityCollisionSceneContext& defaultSceneContext = sceneContext.getObjectCastRef<DefaultPhysicsEntityCollisionSceneContext>();

	const PhysicsSceneActivationContextEntityIndex currentEntityIndex = defaultSceneContext.getBroadPhaseEntityIndex();
	if (currentEntityIndex == InvalidPhysicsSceneActivationContextEntityIndex)
	{
		EDGE_ASSERT_FAIL_MESSAGE("Trying to remove an already added collision into broad phase.");
		return;
	}

	defaultSceneContext.setBroadPhaseEntityIndex(InvalidPhysicsSceneActivationContextEntityIndex);

	const size_t idsCount = m_ids.size();
	if (currentEntityIndex < idsCount - 1)
	{
		const PhysicsSceneCollisionID exchangeCollisionID = m_ids[idsCount - 1];
		m_ids[currentEntityIndex] = exchangeCollisionID;
		m_collisionManager.getReference()->getCollision(exchangeCollisionID)->getSceneContext().getObjectCastRef<DefaultPhysicsEntityCollisionSceneContext>().setBroadPhaseEntityIndex(currentEntityIndex);
	}

	m_ids.pop_back();
}

void Edge::BruteforcePhysicsBroadPhase::rayCast(const FloatVector3& origin, const FloatVector3& end, PointCastingResultCollector& resultCollector) const
{
	const PhysicsSceneCollisionManagerReference collisionManager = m_collisionManager.getReference();

	for (const PhysicsSceneCollisionID collisionId : m_ids)
	{
		const PhysicsEntityCollisionReference collision = collisionManager->getCollision(collisionId);

		PhysicsCollisionQuery::PointCastingResult result;
		if (collision->rayCast(origin, end, result))
		{
			resultCollector.addHit(PointInstanceCastingResult{ collision, result });
		}

		if (resultCollector.shouldStopCollecting())
		{
			break;
		}
	}
}
