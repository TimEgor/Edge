#pragma once

#include "EdgeCommon/Math/Vector.h"

#include "EdgePhysics/Physics/Collision/PhysicsCollisionQuery.h"

namespace Edge
{
	struct AABB3;
}

namespace Edge::CastAABB3
{
	bool rayCast(const AABB3& aabb, const FloatVector3& origin, const FloatVector3& end, PhysicsCollisionQuery::PointCastingResult& result);
}
