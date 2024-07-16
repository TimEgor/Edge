#include "AABB.h"

#include "ComputeVector.h"

Edge::AABB& Edge::AABB::merge(const AABB& volume)
{
	vectorMin(m_minPosition, volume.m_minPosition).saveToFloatVector3(m_minPosition);
	vectorMax(m_maxPosition, volume.m_maxPosition).saveToFloatVector3(m_maxPosition);

	return *this;
}

Edge::Transform Edge::AABB::getTransform() const
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

float Edge::AABB::getVolume() const
{
	FloatVector3 delta;
	(m_maxPosition - m_minPosition).saveToFloatVector3(delta);

	return delta.m_x * delta.m_y * delta.m_z;
}

bool Edge::AABB::isContained(const AABB& volume) const
{
	return ComputeMath::vector3LessOrEqual(ComputeMath::loadVector3(m_minPosition), ComputeMath::loadVector3(volume.m_minPosition)) &&
		ComputeMath::vector3GreaterOrEqual(ComputeMath::loadVector3(m_maxPosition), ComputeMath::loadVector3(volume.m_maxPosition));
}

Edge::AABB Edge::aabbFromMerging(const AABB& volume1, const AABB& volume2)
{
	AABB result(volume1);
	result.merge(volume2);

	return result;
}
