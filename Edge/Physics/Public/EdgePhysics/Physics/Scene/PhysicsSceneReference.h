#pragma once

#include "EdgeCommon/Reference/MTReference.h"
#include "EdgeCommon/Reference/MTWeakReference.h"

namespace Edge
{
	using PhysicsSceneEntityID = uint32_t;
	constexpr PhysicsSceneEntityID InvalidPhysicsSceneEntityID = 0;

	using PhysicsSceneActivationContextEntityIndex = uint32_t;
	constexpr PhysicsSceneActivationContextEntityIndex InvalidPhysicsSceneActivationContextEntityIndex = -1;

	class PhysicsScene;

	EDGE_MT_REFERENCE(PhysicsScene);
	EDGE_MT_WEAK_REFERENCE(PhysicsScene);
}
