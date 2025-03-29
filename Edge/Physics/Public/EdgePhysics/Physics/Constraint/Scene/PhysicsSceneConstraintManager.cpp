#include "PhysicsSceneConstraintManager.h"

#include "EdgePhysics/Physics/Scene/PhysicsScene.h"

#include "PhysicsSceneActiveConstraintCollection.h"
#include "PhysicsSceneConstraintCollection.h"

bool Edge::PhysicsSceneConstraintManager::init(const PhysicsSceneReference& scene)
{
	m_scene = scene;

	m_constraintCollection = new PhysicsSceneConstraintCollection();
	EDGE_CHECK_INITIALIZATION(m_constraintCollection && m_constraintCollection->init(this));

	m_activeConstraintCollection = new PhysicsSceneActiveConstraintCollection();
	EDGE_CHECK_INITIALIZATION(m_activeConstraintCollection && m_activeConstraintCollection->init(this));

	return true;
}

void Edge::PhysicsSceneConstraintManager::release()
{
	m_scene.reset();

	EDGE_SAFE_DESTROY_WITH_RELEASING(m_constraintCollection);
	EDGE_SAFE_DESTROY_WITH_RELEASING(m_activeConstraintCollection);
}

Edge::JobGraphReference Edge::PhysicsSceneConstraintManager::getPreSolvingJobGraph(float deltaTime)
{
	JobGraphBuilder m_graphBuilder;

	const JobGraphBuilder::JobGraphJobID preSolvingJobID = m_graphBuilder.addJob(
		createLambdaJob([dt = deltaTime, this]()
			{
				preSolve(dt);
			}, "Pre solve constraints")
	);

	return m_graphBuilder.getGraph();
}

Edge::JobGraphReference Edge::PhysicsSceneConstraintManager::getVelocitySolvingJobGraph()
{
	JobGraphBuilder m_graphBuilder;

	const JobGraphBuilder::JobGraphJobID velocitySolvingJobID = m_graphBuilder.addJob(
		createLambdaJob([this]()
			{
				warmUp();
				solveVelocity();
			}, "Solve constraints velocities")
	);

	return m_graphBuilder.getGraph();
}

Edge::JobGraphReference Edge::PhysicsSceneConstraintManager::getPositionSolvingJobGraph()
{
	JobGraphBuilder m_graphBuilder;

	const JobGraphBuilder::JobGraphJobID positionSolvingJobID = m_graphBuilder.addJob(
		createLambdaJob([this]()
			{
				solvePosition();
			}, "Solve constraints positions")
	);

	return m_graphBuilder.getGraph();
}

void Edge::PhysicsSceneConstraintManager::preSolve(float deltaTime)
{
	const PhysicsSceneActiveConstraintCollection::ConstraintCollection& constraints = m_activeConstraintCollection->getConstraints();

	for (const PhysicsSceneConstraintID constraintID : constraints)
	{
		PhysicsConstraintReference constraint = getConstraint(constraintID);
		constraint->preSolve(deltaTime);
	}
}

void Edge::PhysicsSceneConstraintManager::warmUp()
{
	const PhysicsSceneActiveConstraintCollection::ConstraintCollection& constraints = m_activeConstraintCollection->getConstraints();

	for (const PhysicsSceneConstraintID constraintID : constraints)
	{
		PhysicsConstraintReference constraint = getConstraint(constraintID);
		constraint->warmUp();
	}
}

void Edge::PhysicsSceneConstraintManager::solveVelocity()
{
	const PhysicsSceneActiveConstraintCollection::ConstraintCollection& constraints = m_activeConstraintCollection->getConstraints();

	for (size_t iter = 0; iter < 10; ++iter)
	{
		for (const PhysicsSceneConstraintID constraintID : constraints)
		{
			PhysicsConstraintReference constraint = getConstraint(constraintID);
			constraint->solveVelocity();
		}
	}
}

void Edge::PhysicsSceneConstraintManager::solvePosition()
{
	const PhysicsSceneActiveConstraintCollection::ConstraintCollection& constraints = m_activeConstraintCollection->getConstraints();

	for (size_t iter = 0; iter < 2; ++iter)
	{
		for (const PhysicsSceneConstraintID constraintID : constraints)
		{
			PhysicsConstraintReference constraint = getConstraint(constraintID);
			constraint->solvePosition();
		}
	}
}

Edge::PhysicsSceneConstraintID Edge::PhysicsSceneConstraintManager::addConstraint(const PhysicsConstraintReference& constraint, bool activate)
{
	if (!constraint)
	{
		EDGE_ASSERT_FAIL_MESSAGE("Trying to add an invalid constraint to the scene.");
		return InvalidPhysicsSceneConstraintID;
	}

	if (constraint->getSceneContext())
	{
		EDGE_ASSERT_FAIL_MESSAGE("Constraint has already been added to a scene.");
		return InvalidPhysicsSceneConstraintID;
	}

	const PhysicsSceneConstraintID constraintID = m_constraintCollection->addConstraint(constraint);

	if (activate)
	{
		m_activeConstraintCollection->addConstraint(constraint);
	}

	return constraintID;
}

void Edge::PhysicsSceneConstraintManager::removeConstraint(PhysicsSceneConstraintID constraintID)
{
	removeConstraint(getConstraint(constraintID));
}

void Edge::PhysicsSceneConstraintManager::removeConstraint(const PhysicsConstraintReference& constraint)
{
	if (!constraint)
	{
		return;
	}

	deactivateConstraint(constraint);

	m_constraintCollection->removeConstraint(constraint);
}

Edge::PhysicsConstraintReference Edge::PhysicsSceneConstraintManager::getConstraint(PhysicsSceneConstraintID constraintID) const
{
	return m_constraintCollection->getConstraint(constraintID);
}

void Edge::PhysicsSceneConstraintManager::activateConstraint(PhysicsSceneConstraintID constraintID)
{
	activateConstraint(getConstraint(constraintID));
}

void Edge::PhysicsSceneConstraintManager::activateConstraint(const PhysicsConstraintReference& constraint)
{
	if (!constraint || constraint->isActive())
	{
		return;
	}

	m_activeConstraintCollection->addConstraint(constraint);
}

void Edge::PhysicsSceneConstraintManager::deactivateConstraint(PhysicsSceneConstraintID constraintID)
{
	deactivateConstraint(getConstraint(constraintID));
}

void Edge::PhysicsSceneConstraintManager::deactivateConstraint(const PhysicsConstraintReference& constraint)
{
	if (!constraint || !constraint->isActive())
	{
		return;
	}

	m_activeConstraintCollection->removeConstraint(constraint);
}

Edge::PhysicsSceneWeakReference Edge::PhysicsSceneConstraintManager::getScene() const
{
	return m_scene;
}
