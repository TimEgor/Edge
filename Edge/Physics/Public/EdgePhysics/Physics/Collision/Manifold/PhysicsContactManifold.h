#pragma once

#include "EdgeCommon/Math/ComputeVector3.h"

#include <vector>

namespace Edge
{
	struct PhysicsContactManifold final
	{
		using PositionCollection = std::vector<ComputeVector3>;

		PositionCollection m_positions1;
		PositionCollection m_positions2;
		ComputeVector3 m_normal = ComputeVector3Zero;
		ComputeValueType m_depth = 0.0f;

		uint32_t getContactPointCount() const { return m_positions1.size(); }
	};

	struct PhysicsInstanceContactManifold final
	{
		PhysicsContactManifold m_manifoldData;
		PhysicsCollisionContactID m_contactID;
	};
}
