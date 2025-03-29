#pragma once

#include "EdgeCommon/Math/ComputeVector3.h"

namespace Edge
{
	class PhysicsCollisionQuery
	{
	public:
		struct PointCastingResult final
		{
			ComputeVector3 m_hitPosition = ComputeVector3Zero;
			ComputeValueType m_distance = Math::Max;
		};

		PhysicsCollisionQuery() = default;
		virtual ~PhysicsCollisionQuery() = default;

		virtual bool rayCast(const ComputeVector3& origin, const ComputeVector3& end, PointCastingResult& result) const = 0;
	};
}