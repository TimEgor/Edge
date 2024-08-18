#pragma once

#include "PhysicsBoxShape.h"

namespace Edge
{
	class PhysicsBoxShapeFactory final
	{
	public:
		PhysicsBoxShapeFactory() = default;

		PhysicsBoxShapeReference createBoxShape(const FloatVector3& size) { return new PhysicsBoxShape(size); }
	};
}
