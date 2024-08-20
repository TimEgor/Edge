#include "PhysicsScene.h"

#include "EdgeCommon/Job/JobController.h"
#include "EdgeCommon/Profile/Profile.h"

#include "EdgePhysics/Physics/Physics.h"
#include "EdgePhysics/Physics/PhysicsCore.h"

#include "PhysicsSceneActiveEntityCollection.h"
#include "PhysicsSceneEntityCollection.h"

Edge::JobGraphReference Edge::PhysicsScene::getUpdateJobGraph(float deltaTime)
{
	JobGraphBuilder m_graphBuilder;

	JobGraphBuilder::JobGraphJobID applyingForceJobID = m_graphBuilder.addJob(
		createLambdaJob([this, deltaTime]() { entityUpdate(deltaTime); }, "Applying forces"));

	return m_graphBuilder.getGraph();
}

void Edge::PhysicsScene::entityUpdate(float deltaTime)
{
	PhysicsSceneActiveEntityCollectionIterator entityIter(*m_activeEntityCollection);

	while (entityIter)
	{
		PhysicsEntityReference entity = entityIter.getCurrentEntity();
		PhysicsEntityMotionReference entityMotion = entity->getMotion();
		entityMotion->applyAcceleration(deltaTime, m_gravity);
		entity->updateTransformWithMotion(deltaTime);

		entityIter.next();
	}
}

Edge::PhysicsScene::PhysicsScene(const PhysicsWorldReference& world)
	: m_world(world) {}

bool Edge::PhysicsScene::init()
{
	m_entityCollection = new PhysicsSceneEntityCollection();
	EDGE_CHECK_INITIALIZATION(m_entityCollection && m_entityCollection->init(this));
	m_activeEntityCollection = new PhysicsSceneActiveEntityCollection();
	EDGE_CHECK_INITIALIZATION(m_activeEntityCollection && m_activeEntityCollection->init());

	m_collisionManager = new PhysicsSceneCollisionManager();
	EDGE_CHECK_INITIALIZATION(m_collisionManager && m_collisionManager->init(this));

	return true;
}

void Edge::PhysicsScene::release()
{
	EDGE_SAFE_DESTROY_WITH_RELEASING(m_activeEntityCollection);
	EDGE_SAFE_DESTROY_WITH_RELEASING(m_entityCollection);
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
	if (!entity)
	{
		EDGE_ASSERT_FAIL_MESSAGE("Trying to add an invalid entity to the scene.");
		return InvalidPhysicsSceneEntityID;
	}

	if (entity->getSceneContext())
	{
		EDGE_ASSERT_FAIL_MESSAGE("Entity has already been added to a scene.");
		return InvalidPhysicsSceneEntityID;
	}

	const PhysicsSceneEntityID entityID = m_entityCollection->addEntity(entity) != InvalidPhysicsSceneEntityID;
	if (entityID == InvalidPhysicsSceneEntityID)
	{
		return InvalidPhysicsSceneEntityID;
	}

	if (activate)
	{
		activateEntity(entity);
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
	const PhysicsEntityReference entity = getEntity(entityID);
	removeEntity(entity);
}

void Edge::PhysicsScene::removeEntity(const PhysicsEntityReference& entity)
{
	if (!entity)
	{
		return;
	}

	const PhysicsEntityCollisionReference entityCollision = entity->getCollision();
	if (entityCollision)
	{
		m_collisionManager->removeCollision(entityCollision);
	}

	deactivateEntity(entity);

	m_entityCollection->removeEntity(entity);
}

Edge::PhysicsEntityReference Edge::PhysicsScene::getEntity(PhysicsSceneEntityID entityID) const
{
	return m_entityCollection->getEntity(entityID);
}

void Edge::PhysicsScene::activateEntity(PhysicsSceneEntityID entityID)
{
	activateEntity(getEntity(entityID));
}

void Edge::PhysicsScene::activateEntity(PhysicsEntityReference entity)
{
	if (!entity || !entity->getMotion() || entity->isActive())
	{
		return;
	}

	m_activeEntityCollection->addEntity(entity);
}

void Edge::PhysicsScene::deactivateEntity(PhysicsEntityReference entity)
{
	if (!entity || !entity->getMotion() || !entity->isActive())
	{
		return;
	}

	m_activeEntityCollection->removeEntity(entity);
}

Edge::PhysicsSceneCollisionManagerReference Edge::PhysicsScene::getCollisionManager() const
{
	return m_collisionManager;
}

Edge::PhysicsWorldWeakReference Edge::PhysicsScene::getWorld()
{
	return m_world;
}
