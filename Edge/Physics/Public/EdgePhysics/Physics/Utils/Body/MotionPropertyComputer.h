#pragma once

#include "EdgeCommon/Math/Vector.h"

namespace Edge
{
	namespace MotionPropertyComputer
	{
		float CalcSphereMass(float radius, float density);
		FloatVector3 CalcSphereInertiaTensor(float mass, float radius);

		float CalcBoxMass(const FloatVector3& size, float density);
		FloatVector3 CalcBoxInertiaTensor(float mass, const FloatVector3& size);
	};
}
