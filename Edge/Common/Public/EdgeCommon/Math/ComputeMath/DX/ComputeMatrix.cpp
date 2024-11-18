#include "EdgeCommon/Math/ComputeMath/ComputeMath.h"

#ifdef EDGE_MATH_DX
#include "EdgeCommon/Math/ComputeMath/ComputeMatrix.h"

#pragma region Loading
Edge::ComputeMath::Matrix Edge::ComputeMath::matrix2x2Load(const FloatMatrix2x2& matrix)
{
	return matrix4x4Load(
		matrix.m_m11, matrix.m_m12, 0.0f, 0.0f,
		matrix.m_m21, matrix.m_m22, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 0.0f);
}

Edge::ComputeMath::Matrix Edge::ComputeMath::matrix3x3Load(const FloatMatrix3x3& matrix)
{
	return XMLoadFloat3x3(reinterpret_cast<const DirectX::XMFLOAT3X3*>(&matrix));
}

Edge::ComputeMath::Matrix Edge::ComputeMath::matrix4x4Load(const FloatMatrix4x4& matrix)
{
	return XMLoadFloat4x4(reinterpret_cast<const DirectX::XMFLOAT4X4*>(&matrix));
}

Edge::ComputeMath::Matrix Edge::ComputeMath::matrix4x4Load(
	float m11, float m12, float m13, float m14,
	float m21, float m22, float m23, float m24,
	float m31, float m32, float m33, float m34,
	float m41, float m42, float m43, float m44)
{
	return DirectX::XMMatrixSet(
		m11, m12, m13, m14,
		m21, m22, m23, m24,
		m31, m32, m33, m34,
		m41, m42, m43, m44
	);
}
#pragma endregion

#pragma region Saving
Edge::FloatMatrix2x2 Edge::ComputeMath::matrix2x2Save(const Matrix& matrix)
{
	FloatMatrix2x2 result;
	matrix2x2Save(matrix, result);

	return result;
}

Edge::FloatMatrix3x3 Edge::ComputeMath::matrix3x3Save(const Matrix& matrix)
{
	FloatMatrix3x3 result;
	matrix3x3Save(matrix, result);

	return result;
}

Edge::FloatMatrix4x4 Edge::ComputeMath::matrix4x4Save(const Matrix& matrix)
{
	FloatMatrix4x4 result;
	matrix4x4Save(matrix, result);

	return result;
}

void Edge::ComputeMath::matrix2x2Save(const Matrix& matrix, FloatMatrix2x2& result)
{
	//TODO: need to rework this method

	FloatMatrix4x4 tmp;
	XMStoreFloat4x4(reinterpret_cast<DirectX::XMFLOAT4X4*>(&tmp), matrix);

	result = FloatMatrix2x2(tmp.m_m11, tmp.m_m12, tmp.m_m21, tmp.m_m22);
}

void Edge::ComputeMath::matrix3x3Save(const Matrix& matrix, FloatMatrix3x3& result)
{
	XMStoreFloat3x3(reinterpret_cast<DirectX::XMFLOAT3X3*>(&result), matrix);
}

void Edge::ComputeMath::matrix4x4Save(const Matrix& matrix, FloatMatrix4x4& result)
{
	XMStoreFloat4x4(reinterpret_cast<DirectX::XMFLOAT4X4*>(&result), matrix);
}
#pragma endregion

#pragma region Arithmetic
Edge::ComputeMath::Vector Edge::ComputeMath::matrixDeterminantV(const Matrix& matrix)
{
	return DirectX::XMMatrixDeterminant(matrix);
}

float Edge::ComputeMath::matrixDeterminant(const Matrix& matrix)
{
	return vectorGetX(matrixDeterminantV(matrix));
}

Edge::ComputeMath::Matrix Edge::ComputeMath::matrixInverse(const Matrix& matrix)
{
	return DirectX::XMMatrixInverse(nullptr, matrix);
}

bool Edge::ComputeMath::matrixIsIdentity(const Matrix& matrix)
{
	return DirectX::XMMatrixIsIdentity(matrix);
}

bool Edge::ComputeMath::matrixIsInfinite(const Matrix& matrix)
{
	return DirectX::XMMatrixIsInfinite(matrix);
}

bool Edge::ComputeMath::matrixIsNaN(const Matrix& matrix)
{
	return DirectX::XMMatrixIsNaN(matrix);
}

Edge::ComputeMath::Matrix Edge::ComputeMath::matrixMultiply(const Matrix& matrix1, const Matrix& matrix2)
{
	return DirectX::XMMatrixMultiply(matrix1, matrix2);
}

Edge::ComputeMath::Matrix Edge::ComputeMath::matrixSum(const Matrix& matrix1, const Matrix& matrix2)
{
	Matrix result;
	result.r[0] = vectorAdd(matrix1.r[0], matrix2.r[0]);
	result.r[1] = vectorAdd(matrix1.r[1], matrix2.r[1]);
	result.r[2] = vectorAdd(matrix1.r[2], matrix2.r[2]);
	result.r[3] = vectorAdd(matrix1.r[3], matrix2.r[3]);

	return result;
}

Edge::ComputeMath::Matrix Edge::ComputeMath::matrixTranspose(const Matrix& matrix)
{
	return DirectX::XMMatrixTranspose(matrix);
}
#pragma endregion

#pragma region Transformation
Edge::ComputeMath::Matrix Edge::ComputeMath::matrixLookAtLH(const Vector& eyePos, const Vector& focusPos, const Vector& upDir)
{
	return DirectX::XMMatrixLookAtLH(eyePos, focusPos, upDir);
}

Edge::ComputeMath::Matrix Edge::ComputeMath::matrixLookAtRH(const Vector& eyePos, const Vector& focusPos, const Vector& upDir)
{
	return DirectX::XMMatrixLookAtRH(eyePos, focusPos, upDir);
}

Edge::ComputeMath::Matrix Edge::ComputeMath::matrixLookToLH(const Vector& eyePos, const Vector& eyeDir, const Vector& upDir)
{
	return DirectX::XMMatrixLookToLH(eyePos, eyeDir, upDir);
}

Edge::ComputeMath::Matrix Edge::ComputeMath::matrixLookToRH(const Vector& eyePos, const Vector& eyeDir, const Vector& upDir)
{
	return DirectX::XMMatrixLookToRH(eyePos, eyeDir, upDir);
}

Edge::ComputeMath::Matrix Edge::ComputeMath::matrixOrthographicLH(float viewWidth, float viewHeight, float nearZ, float farZ)
{
	return DirectX::XMMatrixOrthographicLH(viewWidth, viewHeight, nearZ, farZ);
}

Edge::ComputeMath::Matrix Edge::ComputeMath::matrixOrthographicRH(float viewWidth, float viewHeight, float nearZ, float farZ)
{
	return DirectX::XMMatrixOrthographicRH(viewWidth, viewHeight, nearZ, farZ);
}

Edge::ComputeMath::Matrix Edge::ComputeMath::matrixOrthographicOffCenterLH(float viewLeft, float viewRight, float viewBottom, float viewTop, float nearZ, float farZ)
{
	return DirectX::XMMatrixOrthographicOffCenterLH(viewLeft, viewRight, viewBottom, viewTop, nearZ, farZ);
}

Edge::ComputeMath::Matrix Edge::ComputeMath::matrixOrthographicOffCenterRH(float viewLeft, float viewRight, float viewBottom, float viewTop, float nearZ, float farZ)
{
	return DirectX::XMMatrixOrthographicOffCenterRH(viewLeft, viewRight, viewBottom, viewTop, nearZ, farZ);
}

Edge::ComputeMath::Matrix Edge::ComputeMath::matrixPerspectiveFovLH(float fovAngleY, float aspectRatio, float nearZ, float farZ)
{
	return DirectX::XMMatrixPerspectiveFovLH(fovAngleY, aspectRatio, nearZ, farZ);
}

Edge::ComputeMath::Matrix Edge::ComputeMath::matrixPerspectiveFovRH(float fovAngleY, float aspectRatio, float nearZ, float farZ)
{
	return DirectX::XMMatrixPerspectiveFovRH(fovAngleY, aspectRatio, nearZ, farZ);
}

Edge::ComputeMath::Matrix Edge::ComputeMath::matrixPerspectiveLH(float viewWidth, float viewHeight, float nearZ, float farZ)
{
	return DirectX::XMMatrixPerspectiveLH(viewWidth, viewHeight, nearZ, farZ);
}

Edge::ComputeMath::Matrix Edge::ComputeMath::matrixPerspectiveRH(float viewWidth, float viewHeight, float nearZ, float farZ)
{
	return DirectX::XMMatrixPerspectiveRH(viewWidth, viewHeight, nearZ, farZ);
}

Edge::ComputeMath::Matrix Edge::ComputeMath::matrixPerspectiveOffCenterLH(float viewLeft, float viewRight, float viewBottom, float viewTop, float nearZ, float farZ)
{
	return DirectX::XMMatrixPerspectiveOffCenterLH(viewLeft, viewRight, viewBottom, viewTop, nearZ, farZ);
}

Edge::ComputeMath::Matrix Edge::ComputeMath::matrixPerspectiveOffCenterRH(float viewLeft, float viewRight, float viewBottom, float viewTop, float nearZ, float farZ)
{
	return DirectX::XMMatrixPerspectiveOffCenterRH(viewLeft, viewRight, viewBottom, viewTop, nearZ, farZ);
}

Edge::ComputeMath::Matrix Edge::ComputeMath::matrixRotationAxis(const Vector& axis, float angle)
{
	return DirectX::XMMatrixRotationAxis(axis, angle);
}

Edge::ComputeMath::Matrix Edge::ComputeMath::matrixRotationNormal(const Vector& normalAxis, float angle)
{
	return DirectX::XMMatrixRotationNormal(normalAxis, angle);
}

Edge::ComputeMath::Matrix Edge::ComputeMath::matrixRotationQuaternion(const Quaternion& quaternion)
{
	return DirectX::XMMatrixRotationQuaternion(quaternion);
}

Edge::ComputeMath::Matrix Edge::ComputeMath::matrixRotationRollPitchYaw(float pitch, float yaw, float roll)
{
	return DirectX::XMMatrixRotationRollPitchYaw(pitch, yaw, roll);
}

Edge::ComputeMath::Matrix Edge::ComputeMath::matrixRotationRollPitchYaw(const FloatVector3& angles)
{
	return matrixRotationRollPitchYaw(angles.m_x, angles.m_y, angles.m_z);
}

Edge::ComputeMath::Matrix Edge::ComputeMath::matrixRotationRollPitchYaw(const Vector& angles)
{
	return DirectX::XMMatrixRotationRollPitchYawFromVector(angles);
}

Edge::ComputeMath::Matrix Edge::ComputeMath::matrixRotationX(float angle)
{
	return DirectX::XMMatrixRotationX(angle);
}

Edge::ComputeMath::Matrix Edge::ComputeMath::matrixRotationY(float angle)
{
	return DirectX::XMMatrixRotationY(angle);
}

Edge::ComputeMath::Matrix Edge::ComputeMath::matrixRotationZ(float angle)
{
	return DirectX::XMMatrixRotationZ(angle);
}

Edge::ComputeMath::Matrix Edge::ComputeMath::matrixScaling(float scaleX, float scaleY, float scaleZ)
{
	return DirectX::XMMatrixScaling(scaleX, scaleY, scaleZ);
}

Edge::ComputeMath::Matrix Edge::ComputeMath::matrixScaling(const FloatVector3& scale)
{
	return DirectX::XMMatrixScaling(scale.m_x, scale.m_y, scale.m_z);
}

Edge::ComputeMath::Matrix Edge::ComputeMath::matrixScaling(const Vector& scale)
{
	return DirectX::XMMatrixScalingFromVector(scale);
}

Edge::ComputeMath::Matrix Edge::ComputeMath::matrixTranslation(float offsetX, float offsetY, float offsetZ)
{
	return DirectX::XMMatrixTranslation(offsetX, offsetY, offsetZ);
}

Edge::ComputeMath::Matrix Edge::ComputeMath::matrixTranslation(const FloatVector3& pos)
{
	return matrixTranslation(pos.m_x, pos.m_y, pos.m_z);
}

Edge::ComputeMath::Matrix Edge::ComputeMath::matrixTranslation(const Vector& offsets)
{
	return DirectX::XMMatrixTranslationFromVector(offsets);
}

Edge::ComputeMath::Vector Edge::ComputeMath::transformPoint3(const Vector& point, const Matrix& transform)
{
	return DirectX::XMVector3TransformCoord(point, transform);
}

Edge::ComputeMath::Vector Edge::ComputeMath::transformVector(const Vector& vector, const Matrix& transform)
{
	return DirectX::XMVector4Transform(vector, transform);
}


Edge::ComputeMath::Vector Edge::ComputeMath::transformNormal(const Vector& vector, const Matrix& transform)
{
	return DirectX::XMVector3TransformNormal(vector, transform);
}

void Edge::ComputeMath::anglesFromMatrixRotation(const Matrix& rotationMatrix, float& pitch, float& yaw, float& roll)
{
	DirectX::XMFLOAT4X4 XMFLOAT4X4_Values;
	DirectX::XMStoreFloat4x4(&XMFLOAT4X4_Values, DirectX::XMMatrixTranspose(rotationMatrix));
	pitch = (float)asin(-XMFLOAT4X4_Values._23);
	yaw = (float)atan2(XMFLOAT4X4_Values._13, XMFLOAT4X4_Values._33);
	roll = (float)atan2(XMFLOAT4X4_Values._21, XMFLOAT4X4_Values._22);
}

//
void Edge::ComputeMath::matrixSetElement(Matrix& matrix, uint32_t i, uint32_t j, float val)
{
	matrix.r[i].m128_f32[j] = val;
}
#pragma endregion
#endif