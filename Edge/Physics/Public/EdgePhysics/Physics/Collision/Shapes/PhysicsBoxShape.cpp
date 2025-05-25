#include "PhysicsBoxShape.h"

#include "EdgePhysics/Physics/Collision/Cast/AABB3Cast.h"

Edge::AABB3 Edge::PhysicsBoxShape::getAABB() const
{
	const ComputeVector3 halfSize = m_size * 0.5f;
	return AABB3(ComputeVector3(halfSize).negate(), halfSize);
}

Edge::ComputeVector3 Edge::PhysicsBoxShape::getFurthestKeyPoint(const ComputeVector3& direction) const
{
	ComputeValueType maxDistance = -Math::Max;
	uint32_t maxDistancePointIndex = -1;

	const ComputeVector3 halfSize = m_size * ComputeValueType(0.5);
	const ComputeVector3 points[] = {
		{-halfSize.getX(), -halfSize.getY(), -halfSize.getZ()},
		{halfSize.getX(), -halfSize.getY(), -halfSize.getZ()},
		{-halfSize.getX(), halfSize.getY(), -halfSize.getZ()},
		{halfSize.getX(), halfSize.getY(), -halfSize.getZ()},
		{-halfSize.getX(), -halfSize.getY(), halfSize.getZ()},
		{halfSize.getX(), -halfSize.getY(), halfSize.getZ()},
		{-halfSize.getX(), halfSize.getY(), halfSize.getZ()},
		{halfSize.getX(), halfSize.getY(), halfSize.getZ()}
	};

	for (uint32_t pointIndex = 0; pointIndex < 8; ++pointIndex)
	{
		const float pointDistance = DotComputeVector3(direction, points[pointIndex]);
		if (maxDistance < pointDistance)
		{
			maxDistance = pointDistance;
			maxDistancePointIndex = pointIndex;
		}
	}

	return points[maxDistancePointIndex];
}

void Edge::PhysicsBoxShape::getSupportingFace(const ComputeVector3& direction, SupportingFaceVertexCollection& vertices) const
{
	vertices.resize(4);

	const uint32_t axis = direction.getAbs().getMaxElementIndex();
	const ComputeVector3 halfSize = m_size * ComputeValueType(0.5);

	if (direction[axis] < ComputeValueType(0.0))
	{
		switch (axis)
		{
		case 0:
			vertices[0] = ComputeVector3(halfSize.getX(), -halfSize.getY(), -halfSize.getZ());
			vertices[1] = ComputeVector3(halfSize.getX(), halfSize.getY(), -halfSize.getZ());
			vertices[2] = ComputeVector3(halfSize.getX(), halfSize.getY(), halfSize.getZ());
			vertices[3] = ComputeVector3(halfSize.getX(), -halfSize.getY(), halfSize.getZ());
			break;

		case 1:
			vertices[0] = ComputeVector3(-halfSize.getX(), halfSize.getY(), -halfSize.getZ());
			vertices[1] = ComputeVector3(-halfSize.getX(), halfSize.getY(), halfSize.getZ());
			vertices[2] = ComputeVector3(halfSize.getX(), halfSize.getY(), halfSize.getZ());
			vertices[3] = ComputeVector3(halfSize.getX(), halfSize.getY(), -halfSize.getZ());
			break;

		case 2:
			vertices[0] = ComputeVector3(-halfSize.getX(), -halfSize.getY(), halfSize.getZ());
			vertices[1] = ComputeVector3(halfSize.getX(), -halfSize.getY(), halfSize.getZ());
			vertices[2] = ComputeVector3(halfSize.getX(), halfSize.getY(), halfSize.getZ());
			vertices[3] = ComputeVector3(-halfSize.getX(), halfSize.getY(), halfSize.getZ());
			break;
		}
	}
	else
	{
		switch (axis)
		{
		case 0:
			vertices[0] = ComputeVector3(-halfSize.getX(), -halfSize.getY(), -halfSize.getZ());
			vertices[1] = ComputeVector3(-halfSize.getX(), -halfSize.getY(), halfSize.getZ());
			vertices[2] = ComputeVector3(-halfSize.getX(), halfSize.getY(), halfSize.getZ());
			vertices[3] = ComputeVector3(-halfSize.getX(), halfSize.getY(), -halfSize.getZ());
			break;

		case 1:
			vertices[0] = ComputeVector3(-halfSize.getX(), -halfSize.getY(), -halfSize.getZ());
			vertices[1] = ComputeVector3(halfSize.getX(), -halfSize.getY(), -halfSize.getZ());
			vertices[2] = ComputeVector3(halfSize.getX(), -halfSize.getY(), halfSize.getZ());
			vertices[3] = ComputeVector3(-halfSize.getX(), -halfSize.getY(), halfSize.getZ());
			break;

		case 2:
			vertices[0] = ComputeVector3(-halfSize.getX(), -halfSize.getY(), -halfSize.getZ());
			vertices[1] = ComputeVector3(-halfSize.getX(), halfSize.getY(), -halfSize.getZ());
			vertices[2] = ComputeVector3(halfSize.getX(), halfSize.getY(), -halfSize.getZ());
			vertices[3] = ComputeVector3(halfSize.getX(), -halfSize.getY(), -halfSize.getZ());
			break;
		}
	}
}

bool Edge::PhysicsBoxShape::rayCast(const ComputeVector3& origin, const ComputeVector3& end, PointCastingResult& result) const
{
	return CastAABB3::rayCast(getAABB(), origin, end, result);
}
