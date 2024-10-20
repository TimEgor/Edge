#include "MotionPropertyComputer.h"

#include "EdgeCommon/Math/ComputeVector.h"
#include "EdgeCommon/Math/Const.h"

float Edge::MotionPropertyComputer::CalcSphereMass(float radius, float density)
{
	const float volume = radius * radius * radius * EDGE_PI * (4.0f / 3.0f);
	return volume * density;
}

Edge::FloatVector3 Edge::MotionPropertyComputer::CalcSphereInertiaTensor(float mass, float radius)
{
	const float inertia = mass * radius * radius * (2.0f / 5.0f);
	return FloatVector3(inertia);
}

float Edge::MotionPropertyComputer::CalcBoxMass(const FloatVector3& size, float density)
{
	const float volume = size.m_x * size.m_y * size.m_z;
	return volume * density;
}

Edge::FloatVector3 Edge::MotionPropertyComputer::CalcBoxInertiaTensor(float mass, const FloatVector3& size)
{
	const ComputeVector sizeSqr = MultiplyVector(size, size);
	const ComputeVector axisDistanceCoeff = ComputeVector(ComputeMath::vectorSwizzle(sizeSqr.m_vector, 1, 0, 0, 4)) + ComputeVector(ComputeMath::vectorSwizzle(sizeSqr.m_vector, 2, 2, 1, 4));
	const ComputeVector inertia = axisDistanceCoeff * (mass / 12.0f);

	return inertia.getFloatVector3();
}
