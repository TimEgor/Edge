#pragma once

#include "PhysicsCollisionDispatcher.h"

namespace Edge
{
	class GJKCollisionDispatcher final : public PhysicsCollisionDispatcher
	{
	public:
		GJKCollisionDispatcher() = default;

		virtual uint32_t dispatch(const PhysicsEntityCollisionReference& collision1, const PhysicsEntityCollisionReference& collision2,
			PhysicsCollisionContactID contactID, ContactManifoldDispatchingResultCollection& results) override;
	};
}
