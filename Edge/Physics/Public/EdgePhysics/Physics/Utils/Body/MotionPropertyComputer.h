#pragma once

#include "EdgeCommon/Math/Vector.h"
#include "EdgeCommon/Patterns/NonInstanceable.h"

namespace Edge
{
	class MotionPropertyComputer final : NonInstanceable
	{
	public:
		static float CalcSphereMass(float radius, float density);
		static FloatVector3 CalcSphereInertiaTensor(float mass, float radius);

		static float CalcBoxMass(const FloatVector3& size, float density);
		static FloatVector3 CalcBoxInertiaTensor(float mass, const FloatVector3& size);
	};
}
