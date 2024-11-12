#include "PhysicsConstraint.h"

#include "EdgeCommon/Assert/AssertCore.h"

void Edge::PhysicsConstraint::setSceneContext(const PhysicsConstraintSceneContextReference& context)
{
	if (context && m_sceneContext)
	{
		EDGE_ASSERT_FAIL_MESSAGE("Constraint scene context has been already set.");
		return;
	}

	m_sceneContext = context;
}

bool Edge::PhysicsConstraint::isActive() const
{
	return m_sceneContext && m_sceneContext->isActive();
}
