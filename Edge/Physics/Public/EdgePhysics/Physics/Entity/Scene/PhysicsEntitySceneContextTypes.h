#pragma once

#include <cstdint>

namespace Edge
{
	using PhysicsSceneEntityID = uint32_t;
	constexpr PhysicsSceneEntityID InvalidPhysicsSceneEntityID = 0;

	using PhysicsSceneActivationContextEntityIndex = uint32_t;
	constexpr PhysicsSceneActivationContextEntityIndex InvalidPhysicsSceneActivationContextEntityIndex = -1;
}
