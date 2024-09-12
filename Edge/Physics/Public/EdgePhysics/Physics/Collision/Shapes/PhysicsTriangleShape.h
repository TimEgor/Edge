#pragma once

#include "EdgePhysics/Physics/Collision/PhysicsEntityCollisionShape.h"

namespace Edge
{
	class PhysicsTriangleShape : public PhysicsEntityCollisionShape
	{
	private:
		const FloatVector3 m_vertices[3];

	public:
		PhysicsTriangleShape(const FloatVector3& vert1, const FloatVector3& vert2, const FloatVector3& vert3)
			: m_vertices{ vert1, vert2, vert3 } {}

		const FloatVector3* getVertices() const { return m_vertices; }

		virtual AABB3 getAABB() const override;

		virtual bool rayCast(const FloatVector3& origin, const FloatVector3& end, PointCastingResult& result) const override;

		EDGE_PHYSICS_COLLISION_SHAPE_TYPE(TRIANGLE);
	};

	EDGE_MT_REFERENCE(PhysicsTriangleShape);
}
