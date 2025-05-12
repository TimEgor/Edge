#pragma once

#include <cstdint>

namespace Edge
{
	using PhysicsSceneConstraintID = uint32_t;
	inline constexpr PhysicsSceneConstraintID InvalidPhysicsSceneConstraintID = 0;

	using PhysicsSceneActivationContextConstraintIndex = uint32_t;
	inline constexpr PhysicsSceneActivationContextConstraintIndex InvalidPhysicsSceneActivationContextConstraintIndex = -1;
}
