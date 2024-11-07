#pragma once

#include "EdgeCommon/Reference/MTCountableObjectBase.h"

namespace Edge
{
	class PhysicsEntitySceneContext;

	class PhysicsEntitySceneContextCollection : public DefaultDestroyingMTCountableObjectBase
	{
	public:
		PhysicsEntitySceneContextCollection() = default;

		virtual PhysicsEntitySceneContext* createContext() = 0;
		virtual void destroyContext(PhysicsEntitySceneContext* context) = 0;
	};

	EDGE_MT_REFERENCE(PhysicsEntitySceneContextCollection);
}
