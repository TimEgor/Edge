#pragma once

#include "EdgeCommon/Reference/MTReference.h"
#include "EdgeCommon/Reference/MTWeakReference.h"

namespace Edge
{
	class PhysicsWorld;

	EDGE_MT_REFERENCE(PhysicsWorld);
	EDGE_MT_WEAK_REFERENCE(PhysicsWorld);
}
