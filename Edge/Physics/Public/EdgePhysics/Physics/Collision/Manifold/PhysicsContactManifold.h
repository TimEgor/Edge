#pragma once

#include "EdgeCommon/Math/Vector.h"

#include <vector>

namespace Edge
{
	struct PhysicsContactManifold final
	{
		using PositionCollection = std::vector<FloatVector3>;

		PositionCollection m_positions;
		FloatVector3 m_normal = FloatVector3Zero;
		float m_depth = 0.0f;
	};

	struct PhysicsInstanceContactManifold final
	{
		PhysicsContactManifold m_manifoldData;
		PhysicsCollisionContactID m_contactID;
	};
}
