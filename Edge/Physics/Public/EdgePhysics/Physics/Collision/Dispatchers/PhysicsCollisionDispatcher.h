#pragma once

#include "EdgePhysics/Physics/Collision/PhysicsCollisionContact.h"
#include "EdgePhysics/Physics/Collision/PhysicsEntityCollision.h"
#include "EdgePhysics/Physics/Collision/Manifold/PhysicsContactManifold.h"

#include <vector>

namespace Edge
{
	class PhysicsCollisionDispatcher
	{
	public:
		using ContactManifoldDispatchingResultCollection = std::vector<PhysicsInstanceContactManifold>;

		PhysicsCollisionDispatcher() = default;
		virtual ~PhysicsCollisionDispatcher() = default;

		virtual uint32_t dispatch(const PhysicsEntityCollisionReference& collision1, const PhysicsEntityCollisionReference& collision2,
			PhysicsCollisionContactID contactID, ContactManifoldDispatchingResultCollection& results) = 0; // return contact point count
	};
}
