#include "AABB3Cast.h"

#include "EdgeCommon/Math/AABB.h"
#include "EdgeCommon/Math/ComputeVector.h"
#include "EdgeCommon/Math/Const.h"

bool Edge::CastAABB3::rayCast(const AABB3& aabb, const FloatVector3& origin, const FloatVector3& end, PhysicsCollisionQuery::PointCastingResult& result)
{
	const ComputeVector ray = end - origin;

	float tMin = 0.0f;
	//float tMax = TS_FLT_MAX;
	float tMax = 1.0f;

	for (uint32_t slabIndex = 0; slabIndex < 3; ++slabIndex)
	{
		const float directionElement = ray.getElement(slabIndex);

		const float originElement = origin.getElement(slabIndex);

		const float minBoundPositionElement = aabb.m_minPosition.getElement(slabIndex);
		const float maxBoundPositionElement = aabb.m_maxPosition.getElement(slabIndex);

		if (fabs(directionElement) < EDGE_EPSILON)
		{
			if (originElement < minBoundPositionElement ||
				originElement > maxBoundPositionElement)
			{
				return false;
			}
		}
		else
		{
			const float ood = 1.0f / directionElement;
			float t1 = (minBoundPositionElement - originElement) * ood;
			float t2 = (maxBoundPositionElement - originElement) * ood;

			if (t1 > t2)
			{
				const float tmp = t1;
				t1 = t2;
				t2 = tmp;
			}

			if (t1 > tMin)
			{
				tMin = t1;
			}

			if (t2 < tMax)
			{
				tMax = t2;
			}

			if (tMin > tMax)
			{
				return false;
			}
		}

	}

	if (tMin > 1.0f)
	{
		return false;
	}

	ComputeVector hitPos = origin;
	const ComputeVector delta = ray * tMin;
	hitPos += delta;

	hitPos.saveToFloatVector3(result.m_hitPosition);
	result.m_distance = delta.length3();

	return true;
}
