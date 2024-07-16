#pragma once

#include "ComputeMatrix.h"
#include "EdgeEngine/Core/Math/Quaternion.h"

namespace Edge
{
	namespace ComputeMath
	{
		//Loading
		Quaternion loadQuaternion(const FloatQuaternion& quat);
		Quaternion loadQuaternion(float x = 0.0f, float y = 0.0f, float z = 0.0f, float w = 0.0f);

		//Saving
		FloatQuaternion saveQuaternion(const Quaternion& quat);
		void saveQuaternion(const Quaternion& quat, FloatQuaternion& result);

		Quaternion quaternionConjugate(const Quaternion& quat);
		Quaternion quaternionInverse(const Quaternion& quat);

		Quaternion quaternionNormalize(const Quaternion& quat);

		Quaternion quaternionMultiply(const Quaternion& quat1, const Quaternion& quat2);
		float quaternionDot(const Quaternion& quat1, const Quaternion& quat2);
		Quaternion quaternionDotV(const Quaternion& quat1, const Quaternion& quat2);

		Quaternion quaternionRotationAxis(const Vector& axis, float angle);
		Quaternion quaternionRotationMatrix(const Matrix& matrix);
		Quaternion quaternionRotationRollPitchYaw(const Vector& angles);
		Quaternion quaternionRotationRollPitchYaw(const FloatVector3& angles);
		Quaternion quaternionRotationRollPitchYaw(float pitch, float yaw, float roll);

		void quaternionAxisAngle(Vector& axis, float& angle, const Quaternion& quat);

		bool quaternionEqual(const Quaternion& quat1, const Quaternion& quat2);

		Quaternion quaternionSlerp(const Quaternion& quat1, const Quaternion& quat2, float t);
		Quaternion quaternionSlerpV(const Quaternion& quat1, const Quaternion& quat2, const Vector& t);

		Vector quaternionLengthV(const Quaternion& quat);
		Vector quaternionLengthSqrV(const Quaternion& quat);

		float quaternionLength(const Quaternion& quat);
		float quaternionLengthSqr(const Quaternion& quat);
	}
}
