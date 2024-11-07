#include "PhysicsScene.h"

#include "EdgeCommon/UtilsMacros.h"
#include "EdgeCommon/Job/JobController.h"
#include "EdgeCommon/Profile/Profile.h"

#include "EdgePhysics/Physics/Physics.h"
#include "EdgePhysics/Physics/PhysicsCore.h"

Edge::JobGraphReference Edge::PhysicsScene::getUpdateJobGraph(float deltaTime)
{
	JobGraphBuilder m_graphBuilder;

	const JobGraphBuilder::JobGraphJobID collisionPreparationJobsID = m_graphBuilder.addJobGraph(
		m_collisionManager->getPreparationJobGraph(m_entityManager->getActiveEntities()));

	const JobGraphBuilder::JobGraphJobID collisionApplyingJobsID = m_graphBuilder.addJobGraphAfter(
		m_collisionManager->getApplyingJobGraph(),
		collisionPreparationJobsID);

	const JobGraphBuilder::JobGraphJobID applyingForceJobID = m_graphBuilder.addJobGraphAfter(
		m_entityManager->getUpdateJobGraph(deltaTime, m_gravity),
		collisionApplyingJobsID);

	return m_graphBuilder.getGraph();
}

Edge::PhysicsScene::PhysicsScene(const PhysicsWorldReference& world)
	: m_world(world) {}

bool Edge::PhysicsScene::init()
{
	m_entityManager = new PhysicsSceneEntityManager();
	EDGE_CHECK_INITIALIZATION(m_entityManager && m_entityManager->init(this));

	m_collisionManager = new PhysicsSceneCollisionManager();
	EDGE_CHECK_INITIALIZATION(m_collisionManager && m_collisionManager->init(this));

	return true;
}

void Edge::PhysicsScene::release()
{
	m_entityManager.reset();
	m_collisionManager.reset();
}

void Edge::PhysicsScene::update(float deltaTime)
{
	EDGE_PROFILE_BLOCK_EVENT("Phys scene update");

	JobController& jobContoller = GetPhysics().getJobController();

	const JobGraphReference physSceneUpdateJobGraph = getUpdateJobGraph(deltaTime);
	jobContoller.addJobGraph(physSceneUpdateJobGraph);
	jobContoller.wait(physSceneUpdateJobGraph);
}

Edge::PhysicsSceneEntityID Edge::PhysicsScene::addEntity(const PhysicsEntityReference& entity, bool activate)
{
	const PhysicsSceneEntityID entityID = m_entityManager->addEntity(entity);

	if (entityID == InvalidPhysicsSceneActivationContextEntityIndex)
	{
		return InvalidPhysicsSceneActivationContextEntityIndex;
	}

	const PhysicsEntityCollisionReference entityCollision = entity->getCollision();
	if (entityCollision)
	{
		m_collisionManager->addCollision(entityCollision);
	}

	return entityID;
}

void Edge::PhysicsScene::removeEntity(PhysicsSceneEntityID entityID)
{
	m_entityManager->removeEntity(entityID);
}

void Edge::PhysicsScene::removeEntity(const PhysicsEntityReference& entity)
{
	if (entity)
	{
		const PhysicsEntityCollisionReference entityCollision = entity->getCollision();
		if (entityCollision)
		{
			m_collisionManager->removeCollision(entityCollision);
		}
	}

	m_entityManager->removeEntity(entity);
}

Edge::PhysicsEntityReference Edge::PhysicsScene::getEntity(PhysicsSceneEntityID entityID) const
{
	return m_entityManager->getEntity(entityID);
}

void Edge::PhysicsScene::makeTransformChangingNotification(const PhysicsEntityReference& entity)
{
	if (!entity)
	{
		return;
	}

	const PhysicsEntityCollisionReference collision = entity->getCollision();
	m_collisionManager->updateCollisionTransform(collision);
}

Edge::PhysicsSceneEntityManagerReference Edge::PhysicsScene::getEntityManager() const
{
	return m_entityManager;
}

Edge::PhysicsSceneCollisionManagerReference Edge::PhysicsScene::getCollisionManager() const
{
	return m_collisionManager;
}

Edge::PhysicsWorldWeakReference Edge::PhysicsScene::getWorld()
{
	return m_world;
}
