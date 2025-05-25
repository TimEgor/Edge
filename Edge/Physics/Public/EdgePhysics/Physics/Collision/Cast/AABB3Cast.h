#pragma once

#include "EdgeCommon/Math/ComputeVector3.h"

#include "EdgePhysics/Physics/Collision/PhysicsCollisionQuery.h"

namespace Edge
{
	struct AABB3;
}

namespace Edge::CastAABB3
{
	bool rayCast(const AABB3& aabb, const ComputeVector3& origin, const ComputeVector3& end, PhysicsCollisionQuery::PointCastingResult& result);
}
