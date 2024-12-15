#pragma once

#include "EdgeCommon/Math/Vector.h"

#include <vector>

namespace Edge
{
	struct PhysicsContactManifold final
	{
		using PositionCollection = std::vector<FloatVector3>;

		PositionCollection m_positions1;
		PositionCollection m_positions2;
		FloatVector3 m_normal = FloatVector3Zero;
		float m_depth = 0.0f;

		uint32_t getContactPointCount() const { return m_positions1.size(); }
	};

	struct PhysicsInstanceContactManifold final
	{
		PhysicsContactManifold m_manifoldData;
		PhysicsCollisionContactID m_contactID;
	};
}
