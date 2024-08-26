#include "SphereCast.h"

#include "EdgeCommon/Math/ComputeVector.h"

bool Edge::CastSphere::rayCast(const FloatVector3& sphereCenter, float sphereRadius, const FloatVector3& origin, const FloatVector3& end, PhysicsCollisionQuery::PointCastingResult& result)
{
	const ComputeVector baseDelta = origin - sphereCenter;
	const ComputeVector ray = end - origin;
	const float rayLength = ray.length3();
	const ComputeVector rayDirection = ray / rayLength;

	const float b = dotVector3(baseDelta, normalizeVector(rayDirection));
	const float c = dotVector3(baseDelta, baseDelta) - sphereRadius * sphereRadius;

	if (c > 0.0f && b > 0.0f)
	{
		return false;
	}

	const float discriminant = b * b - c;
	if (discriminant < 0.0f)
	{
		return false;
	}

	float t = -b - sqrtf(discriminant);

	if (t > rayLength)
	{
		return false;
	}

	if (t < 0.0f) // ray origin is located inside a sphere
	{
		t = 0.0f;
	}

	ComputeVector hitPos = origin;
	const ComputeVector delta = rayDirection * t;
	hitPos += delta;

	hitPos.saveToFloatVector3(result.m_hitPosition);
	result.m_distance = delta.length3();

	return true;
}
