#pragma once

#include "EdgeCommon/Reference/MTReference.h"
#include "EdgeCommon/Reference/MTWeakReference.h"

namespace Edge
{
	class PhysicsScene;

	EDGE_MT_REFERENCE(PhysicsScene);
	EDGE_MT_WEAK_REFERENCE(PhysicsScene);
}
