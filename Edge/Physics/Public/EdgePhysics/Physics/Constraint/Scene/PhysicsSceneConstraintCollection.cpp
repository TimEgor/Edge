#include "PhysicsSceneConstraintCollection.h"

#include "EdgePhysics/Physics/Constraint/Scene/PhysicsSceneConstraintManager.h"

#include "DefaultPhysicsConstraintSceneContext.h"

bool Edge::DefaultPhysicsConstraintSceneContextCollection::init()
{
	EDGE_CHECK_INITIALIZATION(m_pool.init());

	return true;
}

void Edge::DefaultPhysicsConstraintSceneContextCollection::release()
{
	m_pool.release();
}

Edge::PhysicsConstraintSceneContext* Edge::DefaultPhysicsConstraintSceneContextCollection::createContext()
{
	return createDefaultContext();
}

void Edge::DefaultPhysicsConstraintSceneContextCollection::destroyContext(PhysicsConstraintSceneContext* context)
{
	if (!context || context->getType() != DefaultPhysicsConstraintSceneContext::PhysicsConstraintSceneContextType)
	{
		EDGE_ASSERT_FAIL_MESSAGE("Trying to destroying of an invalid context.");
		return;
	}

	destroyDefaultContext(static_cast<DefaultPhysicsConstraintSceneContext*>(context));
}

Edge::DefaultPhysicsConstraintSceneContext* Edge::DefaultPhysicsConstraintSceneContextCollection::createDefaultContext()
{
	EntitySceneContextPool::NewElementInfo newContextInfo;
	m_pool.addElement(newContextInfo);

	DefaultPhysicsConstraintSceneContext* context = newContextInfo.m_elementPtr;
	context->setContextCollection(this, newContextInfo.m_elementHandle.getKey());

	return context;
}

void Edge::DefaultPhysicsConstraintSceneContextCollection::destroyDefaultContext(DefaultPhysicsConstraintSceneContext* context)
{
	if (!context)
	{
		EDGE_ASSERT_FAIL_MESSAGE("Trying to destroying of an invalid context.");
		return;
	}

	m_pool.removeElement(context->getSceneContextID());
}

bool Edge::PhysicsSceneConstraintCollection::init(const PhysicsSceneConstraintManagerReference& constraintManager)
{
	m_constraintManager = constraintManager;
	EDGE_CHECK_INITIALIZATION(m_constraintManager);

	EDGE_CHECK_INITIALIZATION(m_entityPool.init());

	m_sceneContextManager = new DefaultPhysicsConstraintSceneContextCollection();
	EDGE_CHECK_INITIALIZATION(m_sceneContextManager && m_sceneContextManager->init());

	return true;
}

void Edge::PhysicsSceneConstraintCollection::release()
{
	m_constraintManager.reset();

	m_sceneContextManager.reset();
	m_entityPool.release();
}

Edge::PhysicsSceneConstraintID Edge::PhysicsSceneConstraintCollection::addConstraint(const PhysicsConstraintReference& constraint)
{
	if (!constraint)
	{
		return InvalidPhysicsSceneConstraintID;
	}

	const PhysicsSceneConstraintID constraintID = m_entityPool.addElement(constraint).m_elementHandle.getKey();


	if (constraintID != InvalidPhysicsSceneConstraintID)
	{
		DefaultPhysicsConstraintSceneContext* sceneContext = m_sceneContextManager->createDefaultContext();
		constraint->setSceneContext(sceneContext);
		sceneContext->setConstraintManager(m_constraintManager.getReference(), constraintID);
	}

	return constraintID;
}

void Edge::PhysicsSceneConstraintCollection::removeConstraint(const PhysicsConstraintReference& constraint)
{
	if (!constraint)
	{
		return;
	}

	PhysicsConstraintSceneContextReference sceneContext = constraint->getSceneContext();
	if (sceneContext->getType() != DefaultPhysicsConstraintSceneContext::getPhysicsConstraintSceneContextType())
	{
		EDGE_ASSERT_FAIL_MESSAGE("Entity scene context has an invalid type.");
		return;
	}


	DefaultPhysicsConstraintSceneContext& defaultSceneContext = sceneContext.getObjectCastRef<DefaultPhysicsConstraintSceneContext>();
	const PhysicsSceneConstraintID constraintID = defaultSceneContext.getSceneConstraintID();
	defaultSceneContext.setConstraintManager(nullptr, InvalidPhysicsSceneConstraintID);

	constraint->setSceneContext(nullptr);

	if (constraintID == InvalidPhysicsSceneConstraintID)
	{
		EDGE_ASSERT_FAIL_MESSAGE("Scene context has an invalid data.");
		return;
	}

	m_entityPool.removeElement(constraintID);
}

Edge::PhysicsConstraintReference Edge::PhysicsSceneConstraintCollection::getConstraint(PhysicsSceneConstraintID constraintID) const
{
	return *m_entityPool.getElement(EntityHandle(constraintID));
}
