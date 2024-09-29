#pragma once
#include "EdgeCommon/Math/Vector.h"

namespace Edge
{
	class MotionPropertyComputer final
	{
	public:
		MotionPropertyComputer() = delete;

		static float CalcSphereMass(float radius, float density);
		static FloatVector3 CalcSphereInertiaTensor(float mass, float radius);

		static float CalcBoxMass(const FloatVector3& size, float density);
		static FloatVector3 CalcBoxInertiaTensor(float mass, const FloatVector3& size);
	};
}
