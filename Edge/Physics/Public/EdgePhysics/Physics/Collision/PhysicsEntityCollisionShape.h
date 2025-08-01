#pragma once

#include "EdgeCommon/Math/AABB.h"
#include "EdgeCommon/Reference/Reference.h"
#include "EdgeCommon/RTTI/RTTI.h"

#include "EdgePhysics/Physics/Collision/PhysicsCollisionQuery.h"

#include <vector>

namespace Edge
{
	class PhysicsEntityCollisionShape : public PhysicsCollisionQuery, public DefaultDestroyingMTCountableObjectBase
	{
	public:
		using SupportingFaceVertexCollection = std::vector<ComputeVector3>;

		PhysicsEntityCollisionShape() = default;

		virtual AABB3 getAABB() const = 0;
		virtual ComputeVector3 getFurthestKeyPoint(const ComputeVector3& direction) const = 0;
		virtual ComputeVector3 getSupportingPoint(const ComputeVector3& direction) const = 0;
		virtual ComputeValue getSupportingRadius() const = 0;
		virtual void getSupportingFace(const ComputeVector3& direction, SupportingFaceVertexCollection& vertices) const = 0;

		EDGE_RTTI_VIRTUAL_BASE(PhysicsEntityCollisionShape)
	};

	EDGE_REFERENCE(PhysicsEntityCollisionShape);

	using PhysicsEntityCollisionShapeType = RTTI::TypeMetaInfoID;
}