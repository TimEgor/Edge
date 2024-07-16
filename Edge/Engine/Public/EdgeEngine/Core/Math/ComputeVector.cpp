#include "ComputeVector.h"

TS::ComputeVector::ComputeVector(const ComputeMath::Vector& vector)
	: m_vector(vector) {}

TS::ComputeVector::ComputeVector(const FloatVector2& vector)
{
	loadFromFloatVector2(vector);
}

TS::ComputeVector::ComputeVector(const FloatVector3& vector)
{
	loadFromFloatVector3(vector);
}

TS::ComputeVector::ComputeVector(const FloatVector4& vector)
{
	loadFromFloatVector4(vector);
}

TS::ComputeVector& TS::ComputeVector::operator-()
{
	return negate();
}

TS::ComputeVector& TS::ComputeVector::operator+=(const ComputeVector& vector)
{
	m_vector = ComputeMath::vectorAdd(m_vector, vector.m_vector);
	return *this;
}

TS::ComputeVector& TS::ComputeVector::operator-=(const ComputeVector& vector)
{
	m_vector = ComputeMath::vectorSubtract(m_vector, vector.m_vector);
	return *this;
}

TS::ComputeVector& TS::ComputeVector::operator*=(float val)
{
	m_vector = ComputeMath::vectorScale(m_vector, val);
	return *this;
}

TS::ComputeVector& TS::ComputeVector::operator/=(float val)
{
	m_vector = ComputeMath::vectorScale(m_vector, 1.0f / val);
	return *this;
}

TS::ComputeVector& TS::ComputeVector::negate()
{
	m_vector = ComputeMath::vectorNegate(m_vector);
	return *this;
}

TS::ComputeVector& TS::ComputeVector::normalize()
{
	m_vector = ComputeMath::vector4Normalize(m_vector);
	return *this;
}

TS::ComputeVector& TS::ComputeVector::reciprocal()
{
	m_vector = ComputeMath::vectorReciprocal(m_vector);
	return *this;
}

float TS::ComputeVector::getX() const
{
	return ComputeMath::vectorGetX(m_vector);
}

float TS::ComputeVector::getY() const
{
	return ComputeMath::vectorGetY(m_vector);
}

float TS::ComputeVector::getZ() const
{
	return ComputeMath::vectorGetZ(m_vector);
}

float TS::ComputeVector::getW() const
{
	return ComputeMath::vectorGetW(m_vector);
}

float TS::ComputeVector::getElement(uint32_t index) const
{
	switch (index)
	{
	case 0: return getX();
	case 1: return getY();
	case 2: return getZ();
	case 3: return getW();
	default: return 0.0f;
	}
}

float TS::ComputeVector::length2() const
{
	return ComputeMath::vector2Length(m_vector);
}

float TS::ComputeVector::length3() const
{
	return ComputeMath::vector3Length(m_vector);
}

float TS::ComputeVector::length4() const
{
	return ComputeMath::vector4Length(m_vector);
}

float TS::ComputeVector::length2Sqr() const
{
	return ComputeMath::vector2LengthSqr(m_vector);
}

float TS::ComputeVector::length3Sqr() const
{
	return ComputeMath::vector3LengthSqr(m_vector);
}

float TS::ComputeVector::length4Sqr() const
{
	return ComputeMath::vector4LengthSqr(m_vector);
}

float TS::ComputeVector::length() const
{
	return length4();
}

float TS::ComputeVector::lengthSqr() const
{
	return length4Sqr();
}

void TS::ComputeVector::loadFromFloatVector2(const FloatVector2& vector)
{
	m_vector = ComputeMath::loadVector2(vector);
}

void TS::ComputeVector::loadFromFloatVector3(const FloatVector3& vector)
{
	m_vector = ComputeMath::loadVector3(vector);
}

void TS::ComputeVector::loadFromFloatVector4(const FloatVector4& vector)
{
	m_vector = ComputeMath::loadVector4(vector);
}

void TS::ComputeVector::saveToFloatVector2(FloatVector2& vector) const
{
	ComputeMath::saveVector2(m_vector, vector);
}

void TS::ComputeVector::saveToFloatVector3(FloatVector3& vector) const
{
	ComputeMath::saveVector3(m_vector, vector);
}

void TS::ComputeVector::saveToFloatVector4(FloatVector4& vector) const
{
	ComputeMath::saveVector4(m_vector, vector);
}

TS::FloatVector2 TS::ComputeVector::getFloatVector2() const
{
	return ComputeMath::saveVector2(m_vector);
}

TS::FloatVector3 TS::ComputeVector::getFloatVector3() const
{
	return ComputeMath::saveVector3(m_vector);
}

TS::FloatVector4 TS::ComputeVector::getFloatVector4() const
{
	return ComputeMath::saveVector4(m_vector);
}

TS::ComputeVector TS::computeVectorFromPoint(const FloatVector2& position)
{
	return FloatVector4(position.m_x, position.m_y, 0.0f, 1.0f);
}

TS::ComputeVector TS::computeVectorFromPoint(const FloatVector3& position)
{
	return FloatVector4(position.m_x, position.m_y, position.m_z, 1.0f);
}

TS::ComputeVector TS::negateVector(const ComputeVector& vector)
{
	return ComputeMath::vectorNegate(vector.m_vector);
}

TS::ComputeVector TS::normalizeVector(const ComputeVector& vector)
{
	return ComputeMath::vector4Normalize(vector.m_vector);
}

TS::ComputeVector TS::reciprocalVector(const ComputeVector& vector)
{
	return ComputeMath::vectorReciprocal(vector.m_vector);
}

TS::ComputeVector TS::vectorMin(const ComputeVector& vector1, const ComputeVector& vector2)
{
	return ComputeMath::vectorMin(vector1.m_vector, vector2.m_vector);
}

TS::ComputeVector TS::vectorMax(const ComputeVector& vector1, const ComputeVector& vector2)
{
	return ComputeMath::vectorMax(vector1.m_vector, vector2.m_vector);
}

float TS::vectorLength2(const ComputeVector& vector)
{
	return ComputeMath::vector2Length(vector.m_vector);
}

float TS::vectorLength3(const ComputeVector& vector)
{
	return ComputeMath::vector3Length(vector.m_vector);
}

float TS::vectorLength4(const ComputeVector& vector)
{
	return ComputeMath::vector4Length(vector.m_vector);
}

float TS::vectorLength2Sqr(const ComputeVector& vector)
{
	return ComputeMath::vector2LengthSqr(vector.m_vector);
}

float TS::vectorLength3Sqr(const ComputeVector& vector)
{
	return ComputeMath::vector3LengthSqr(vector.m_vector);
}

float TS::vectorLength4Sqr(const ComputeVector& vector)
{
	return ComputeMath::vector4LengthSqr(vector.m_vector);
}

float TS::vectorLength(const ComputeVector& vector)
{
	return vectorLength4(vector);
}

float TS::vectorLengthSqr(const ComputeVector& vector)
{
	return vectorLength4Sqr(vector);
}

float TS::dotVector2(const ComputeVector& vector1, const ComputeVector& vector2)
{
	return ComputeMath::vector2Dot(vector1.m_vector, vector2.m_vector);
}

float TS::dotVector3(const ComputeVector& vector1, const ComputeVector& vector2)
{
	return ComputeMath::vector3Dot(vector1.m_vector, vector2.m_vector);
}

float TS::dotVector4(const ComputeVector& vector1, const ComputeVector& vector2)
{
	return ComputeMath::vector4Dot(vector1.m_vector, vector2.m_vector);
}

TS::ComputeVector TS::crossVector2(const ComputeVector& vector1, const ComputeVector& vector2)
{
	return ComputeMath::vector2Cross(vector1.m_vector, vector2.m_vector);
}

TS::ComputeVector TS::crossVector3(const ComputeVector& vector1, const ComputeVector& vector2)
{
	return ComputeMath::vector3Cross(vector1.m_vector, vector2.m_vector);
}

TS::ComputeVector TS::operator+(const ComputeVector& vector1, const ComputeVector& vector2)
{
	ComputeVector result(vector1);
	return result += vector2;
}

TS::ComputeVector TS::operator-(const ComputeVector& vector1, const ComputeVector& vector2)
{
	ComputeVector result(vector1);
	return result -= vector2;
}

TS::ComputeVector TS::operator*(float val, const ComputeVector& vector)
{
	ComputeVector result(vector);
	return result *= val;
}

TS::ComputeVector TS::operator*(const ComputeVector& vector, float val)
{
	ComputeVector result(vector);
	return result *= val;
}

TS::ComputeVector TS::operator/(const ComputeVector& vector, float val)
{
	ComputeVector result(vector);
	return result /= val;
}
