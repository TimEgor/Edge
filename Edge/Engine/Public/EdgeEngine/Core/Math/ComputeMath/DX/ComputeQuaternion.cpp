#include "EdgeEngine/Core/Math/ComputeMath/ComputeMath.h"

#ifdef EDGE_MATH_DX
#include "EdgeEngine/Core/Math/ComputeMath/ComputeQuaternion.h"

Edge::ComputeMath::Quaternion Edge::ComputeMath::loadQuaternion(const FloatQuaternion& quat)
{
	return loadVector4(quat.m_elements);
}

Edge::ComputeMath::Quaternion Edge::ComputeMath::loadQuaternion(float x, float y, float z, float w)
{
	return loadVector4(x, y, z, w);
}

Edge::FloatQuaternion Edge::ComputeMath::saveQuaternion(const Quaternion& quat)
{
	return saveVector4(quat);
}

void Edge::ComputeMath::saveQuaternion(const Quaternion& quat, FloatQuaternion& result)
{
	saveVector4(quat, result.m_elements);
}

Edge::ComputeMath::Quaternion Edge::ComputeMath::quaternionConjugate(const Quaternion& quat)
{
	return DirectX::XMQuaternionConjugate(quat);
}

Edge::ComputeMath::Quaternion Edge::ComputeMath::quaternionInverse(const Quaternion& quat)
{
	return DirectX::XMQuaternionInverse(quat);
}

Edge::ComputeMath::Quaternion Edge::ComputeMath::quaternionNormalize(const Quaternion& quat)
{
	return DirectX::XMQuaternionNormalize(quat);
}

Edge::ComputeMath::Quaternion Edge::ComputeMath::quaternionMultiply(const Quaternion& quat1, const Quaternion& quat2)
{
	return DirectX::XMQuaternionMultiply(quat1, quat2);
}

float Edge::ComputeMath::quaternionDot(const Quaternion& quat1, const Quaternion& quat2)
{
	return vectorGetX(DirectX::XMQuaternionDot(quat1, quat2));
}

Edge::ComputeMath::Quaternion Edge::ComputeMath::quaternionDotV(const Quaternion& quat1, const Quaternion& quat2)
{
	return DirectX::XMQuaternionDot(quat1, quat2);
}

Edge::ComputeMath::Quaternion Edge::ComputeMath::quaternionRotationAxis(const Vector& axis, float angle)
{
	return DirectX::XMQuaternionRotationAxis(axis, angle);
}

Edge::ComputeMath::Quaternion Edge::ComputeMath::quaternionRotationMatrix(const Matrix& matrix)
{
	return XMQuaternionRotationMatrix(matrix);
}

Edge::ComputeMath::Quaternion Edge::ComputeMath::quaternionRotationRollPitchYaw(const Vector& angles)
{
	return DirectX::XMQuaternionRotationRollPitchYawFromVector(angles);
}

Edge::ComputeMath::Quaternion Edge::ComputeMath::quaternionRotationRollPitchYaw(const FloatVector3& angles)
{
	return quaternionRotationRollPitchYaw(angles.m_x, angles.m_y, angles.m_z);
}

Edge::ComputeMath::Quaternion Edge::ComputeMath::quaternionRotationRollPitchYaw(float pitch, float yaw, float roll)
{
	return DirectX::XMQuaternionRotationRollPitchYaw(pitch, yaw, roll);
}

void Edge::ComputeMath::quaternionAxisAngle(Vector& axis, float& angle, const Quaternion& quat)
{
	DirectX::XMQuaternionToAxisAngle(&axis, &angle, quat);
}

bool Edge::ComputeMath::quaternionEqual(const Quaternion& quat1, const Quaternion& quat2)
{
	return DirectX::XMQuaternionEqual(quat1, quat2);
}

Edge::ComputeMath::Quaternion Edge::ComputeMath::quaternionSlerp(const Quaternion& quat1, const Quaternion& quat2, float t)
{
	return DirectX::XMQuaternionSlerp(quat1, quat2, t);
}

Edge::ComputeMath::Quaternion Edge::ComputeMath::quaternionSlerpV(const Quaternion& quat1, const Quaternion& quat2, const
                                                             Vector& t)
{
	return DirectX::XMQuaternionSlerpV(quat1, quat2, t);
}

Edge::ComputeMath::Vector Edge::ComputeMath::quaternionLengthV(const Quaternion& quat)
{
	return DirectX::XMQuaternionLength(quat);
}

Edge::ComputeMath::Vector Edge::ComputeMath::quaternionLengthSqrV(const Quaternion& quat)
{
	return DirectX::XMQuaternionLengthSq(quat);
}

float Edge::ComputeMath::quaternionLength(const Quaternion& quat)
{
	return vectorGetX(DirectX::XMQuaternionLength(quat));
}

float Edge::ComputeMath::quaternionLengthSqr(const Quaternion& quat)
{
	return vectorGetX(DirectX::XMQuaternionLengthSq(quat));
}
#endif