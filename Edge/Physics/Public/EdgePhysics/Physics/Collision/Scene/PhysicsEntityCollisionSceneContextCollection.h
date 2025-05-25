#pragma once

#include "EdgeCommon/Reference/Reference.h"

namespace Edge
{
	class PhysicsEntityCollisionSceneContext;

	class PhysicsEntityCollisionSceneContextCollection : public DefaultDestroyingMTCountableObjectBase
	{
	public:
		PhysicsEntityCollisionSceneContextCollection() = default;

		virtual PhysicsEntityCollisionSceneContext* createContext() = 0;
		virtual void destroyContext(PhysicsEntityCollisionSceneContext* context) = 0;
	};

	EDGE_REFERENCE(PhysicsEntityCollisionSceneContextCollection);
}
