#pragma once

#include "ComputeMatrix.h"
#include "ComputeMath/ComputeQuaternion.h"

namespace Edge
{
	class ComputeQuaternion final
	{
	public:
		ComputeMath::Quaternion m_quaternion;

		ComputeQuaternion() = default;
		ComputeQuaternion(const ComputeMath::Quaternion& quaternion);
		ComputeQuaternion(const FloatQuaternion& quaternion);
		ComputeQuaternion(const ComputeQuaternion& quaternion) = default;

		ComputeQuaternion& operator=(const ComputeQuaternion& quaternion) = default;

		ComputeQuaternion& operator*=(const ComputeQuaternion& quaternion);

		ComputeQuaternion& setupFromRotationAxis(const ComputeVector& axis, float angle);
		ComputeQuaternion& setupFromRotationMatrix(const ComputeMatrix& rotation);
		ComputeQuaternion& setupFromRollPitchYaw(const ComputeVector& angles);
		ComputeQuaternion& setupFromRollPitchYaw(float pitch, float yaw, float roll);

		ComputeQuaternion& normalize();

		float length() const;
		float lengthSqr() const;

		void loadFromFloatQuaternion(const FloatQuaternion& quaternion);

		void saveToFloatQuaternion(FloatQuaternion& quaternion) const;

		FloatQuaternion getFloatQuaternion() const;
	};

	ComputeQuaternion ComputeQuaternionFromRotationAxis(const ComputeVector& axis, float angle);
	ComputeQuaternion ComputeQuaternionFromRotationMatrix(const ComputeMatrix& rotation);
	ComputeQuaternion ComputeQuaternionFromRollPitchYaw(const ComputeVector& angles);
	ComputeQuaternion ComputeQuaternionFromRollPitchYaw(float pitch, float yaw, float roll);

	ComputeQuaternion NormalizeQuaternion(const ComputeQuaternion& quaternion);

	ComputeVector RotateVector(const ComputeQuaternion& quaternion, const ComputeVector& vector);

	float QuaternionLength(const ComputeQuaternion& quaternion);
	float QuaternionLengthSqr(const ComputeQuaternion& quaternion);

	float DotQuaternion(const ComputeQuaternion& quaternion1, const ComputeQuaternion& quaternion2);

	ComputeQuaternion operator*(const ComputeQuaternion& quaternion1, const ComputeQuaternion& quaternion2);
}