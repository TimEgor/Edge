#include "PhysicsSceneCollisionManager.h"

#include "EdgeCommon/Job/JobController.h"
#include "EdgeCommon/Profile/Profile.h"

#include "EdgePhysics/Physics/Physics.h"
#include "EdgePhysics/Physics/PhysicsCore.h"
#include "EdgePhysics/Physics/Collision/PhysicsCollisionContact.h"
#include "EdgePhysics/Physics/Collision/BroadPhases/BruteforcePhysicsBroadPhase.h"
#include "EdgePhysics/Physics/Entity/PhysicsEntity.h"
#include "EdgePhysics/Physics/Scene/PhysicsScene.h"

#include "PhysicsCollisionConstraintManager.h"
#include "PhysicsSceneCollisionCollection.h"

Edge::JobGraphReference Edge::PhysicsSceneCollisionManager::getCollisionFindingJobGraph(
	uint32_t jobCount,
	const CollisionFindingContextReference& findingContext,
	const std::vector<PhysicsSceneEntityID>& activeEntityIDs
)
{
	findingContext->m_collisionCollections.resize(jobCount);

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
			createLambdaJob(
				[this, findingContext, activeEntityIDs, baseEntityIndex, entityCount, jobIndex]()
				{
					PhysicsSceneReference scene = m_scene.getReference();

					const size_t lastEntityIDIndex = baseEntityIndex + entityCount;
					for (size_t idIndex = baseEntityIndex; idIndex < lastEntityIDIndex; ++idIndex)
					{
						const PhysicsEntityReference& activeEntity = scene->getEntity(activeEntityIDs[idIndex]);
						const PhysicsEntityCollisionReference& activeEntityCollision = activeEntity->getCollision();

						m_broadPhase->findCollidingPairs(activeEntityCollision, findingContext->m_collisionCollections[jobIndex]);
					}
				},
				"Find collision contacts"
			)
		);

		restEntityCount -= entityCount;
		baseEntityIndex += entityCount;
	}

	EDGE_ASSERT(restEntityCount == 0);

	return m_graphBuilder.getGraph();
}

Edge::JobGraphReference Edge::PhysicsSceneCollisionManager::getCollisionDispatchingJobGraph(
	uint32_t jobCount,
	const CollisionDispatchingContextReference& dispatchingContext,
	const CollisionFindingContextReference& findingContext
)
{
	dispatchingContext->m_manifoldCollections.resize(jobCount);
	dispatchingContext->m_manifoldContactIDCollections.resize(jobCount);
	dispatchingContext->m_contactPointCountCollection.resize(jobCount);

	JobGraphBuilder m_graphBuilder;

	for (uint32_t jobIndex = 0; jobIndex < jobCount; ++jobIndex)
	{
		dispatchingContext->m_contactPointCountCollection[jobIndex] = 0;

		m_graphBuilder.addJob(
			createLambdaJob(
				[this, findingContext, dispatchingContext, jobIndex]()
				{
					const PhysicsBroadPhase::PhysicsSceneCollisionPairCollection& collisionPairCollection = findingContext->m_collisionCollections[jobIndex];
					const size_t collisionPairCount = collisionPairCollection.size();

					PhysicsCollisionContactManager::CollisionManifoldCollection& manifolds = dispatchingContext->m_manifoldCollections[jobIndex];
					CollisionDispatchingContext::CollisionContactIDCollection& contactIDs = dispatchingContext->m_manifoldContactIDCollections[jobIndex];
					uint32_t& contactPointCount = dispatchingContext->m_contactPointCountCollection[jobIndex];

					for (size_t collisionIndex = 0; collisionIndex < collisionPairCount; ++collisionIndex)
					{
						const PhysicsBroadPhase::CollisionPair& pair = collisionPairCollection[collisionIndex];

						const PhysicsEntityCollisionReference collision1 = getCollision(pair.m_collision1);
						const PhysicsEntityCollisionReference collision2 = getCollision(pair.m_collision2);

						const PhysicsCollisionContactID contactID(pair.m_collision1, pair.m_collision2);

						const uint32_t prelManifoldCount = manifolds.size();

						contactPointCount += m_contactManager->dispatchCollision(collision1, collision2, manifolds);

						const uint32_t postManifoldCount = manifolds.size();

						const uint32_t newManifoldCount = postManifoldCount - prelManifoldCount;
						for (uint32_t manifoldIndex = 0; manifoldIndex < newManifoldCount; ++manifoldIndex)
						{
							contactIDs.emplace_back(contactID);
						}
					}
				},
				"Dispatch collision contacts"
			)
		);
	}

	return m_graphBuilder.getGraph();
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

	const uint32_t jobCount = GetPhysics().getJobController().getJobExecutorCount();

	CollisionFindingContextReference collisionFindingContext = new CollisionFindingContext();
	CollisionDispatchingContextReference collisionDispatchingContext = new CollisionDispatchingContext();

	const JobGraphBuilder::JobGraphJobID collisionFindingJobsID = m_graphBuilder.addJobGraph(
		getCollisionFindingJobGraph(jobCount, collisionFindingContext, activeEntityIDs)
	);

	const JobGraphBuilder::JobGraphJobID collisionDispatchingJobsID = m_graphBuilder.addJobGraphAfter(
		getCollisionDispatchingJobGraph(jobCount, collisionDispatchingContext, collisionFindingContext),
		collisionFindingJobsID
	);

	const JobGraphBuilder::JobGraphJobID collisionHandlingJobID = m_graphBuilder.addJobAfter(
		createLambdaJob(
			[this, collisionDispatchingContext, jobCount]()
			{
				uint32_t totalManifoldCount = 0;
				uint32_t totalPointCount = 0;
				for (uint32_t collectionIndex = 0; collectionIndex < jobCount; ++collectionIndex)
				{
					totalManifoldCount += collisionDispatchingContext->m_manifoldCollections[collectionIndex].size();
					totalPointCount += collisionDispatchingContext->m_contactPointCountCollection[collectionIndex];
				}

				m_contactManager->prepareContacts(totalManifoldCount, totalPointCount);

				for (uint32_t collectionIndex = 0; collectionIndex < jobCount; ++collectionIndex)
				{
					const PhysicsCollisionContactManager::CollisionManifoldCollection& manifoldCollection = collisionDispatchingContext->m_manifoldCollections[collectionIndex];
					const CollisionDispatchingContext::CollisionContactIDCollection& contactIdCollection = collisionDispatchingContext->m_manifoldContactIDCollections[collectionIndex];

					const uint32_t manifoldCount = manifoldCollection.size();
					const uint32_t contactCount = contactIdCollection.size();

					EDGE_ASSERT(manifoldCount == contactCount);

					for (uint32_t manifoldIndex = 0; manifoldIndex < manifoldCount; ++manifoldIndex)
					{
						PhysicsCollisionContactID contactID = contactIdCollection[manifoldIndex];
						const PhysicsEntityCollisionReference collision1 = getCollision(contactID.m_collisionID1);
						const PhysicsEntityCollisionReference collision2 = getCollision(contactID.m_collisionID2);

						const PhysicsEntityReference entity1 = collision1->getEntity();
						const PhysicsEntityReference entity2 = collision2->getEntity();

						const PhysicsContactManifold& manifold = manifoldCollection[manifoldIndex];

						m_contactManager->addManifold(contactID, manifold, entity1, entity2);
					}
				}
			},
			"Handle collision contacts"
		),
		collisionDispatchingJobsID
	);

	return m_graphBuilder.getGraph();
}

Edge::JobGraphReference Edge::PhysicsSceneCollisionManager::getPreSolvingJobGraph(ComputeValueType deltaTime)
{
	return m_contactManager->getPreSolvingJobGraph(deltaTime);
}

Edge::JobGraphReference Edge::PhysicsSceneCollisionManager::getVelocitySolvingJobGraph(ComputeValueType deltaTime)
{
	return m_contactManager->getVelocitySolvingJobGraph(deltaTime);
}

Edge::JobGraphReference Edge::PhysicsSceneCollisionManager::getPositionSolvingJobGraph(ComputeValueType deltaTime)
{
	return m_contactManager->getPositionSolvingJobGraph(deltaTime);
}

Edge::JobGraphReference Edge::PhysicsSceneCollisionManager::getPostConstraintSolvingJobGraph()
{
	JobGraphBuilder m_graphBuilder;

	m_graphBuilder.addJob(
		createLambdaJob(
			[this]()
			{
				m_contactManager->cacheConstraintDatas();
			},
			"Cache contact constraints"
		)
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
}

void Edge::PhysicsSceneCollisionManager::rayCast(const ComputeVector3& origin, const ComputeVector3& end, PointCastingResultCollector& resultCollector) const
{
	m_broadPhase->rayCast(origin, end, resultCollector);
}

Edge::PhysicsSceneWeakReference Edge::PhysicsSceneCollisionManager::getScene() const
{
	return m_scene;
}
