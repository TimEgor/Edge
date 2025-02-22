#include "AABB.h"

#include "ComputeVector.h"

Edge::AABB3& Edge::AABB3::merge(const AABB3& volume)
{
	VectorMin(m_minPosition, volume.m_minPosition).saveToFloatVector3(m_minPosition);
	VectorMax(m_maxPosition, volume.m_maxPosition).saveToFloatVector3(m_maxPosition);

	return *this;
}

Edge::Transform Edge::AABB3::getTransform() const
{
	const ComputeVector delta = m_maxPosition - m_minPosition;
	const ComputeVector size = delta * 0.5f;
	const ComputeVector center = m_minPosition + size;

	FloatVector3 sizeVals;
	delta.saveToFloatVector3(sizeVals);

	Transform transform;
	transform.setOrigin(center.getFloatVector3());
	transform.m_matrix.m_row1.m_x = sizeVals.m_x;
	transform.m_matrix.m_row2.m_y = sizeVals.m_y;
	transform.m_matrix.m_row3.m_z = sizeVals.m_z;

	return transform;
}

float Edge::AABB3::getVolume() const
{
	FloatVector3 delta;
	(m_maxPosition - m_minPosition).saveToFloatVector3(delta);

	return delta.m_x * delta.m_y * delta.m_z;
}

bool Edge::AABB3::isContained(const AABB3& volume) const
{
	return ComputeMath::vector3LessOrEqual(ComputeMath::vector3Load(m_minPosition), ComputeMath::vector3Load(volume.m_minPosition)) &&
		ComputeMath::vector3GreaterOrEqual(ComputeMath::vector3Load(m_maxPosition), ComputeMath::vector3Load(volume.m_maxPosition));
}

bool Edge::AABB3::isOverlapped(const AABB3& volume) const
{
	return !(ComputeMath::vector3AnyLess(ComputeMath::vector3Load(m_maxPosition), ComputeMath::vector3Load(volume.m_minPosition)) ||
		ComputeMath::vector3AnyGreater(ComputeMath::vector3Load(m_minPosition), ComputeMath::vector3Load(volume.m_maxPosition)));
}

Edge::AABB3 Edge::aabbFromMerging(const AABB3& volume1, const AABB3& volume2)
{
	AABB3 result(volume1);
	result.merge(volume2);

	return result;
}
