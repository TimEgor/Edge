#pragma once

#include "EdgeCommon/Reference/Reference.h"
#include "EdgeCommon/Reference/MTWeakReference.h"

namespace Edge
{
	class PhysicsScene;

	EDGE_REFERENCE(PhysicsScene);
	EDGE_MT_WEAK_REFERENCE(PhysicsScene);
}
