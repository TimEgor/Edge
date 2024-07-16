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

		void setupFromRotationAxis(const ComputeVector& axis, float angle);
		void setupFromRotationMatrix(const ComputeMatrix& rotation);
		void setupFromRollPitchYaw(const ComputeVector& angles);
		void setupFromRollPitchYaw(float pitch, float yaw, float roll);

		ComputeQuaternion& normalize();

		float length() const;
		float lengthSqr() const;

		void loadFromFloatQuaternion(const FloatQuaternion& quaternion);

		void saveToFloatQuaternion(FloatQuaternion& quaternion) const;

		FloatQuaternion getFloatQuaternion() const;
	};

	ComputeQuaternion computeQuaternionFromRotationAxis(const ComputeVector& axis, float angle);
	ComputeQuaternion computeQuaternionFromRotationMatrix(const ComputeMatrix& rotation);
	ComputeQuaternion computeQuaternionFromRollPitchYaw(const ComputeVector& angles);
	ComputeQuaternion computeQuaternionFromRollPitchYaw(float pitch, float yaw, float roll);

	ComputeQuaternion normalizeQuaternion(const ComputeQuaternion& quaternion);

	float quaternionLength(const ComputeQuaternion& quaternion);
	float quaternionLengthSqr(const ComputeQuaternion& quaternion);

	float dotQuaternion(const ComputeQuaternion& quaternion1, const ComputeQuaternion& quaternion2);

	ComputeQuaternion operator*(const ComputeQuaternion& quaternion1, const ComputeQuaternion& quaternion2);
}