#pragma once

#include "EdgePhysics/Physics/Collision/PhysicsEntityCollisionShape.h"

namespace Edge
{
	class PhysicsSphereShape : public PhysicsEntityCollisionShape
	{
	private:
		const float m_radius = 0.0f;

	public:
		PhysicsSphereShape(float radius)
			: m_radius(radius) {}

		float getRadius() const { return m_radius; }

		virtual AABB3 getAABB() const override;

		virtual bool rayCast(const FloatVector3& origin, const FloatVector3& end, PointCastingResult& result) const override;

		EDGE_PHYSICS_COLLISION_SHAPE_TYPE(SPHERE);
	};

	EDGE_MT_REFERENCE(PhysicsSphereShape);
}
