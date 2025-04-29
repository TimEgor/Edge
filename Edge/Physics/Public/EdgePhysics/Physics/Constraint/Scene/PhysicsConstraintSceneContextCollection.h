#pragma once

#include "EdgeCommon/Reference/Reference.h"

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

	EDGE_REFERENCE(PhysicsConstraintSceneContextCollection);
}
