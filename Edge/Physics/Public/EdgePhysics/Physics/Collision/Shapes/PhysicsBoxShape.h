#pragma once

#include "EdgePhysics/Physics/Collision/PhysicsEntityCollisionShape.h"

namespace Edge
{
	class PhysicsBoxShape : public PhysicsEntityCollisionShape
	{
	private:
		const FloatVector3 m_size = FloatVector3Zero;

	public:
		PhysicsBoxShape(const FloatVector3& size)
			: m_size(size) {}

		const FloatVector3& getSize() const { return m_size; }

		virtual AABB3 getAABB() const override;
		virtual FloatVector3 getFurthestKeyPoint(const FloatVector3& direction) const override;
		virtual FloatVector3 getFurthestBoundSurfacePoint(const FloatVector3& direction) const override;

		virtual bool rayCast(const FloatVector3& origin, const FloatVector3& end, PointCastingResult& result) const override;

		EDGE_PHYSICS_COLLISION_SHAPE_TYPE(BOX);
	};

	EDGE_MT_REFERENCE(PhysicsBoxShape);
}
