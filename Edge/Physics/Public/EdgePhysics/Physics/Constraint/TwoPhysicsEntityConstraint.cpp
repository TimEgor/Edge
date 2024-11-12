#include "TwoPhysicsEntityConstraint.h"

#include "EdgePhysics/Physics/Scene/PhysicsScene.h"

Edge::TwoPhysicsEntityConstraint::TwoPhysicsEntityConstraint(const PhysicsEntityReference& entity1, const PhysicsEntityReference& entity2)
	: m_entity1(entity1), m_entity2(entity2)
{
	EDGE_ASSERT(entity1);
	EDGE_ASSERT(entity2);
}

bool Edge::TwoPhysicsEntityConstraint::validateEntity(const PhysicsEntityReference& entity)
{
	if (!entity || !entity->getScene())
	{
		EDGE_ASSERT_FAIL_MESSAGE("Constraint entity is invalid or has been removed from a scene.");
		return false;
	}

	return true;
}

bool Edge::TwoPhysicsEntityConstraint::validateEntities() const
{
	return validateEntity(m_entity1) && validateEntity(m_entity2);
}

Edge::PhysicsEntityReference Edge::TwoPhysicsEntityConstraint::getEntity2() const
{
	return m_entity2;
}

Edge::PhysicsEntityReference Edge::TwoPhysicsEntityConstraint::getEntity1() const
{
	return m_entity1;
}