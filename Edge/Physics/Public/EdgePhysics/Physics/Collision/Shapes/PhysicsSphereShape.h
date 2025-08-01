#pragma once

#include "EdgePhysics/Physics/Collision/PhysicsEntityCollisionShape.h"

namespace Edge
{
	class PhysicsSphereShape : public PhysicsEntityCollisionShape
	{
	private:
		const ComputeValueType m_radius = 0.0_ecv;

	public:
		PhysicsSphereShape(ComputeValueType radius)
			: m_radius(radius) {}

		ComputeValueType getRadius() const { return m_radius; }

		virtual AABB3 getAABB() const override;
		virtual ComputeVector3 getFurthestKeyPoint(const ComputeVector3& direction) const override;

		virtual ComputeVector3 getSupportingPoint(const ComputeVector3& direction) const override;
		virtual ComputeValue getSupportingRadius() const override;
		virtual void getSupportingFace(const ComputeVector3& direction, SupportingFaceVertexCollection& vertices) const override {}

		virtual bool rayCast(const ComputeVector3& origin, const ComputeVector3& end, PointCastingResult& result) const override;

		EDGE_RTTI_VIRTUAL(Edge::PhysicsSphereShape, PhysicsEntityCollisionShape)
	};

	EDGE_REFERENCE(PhysicsSphereShape);
}