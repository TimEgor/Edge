#pragma once

#include "EdgePhysics/Physics/Scene/PhysicsSceneReference.h"

namespace Edge
{
	using PhysicsSceneCollisionID = PhysicsSceneEntityID;
	constexpr PhysicsSceneCollisionID InvalidPhysicsSceneCollisionID = 0;

	class PhysicsSceneCollisionManager;

	EDGE_MT_REFERENCE(PhysicsSceneCollisionManager);
	EDGE_MT_WEAK_REFERENCE(PhysicsSceneCollisionManager);
}
