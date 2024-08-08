#pragma once

#include "EdgeCommon/Patterns/NonCopyable.h"

#include "PhysicsWorldReference.h"

namespace Edge
{
	class PhysicsWorld final : public NonCopyable, public DefaultDestroyingMTCountableObjectBase, public MTWeakReferencableBase<PhysicsWorld>
	{
	public:
		PhysicsWorld() = default;

		bool init();
		void release();
	};
}
