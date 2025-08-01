#pragma once

#include "EdgePhysics/Physics/Collision/PhysicsEntityCollisionShape.h"

namespace Edge
{
	class PhysicsBoxShape : public PhysicsEntityCollisionShape
	{
	private:
		const ComputeVector3 m_size = ComputeVector3Zero;

	public:
		PhysicsBoxShape(const ComputeVector3& size)
			: m_size(size) {}

		const ComputeVector3& getSize() const { return m_size; }

		virtual AABB3 getAABB() const override;
		virtual ComputeVector3 getFurthestKeyPoint(const ComputeVector3& direction) const override;

		virtual ComputeVector3 getSupportingPoint(const ComputeVector3& direction) const override;
		virtual ComputeValue getSupportingRadius() const override;
		virtual void getSupportingFace(const ComputeVector3& direction, SupportingFaceVertexCollection& vertices) const override;

		virtual bool rayCast(const ComputeVector3& origin, const ComputeVector3& end, PointCastingResult& result) const override;

		EDGE_RTTI_VIRTUAL(PhysicsBoxShape)
	};

	EDGE_REFERENCE(PhysicsBoxShape);
}

EDGE_RTTI(Edge::PhysicsBoxShape)