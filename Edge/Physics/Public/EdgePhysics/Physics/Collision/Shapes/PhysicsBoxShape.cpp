#include "PhysicsBoxShape.h"

#include "EdgePhysics/Physics/Collision/Cast/AABB3Cast.h"

Edge::AABB3 Edge::PhysicsBoxShape::getAABB() const
{
	return AABB3(ComputeVector(m_size).negate().getFloatVector3(), m_size);
}

bool Edge::PhysicsBoxShape::rayCast(const FloatVector3& origin, const FloatVector3& end, PointCastingResult& result) const
{
	return CastAABB3::rayCast(getAABB(), origin, end, result);
}
