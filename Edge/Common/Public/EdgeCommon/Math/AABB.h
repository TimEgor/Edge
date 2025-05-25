#pragma once

#include "ComputeVector3.h"
#include "Transform.h"
#include "Vector.h"

namespace Edge
{
	struct AABB3 final
	{
		ComputeVector3 m_minPosition = ComputeVector3Zero;
		ComputeVector3 m_maxPosition = ComputeVector3Zero;

		constexpr AABB3() = default;
		constexpr AABB3(const ComputeVector3& min, const ComputeVector3& max) : m_minPosition(min), m_maxPosition(max) {}

		AABB3& merge(const AABB3& volume);

		Transform getTransform() const;


		float getVolume() const;

		bool isContained(const AABB3& volume) const;
		bool isOverlapped(const AABB3& volume) const;
	};

	AABB3 aabbFromMerging(const AABB3& volume1, const AABB3& volume2);
}