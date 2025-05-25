#include "MotionPropertyComputer.h"

Edge::ComputeValueType Edge::MotionPropertyComputer::CalcSphereMass(ComputeValueType radius, ComputeValueType density)
{
	const ComputeValueType volume = radius * radius * radius * Math::Pi * (ComputeValueType(4.0) / ComputeValueType(3.0));
	return volume * density;
}

Edge::ComputeVector3 Edge::MotionPropertyComputer::CalcSphereInertiaTensor(ComputeValueType mass, ComputeValueType radius)
{
	const ComputeValueType inertia = mass * radius * radius * (ComputeValueType(2.0) / ComputeValueType(5.0));
	return ComputeVector3(inertia);
}

Edge::ComputeValueType Edge::MotionPropertyComputer::CalcBoxMass(const ComputeVector3& size, ComputeValueType density)
{
	const ComputeValueType volume = size.getX() * size.getY() * size.getZ();
	return volume * density;
}

Edge::ComputeVector3 Edge::MotionPropertyComputer::CalcBoxInertiaTensor(ComputeValueType mass, const ComputeVector3& size)
{
	const ComputeVector3 sizeSqr = MultiplyComputeVector3Elements(size, size);
	const ComputeVector3 axisDistanceCoeff = sizeSqr.swizzle(1, 0, 0) + sizeSqr.swizzle(2, 2, 1);
	const ComputeVector3 inertia = axisDistanceCoeff * (mass / ComputeValueType(12.0));

	return inertia;
}
