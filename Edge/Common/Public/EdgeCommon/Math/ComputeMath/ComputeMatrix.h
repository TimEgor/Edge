#pragma once

#include "EdgeCommon/Math/Matrix.h"
#include "EdgeCommon/Math/ComputeMath/ComputeVector.h"

namespace Edge
{
	namespace ComputeMath
	{
#if defined(EDGE_MATH_DX)
		using Matrix = DirectX::XMMATRIX;
#else
		static_assert("Compute matrix isn't defined");
#endif

		//Loading
		Matrix loadMatrix2x2(const FloatMatrix2x2& matrix);
		Matrix loadMatrix3x3(const FloatMatrix3x3& matrix);
		Matrix loadMatrix4x4(const FloatMatrix4x4& matrix);
		Matrix loadMatrix4x4(
			float m11, float m12, float m13, float m14,
			float m21, float m22, float m23, float m24,
			float m31, float m32, float m33, float m34,
			float m41, float m42, float m43, float m44);

		//Saving
		FloatMatrix2x2 saveMatrix2x2(const Matrix& matrix);
		FloatMatrix3x3 saveMatrix3x3(const Matrix& matrix);
		FloatMatrix4x4 saveMatrix4x4(const Matrix& matrix);
		void saveMatrix2x2(const Matrix& matrix, FloatMatrix2x2& result);
		void saveMatrix3x3(const Matrix& matrix, FloatMatrix3x3& result);
		void saveMatrix4x4(const Matrix& matrix, FloatMatrix4x4& result);

		//Arithmetic
		Vector matrixDeterminantV(const Matrix& matrix);
		float matrixDeterminant(const Matrix& matrix);
		Matrix matrixInverse(const Matrix& matrix);
		bool matrixIsIdentity(const Matrix& matrix);
		bool matrixIsInfinite(const Matrix& matrix);
		bool matrixIsNaN(const Matrix& matrix);
		Matrix matrixMultiply(const Matrix& matrix1, const Matrix& matrix2);
		Matrix matrixTranspose(const Matrix& matrix);

		//Transformation
		Matrix matrixLookAtLH(const Vector& eyePos, const Vector& focusPos, const Vector& upDir);
		Matrix matrixLookAtRH(const Vector& eyePos, const Vector& focusPos, const Vector& upDir);
		Matrix matrixLookToLH(const Vector& eyePos, const Vector& eyeDir, const Vector& upDir);
		Matrix matrixLookToRH(const Vector& eyePos, const Vector& eyeDir, const Vector& upDir);
		Matrix matrixOrthographicLH(float viewWidth, float viewHeight, float nearZ, float farZ);
		Matrix matrixOrthographicRH(float viewWidth, float viewHeight, float nearZ, float farZ);
		Matrix matrixOrthographicOffCenterLH(float viewLeft, float viewRight, float viewBottom, float viewTop, float nearZ, float farZ);
		Matrix matrixOrthographicOffCenterRH(float viewLeft, float viewRight, float viewBottom, float viewTop, float nearZ, float farZ);
		Matrix matrixPerspectiveFovLH(float fovAngleY, float aspectRatio, float nearZ, float farZ);
		Matrix matrixPerspectiveFovRH(float fovAngleY, float aspectRatio, float nearZ, float farZ);
		Matrix matrixPerspectiveLH(float viewWidth, float viewHeight, float nearZ, float farZ);
		Matrix matrixPerspectiveRH(float viewWidth, float viewHeight, float nearZ, float farZ);
		Matrix matrixPerspectiveOffCenterLH(float viewLeft, float viewRight, float viewBottom, float viewTop, float nearZ, float farZ);
		Matrix matrixPerspectiveOffCenterRH(float viewLeft, float viewRight, float viewBottom, float viewTop, float nearZ, float farZ);

		Matrix matrixRotationAxis(const Vector& axis, float angle);
		Matrix matrixRotationNormal(const Vector& normalAxis, float angle);
		Matrix matrixRotationQuaternion(const Quaternion& quaternion);
		Matrix matrixRotationRollPitchYaw(float pitch, float yaw, float roll);
		Matrix matrixRotationRollPitchYaw(const FloatVector3& angles);
		Matrix matrixRotationRollPitchYaw(const Vector& angles);
		Matrix matrixRotationX(float angle);
		Matrix matrixRotationY(float angle);
		Matrix matrixRotationZ(float angle);
		Matrix matrixScaling(float scaleX, float scaleY, float scaleZ);
		Matrix matrixScaling(const FloatVector3& scale);
		Matrix matrixScaling(const Vector& scale);
		Matrix matrixTranslation(float offsetX, float offsetY, float offsetZ);
		Matrix matrixTranslation(const FloatVector3& pos);
		Matrix matrixTranslation(const Vector& offsets);

		Vector transformPoint3(const Vector& point, const Matrix& transform);
		Vector transformVector(const Vector& vector, const Matrix& transform);
		Vector transformNormal(const Vector& vector, const Matrix& transform);
	}
}