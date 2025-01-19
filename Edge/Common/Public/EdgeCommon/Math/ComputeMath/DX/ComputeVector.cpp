#include "EdgeCommon/Math/ComputeMath/ComputeMath.h"

#ifdef EDGE_MATH_DX
#include "EdgeCommon/Math/ComputeMath/ComputeVector.h"

#pragma region Loading
Edge::ComputeMath::Vector Edge::ComputeMath::vector2Load(const FloatVector2& vec)
{
	return DirectX::XMLoadFloat2(reinterpret_cast<const DirectX::XMFLOAT2*>(&vec));
}

Edge::ComputeMath::Vector Edge::ComputeMath::vector3Load(const FloatVector3& vec)
{
	return DirectX::XMLoadFloat3(reinterpret_cast<const DirectX::XMFLOAT3*>(&vec));
}

Edge::ComputeMath::Vector Edge::ComputeMath::vector4Load(const FloatVector4& vec)
{
	return DirectX::XMLoadFloat4(reinterpret_cast<const DirectX::XMFLOAT4*>(&vec));
}

Edge::ComputeMath::Vector Edge::ComputeMath::vector4Load(float x, float y, float z, float w)
{
	return DirectX::XMVectorSet(x, y, z, w);
}
#pragma endregion

#pragma region Saving
Edge::FloatVector2 Edge::ComputeMath::vector2Save(const Vector& vec)
{
	FloatVector2 result;
	vector2Save(vec, result);

	return result;
}

Edge::FloatVector3 Edge::ComputeMath::vector3Save(const Vector& vec)
{
	FloatVector3 result;
	vector3Save(vec, result);

	return result;
}

Edge::FloatVector4 Edge::ComputeMath::vector4Save(const Vector& vec)
{
	FloatVector4 result;
	vector4Save(vec, result);

	return result;
}

void Edge::ComputeMath::vector2Save(const Vector& vec, FloatVector2& result)
{
	DirectX::XMStoreFloat2(reinterpret_cast<DirectX::XMFLOAT2*>(&result), vec);
}

void Edge::ComputeMath::vector3Save(const Vector& vec, FloatVector3& result)
{
	DirectX::XMStoreFloat3(reinterpret_cast<DirectX::XMFLOAT3*>(&result), vec);
}

void Edge::ComputeMath::vector4Save(const Vector& vec, FloatVector4& result)
{
	DirectX::XMStoreFloat4(reinterpret_cast<DirectX::XMFLOAT4*>(&result), vec);
}
#pragma endregion

#pragma region Arithmetic
Edge::ComputeMath::Vector Edge::ComputeMath::vectorAbs(const Vector& vec)
{
	return DirectX::XMVectorAbs(vec);
}

Edge::ComputeMath::Vector Edge::ComputeMath::vectorAdd(const Vector& vec1, const Vector& vec2)
{
	return DirectX::XMVectorAdd(vec1, vec2);
}

Edge::ComputeMath::Vector Edge::ComputeMath::vectorClamp(const Vector& vec, const Vector& minVec, const Vector& maxVec)
{
	return DirectX::XMVectorClamp(vec, minVec, maxVec);
}

Edge::ComputeMath::Vector Edge::ComputeMath::vectorDivide(const Vector& vec1, const Vector& vec2)
{
	return DirectX::XMVectorDivide(vec1, vec2);
}

Edge::ComputeMath::Vector Edge::ComputeMath::vectorMax(const Vector& vec1, const Vector& vec2)
{
	return DirectX::XMVectorMax(vec1, vec2);
}

Edge::ComputeMath::Vector Edge::ComputeMath::vectorMin(const Vector& vec1, const Vector& vec2)
{
	return DirectX::XMVectorMin(vec1, vec2);
}

Edge::ComputeMath::Vector Edge::ComputeMath::vectorMultiply(const Vector& vec1, const Vector& vec2)
{
	return DirectX::XMVectorMultiply(vec1, vec2);
}

Edge::ComputeMath::Vector Edge::ComputeMath::vectorNegate(const Vector& vec)
{
	return DirectX::XMVectorNegate(vec);
}

Edge::ComputeMath::Vector Edge::ComputeMath::vectorReciprocal(const Vector& vec)
{
	return DirectX::XMVectorReciprocal(vec);
}

Edge::ComputeMath::Vector Edge::ComputeMath::vectorReciprocalSqrt(const Vector& vec)
{
	return DirectX::XMVectorReciprocalSqrt(vec);
}

Edge::ComputeMath::Vector Edge::ComputeMath::vectorSaturate(const Vector& vec)
{
	return DirectX::XMVectorSaturate(vec);
}

Edge::ComputeMath::Vector Edge::ComputeMath::vectorScale(const Vector& vec, float factor)
{
	return DirectX::XMVectorScale(vec, factor);
}

Edge::ComputeMath::Vector Edge::ComputeMath::vectorSqrt(const Vector& vec)
{
	return DirectX::XMVectorSqrt(vec);
}

Edge::ComputeMath::Vector Edge::ComputeMath::vectorSubtract(const Vector& vec1, const Vector& vec2)
{
	return DirectX::XMVectorSubtract(vec1, vec2);
}
#pragma endregion

#pragma region Comparison
Edge::ComputeMath::Vector Edge::ComputeMath::vectorEqualV(const Vector& vec1, const Vector& vec2)
{
	return DirectX::XMVectorEqual(vec1, vec2);
}

Edge::ComputeMath::Vector Edge::ComputeMath::vectorGreaterV(const Vector& vec1, const Vector& vec2)
{
	return DirectX::XMVectorGreater(vec1, vec2);
}

Edge::ComputeMath::Vector Edge::ComputeMath::vectorGreaterOrEqualV(const Vector& vec1, const Vector& vec2)
{
	return DirectX::XMVectorGreaterOrEqual(vec1, vec2);
}

Edge::ComputeMath::Vector Edge::ComputeMath::vectorLessV(const Vector& vec1, const Vector& vec2)
{
	return DirectX::XMVectorLess(vec1, vec2);
}

Edge::ComputeMath::Vector Edge::ComputeMath::vectorLessOrEqualV(const Vector& vec1, const Vector& vec2)
{
	return DirectX::XMVectorLessOrEqual(vec1, vec2);
}

Edge::ComputeMath::Vector Edge::ComputeMath::vectorNearEqualV(const Vector& vec1, const Vector& vec2, const Vector& epsilon)
{
	return DirectX::XMVectorNearEqual(vec1, vec2, epsilon);
}

bool Edge::ComputeMath::vector3Equal(const Vector& vec1, const Vector& vec2)
{
	return DirectX::XMVector3Equal(vec1, vec2);
}

bool Edge::ComputeMath::vector3Greater(const Vector& vec1, const Vector& vec2)
{
	return DirectX::XMVector3Greater(vec1, vec2);
}

bool Edge::ComputeMath::vector3GreaterOrEqual(const Vector& vec1, const Vector& vec2)
{
	return DirectX::XMVector3GreaterOrEqual(vec1, vec2);
}

bool Edge::ComputeMath::vector3Less(const Vector& vec1, const Vector& vec2)
{
	return DirectX::XMVector3Less(vec1, vec2);
}

bool Edge::ComputeMath::vector3LessOrEqual(const Vector& vec1, const Vector& vec2)
{
	return DirectX::XMVector3LessOrEqual(vec1, vec2);
}

bool Edge::ComputeMath::vector3NearEqual(const Vector& vec1, const Vector& vec2, const Vector& epsilon)
{
	return DirectX::XMVector3NearEqual(vec1, vec2, epsilon);
}

bool Edge::ComputeMath::vector3AnyEqual(const Vector& vec1, const Vector& vec2)
{
	const uint32_t result = DirectX::XMVector3EqualR(vec1, vec2);
	return DirectX::XMComparisonAnyTrue(result);
}

bool Edge::ComputeMath::vector3AnyGreater(const Vector& vec1, const Vector& vec2)
{
	const uint32_t result = DirectX::XMVector3GreaterR(vec1, vec2);
	return DirectX::XMComparisonAnyTrue(result);
}

bool Edge::ComputeMath::vector3AnyGreaterOrEqual(const Vector& vec1, const Vector& vec2)
{
	const uint32_t result = DirectX::XMVector3GreaterOrEqualR(vec1, vec2);
	return DirectX::XMComparisonAnyTrue(result);
}

bool Edge::ComputeMath::vector3AnyLess(const Vector& vec1, const Vector& vec2)
{
	const uint32_t result = DirectX::XMVector3GreaterOrEqualR(vec1, vec2);
	return DirectX::XMComparisonAnyFalse(result);
}

bool Edge::ComputeMath::vector3AnyLessOrEqual(const Vector& vec1, const Vector& vec2)
{
	const uint32_t result = DirectX::XMVector3GreaterR(vec1, vec2);
	return DirectX::XMComparisonAnyFalse(result);
}

bool Edge::ComputeMath::vector4Equal(const Vector& vec1, const Vector& vec2)
{
	return DirectX::XMVector4Equal(vec1, vec2);
}

bool Edge::ComputeMath::vector4Greater(const Vector& vec1, const Vector& vec2)
{
	return DirectX::XMVector4Greater(vec1, vec2);
}

bool Edge::ComputeMath::vector4GreaterOrEqual(const Vector& vec1, const Vector& vec2)
{
	return DirectX::XMVector4GreaterOrEqual(vec1, vec2);
}

bool Edge::ComputeMath::vector4Less(const Vector& vec1, const Vector& vec2)
{
	return DirectX::XMVector4Less(vec1, vec2);
}

bool Edge::ComputeMath::vector4LessOrEqual(const Vector& vec1, const Vector& vec2)
{
	return DirectX::XMVector4LessOrEqual(vec1, vec2);
}

bool Edge::ComputeMath::vector4NearEqual(const Vector& vec1, const Vector& vec2, const Vector& epsilon)
{
	return DirectX::XMVector4NearEqual(vec1, vec2, epsilon);
}

bool Edge::ComputeMath::vector4AnyEqual(const Vector& vec1, const Vector& vec2)
{
	const uint32_t result = DirectX::XMVector4EqualR(vec1, vec2);
	return DirectX::XMComparisonAnyTrue(result);
}

bool Edge::ComputeMath::vector4AnyGreater(const Vector& vec1, const Vector& vec2)
{
	const uint32_t result = DirectX::XMVector4GreaterR(vec1, vec2);
	return DirectX::XMComparisonAnyTrue(result);
}

bool Edge::ComputeMath::vector4AnyGreaterOrEqual(const Vector& vec1, const Vector& vec2)
{
	const uint32_t result = DirectX::XMVector4GreaterOrEqualR(vec1, vec2);
	return DirectX::XMComparisonAnyTrue(result);
}

bool Edge::ComputeMath::vector4AnyLess(const Vector& vec1, const Vector& vec2)
{
	const uint32_t result = DirectX::XMVector4GreaterOrEqualR(vec1, vec2);
	return DirectX::XMComparisonAnyFalse(result);
}

bool Edge::ComputeMath::vector4AnyLessOrEqual(const Vector& vec1, const Vector& vec2)
{
	const uint32_t result = DirectX::XMVector3GreaterR(vec1, vec2);
	return DirectX::XMComparisonAnyFalse(result);
}

Edge::ComputeMath::Vector Edge::ComputeMath::vectorIsNanV(const Vector& vec)
{
	return DirectX::XMVectorIsNaN(vec);
}

Edge::ComputeMath::Vector Edge::ComputeMath::vectorIsInfiniteV(const Vector& vec)
{
	return DirectX::XMVectorIsInfinite(vec);
}

bool Edge::ComputeMath::vector2IsNan(const Vector& vec)
{
	return DirectX::XMVector2IsNaN(vec);
}

bool Edge::ComputeMath::vector2IsInfinite(const Vector& vec)
{
	return DirectX::XMVector2IsInfinite(vec);
}

bool Edge::ComputeMath::vector3IsNan(const Vector& vec)
{
	return DirectX::XMVector3IsNaN(vec);
}

bool Edge::ComputeMath::vector3IsInfinite(const Vector& vec)
{
	return DirectX::XMVector3IsInfinite(vec);
}

bool Edge::ComputeMath::vector4IsNan(const Vector& vec)
{
	return DirectX::XMVector4IsNaN(vec);
}

bool Edge::ComputeMath::vector4IsInfinite(const Vector& vec)
{
	return DirectX::XMVector4IsInfinite(vec);
}
#pragma endregion

#pragma region Geometric
Edge::ComputeMath::Vector Edge::ComputeMath::vectorLerp(const Vector& vec1, const Vector& vec2, float t)
{
	return DirectX::XMVectorLerp(vec1, vec2, t);
}

Edge::ComputeMath::Vector Edge::ComputeMath::vectorLerpV(const Vector& vec1, const Vector& vec2, const Vector& t)
{
	return DirectX::XMVectorLerpV(vec1, vec2, t);
}

Edge::ComputeMath::Vector Edge::ComputeMath::vector2LengthV(const Vector& vec)
{
	return DirectX::XMVector2Length(vec);
}

Edge::ComputeMath::Vector Edge::ComputeMath::vector2LengthSqrV(const Vector& vec)
{
	return DirectX::XMVector2LengthSq(vec);
}

Edge::ComputeMath::Vector Edge::ComputeMath::vector3LengthV(const Vector& vec)
{
	return DirectX::XMVector3Length(vec);
}

Edge::ComputeMath::Vector Edge::ComputeMath::vector3LengthSqrV(const Vector& vec)
{
	return DirectX::XMVector3LengthSq(vec);
}

Edge::ComputeMath::Vector Edge::ComputeMath::vector4LengthV(const Vector& vec)
{
	return DirectX::XMVector4Length(vec);
}

Edge::ComputeMath::Vector Edge::ComputeMath::vector4LengthSqrV(const Vector& vec)
{
	return DirectX::XMVector4LengthSq(vec);
}

float Edge::ComputeMath::vector2Length(const Vector& vec)
{
	return vectorGetX(vector2LengthV(vec));
}

float Edge::ComputeMath::vector2LengthSqr(const Vector& vec)
{
	return vectorGetX(vector2LengthSqrV(vec));
}

float Edge::ComputeMath::vector3Length(const Vector& vec)
{
	return vectorGetX(vector3LengthV(vec));
}

float Edge::ComputeMath::vector3LengthSqr(const Vector& vec)
{
	return vectorGetX(vector3LengthSqrV(vec));
}

float Edge::ComputeMath::vector4Length(const Vector& vec)
{
	return vectorGetX(vector4LengthV(vec));
}

float Edge::ComputeMath::vector4LengthSqr(const Vector& vec)
{
	return vectorGetX(vector4LengthSqrV(vec));
}

Edge::ComputeMath::Vector Edge::ComputeMath::vector2DotV(const Vector& vec1, const Vector& vec2)
{
	return DirectX::XMVector2Dot(vec1, vec2);
}

Edge::ComputeMath::Vector Edge::ComputeMath::vector3DotV(const Vector& vec1, const Vector& vec2)
{
	return DirectX::XMVector3Dot(vec1, vec2);
}

Edge::ComputeMath::Vector Edge::ComputeMath::vector4DotV(const Vector& vec1, const Vector& vec2)
{
	return DirectX::XMVector4Dot(vec1, vec2);
}

float Edge::ComputeMath::vector2Dot(const Vector& vec1, const Vector& vec2)
{
	return vectorGetX(vector2DotV(vec1, vec2));
}

float Edge::ComputeMath::vector3Dot(const Vector& vec1, const Vector& vec2)
{
	return vectorGetX(vector3DotV(vec1, vec2));
}

float Edge::ComputeMath::vector4Dot(const Vector& vec1, const Vector& vec2)
{
	return vectorGetX(vector4DotV(vec1, vec2));
}

Edge::ComputeMath::Vector Edge::ComputeMath::vector2Normalize(const Vector& vec)
{
	return DirectX::XMVector2Normalize(vec);
}

Edge::ComputeMath::Vector Edge::ComputeMath::vector3Normalize(const Vector& vec)
{
	return DirectX::XMVector3Normalize(vec);
}

Edge::ComputeMath::Vector Edge::ComputeMath::vector4Normalize(const Vector& vec)
{
	return DirectX::XMVector4Normalize(vec);
}

Edge::ComputeMath::Vector Edge::ComputeMath::vector2Orthogonal(const Vector& vec)
{
	return DirectX::XMVector2Orthogonal(vec);
}

Edge::ComputeMath::Vector Edge::ComputeMath::vector3Orthogonal(const Vector& vec)
{
	return DirectX::XMVector3Orthogonal(vec);
}

Edge::ComputeMath::Vector Edge::ComputeMath::vector4Orthogonal(const Vector& vec)
{
	return DirectX::XMVector4Orthogonal(vec);
}

Edge::ComputeMath::Vector Edge::ComputeMath::vector2Cross(const Vector& vec1, const Vector& vec2)
{
	return DirectX::XMVector2Cross(vec1, vec2);
}

Edge::ComputeMath::Vector Edge::ComputeMath::vector3Cross(const Vector& vec1, const Vector& vec2)
{
	return DirectX::XMVector3Cross(vec1, vec2);
}

Edge::ComputeMath::Vector Edge::ComputeMath::vector3Rotate(const Vector& vec, const Quaternion& quat)
{
	return DirectX::XMVector3Rotate(vec, quat);
}

#pragma endregion

Edge::ComputeMath::Vector Edge::ComputeMath::vectorSwizzle(const Vector& vec, uint32_t e0, uint32_t e1, uint32_t e2, uint32_t e3)
{
	return DirectX::XMVectorSwizzle(vec, e0, e1, e2, e3);
}

float Edge::ComputeMath::vectorGetX(const Vector& vec)
{
	return DirectX::XMVectorGetX(vec);
}

float Edge::ComputeMath::vectorGetY(const Vector& vec)
{
	return DirectX::XMVectorGetY(vec);
}

float Edge::ComputeMath::vectorGetZ(const Vector& vec)
{
	return DirectX::XMVectorGetZ(vec);
}

float Edge::ComputeMath::vectorGetW(const Vector& vec)
{
	return DirectX::XMVectorGetZ(vec);
}

void Edge::ComputeMath::vectorSetX(Vector& vec, float val)
{
	vec = DirectX::XMVectorSetX(vec, val);
}

void Edge::ComputeMath::vectorSetY(Vector& vec, float val)
{
	vec = DirectX::XMVectorSetY(vec, val);
}

void Edge::ComputeMath::vectorSetZ(Vector& vec, float val)
{
	vec = DirectX::XMVectorSetZ(vec, val);
}

void Edge::ComputeMath::vectorSetW(Vector& vec, float val)
{
	vec = DirectX::XMVectorSetW(vec, val);
}
#endif