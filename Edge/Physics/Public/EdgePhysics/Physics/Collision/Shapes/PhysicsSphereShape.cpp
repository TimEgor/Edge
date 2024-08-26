#include "PhysicsSphereShape.h"

#include "EdgePhysics/Physics/Collision/Cast/SphereCast.h"

Edge::AABB3 Edge::PhysicsSphereShape::getAABB() const
{
	return AABB3(FloatVector3(-m_radius), FloatVector3(m_radius));
}

bool Edge::PhysicsSphereShape::rayCast(const FloatVector3& origin, const FloatVector3& end, PointCastingResult& result) const
{
	return CastSphere::rayCast(FloatVector3Zero, m_radius, origin, end, result);
}
