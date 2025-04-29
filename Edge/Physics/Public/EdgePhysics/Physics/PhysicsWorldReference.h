#pragma once

#include "EdgeCommon/Reference/Reference.h"
#include "EdgeCommon/Reference/MTWeakReference.h"

namespace Edge
{
	class PhysicsWorld;

	EDGE_REFERENCE(PhysicsWorld);
	EDGE_MT_WEAK_REFERENCE(PhysicsWorld);
}
