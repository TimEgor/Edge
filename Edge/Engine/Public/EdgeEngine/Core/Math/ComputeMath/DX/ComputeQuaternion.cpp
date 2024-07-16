#include "TinySimCommon/Math/ComputeMath/ComputeQuaternion.h"
#ifdef TS_MATH_DX

TS::ComputeMath::Quaternion TS::ComputeMath::loadQuaternion(const FloatQuaternion& quat)
{
	return loadVector4(quat.m_elements);
}

TS::ComputeMath::Quaternion TS::ComputeMath::loadQuaternion(float x, float y, float z, float w)
{
	return loadVector4(x, y, z, w);
}

TS::FloatQuaternion TS::ComputeMath::saveQuaternion(const Quaternion& quat)
{
	return saveVector4(quat);
}

void TS::ComputeMath::saveQuaternion(const Quaternion& quat, FloatQuaternion& result)
{
	saveVector4(quat, result.m_elements);
}

TS::ComputeMath::Quaternion TS::ComputeMath::quaternionConjugate(const Quaternion& quat)
{
	return DirectX::XMQuaternionConjugate(quat);
}

TS::ComputeMath::Quaternion TS::ComputeMath::quaternionInverse(const Quaternion& quat)
{
	return DirectX::XMQuaternionInverse(quat);
}

TS::ComputeMath::Quaternion TS::ComputeMath::quaternionNormalize(const Quaternion& quat)
{
	return DirectX::XMQuaternionNormalize(quat);
}

TS::ComputeMath::Quaternion TS::ComputeMath::quaternionMultiply(const Quaternion& quat1, const Quaternion& quat2)
{
	return DirectX::XMQuaternionMultiply(quat1, quat2);
}

float TS::ComputeMath::quaternionDot(const Quaternion& quat1, const Quaternion& quat2)
{
	return vectorGetX(DirectX::XMQuaternionDot(quat1, quat2));
}

TS::ComputeMath::Quaternion TS::ComputeMath::quaternionDotV(const Quaternion& quat1, const Quaternion& quat2)
{
	return DirectX::XMQuaternionDot(quat1, quat2);
}

TS::ComputeMath::Quaternion TS::ComputeMath::quaternionRotationAxis(const Vector& axis, float angle)
{
	return DirectX::XMQuaternionRotationAxis(axis, angle);
}

TS::ComputeMath::Quaternion TS::ComputeMath::quaternionRotationMatrix(const Matrix& matrix)
{
	return XMQuaternionRotationMatrix(matrix);
}

TS::ComputeMath::Quaternion TS::ComputeMath::quaternionRotationRollPitchYaw(const Vector& angles)
{
	return DirectX::XMQuaternionRotationRollPitchYawFromVector(angles);
}

TS::ComputeMath::Quaternion TS::ComputeMath::quaternionRotationRollPitchYaw(const FloatVector3& angles)
{
	return quaternionRotationRollPitchYaw(angles.m_x, angles.m_y, angles.m_z);
}

TS::ComputeMath::Quaternion TS::ComputeMath::quaternionRotationRollPitchYaw(float pitch, float yaw, float roll)
{
	return DirectX::XMQuaternionRotationRollPitchYaw(pitch, yaw, roll);
}

void TS::ComputeMath::quaternionAxisAngle(Vector& axis, float& angle, const Quaternion& quat)
{
	DirectX::XMQuaternionToAxisAngle(&axis, &angle, quat);
}

bool TS::ComputeMath::quaternionEqual(const Quaternion& quat1, const Quaternion& quat2)
{
	return DirectX::XMQuaternionEqual(quat1, quat2);
}

TS::ComputeMath::Quaternion TS::ComputeMath::quaternionSlerp(const Quaternion& quat1, const Quaternion& quat2, float t)
{
	return DirectX::XMQuaternionSlerp(quat1, quat2, t);
}

TS::ComputeMath::Quaternion TS::ComputeMath::quaternionSlerpV(const Quaternion& quat1, const Quaternion& quat2, const
                                                             Vector& t)
{
	return DirectX::XMQuaternionSlerpV(quat1, quat2, t);
}

TS::ComputeMath::Vector TS::ComputeMath::quaternionLengthV(const Quaternion& quat)
{
	return DirectX::XMQuaternionLength(quat);
}

TS::ComputeMath::Vector TS::ComputeMath::quaternionLengthSqrV(const Quaternion& quat)
{
	return DirectX::XMQuaternionLengthSq(quat);
}

float TS::ComputeMath::quaternionLength(const Quaternion& quat)
{
	return vectorGetX(DirectX::XMQuaternionLength(quat));
}

float TS::ComputeMath::quaternionLengthSqr(const Quaternion& quat)
{
	return vectorGetX(DirectX::XMQuaternionLengthSq(quat));
}
#endif