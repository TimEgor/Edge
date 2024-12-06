#include "ComputeVector.h"

#include "ComputeMatrix.h"
#include "ComputeMath/ComputeMatrix.h"

Edge::ComputeVector::ComputeVector(const ComputeMath::Vector& vector)
	: m_vector(vector) {}

Edge::ComputeVector::ComputeVector(const FloatVector2& vector)
{
	loadFromFloatVector2(vector);
}

Edge::ComputeVector::ComputeVector(const FloatVector3& vector)
{
	loadFromFloatVector3(vector);
}

Edge::ComputeVector::ComputeVector(const FloatVector4& vector)
{
	loadFromFloatVector4(vector);
}

Edge::ComputeVector& Edge::ComputeVector::operator-()
{
	return negate();
}

Edge::ComputeVector& Edge::ComputeVector::operator+=(const ComputeVector& vector)
{
	m_vector = ComputeMath::vectorAdd(m_vector, vector.m_vector);
	return *this;
}

Edge::ComputeVector& Edge::ComputeVector::operator-=(const ComputeVector& vector)
{
	m_vector = ComputeMath::vectorSubtract(m_vector, vector.m_vector);
	return *this;
}

Edge::ComputeVector& Edge::ComputeVector::operator*=(float val)
{
	m_vector = ComputeMath::vectorScale(m_vector, val);
	return *this;
}

Edge::ComputeVector& Edge::ComputeVector::operator/=(float val)
{
	m_vector = ComputeMath::vectorScale(m_vector, 1.0f / val);
	return *this;
}

Edge::ComputeVector& Edge::ComputeVector::negate()
{
	m_vector = ComputeMath::vectorNegate(m_vector);
	return *this;
}

Edge::ComputeVector& Edge::ComputeVector::normalize()
{
	m_vector = ComputeMath::vector4Normalize(m_vector);
	return *this;
}

Edge::ComputeVector& Edge::ComputeVector::reciprocal()
{
	m_vector = ComputeMath::vectorReciprocal(m_vector);
	return *this;
}

Edge::ComputeVector& Edge::ComputeVector::abs()
{
	m_vector = ComputeMath::vectorAbs(m_vector);
	return *this;
}

float Edge::ComputeVector::getX() const
{
	return ComputeMath::vectorGetX(m_vector);
}

float Edge::ComputeVector::getY() const
{
	return ComputeMath::vectorGetY(m_vector);
}

float Edge::ComputeVector::getZ() const
{
	return ComputeMath::vectorGetZ(m_vector);
}

float Edge::ComputeVector::getW() const
{
	return ComputeMath::vectorGetW(m_vector);
}

void Edge::ComputeVector::setX(float x)
{
	ComputeMath::vectorSetX(m_vector, x);
}

void Edge::ComputeVector::setY(float y)
{
	ComputeMath::vectorSetY(m_vector, y);
}

void Edge::ComputeVector::setZ(float z)
{
	ComputeMath::vectorSetZ(m_vector, z);
}

void Edge::ComputeVector::setW(float w)
{
	ComputeMath::vectorSetW(m_vector, w);
}

float Edge::ComputeVector::getElement(uint32_t index) const
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

uint32_t Edge::ComputeVector::getLowestComponentIndex() const
{
	return getX() < getY() ?
		getX() < getZ() ? 0 : 2 :
		getY() < getZ() ? 1 : 2;
}

uint32_t Edge::ComputeVector::getHighestComponentIndex() const
{
	return getX() > getY() ?
		getX() > getZ() ? 0 : 2 :
		getY() > getZ() ? 1 : 2;
}

float Edge::ComputeVector::getLength2() const
{
	return ComputeMath::vector2Length(m_vector);
}

float Edge::ComputeVector::getLength3() const
{
	return ComputeMath::vector3Length(m_vector);
}

float Edge::ComputeVector::getLength4() const
{
	return ComputeMath::vector4Length(m_vector);
}

float Edge::ComputeVector::getLength2Sqr() const
{
	return ComputeMath::vector2LengthSqr(m_vector);
}

float Edge::ComputeVector::getLength3Sqr() const
{
	return ComputeMath::vector3LengthSqr(m_vector);
}

float Edge::ComputeVector::getLength4Sqr() const
{
	return ComputeMath::vector4LengthSqr(m_vector);
}

float Edge::ComputeVector::getLength() const
{
	return getLength4();
}

float Edge::ComputeVector::getLengthSqr() const
{
	return getLength4Sqr();
}

void Edge::ComputeVector::loadFromFloatVector2(const FloatVector2& vector)
{
	m_vector = ComputeMath::vector2Load(vector);
}

void Edge::ComputeVector::loadFromFloatVector3(const FloatVector3& vector)
{
	m_vector = ComputeMath::vector3Load(vector);
}

void Edge::ComputeVector::loadFromFloatVector4(const FloatVector4& vector)
{
	m_vector = ComputeMath::vector4Load(vector);
}

void Edge::ComputeVector::saveToFloatVector2(FloatVector2& vector) const
{
	ComputeMath::vector2Save(m_vector, vector);
}

void Edge::ComputeVector::saveToFloatVector3(FloatVector3& vector) const
{
	ComputeMath::vector3Save(m_vector, vector);
}

void Edge::ComputeVector::saveToFloatVector4(FloatVector4& vector) const
{
	ComputeMath::vector4Save(m_vector, vector);
}

Edge::FloatVector2 Edge::ComputeVector::getFloatVector2() const
{
	return ComputeMath::vector2Save(m_vector);
}

Edge::FloatVector3 Edge::ComputeVector::getFloatVector3() const
{
	return ComputeMath::vector3Save(m_vector);
}

Edge::FloatVector4 Edge::ComputeVector::getFloatVector4() const
{
	return ComputeMath::vector4Save(m_vector);
}

Edge::ComputeVector Edge::ComputeVectorFromPoint(const FloatVector2& position)
{
	return FloatVector4(position.m_x, position.m_y, 0.0f, 1.0f);
}

Edge::ComputeVector Edge::ComputeVectorFromPoint(const FloatVector3& position)
{
	return FloatVector4(position.m_x, position.m_y, position.m_z, 1.0f);
}

Edge::ComputeVector Edge::NegateVector(const ComputeVector& vector)
{
	return ComputeMath::vectorNegate(vector.m_vector);
}

Edge::ComputeVector Edge::NormalizeVector(const ComputeVector& vector)
{
	return ComputeMath::vector4Normalize(vector.m_vector);
}

Edge::ComputeVector Edge::ReciprocalVector(const ComputeVector& vector)
{
	return ComputeMath::vectorReciprocal(vector.m_vector);
}

Edge::ComputeVector Edge::AbsVector(const ComputeVector& vector)
{
	return ComputeMath::vectorAbs(vector.m_vector);
}

Edge::ComputeVector Edge::MultiplyVector(const ComputeVector& vector1, const ComputeVector& vector2)
{
	return ComputeMath::vectorMultiply(vector1.m_vector, vector2.m_vector);
}

Edge::ComputeVector Edge::VectorMin(const ComputeVector& vector1, const ComputeVector& vector2)
{
	return ComputeMath::vectorMin(vector1.m_vector, vector2.m_vector);
}

Edge::ComputeVector Edge::VectorMax(const ComputeVector& vector1, const ComputeVector& vector2)
{
	return ComputeMath::vectorMax(vector1.m_vector, vector2.m_vector);
}

uint32_t Edge::VectorLowestComponentIndex(const ComputeVector& vector)
{
	return vector.getLowestComponentIndex();
}

uint32_t Edge::VectorHighestComponentIndex(const ComputeVector& vector)
{
	return vector.getHighestComponentIndex();
}

float Edge::VectorLength2(const ComputeVector& vector)
{
	return ComputeMath::vector2Length(vector.m_vector);
}

float Edge::VectorLength3(const ComputeVector& vector)
{
	return ComputeMath::vector3Length(vector.m_vector);
}

float Edge::VectorLength4(const ComputeVector& vector)
{
	return ComputeMath::vector4Length(vector.m_vector);
}

float Edge::VectorLength2Sqr(const ComputeVector& vector)
{
	return ComputeMath::vector2LengthSqr(vector.m_vector);
}

float Edge::VectorLength3Sqr(const ComputeVector& vector)
{
	return ComputeMath::vector3LengthSqr(vector.m_vector);
}

float Edge::VectorLength4Sqr(const ComputeVector& vector)
{
	return ComputeMath::vector4LengthSqr(vector.m_vector);
}

float Edge::VectorLength(const ComputeVector& vector)
{
	return VectorLength4(vector);
}

float Edge::VectorLengthSqr(const ComputeVector& vector)
{
	return VectorLength4Sqr(vector);
}

float Edge::DotVector2(const ComputeVector& vector1, const ComputeVector& vector2)
{
	return ComputeMath::vector2Dot(vector1.m_vector, vector2.m_vector);
}

float Edge::DotVector3(const ComputeVector& vector1, const ComputeVector& vector2)
{
	return ComputeMath::vector3Dot(vector1.m_vector, vector2.m_vector);
}

float Edge::DotVector4(const ComputeVector& vector1, const ComputeVector& vector2)
{
	return ComputeMath::vector4Dot(vector1.m_vector, vector2.m_vector);
}

float Edge::TripleVector3(const ComputeVector& vector1, const ComputeVector& vector2, const ComputeVector& vector3)
{
	return ComputeMath::vector3Dot(vector1.m_vector, ComputeMath::vector3Cross(vector2.m_vector, vector3.m_vector));
}

Edge::ComputeVector Edge::Vector2Orthogonal(const ComputeVector& vector)
{
	return ComputeMath::vector2Orthogonal(vector.m_vector);
}

Edge::ComputeVector Edge::CrossVector2(const ComputeVector& vector1, const ComputeVector& vector2)
{
	return ComputeMath::vector2Cross(vector1.m_vector, vector2.m_vector);
}

Edge::ComputeVector Edge::CrossVector3(const ComputeVector& vector1, const ComputeVector& vector2)
{
	return ComputeMath::vector3Cross(vector1.m_vector, vector2.m_vector);
}

Edge::ComputeVector Edge::RotateVector2(const ComputeVector& vector, float angle)
{
	return ComputeMatrix(ComputeMath::matrixRotationZ(angle)) * vector;
}

Edge::ComputeVector Edge::operator+(const ComputeVector& vector1, const ComputeVector& vector2)
{
	ComputeVector result(vector1);
	return result += vector2;
}

Edge::ComputeVector Edge::operator-(const ComputeVector& vector1, const ComputeVector& vector2)
{
	ComputeVector result(vector1);
	return result -= vector2;
}

Edge::ComputeVector Edge::operator*(float val, const ComputeVector& vector)
{
	ComputeVector result(vector);
	return result *= val;
}

Edge::ComputeVector Edge::operator*(const ComputeVector& vector, float val)
{
	ComputeVector result(vector);
	return result *= val;
}

Edge::ComputeVector Edge::operator/(const ComputeVector& vector, float val)
{
	ComputeVector result(vector);
	return result /= val;
}

bool Edge::operator==(const ComputeVector& vector1, const ComputeVector& vector2)
{
	return ComputeMath::vector3Equal(vector1.m_vector, vector2.m_vector);
}

bool Edge::operator!=(const ComputeVector& vector1, const ComputeVector& vector2)
{
	return !(vector1 == vector2);
}

bool Edge::IsVectorEqual(const ComputeVector& vector1, const ComputeVector& vector2)
{
	return vector1 == vector2;
}
