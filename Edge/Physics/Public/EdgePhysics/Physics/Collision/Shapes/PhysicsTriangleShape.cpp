#include "PhysicsTriangleShape.h"

Edge::AABB3 Edge::PhysicsTriangleShape::getAABB() const
{
	ComputeVector minPosition = FloatVector3(EDGE_FLT_MAX);
	ComputeVector maxPosition = FloatVector3(EDGE_FLT_MIN);

	for (uint32_t vertexIndex = 0; vertexIndex < 3; ++vertexIndex)
	{
		const ComputeVector vertex = m_vertices[vertexIndex];

		minPosition = ComputeMath::vectorMin(minPosition.m_vector, vertex.m_vector);
		maxPosition = ComputeMath::vectorMax(maxPosition.m_vector, vertex.m_vector);
	}

	return AABB3(minPosition.getFloatVector3(), maxPosition.getFloatVector3());
}

bool Edge::PhysicsTriangleShape::rayCast(const FloatVector3& origin, const FloatVector3& end, PointCastingResult& result) const
{
	const ComputeVector ray = end - origin;

	const ComputeVector edge1 = m_vertices[0] - origin;
	const ComputeVector edge2 = m_vertices[1] - origin;
	const ComputeVector edge3 = m_vertices[2] - origin;

	FloatVector3 localCoords = FloatVector3Zero; // barycentric coordinates
	localCoords.m_x = tripleVector3(ray, edge3, edge2);
	if (localCoords.m_x < 0.0f)
	{
		return false;
	}

	localCoords.m_y = tripleVector3(ray, edge1, edge3);
	if (localCoords.m_y < 0.0f)
	{
		return false;
	}

	localCoords.m_z = tripleVector3(ray, edge2, edge1);
	if (localCoords.m_z < 0.0f)
	{
		return false;
	}

	const float denom = 1.0f / (localCoords.m_x + localCoords.m_y + localCoords.m_z);
	(localCoords * denom).saveToFloatVector3(localCoords);

	ComputeVector hitPosition = m_vertices[0] * localCoords.m_x;
	hitPosition += m_vertices[1] * localCoords.m_y;
	hitPosition += m_vertices[2] * localCoords.m_z;

	hitPosition.saveToFloatVector3(result.m_hitPosition);
	result.m_distance = (hitPosition - origin).length3();

	return true;
}
