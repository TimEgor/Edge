#pragma once

#include "EdgeCommon/Math/ComputeVector3.h"

namespace Edge
{
	namespace MotionPropertyComputer
	{
		ComputeValueType CalcSphereMass(ComputeValueType radius, ComputeValueType density);
		ComputeVector3 CalcSphereInertiaTensor(ComputeValueType mass, ComputeValueType radius);

		ComputeValueType CalcBoxMass(const ComputeVector3& size, ComputeValueType density);
		ComputeVector3 CalcBoxInertiaTensor(ComputeValueType mass, const ComputeVector3& size);
	};
}
