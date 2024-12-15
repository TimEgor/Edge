#pragma once

#include "PhysicsCollisionDispatcher.h"

namespace Edge
{
	class SphereVsSphereCollisionDispatcher final : public PhysicsCollisionDispatcher
	{
	public:
		SphereVsSphereCollisionDispatcher() = default;

		virtual uint32_t dispatch(const PhysicsEntityCollisionReference& collision1, const PhysicsEntityCollisionReference& collision2,
			PhysicsCollisionContactID contactID, ContactManifoldDispatchingResultCollection& results) override;
	};
}
