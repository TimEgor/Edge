#include "SphereCast.h"

#include "EdgeCommon/Math/ComputeVector3.h"

bool Edge::CastSphere::rayCast(const ComputeVector3& sphereCenter, ComputeValueType sphereRadius, const ComputeVector3& origin, const ComputeVector3& end, PhysicsCollisionQuery::PointCastingResult& result)
{
	const ComputeVector3 baseDelta = origin - sphereCenter;
	const ComputeVector3 ray = end - origin;
	const ComputeValueType rayLength = ray.getLength();
	const ComputeVector3 rayDirection = ray / rayLength;

	const ComputeValueType b = DotComputeVector3(baseDelta, NormalizeComputeVector3(rayDirection));
	const ComputeValueType c = DotComputeVector3(baseDelta, baseDelta) - sphereRadius * sphereRadius;

	if (c > ComputeValueType(0.0) && b > ComputeValueType(0.0))
	{
		return false;
	}

	const ComputeValueType discriminant = b * b - c;
	if (discriminant < ComputeValueType(0.0))
	{
		return false;
	}

	ComputeValueType t = -b - sqrt(discriminant);

	if (t > rayLength)
	{
		return false;
	}

	if (t < ComputeValueType(0.0)) // ray origin is located inside a sphere
	{
		t = ComputeValueType(0.0);
	}

	result.m_hitPosition = origin;
	const ComputeVector3 delta = rayDirection * t;
	result.m_hitPosition += delta;

	result.m_distance = delta.getLength();

	return true;
}
