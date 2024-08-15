#include "PhysicsEntityWeakLinkObject.h"

#include "EdgeCommon/Assert/AssertCore.h"

#include "PhysicsEntity.h"

void Edge::PhysicsEntityWeakLinkObject::setEntityLink(PhysicsEntity* entity)
{
	if (entity && m_entity)
	{
		EDGE_ASSERT_FAIL_MESSAGE("Entity link has been already set.");
		return;
	}

	m_entity = entity;
}

Edge::PhysicsEntityWeakLinkObject::~PhysicsEntityWeakLinkObject()
{
	EDGE_ASSERT(m_entity == nullptr);
}

Edge::PhysicsEntityReference Edge::PhysicsEntityWeakLinkObject::getEntity() const
{
	return m_entity;
}

bool Edge::PhysicsEntityWeakLinkObject::isEntityLinkEqual(const PhysicsEntityWeakLinkObject& link) const
{
	return m_entity == link.m_entity;
}
