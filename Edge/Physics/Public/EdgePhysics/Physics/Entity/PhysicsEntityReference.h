#pragma once

#include "EdgeCommon/HashedType.h"
#include "EdgeCommon/Reference/Reference.h"

namespace Edge
{
	using PhysicsEntityType = HashedType::Type;

	class PhysicsEntity;

	EDGE_REFERENCE(PhysicsEntity);
}
