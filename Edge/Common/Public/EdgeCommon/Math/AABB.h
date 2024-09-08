#pragma once

#include "Transform.h"
#include "Vector.h"

namespace Edge
{
	struct AABB3 final
	{
		FloatVector3 m_minPosition = FloatVector3Zero;
		FloatVector3 m_maxPosition = FloatVector3Zero;

		constexpr AABB3() = default;
		constexpr AABB3(const FloatVector3& min, const FloatVector3& max) : m_minPosition(min), m_maxPosition(max) {}

		AABB3& merge(const AABB3& volume);

		Transform getTransform() const;


		float getVolume() const;

		bool isContained(const AABB3& volume) const;
		bool isOverlapped(const AABB3& volume) const;
	};

	AABB3 aabbFromMerging(const AABB3& volume1, const AABB3& volume2);
}