#pragma once

#include "EdgeCommon/Reference/MTReference.h"

namespace Edge
{
	class PhysicsConstraintSceneContext;

	class PhysicsConstraintSceneContextCollection : public DefaultDestroyingMTCountableObjectBase
	{
	public:
		PhysicsConstraintSceneContextCollection() = default;

		virtual PhysicsConstraintSceneContext* createContext() = 0;
		virtual void destroyContext(PhysicsConstraintSceneContext* context) = 0;
	};

	EDGE_MT_REFERENCE(PhysicsConstraintSceneContextCollection);
}
