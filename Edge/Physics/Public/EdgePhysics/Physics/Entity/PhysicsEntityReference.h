#pragma once

#include "EdgeCommon/HashedType.h"
#include "EdgeCommon/Reference/MTReference.h"

namespace Edge
{
	using PhysicsEntityType = HashedType::Type;

	class PhysicsEntity;

	EDGE_MT_REFERENCE(PhysicsEntity);
}
