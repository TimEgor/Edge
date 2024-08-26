#include "EdgeCommon/Math/Vector.h"

#include "EdgePhysics/Physics/Collision/PhysicsCollisionQuery.h"

namespace Edge::CastSphere
{
	bool rayCast(const FloatVector3& sphereCenter, float sphereRadius, const FloatVector3& origin, const FloatVector3& end, PhysicsCollisionQuery::PointCastingResult& result);
}
