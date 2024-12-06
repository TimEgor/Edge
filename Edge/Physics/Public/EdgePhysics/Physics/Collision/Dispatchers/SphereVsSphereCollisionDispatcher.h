#pragma once

#include "PhysicsCollisionDispatcher.h"

namespace Edge
{
	class SphereVsSphereCollisionDispatcher final : public PhysicsCollisionDispatcher
	{
	public:
		SphereVsSphereCollisionDispatcher() = default;

		virtual void dispatch(const PhysicsEntityCollisionReference& collision1, const PhysicsEntityCollisionReference& collision2, PhysicsCollisionContactID contactID, ContactManifoldDispatchingResultCollection& results) override;
	};
}
