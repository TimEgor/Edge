#include "PhysicsSceneCollisionManager.h"

#include "EdgeCommon/Job/JobController.h"
#include "EdgeCommon/Profile/Profile.h"

#include "EdgePhysics/Physics/Physics.h"
#include "EdgePhysics/Physics/PhysicsCore.h"
#include "EdgePhysics/Physics/Collision/PhysicsCollisionContact.h"
#include "EdgePhysics/Physics/Collision/BroadPhases/BruteforcePhysicsBroadPhase.h"
#include "EdgePhysics/Physics/Entity/PhysicsEntity.h"
#include "EdgePhysics/Physics/Scene/PhysicsScene.h"

#include "PhysicsCollisionContactManager.h"
#include "PhysicsSceneCollisionCollection.h"

Edge::JobGraphReference Edge::PhysicsSceneCollisionManager::getCollisionFindingJobGraph(uint32_t jobCount, const CollisionFindingContextReference& context,
	const std::vector<PhysicsSceneEntityID>& activeEntityIDs)
{
	context->m_collisionCollector.resize(jobCount);

	JobGraphBuilder m_graphBuilder;

	static constexpr size_t minJobEntityCount = 50;

	const size_t activeEntityCount = activeEntityIDs.size();
	const size_t jobEntityCount = static_cast<size_t>(std::ceilf(static_cast<float>(activeEntityCount) / jobCount));
	const size_t perJobEntityCount = std::max(jobEntityCount, minJobEntityCount);

	size_t restEntityCount = activeEntityCount;
	size_t baseEntityIndex = 0;
	for (uint32_t jobIndex = 0; jobIndex < jobCount; ++jobIndex)
	{
		const size_t entityCount = std::min(restEntityCount, perJobEntityCount);

		m_graphBuilder.addJob(
			createLambdaJob([this, context, activeEntityIDs, baseEntityIndex, entityCount, jobIndex]()
				{
					const size_t lastEntityIDIndex = baseEntityIndex + entityCount;
					for (size_t idIndex = baseEntityIndex; idIndex < lastEntityIDIndex; ++idIndex)
					{
						const PhysicsEntityReference& activeEntity = m_scene.getReference()->getEntity(activeEntityIDs[idIndex]);
						const PhysicsEntityCollisionReference& activeEntityCollision = activeEntity->getCollision();

						m_broadPhase->findCollidingPairs(activeEntityCollision, context->m_collisionCollector[jobIndex]);
					}
				}, "Find collision contacts"));

		restEntityCount -= entityCount;
		baseEntityIndex += entityCount;
	}

	EDGE_ASSERT(restEntityCount == 0);

	return m_graphBuilder.getGraph();
}

void Edge::PhysicsSceneCollisionManager::prepareCollisionContacts(const CollisionFindingContextReference& context) const
{
	for (const auto& collectedResult : context->m_collisionCollector)
	{
		const size_t collisionPairCount = collectedResult.size();
		for (size_t collisionPairIndex = 0; collisionPairIndex < collisionPairCount; ++collisionPairIndex)
		{
			const PhysicsBroadPhase::CollisionPair& pair = collectedResult[collisionPairIndex];
			const PhysicsCollisionContactID contactID(pair.m_collision1, pair.m_collision2);

			m_contactManager->addContact(contactID);
		}
	}
}

bool Edge::PhysicsSceneCollisionManager::checkCollision(const PhysicsEntityCollisionReference& collision) const
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

	m_contactManager = new PhysicsCollisionContactManager();
	EDGE_CHECK_INITIALIZATION(m_contactManager && m_contactManager->init(this));

	m_broadPhase = new BruteforcePhysicsBroadPhase();
	EDGE_CHECK_INITIALIZATION(m_broadPhase && m_broadPhase->init(this));

	return true;
}

void Edge::PhysicsSceneCollisionManager::release()
{
	EDGE_SAFE_DESTROY_WITH_RELEASING(m_broadPhase);

	EDGE_SAFE_DESTROY_WITH_RELEASING(m_contactManager);
	EDGE_SAFE_DESTROY_WITH_RELEASING(m_collisionCollection);
}

Edge::JobGraphReference Edge::PhysicsSceneCollisionManager::getPreparationJobGraph(const std::vector<PhysicsSceneEntityID>& activeEntityIDs)
{
	JobGraphBuilder m_graphBuilder;

	const size_t jobCount = GetPhysics().getJobController().getJobExecutorCount();

	CollisionFindingContextReference findingCollisionContext = new CollisionFindingContext();

	const JobGraphBuilder::JobGraphJobID collisionFindingJobsID = m_graphBuilder.addJobGraph(
		getCollisionFindingJobGraph(jobCount, findingCollisionContext, activeEntityIDs));

	const JobGraphBuilder::JobGraphJobID prepareCollisionJobID = m_graphBuilder.addJobAfter(
		createLambdaJob([this, findingCollisionContext]()
			{
				prepareCollisionContacts(findingCollisionContext);
			}, "Prepare collision contacts"),
		collisionFindingJobsID);

	const JobGraphBuilder::JobGraphJobID updateCollisionJobID = m_graphBuilder.addJobAfter(
		createLambdaJob([this]()
			{
				m_contactManager->updateContacts();
			}, "Update collision contacts"),
		prepareCollisionJobID);

	return m_graphBuilder.getGraph();
}

Edge::JobGraphReference Edge::PhysicsSceneCollisionManager::getApplyingJobGraph()
{
	JobGraphBuilder m_graphBuilder;

	const JobGraphBuilder::JobGraphJobID applyCollisionJobID = m_graphBuilder.addJob(
		createLambdaJob([this]()
			{
				m_contactManager->applyCollision();
			}, "Apply collision")
	);

	return m_graphBuilder.getGraph();
}

void Edge::PhysicsSceneCollisionManager::addCollision(const PhysicsEntityCollisionReference& collision)
{
	if (!checkCollision(collision))
	{
		return;
	}

	m_collisionCollection->addCollision(collision);

	m_broadPhase->addCollision(collision);
}

void Edge::PhysicsSceneCollisionManager::removeCollision(const PhysicsEntityCollisionReference& collision)
{
	if (!checkCollision(collision))
	{
		return;
	}

	m_broadPhase->removeCollision(collision);

	m_collisionCollection->removeCollision(collision);
}

Edge::PhysicsEntityCollisionReference Edge::PhysicsSceneCollisionManager::getCollision(PhysicsSceneCollisionID id) const
{
	return m_collisionCollection->getCollision(id);
}

void Edge::PhysicsSceneCollisionManager::updateCollisionTransform(const PhysicsEntityCollisionReference& collision)
{
	if (!checkCollision(collision))
	{
		return;
	}

	m_broadPhase->updateCollisionBoundChanged(collision);
	m_contactManager->markContactsForChecking(collision);
}

void Edge::PhysicsSceneCollisionManager::rayCast(const FloatVector3& origin, const FloatVector3& end, PointCastingResultCollector& resultCollector) const
{
	m_broadPhase->rayCast(origin, end, resultCollector);
}

const Edge::PhysicsCollisionContactManager& Edge::PhysicsSceneCollisionManager::getContactManager() const
{
	EDGE_ASSERT(m_contactManager);
	return *m_contactManager;
}

Edge::PhysicsSceneWeakReference Edge::PhysicsSceneCollisionManager::getScene() const
{
	return m_scene;
}
