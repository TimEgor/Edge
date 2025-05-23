#include "PhysicsScene.h"

#include "EdgeCommon/UtilsMacros.h"
#include "EdgeCommon/Job/JobController.h"
#include "EdgeCommon/Profile/Profile.h"

#include "EdgePhysics/Physics/Physics.h"
#include "EdgePhysics/Physics/PhysicsCore.h"
#include "EdgePhysics/Physics/Collision/Scene/PhysicsCollisionConstraintManager.h"

Edge::JobGraphReference Edge::PhysicsScene::getUpdateJobGraph(ComputeValueType deltaTime)
{
	JobGraphBuilder m_graphBuilder;

	const JobGraphBuilder::JobGraphJobID accelerationApplyingJobID = m_graphBuilder.addJobGraph(
		m_entityManager->getAccelerationApplyingJobGraph(deltaTime, m_gravity));

	const JobGraphBuilder::JobGraphJobID collisionPreparationJobsID = m_graphBuilder.addJobGraphAfter(
		m_collisionManager->getPreparationJobGraph(m_entityManager->getActiveEntities()),
		accelerationApplyingJobID);

	const JobGraphBuilder::JobGraphJobID constraintPreSolvingJobsID = m_graphBuilder.addJobGraphAfter(
		getConstraintPreparationJobGraph(deltaTime),
		collisionPreparationJobsID);

	const JobGraphBuilder::JobGraphJobID constraintVelocitySolvingJobsID = m_graphBuilder.addJobGraphAfter(
		getConstraintVelocitySolvingJobGraph(deltaTime),
		constraintPreSolvingJobsID);

	const JobGraphBuilder::JobGraphJobID velocityIntegrationJobsID = m_graphBuilder.addJobGraphAfter(
		m_entityManager->getVelocityIntegrationJobGraph(deltaTime),
		constraintVelocitySolvingJobsID);

	const JobGraphBuilder::JobGraphJobID constraintPositionSolvingJobsID = m_graphBuilder.addJobGraphAfter(
		getConstraintPositionSolvingJobGraph(deltaTime),
		velocityIntegrationJobsID);

	return m_graphBuilder.getGraph();
}

Edge::JobGraphReference Edge::PhysicsScene::getConstraintPreparationJobGraph(ComputeValueType deltaTime)
{
	JobGraphBuilder m_graphBuilder;

	const JobGraphBuilder::JobGraphJobID collisionConstraintJobID = m_graphBuilder.addJobGraph(
		m_collisionManager->getCollisionConstraintManager().getPreSolvingJobGraph(deltaTime));

	const JobGraphBuilder::JobGraphJobID generalConstraintJobsID = m_graphBuilder.addJobGraphAfter(
		m_constraintManager->getPreSolvingJobGraph(deltaTime),
		collisionConstraintJobID);

	return m_graphBuilder.getGraph();
}

Edge::JobGraphReference Edge::PhysicsScene::getConstraintVelocitySolvingJobGraph(ComputeValueType deltaTime)
{
	JobGraphBuilder m_graphBuilder;

	const JobGraphBuilder::JobGraphJobID collisionConstraintJobID = m_graphBuilder.addJobGraph(
		m_collisionManager->getCollisionConstraintManager().getVelocitySolvingJobGraph());

	const JobGraphBuilder::JobGraphJobID generalConstraintJobsID = m_graphBuilder.addJobGraphAfter(
		m_constraintManager->getVelocitySolvingJobGraph(deltaTime),
		collisionConstraintJobID);

	return m_graphBuilder.getGraph();
}

Edge::JobGraphReference Edge::PhysicsScene::getConstraintPositionSolvingJobGraph(ComputeValueType deltaTime)
{
	JobGraphBuilder m_graphBuilder;

	const JobGraphBuilder::JobGraphJobID collisionConstraintJobID = m_graphBuilder.addJobGraph(
		m_collisionManager->getCollisionConstraintManager().getPositionSolvingJobGraph());

	const JobGraphBuilder::JobGraphJobID generalConstraintJobsID = m_graphBuilder.addJobGraphAfter(
		m_constraintManager->getPositionSolvingJobGraph(deltaTime),
		collisionConstraintJobID);

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

	m_constraintManager = new PhysicsSceneConstraintManager();
	EDGE_CHECK_INITIALIZATION(m_constraintManager && m_constraintManager->init(this));

	return true;
}

void Edge::PhysicsScene::release()
{
	m_entityManager.reset();
	m_collisionManager.reset();
	m_constraintManager.reset();
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
	if (!entity.isNull())
	{
		const PhysicsEntityCollisionReference entityCollision = entity->getCollision();
		if (!entityCollision.isNull())
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

Edge::PhysicsSceneConstraintID Edge::PhysicsScene::addConstraint(const PhysicsConstraintReference& constraint, bool activate)
{
	return m_constraintManager->addConstraint(constraint, activate);
}

void Edge::PhysicsScene::removeConstraint(PhysicsSceneConstraintID constraintID)
{
	m_constraintManager->removeConstraint(constraintID);
}

void Edge::PhysicsScene::removeConstraint(const PhysicsConstraintReference& constraint)
{
	m_constraintManager->removeConstraint(constraint);
}

Edge::PhysicsConstraintReference Edge::PhysicsScene::getConstraint(PhysicsSceneConstraintID constraintID) const
{
	return m_constraintManager->getConstraint(constraintID);
}

void Edge::PhysicsScene::makeTransformChangingNotification(const PhysicsEntityReference& entity)
{
	if (entity.isNull())
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
