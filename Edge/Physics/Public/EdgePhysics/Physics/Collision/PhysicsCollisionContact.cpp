#include "PhysicsCollisionContact.h"

#include <algorithm>

Edge::PhysicsCollisionContactID::PhysicsCollisionContactID(PhysicsSceneCollisionID id1, PhysicsSceneCollisionID id2)
{
	m_collisionID1 = std::max(id1, id2);
	m_collisionID2 = std::min(id1, id2);
}

bool Edge::PhysicsCollisionContactID::operator==(const PhysicsCollisionContactID& id) const
{
	return m_id == id.m_id;
}

bool Edge::PhysicsCollisionContactID::isValid() const
{
	return m_id != InvalidContactIDValue;
}

size_t Edge::PhysicsCollisionContactID::Hasher::operator()(const PhysicsCollisionContactID& id) const
{
	return std::hash<ContactIDValue>()(id.m_id);
}
