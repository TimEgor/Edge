#pragma once

#include "EdgeCommon/Math/Const.h"
#include "EdgeCommon/Math/Vector.h"

namespace Edge
{
	class PhysicsCollisionQuery
	{
	public:
		struct PointCastingResult final
		{
			FloatVector3 m_hitPosition = FloatVector3Zero;
			float m_distance = EDGE_FLT_MAX;
		};

		PhysicsCollisionQuery() = default;
		virtual ~PhysicsCollisionQuery() = default;

		virtual bool rayCast(const FloatVector3& origin, const FloatVector3& end, PointCastingResult& result) const = 0;
	};
}