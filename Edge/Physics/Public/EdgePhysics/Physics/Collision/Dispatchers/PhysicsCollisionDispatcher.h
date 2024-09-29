#pragma once

#include "EdgePhysics/Physics/Collision/PhysicsCollisionContact.h"
#include "EdgePhysics/Physics/Collision/PhysicsEntityCollision.h"

#include <vector>

namespace Edge
{
	class PhysicsCollisionDispatcher
	{
	public:
		using ContactDispatchingResultCollection = std::vector<PhysicsCollisionContactPoint>;

		PhysicsCollisionDispatcher() = default;
		virtual ~PhysicsCollisionDispatcher() = default;

		virtual void dispatch(const PhysicsEntityCollisionReference& collision1, const PhysicsEntityCollisionReference& collision2, PhysicsCollisionContactID contactID, ContactDispatchingResultCollection& results) = 0;
	};
}
