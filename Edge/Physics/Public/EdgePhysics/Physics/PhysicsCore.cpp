#include "PhysicsCore.h"

#include "EdgeCommon/UtilsMacros.h"

#include "Physics.h"
#include "EdgeCommon/Assert/AssertCore.h"

bool Edge::PhysicsCore::initPhysics()
{
	if (m_physics)
	{
		EDGE_ASSERT_FAIL_MESSAGE("Physics has been already inited or copied.");
		return false;
	}

	m_physics = new Physics();
	return m_physics;
}

void Edge::PhysicsCore::releasePhysics()
{
	EDGE_SAFE_DESTROY_WITH_RELEASING(m_physics);
}

Edge::Physics* Edge::PhysicsCore::getPhysics() const
{
	return m_physics;
}

void Edge::PhysicsCore::copyState(const PhysicsCore& core)
{
	if (m_physics)
	{
		EDGE_ASSERT_FAIL_MESSAGE("Physics has been already inited or copied.");
		return;
	}

	m_physics = core.m_physics;
}

Edge::Physics& Edge::GetPhysics()
{
	Physics* physics = PhysicsCore::getInstance().getPhysics();
	EDGE_ASSERT_MESSAGE(physics, "Physics hasn't been inited or copied.");

	return *physics;
}
