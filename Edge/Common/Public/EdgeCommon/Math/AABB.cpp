#include "AABB.h"

#include "ComputeVector3.h"

Edge::AABB3& Edge::AABB3::merge(const AABB3& volume)
{
	m_minPosition = MinComputeVector3(m_minPosition, volume.m_minPosition);
	m_maxPosition = MaxComputeVector3(m_maxPosition, volume.m_maxPosition);

	return *this;
}

Edge::Transform Edge::AABB3::getTransform() const
{
	const ComputeVector3 delta = m_maxPosition - m_minPosition;
	const ComputeVector3 size = delta * 0.5f;
	const ComputeVector3 center = m_minPosition + size;

	Transform transform;
	transform.setOrigin(center);
	transform.m_matrix.getColumn(0).setX(size.getX());
	transform.m_matrix.getColumn(1).setY(size.getY());
	transform.m_matrix.getColumn(2).setZ(size.getZ());

	return transform;
}

float Edge::AABB3::getVolume() const
{
	const ComputeVector3 delta = m_maxPosition - m_minPosition;

	return delta.getX() * delta.getY() * delta.getZ();
}

bool Edge::AABB3::isContained(const AABB3& volume) const
{
	return m_minPosition.isLessOrEqual(volume.m_minPosition) &&
		m_maxPosition.isGreaterOrEqual(volume.m_maxPosition);
}

bool Edge::AABB3::isOverlapped(const AABB3& volume) const
{
	return !(m_maxPosition.isAnyLess(volume.m_minPosition)) ||
		m_minPosition.isAnyGreater(volume.m_maxPosition);
}

Edge::AABB3 Edge::aabbFromMerging(const AABB3& volume1, const AABB3& volume2)
{
	AABB3 result(volume1);
	result.merge(volume2);

	return result;
}
