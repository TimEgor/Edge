#pragma once

#include "EdgeCommon/Reference/MTReference.h"

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

	EDGE_MT_REFERENCE(PhysicsEntityCollisionSceneContextCollection);
}
