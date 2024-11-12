#include "ComputeQuaternion.h"

Edge::ComputeQuaternion::ComputeQuaternion(const ComputeMath::Quaternion& quaternion) : m_quaternion(quaternion) {}

Edge::ComputeQuaternion::ComputeQuaternion(const FloatQuaternion& quaternion)
{
	loadFromFloatQuaternion(quaternion);
}

Edge::ComputeQuaternion& Edge::ComputeQuaternion::operator*=(const ComputeQuaternion& quaternion)
{
	m_quaternion = ComputeMath::quaternionMultiply(m_quaternion, quaternion.m_quaternion);
	return *this;
}

Edge::ComputeQuaternion& Edge::ComputeQuaternion::setupFromRotationAxis(const ComputeVector& axis, float angle)
{
	m_quaternion = ComputeMath::quaternionRotationAxis(axis.m_vector, angle);
	return *this;
}

Edge::ComputeQuaternion& Edge::ComputeQuaternion::setupFromRotationMatrix(const ComputeMatrix& rotation)
{
	m_quaternion = ComputeMath::quaternionRotationMatrix(rotation.m_matrix);
	return *this;
}

Edge::ComputeQuaternion& Edge::ComputeQuaternion::setupFromRollPitchYaw(const ComputeVector& angles)
{
	m_quaternion = ComputeMath::quaternionRotationRollPitchYaw(angles.m_vector);
	return *this;
}

Edge::ComputeQuaternion& Edge::ComputeQuaternion::setupFromRollPitchYaw(float pitch, float yaw, float roll)
{
	m_quaternion = ComputeMath::quaternionRotationRollPitchYaw(pitch, yaw, roll);
	return *this;
}

Edge::ComputeQuaternion& Edge::ComputeQuaternion::normalize()
{
	m_quaternion = ComputeMath::quaternionNormalize(m_quaternion);
	return *this;
}

float Edge::ComputeQuaternion::length() const
{
	return ComputeMath::quaternionLength(m_quaternion);
}

float Edge::ComputeQuaternion::lengthSqr() const
{
	return ComputeMath::quaternionLengthSqr(m_quaternion);
}

void Edge::ComputeQuaternion::loadFromFloatQuaternion(const FloatQuaternion& quaternion)
{
	m_quaternion = ComputeMath::loadQuaternion(quaternion);
}

void Edge::ComputeQuaternion::saveToFloatQuaternion(FloatQuaternion& quaternion) const
{
	ComputeMath::saveQuaternion(m_quaternion, quaternion);
}

Edge::FloatQuaternion Edge::ComputeQuaternion::getFloatQuaternion() const
{
	return ComputeMath::saveQuaternion(m_quaternion);
}

Edge::ComputeQuaternion Edge::ComputeQuaternionFromRotationAxis(const ComputeVector& axis, float angle)
{
	return ComputeMath::quaternionRotationAxis(axis.m_vector, angle);
}

Edge::ComputeQuaternion Edge::ComputeQuaternionFromRotationMatrix(const ComputeMatrix& rotation)
{
	return ComputeMath::quaternionRotationMatrix(rotation.m_matrix);
}

Edge::ComputeQuaternion Edge::ComputeQuaternionFromRollPitchYaw(const ComputeVector& angles)
{
	return ComputeMath::quaternionRotationRollPitchYaw(angles.m_vector);
}

Edge::ComputeQuaternion Edge::ComputeQuaternionFromRollPitchYaw(float pitch, float yaw, float roll)
{
	return ComputeMath::quaternionRotationRollPitchYaw(pitch, yaw, roll);
}

Edge::ComputeQuaternion Edge::NormalizeQuaternion(const ComputeQuaternion& quaternion)
{
	return ComputeMath::quaternionNormalize(quaternion.m_quaternion);
}

Edge::ComputeVector Edge::RotateVector(const ComputeQuaternion& quaternion, const ComputeVector& vector)
{
	return ComputeMath::vector3Rotate(vector.m_vector, quaternion.m_quaternion);
}

float Edge::QuaternionLength(const ComputeQuaternion& quaternion)
{
	return ComputeMath::quaternionLength(quaternion.m_quaternion);
}

float Edge::QuaternionLengthSqr(const ComputeQuaternion& quaternion)
{
	return ComputeMath::quaternionLengthSqr(quaternion.m_quaternion);
}

float Edge::DotQuaternion(const ComputeQuaternion& quaternion1, const ComputeQuaternion& quaternion2)
{
	return ComputeMath::quaternionDot(quaternion1.m_quaternion, quaternion2.m_quaternion);
}

Edge::ComputeQuaternion Edge::operator*(const ComputeQuaternion& quaternion1, const ComputeQuaternion& quaternion2)
{
	ComputeQuaternion quaternion3(quaternion1);
	return quaternion3 *= quaternion2;
}
