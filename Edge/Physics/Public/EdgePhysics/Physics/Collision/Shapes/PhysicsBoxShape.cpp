#include "PhysicsBoxShape.h"

#include "EdgePhysics/Physics/Collision/Cast/AABB3Cast.h"

Edge::AABB3 Edge::PhysicsBoxShape::getAABB() const
{
	const ComputeVector halfSize = m_size * 0.5f;
	return AABB3(ComputeVector(halfSize).negate().getFloatVector3(), halfSize.getFloatVector3());
}

Edge::FloatVector3 Edge::PhysicsBoxShape::getFurthestKeyPoint(const FloatVector3& direction) const
{
	float maxDistance = -EDGE_FLT_MAX;
	uint32_t maxDistancePointIndex = -1;

	const FloatVector3 halfSize = (m_size * 0.5f).getFloatVector3();
	const FloatVector3 points[] = {
		{-halfSize.m_x, -halfSize.m_y, -halfSize.m_z},
		{halfSize.m_x, -halfSize.m_y, -halfSize.m_z},
		{-halfSize.m_x, halfSize.m_y, -halfSize.m_z},
		{halfSize.m_x, halfSize.m_y, -halfSize.m_z},
		{-halfSize.m_x, -halfSize.m_y, halfSize.m_z},
		{halfSize.m_x, -halfSize.m_y, halfSize.m_z},
		{-halfSize.m_x, halfSize.m_y, halfSize.m_z},
		{halfSize.m_x, halfSize.m_y, halfSize.m_z},
	};

	for (uint32_t pointIndex = 0; pointIndex < 8; ++pointIndex)
	{
		const float pointDistance = dotVector3(direction, points[pointIndex]);
		if (maxDistance < pointDistance)
		{
			maxDistance = pointDistance;
			maxDistancePointIndex = pointIndex;
		}
	}

	return points[maxDistancePointIndex];
}

Edge::FloatVector3 Edge::PhysicsBoxShape::getFurthestBoundSurfacePoint(const FloatVector3& direction) const
{
	float maxDistance = -EDGE_FLT_MAX;

	const FloatVector3 halfSize = (m_size * 0.5f).getFloatVector3();
	const FloatVector3 points[] = {
		{-halfSize.m_x, -halfSize.m_y, -halfSize.m_z},
		{halfSize.m_x, -halfSize.m_y, -halfSize.m_z},
		{-halfSize.m_x, halfSize.m_y, -halfSize.m_z},
		{halfSize.m_x, halfSize.m_y, -halfSize.m_z},
		{-halfSize.m_x, -halfSize.m_y, halfSize.m_z},
		{halfSize.m_x, -halfSize.m_y, halfSize.m_z},
		{-halfSize.m_x, halfSize.m_y, halfSize.m_z},
		{halfSize.m_x, halfSize.m_y, halfSize.m_z},
	};

	for (uint32_t pointIndex = 0; pointIndex < 8; ++pointIndex)
	{
		const float pointDistance = dotVector3(direction, points[pointIndex]);
		if (maxDistance < pointDistance)
		{
			maxDistance = pointDistance;
		}
	}

	return (direction * maxDistance).getFloatVector3();
}

bool Edge::PhysicsBoxShape::rayCast(const FloatVector3& origin, const FloatVector3& end, PointCastingResult& result) const
{
	return CastAABB3::rayCast(getAABB(), origin, end, result);
}
