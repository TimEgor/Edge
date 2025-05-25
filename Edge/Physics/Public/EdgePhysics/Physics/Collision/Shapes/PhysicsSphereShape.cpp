#include "PhysicsSphereShape.h"

#include "EdgePhysics/Physics/Collision/Cast/SphereCast.h"

Edge::AABB3 Edge::PhysicsSphereShape::getAABB() const
{
	return AABB3(ComputeVector3(-m_radius), ComputeVector3(m_radius));
}

Edge::ComputeVector3 Edge::PhysicsSphereShape::getFurthestKeyPoint(const ComputeVector3& direction) const
{
	return direction * m_radius;
}

bool Edge::PhysicsSphereShape::rayCast(const ComputeVector3& origin, const ComputeVector3& end, PointCastingResult& result) const
{
	return CastSphere::rayCast(ComputeVector3Zero, m_radius, origin, end, result);
}
