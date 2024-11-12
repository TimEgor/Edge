#include "PhysicsSceneEntityManager.h"

#include "EdgePhysics/Physics/Scene/PhysicsScene.h"

#include "PhysicsSceneActiveEntityCollection.h"
#include "PhysicsSceneEntityCollection.h"

bool Edge::PhysicsSceneEntityManager::init(const PhysicsSceneReference& scene)
{
	m_scene = scene;

	m_entityCollection = new PhysicsSceneEntityCollection();
	EDGE_CHECK_INITIALIZATION(m_entityCollection && m_entityCollection->init(this));

	m_activeEntityCollection = new PhysicsSceneActiveEntityCollection();
	EDGE_CHECK_INITIALIZATION(m_activeEntityCollection && m_activeEntityCollection->init(this));

	return true;
}

void Edge::PhysicsSceneEntityManager::release()
{
	m_scene.reset();

	EDGE_SAFE_DESTROY_WITH_RELEASING(m_activeEntityCollection);
	EDGE_SAFE_DESTROY_WITH_RELEASING(m_entityCollection);
}

Edge::JobGraphReference Edge::PhysicsSceneEntityManager::getAccelerationApplyingJobGraph(float deltaTime, const FloatVector3& gravity)
{
	JobGraphBuilder m_graphBuilder;

	const JobGraphBuilder::JobGraphJobID accelerationApplyingJobID = m_graphBuilder.addJob(
		createLambdaJob([dt = deltaTime, gravity = gravity, this]()
			{
				applyAcceleration(dt, gravity);
			}, "Apply acceleration")
	);

	return m_graphBuilder.getGraph();
}

Edge::JobGraphReference Edge::PhysicsSceneEntityManager::getVelocityIntegrationJobGraph(float deltaTime)
{
	JobGraphBuilder m_graphBuilder;

	const JobGraphBuilder::JobGraphJobID velocityIntegrationJobID = m_graphBuilder.addJob(
		createLambdaJob([dt = deltaTime, this]()
			{
				integrateVelocity(dt);
			}, "Integrate velocity")
	);

	return m_graphBuilder.getGraph();
}

void Edge::PhysicsSceneEntityManager::applyAcceleration(float deltaTime, const FloatVector3& gravity)
{
	const PhysicsSceneActiveEntityCollection::EntityCollection& activeEntityIDs = m_activeEntityCollection->getEntities();

	for (PhysicsSceneEntityID id : activeEntityIDs)
	{
		const PhysicsEntityReference entity = getEntity(id);
		const PhysicsEntityMotionReference entityMotion = entity->getMotion();
		entityMotion->applyAcceleration(deltaTime, gravity);
	}
}

void Edge::PhysicsSceneEntityManager::integrateVelocity(float deltaTime)
{
	const PhysicsSceneActiveEntityCollection::EntityCollection& activeEntityIDs = m_activeEntityCollection->getEntities();

	for (PhysicsSceneEntityID id : activeEntityIDs)
	{
		const PhysicsEntityReference entity = getEntity(id);
		const PhysicsEntityMotionReference entityMotion = entity->getMotion();
		entity->updateTransformWithMotion(deltaTime);
	}
}

Edge::PhysicsSceneEntityID Edge::PhysicsSceneEntityManager::addEntity(const PhysicsEntityReference& entity, bool activate)
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

	const PhysicsSceneEntityID entityID = m_entityCollection->addEntity(entity);
	if (entityID == InvalidPhysicsSceneEntityID)
	{
		return InvalidPhysicsSceneEntityID;
	}

	if (activate)
	{
		activateEntity(entity);
	}

	return entityID;
}

void Edge::PhysicsSceneEntityManager::removeEntity(PhysicsSceneEntityID entityID)
{
	const PhysicsEntityReference entity = getEntity(entityID);
	removeEntity(entity);
}

void Edge::PhysicsSceneEntityManager::removeEntity(const PhysicsEntityReference& entity)
{
	if (!entity)
	{
		return;
	}

	deactivateEntity(entity);

	m_entityCollection->removeEntity(entity);
}

Edge::PhysicsEntityReference Edge::PhysicsSceneEntityManager::getEntity(PhysicsSceneEntityID entityID) const
{
	return m_entityCollection->getEntity(entityID);
}

void Edge::PhysicsSceneEntityManager::activateEntity(PhysicsSceneEntityID entityID)
{
	activateEntity(getEntity(entityID));
}

void Edge::PhysicsSceneEntityManager::activateEntity(const PhysicsEntityReference& entity)
{
	if (!entity || !entity->getMotion() || entity->isActive())
	{
		return;
	}

	m_activeEntityCollection->addEntity(entity);
}

void Edge::PhysicsSceneEntityManager::deactivateEntity(PhysicsSceneEntityID entityID)
{
	deactivateEntity(getEntity(entityID));
}

void Edge::PhysicsSceneEntityManager::deactivateEntity(const PhysicsEntityReference& entity)
{
	if (!entity || !entity->getMotion() || !entity->isActive())
	{
		return;
	}

	m_activeEntityCollection->removeEntity(entity);
}

const Edge::PhysicsSceneActiveEntityCollection::EntityCollection& Edge::PhysicsSceneEntityManager::getActiveEntities() const
{
	EDGE_ASSERT(m_activeEntityCollection);
	return m_activeEntityCollection->getEntities();
}

Edge::PhysicsSceneWeakReference Edge::PhysicsSceneEntityManager::getScene() const
{
	return m_scene;
}
