#pragma once

#include "EdgeCommon/HashedType.h"
#include "EdgeCommon/Math/AABB.h"
#include "EdgeCommon/Reference/MTReference.h"

#include "EdgePhysics/Physics/Collision/PhysicsCollisionQuery.h"

namespace Edge
{
	using PhysicsEntityCollisionShapeType = HashedType::Type;

	class PhysicsEntityCollisionShape : public HashedType, public PhysicsCollisionQuery, public DefaultDestroyingMTCountableObjectBase
	{
	public:
		PhysicsEntityCollisionShape() = default;

		virtual AABB3 getAABB() const = 0;

		virtual PhysicsEntityCollisionShapeType getType() const = 0;
	};

	EDGE_MT_REFERENCE(PhysicsEntityCollisionShape);

#define EDGE_PHYSICS_COLLISION_SHAPE_TYPE(PHYSICS_COLLISION_SHAPE_TYPE) EDGE_HASH_TYPE(#PHYSICS_COLLISION_SHAPE_TYPE, Edge::PhysicsEntityCollisionShapeType, PhysicsEntityCollisionShape)
}
