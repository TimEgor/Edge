#include "PhysicsBoxShape.h"

#include "EdgePhysics/Physics/Collision/Cast/AABB3Cast.h"

Edge::AABB3 Edge::PhysicsBoxShape::getAABB() const
{
	const ComputeVector halfSize = m_size * 0.5f;
	return AABB3(ComputeVector(halfSize).negate().getFloatVector3(), halfSize.getFloatVector3());
}

Edge::FloatVector3 Edge::PhysicsBoxShape::getFurthestKeyPoint(const FloatVector3& direction) const
{
	float maxDistance = -Math::FltMax;
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
		const float pointDistance = DotVector3(direction, points[pointIndex]);
		if (maxDistance < pointDistance)
		{
			maxDistance = pointDistance;
			maxDistancePointIndex = pointIndex;
		}
	}

	return points[maxDistancePointIndex];
}

void Edge::PhysicsBoxShape::getSupportingFace(const FloatVector3& direction, SupportingFaceVertexCollection& vertices) const
{
	vertices.resize(4);

	const uint32_t axis = AbsVector(direction).getHighestComponentIndex();
	const FloatVector3 halfSize = (m_size * 0.5f).getFloatVector3();

	if (direction[axis] < 0.0f)
	{
		switch (axis)
		{
		case 0:
			vertices[0] = FloatVector3(halfSize.m_x, -halfSize.m_y, -halfSize.m_z);
			vertices[1] = FloatVector3(halfSize.m_x, halfSize.m_y, -halfSize.m_z);
			vertices[2] = FloatVector3(halfSize.m_x, halfSize.m_y, halfSize.m_z);
			vertices[3] = FloatVector3(halfSize.m_x, -halfSize.m_y, halfSize.m_z);
			break;

		case 1:
			vertices[0] = FloatVector3(-halfSize.m_x, halfSize.m_y, -halfSize.m_z);
			vertices[1] = FloatVector3(-halfSize.m_x, halfSize.m_y, halfSize.m_z);
			vertices[2] = FloatVector3(halfSize.m_x, halfSize.m_y, halfSize.m_z);
			vertices[3] = FloatVector3(halfSize.m_x, halfSize.m_y, -halfSize.m_z);
			break;

		case 2:
			vertices[0] = FloatVector3(-halfSize.m_x, -halfSize.m_y, halfSize.m_z);
			vertices[1] = FloatVector3(halfSize.m_x, -halfSize.m_y, halfSize.m_z);
			vertices[2] = FloatVector3(halfSize.m_x, halfSize.m_y, halfSize.m_z);
			vertices[3] = FloatVector3(-halfSize.m_x, halfSize.m_y, halfSize.m_z);
			break;
		}
	}
	else
	{
		switch (axis)
		{
		case 0:
			vertices[0] = FloatVector3(-halfSize.m_x, -halfSize.m_y, -halfSize.m_z);
			vertices[1] = FloatVector3(-halfSize.m_x, -halfSize.m_y, halfSize.m_z);
			vertices[2] = FloatVector3(-halfSize.m_x, halfSize.m_y, halfSize.m_z);
			vertices[3] = FloatVector3(-halfSize.m_x, halfSize.m_y, -halfSize.m_z);
			break;

		case 1:
			vertices[0] = FloatVector3(-halfSize.m_x, -halfSize.m_y, -halfSize.m_z);
			vertices[1] = FloatVector3(halfSize.m_x, -halfSize.m_y, -halfSize.m_z);
			vertices[2] = FloatVector3(halfSize.m_x, -halfSize.m_y, halfSize.m_z);
			vertices[3] = FloatVector3(-halfSize.m_x, -halfSize.m_y, halfSize.m_z);
			break;

		case 2:
			vertices[0] = FloatVector3(-halfSize.m_x, -halfSize.m_y, -halfSize.m_z);
			vertices[1] = FloatVector3(-halfSize.m_x, halfSize.m_y, -halfSize.m_z);
			vertices[2] = FloatVector3(halfSize.m_x, halfSize.m_y, -halfSize.m_z);
			vertices[3] = FloatVector3(halfSize.m_x, -halfSize.m_y, -halfSize.m_z);
			break;
		}
	}
}

bool Edge::PhysicsBoxShape::rayCast(const FloatVector3& origin, const FloatVector3& end, PointCastingResult& result) const
{
	return CastAABB3::rayCast(getAABB(), origin, end, result);
}
