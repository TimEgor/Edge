#ifdef TS_MATH_DX
#include "TinySimCommon/Math/ComputeMath/ComputeVector.h"

#pragma region Loading
TS::ComputeMath::Vector TS::ComputeMath::loadVector2(const FloatVector2& vec)
{
	return DirectX::XMLoadFloat2(reinterpret_cast<const DirectX::XMFLOAT2*>(&vec));
}

TS::ComputeMath::Vector TS::ComputeMath::loadVector3(const FloatVector3& vec)
{
	return DirectX::XMLoadFloat3(reinterpret_cast<const DirectX::XMFLOAT3*>(&vec));
}

TS::ComputeMath::Vector TS::ComputeMath::loadVector4(const FloatVector4& vec)
{
	return DirectX::XMLoadFloat4(reinterpret_cast<const DirectX::XMFLOAT4*>(&vec));
}

TS::ComputeMath::Vector TS::ComputeMath::loadVector4(float x, float y, float z, float w)
{
	return DirectX::XMVectorSet(x, y, z, w);
}
#pragma endregion

#pragma region Saving
TS::FloatVector2 TS::ComputeMath::saveVector2(const Vector& vec)
{
	FloatVector2 result;
	saveVector2(vec, result);

	return result;
}

TS::FloatVector3 TS::ComputeMath::saveVector3(const Vector& vec)
{
	FloatVector3 result;
	saveVector3(vec, result);

	return result;
}

TS::FloatVector4 TS::ComputeMath::saveVector4(const Vector& vec)
{
	FloatVector4 result;
	saveVector4(vec, result);

	return result;
}

void TS::ComputeMath::saveVector2(const Vector& vec, FloatVector2& result)
{
	DirectX::XMStoreFloat2(reinterpret_cast<DirectX::XMFLOAT2*>(&result), vec);
}

void TS::ComputeMath::saveVector3(const Vector& vec, FloatVector3& result)
{
	DirectX::XMStoreFloat3(reinterpret_cast<DirectX::XMFLOAT3*>(&result), vec);
}

void TS::ComputeMath::saveVector4(const Vector& vec, FloatVector4& result)
{
	DirectX::XMStoreFloat4(reinterpret_cast<DirectX::XMFLOAT4*>(&result), vec);
}
#pragma endregion

#pragma region Arithmetic
TS::ComputeMath::Vector TS::ComputeMath::vectorAbs(const Vector& vec)
{
	return DirectX::XMVectorAbs(vec);
}

TS::ComputeMath::Vector TS::ComputeMath::vectorAdd(const Vector& vec1, const Vector& vec2)
{
	return DirectX::XMVectorAdd(vec1, vec2);
}

TS::ComputeMath::Vector TS::ComputeMath::vectorClamp(const Vector& vec, const Vector& minVec, const Vector& maxVec)
{
	return DirectX::XMVectorClamp(vec, minVec, maxVec);
}

TS::ComputeMath::Vector TS::ComputeMath::vectorDivide(const Vector& vec1, const Vector& vec2)
{
	return DirectX::XMVectorDivide(vec1, vec2);
}

TS::ComputeMath::Vector TS::ComputeMath::vectorMax(const Vector& vec1, const Vector& vec2)
{
	return DirectX::XMVectorMax(vec1, vec2);
}

TS::ComputeMath::Vector TS::ComputeMath::vectorMin(const Vector& vec1, const Vector& vec2)
{
	return DirectX::XMVectorMin(vec1, vec2);
}

TS::ComputeMath::Vector TS::ComputeMath::vectorMultiply(const Vector& vec1, const Vector& vec2)
{
	return DirectX::XMVectorMultiply(vec1, vec2);
}

TS::ComputeMath::Vector TS::ComputeMath::vectorNegate(const Vector& vec)
{
	return DirectX::XMVectorNegate(vec);
}

TS::ComputeMath::Vector TS::ComputeMath::vectorReciprocal(const Vector& vec)
{
	return DirectX::XMVectorReciprocal(vec);
}

TS::ComputeMath::Vector TS::ComputeMath::vectorReciprocalSqrt(const Vector& vec)
{
	return DirectX::XMVectorReciprocalSqrt(vec);
}

TS::ComputeMath::Vector TS::ComputeMath::vectorSaturate(const Vector& vec)
{
	return DirectX::XMVectorSaturate(vec);
}

TS::ComputeMath::Vector TS::ComputeMath::vectorScale(const Vector& vec, float factor)
{
	return DirectX::XMVectorScale(vec, factor);
}

TS::ComputeMath::Vector TS::ComputeMath::vectorSqrt(const Vector& vec)
{
	return DirectX::XMVectorSqrt(vec);
}

TS::ComputeMath::Vector TS::ComputeMath::vectorSubtract(const Vector& vec1, const Vector& vec2)
{
	return DirectX::XMVectorSubtract(vec1, vec2);
}
#pragma endregion

#pragma region Comparison
TS::ComputeMath::Vector TS::ComputeMath::vectorEqualV(const Vector& vec1, const Vector& vec2)
{
	return DirectX::XMVectorEqual(vec1, vec2);
}

TS::ComputeMath::Vector TS::ComputeMath::vectorGreaterV(const Vector& vec1, const Vector& vec2)
{
	return DirectX::XMVectorGreater(vec1, vec2);
}

TS::ComputeMath::Vector TS::ComputeMath::vectorGreaterOrEqualV(const Vector& vec1, const Vector& vec2)
{
	return DirectX::XMVectorGreaterOrEqual(vec1, vec2);
}

TS::ComputeMath::Vector TS::ComputeMath::vectorLessV(const Vector& vec1, const Vector& vec2)
{
	return DirectX::XMVectorLess(vec1, vec2);
}

TS::ComputeMath::Vector TS::ComputeMath::vectorLessOrEqualV(const Vector& vec1, const Vector& vec2)
{
	return DirectX::XMVectorLessOrEqual(vec1, vec2);
}

TS::ComputeMath::Vector TS::ComputeMath::vectorNearEqualV(const Vector& vec1, const Vector& vec2, const Vector& epsilon)
{
	return DirectX::XMVectorNearEqual(vec1, vec2, epsilon);
}

bool TS::ComputeMath::vector3Equal(const Vector& vec1, const Vector& vec2)
{
	return DirectX::XMVector3Equal(vec1, vec2);
}

bool TS::ComputeMath::vector3Greater(const Vector& vec1, const Vector& vec2)
{
	return DirectX::XMVector3Greater(vec1, vec2);
}

bool TS::ComputeMath::vector3GreaterOrEqual(const Vector& vec1, const Vector& vec2)
{
	return DirectX::XMVector3GreaterOrEqual(vec1, vec2);
}

bool TS::ComputeMath::vector3Less(const Vector& vec1, const Vector& vec2)
{
	return DirectX::XMVector3Less(vec1, vec2);
}

bool TS::ComputeMath::vector3LessOrEqual(const Vector& vec1, const Vector& vec2)
{
	return DirectX::XMVector3LessOrEqual(vec1, vec2);
}

bool TS::ComputeMath::vector3NearEqual(const Vector& vec1, const Vector& vec2, const Vector& epsilon)
{
	return DirectX::XMVector3NearEqual(vec1, vec2, epsilon);
}

bool TS::ComputeMath::vector4Equal(const Vector& vec1, const Vector& vec2)
{
	return DirectX::XMVector4Equal(vec1, vec2);
}

bool TS::ComputeMath::vector4Greater(const Vector& vec1, const Vector& vec2)
{
	return DirectX::XMVector4Greater(vec1, vec2);
}

bool TS::ComputeMath::vector4GreaterOrEqual(const Vector& vec1, const Vector& vec2)
{
	return DirectX::XMVector4GreaterOrEqual(vec1, vec2);
}

bool TS::ComputeMath::vector4Less(const Vector& vec1, const Vector& vec2)
{
	return DirectX::XMVector4Less(vec1, vec2);
}

bool TS::ComputeMath::vector4LessOrEqual(const Vector& vec1, const Vector& vec2)
{
	return DirectX::XMVector4LessOrEqual(vec1, vec2);
}

bool TS::ComputeMath::vector4NearEqual(const Vector& vec1, const Vector& vec2, const Vector& epsilon)
{
	return DirectX::XMVector4NearEqual(vec1, vec2, epsilon);
}

TS::ComputeMath::Vector TS::ComputeMath::vectorIsNanV(const Vector& vec)
{
	return DirectX::XMVectorIsNaN(vec);
}

TS::ComputeMath::Vector TS::ComputeMath::vectorIsInfiniteV(const Vector& vec)
{
	return DirectX::XMVectorIsInfinite(vec);
}

bool TS::ComputeMath::vector3IsNan(const Vector& vec)
{
	return DirectX::XMVector3IsNaN(vec);
}

bool TS::ComputeMath::vector3IsInfinite(const Vector& vec)
{
	return DirectX::XMVector3IsInfinite(vec);
}

bool TS::ComputeMath::vector4IsNan(const Vector& vec)
{
	return DirectX::XMVector4IsNaN(vec);
}

bool TS::ComputeMath::vector4IsInfinite(const Vector& vec)
{
	return DirectX::XMVector4IsInfinite(vec);
}
#pragma endregion

#pragma region Geometric
TS::ComputeMath::Vector TS::ComputeMath::vectorLerp(const Vector& vec1, const Vector& vec2, float t)
{
	return DirectX::XMVectorLerp(vec1, vec2, t);
}

TS::ComputeMath::Vector TS::ComputeMath::vectorLerpV(const Vector& vec1, const Vector& vec2, const Vector& t)
{
	return DirectX::XMVectorLerpV(vec1, vec2, t);
}

TS::ComputeMath::Vector TS::ComputeMath::vector2LengthV(const Vector& vec)
{
	return DirectX::XMVector2Length(vec);
}

TS::ComputeMath::Vector TS::ComputeMath::vector2LengthSqrV(const Vector& vec)
{
	return DirectX::XMVector2LengthSq(vec);
}

TS::ComputeMath::Vector TS::ComputeMath::vector3LengthV(const Vector& vec)
{
	return DirectX::XMVector3Length(vec);
}

TS::ComputeMath::Vector TS::ComputeMath::vector3LengthSqrV(const Vector& vec)
{
	return DirectX::XMVector3LengthSq(vec);
}

TS::ComputeMath::Vector TS::ComputeMath::vector4LengthV(const Vector& vec)
{
	return DirectX::XMVector4Length(vec);
}

TS::ComputeMath::Vector TS::ComputeMath::vector4LengthSqrV(const Vector& vec)
{
	return DirectX::XMVector4LengthSq(vec);
}

float TS::ComputeMath::vector2Length(const Vector& vec)
{
	return vectorGetX(vector2LengthV(vec));
}

float TS::ComputeMath::vector2LengthSqr(const Vector& vec)
{
	return vectorGetX(vector2LengthSqrV(vec));
}

float TS::ComputeMath::vector3Length(const Vector& vec)
{
	return vectorGetX(vector3LengthV(vec));
}

float TS::ComputeMath::vector3LengthSqr(const Vector& vec)
{
	return vectorGetX(vector3LengthSqrV(vec));
}

float TS::ComputeMath::vector4Length(const Vector& vec)
{
	return vectorGetX(vector4LengthV(vec));
}

float TS::ComputeMath::vector4LengthSqr(const Vector& vec)
{
	return vectorGetX(vector4LengthSqrV(vec));
}

TS::ComputeMath::Vector TS::ComputeMath::vector2DotV(const Vector& vec1, const Vector& vec2)
{
	return DirectX::XMVector2Dot(vec1, vec2);
}

TS::ComputeMath::Vector TS::ComputeMath::vector3DotV(const Vector& vec1, const Vector& vec2)
{
	return DirectX::XMVector3Dot(vec1, vec2);
}

TS::ComputeMath::Vector TS::ComputeMath::vector4DotV(const Vector& vec1, const Vector& vec2)
{
	return DirectX::XMVector4Dot(vec1, vec2);
}

float TS::ComputeMath::vector2Dot(const Vector& vec1, const Vector& vec2)
{
	return vectorGetX(vector2DotV(vec1, vec2));
}

float TS::ComputeMath::vector3Dot(const Vector& vec1, const Vector& vec2)
{
	return vectorGetX(vector3DotV(vec1, vec2));
}

float TS::ComputeMath::vector4Dot(const Vector& vec1, const Vector& vec2)
{
	return vectorGetX(vector4DotV(vec1, vec2));
}

TS::ComputeMath::Vector TS::ComputeMath::vector2Normalize(const Vector& vec)
{
	return DirectX::XMVector2Normalize(vec);
}

TS::ComputeMath::Vector TS::ComputeMath::vector3Normalize(const Vector& vec)
{
	return DirectX::XMVector3Normalize(vec);
}

TS::ComputeMath::Vector TS::ComputeMath::vector4Normalize(const Vector& vec)
{
	return DirectX::XMVector4Normalize(vec);
}

TS::ComputeMath::Vector TS::ComputeMath::vector2Cross(const Vector& vec1, const Vector& vec2)
{
	return DirectX::XMVector2Cross(vec1, vec2);
}

TS::ComputeMath::Vector TS::ComputeMath::vector3Cross(const Vector& vec1, const Vector& vec2)
{
	return DirectX::XMVector3Cross(vec1, vec2);
}
#pragma endregion

float TS::ComputeMath::vectorGetX(const Vector& vec)
{
	return DirectX::XMVectorGetX(vec);
}

float TS::ComputeMath::vectorGetY(const Vector& vec)
{
	return DirectX::XMVectorGetY(vec);
}

float TS::ComputeMath::vectorGetZ(const Vector& vec)
{
	return DirectX::XMVectorGetZ(vec);
}

float TS::ComputeMath::vectorGetW(const Vector& vec)
{
	return DirectX::XMVectorGetZ(vec);
}
#endif