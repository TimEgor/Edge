#include "EdgeCommon/Math/Vector.h"

#include "EdgePhysics/Physics/Collision/PhysicsCollisionQuery.h"

namespace Edge::CastSphere
{
	bool rayCast(const ComputeVector3& sphereCenter, ComputeValueType sphereRadius, const ComputeVector3& origin, const ComputeVector3& end, PhysicsCollisionQuery::PointCastingResult& result);
}
