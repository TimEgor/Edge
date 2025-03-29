#include "AABB3Cast.h"

#include "EdgeCommon/Math/AABB.h"
#include "EdgeCommon/Math/ComputeVector3.h"

bool Edge::CastAABB3::rayCast(const AABB3& aabb, const ComputeVector3& origin, const ComputeVector3& end, PhysicsCollisionQuery::PointCastingResult& result)
{
	const ComputeVector3 ray = end - origin;

	ComputeValueType tMin = ComputeValueType(0.0);
	//float tMax = TS_FLT_MAX;
	ComputeValueType tMax = ComputeValueType(1.0);

	for (uint32_t slabIndex = 0; slabIndex < 3; ++slabIndex)
	{
		const ComputeValueType directionElement = ray.getElement(slabIndex);

		const ComputeValueType originElement = origin.getElement(slabIndex);

		const ComputeValueType minBoundPositionElement = aabb.m_minPosition.getElement(slabIndex);
		const ComputeValueType maxBoundPositionElement = aabb.m_maxPosition.getElement(slabIndex);

		if (abs(directionElement) < Math::Epsilon)
		{
			if (originElement < minBoundPositionElement ||
				originElement > maxBoundPositionElement)
			{
				return false;
			}
		}
		else
		{
			const ComputeValueType ood = ComputeValueType(1.0) / directionElement;
			ComputeValueType t1 = (minBoundPositionElement - originElement) * ood;
			ComputeValueType t2 = (maxBoundPositionElement - originElement) * ood;

			if (t1 > t2)
			{
				const ComputeValueType tmp = t1;
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

	if (tMin > ComputeValueType(1.0))
	{
		return false;
	}

	const ComputeVector3 delta = ray * tMin;

	result.m_hitPosition = origin + delta;
	result.m_distance = delta.getLength();

	return true;
}
