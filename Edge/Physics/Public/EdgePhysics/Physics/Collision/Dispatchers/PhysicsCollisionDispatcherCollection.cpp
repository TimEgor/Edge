#include "PhysicsCollisionDispatcherCollection.h"

Edge::PhysicsCollisionDispatcherCollection::DispatcherID::DispatcherID(PhysicsEntityCollisionShapeType type1, PhysicsEntityCollisionShapeType type2)
{
	m_shapeType1 = std::min(type1, type2);
	m_shapeType2 = std::max(type1, type2);
}

bool Edge::PhysicsCollisionDispatcherCollection::DispatcherID::operator==(const DispatcherID& id) const
{
	return m_id == id.m_id;
}

size_t Edge::PhysicsCollisionDispatcherCollection::DispatcherID::Hasher::operator()(const DispatcherID& k) const
{
	return std::hash<DispatcherIDValue>()(k.m_id);
}

void Edge::PhysicsCollisionDispatcherCollection::addDispatcher(PhysicsEntityCollisionShapeType type1, PhysicsEntityCollisionShapeType type2, PhysicsCollisionDispatcher* dispatcher)
{
	if (!dispatcher)
	{
		EDGE_ASSERT_FAIL_MESSAGE("Collision dispatcher is null.");
		return;
	}

	const DispatcherID id(type1, type2);

	const auto findIter = m_dispatchers.find(id);
	if (findIter != m_dispatchers.end())
	{
		EDGE_ASSERT_FAIL_MESSAGE("Collision dispatcher has been already added.");
		return;
	}

	m_dispatchers.insert(std::make_pair(id, dispatcher));
}

void Edge::PhysicsCollisionDispatcherCollection::removeDispatcher(PhysicsEntityCollisionShapeType type1, PhysicsEntityCollisionShapeType type2)
{
	const DispatcherID id(type1, type2);

	const auto findIter = m_dispatchers.find(id);
	if (findIter == m_dispatchers.end())
	{
		EDGE_ASSERT_FAIL_MESSAGE("Collision dispatcher hasn't been added or has been already removed.");
		return;
	}

	m_dispatchers.erase(id);
}

void Edge::PhysicsCollisionDispatcherCollection::setDefaultDispatcher(PhysicsCollisionDispatcher* dispatcher)
{
	if (m_defaultDispatcher)
	{
		EDGE_ASSERT_FAIL_MESSAGE("Default collision dispatcher has been already set.");
		return;
	}

	m_defaultDispatcher = dispatcher;
}

void Edge::PhysicsCollisionDispatcherCollection::resetDefaultDispatcher()
{
	m_defaultDispatcher = nullptr;
}

Edge::PhysicsCollisionDispatcher* Edge::PhysicsCollisionDispatcherCollection::getDispatcher(PhysicsEntityCollisionShapeType type1, PhysicsEntityCollisionShapeType type2) const
{
	const DispatcherID id(type1, type2);

	const auto findIter = m_dispatchers.find(id);
	if (findIter == m_dispatchers.end())
	{
		return m_defaultDispatcher;
	}

	return findIter->second;
}
