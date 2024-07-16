#pragma once

#include "ComputeMath/ComputeVector.h"

namespace Edge
{
	class ComputeVector final
	{
	public:
		ComputeMath::Vector m_vector;

		ComputeVector() = default;
		ComputeVector(const ComputeMath::Vector& vector);
		ComputeVector(const FloatVector2& vector);
		ComputeVector(const FloatVector3& vector);
		ComputeVector(const FloatVector4& vector);
		ComputeVector(const ComputeVector& vector) = default;

		ComputeVector& operator=(const ComputeVector& vector) = default;

		ComputeVector& operator-();

		ComputeVector& operator+=(const ComputeVector& vector);
		ComputeVector& operator-=(const ComputeVector& vector);
		ComputeVector& operator*=(float val);
		ComputeVector& operator/=(float val);

		ComputeVector& negate();
		ComputeVector& normalize();
		ComputeVector& reciprocal();

		float getX() const;
		float getY() const;
		float getZ() const;
		float getW() const;

		float getElement(uint32_t index) const;

		float length2() const;
		float length3() const;
		float length4() const;
		float length2Sqr() const;
		float length3Sqr() const;
		float length4Sqr() const;

		float length() const;
		float lengthSqr() const;
		
		void loadFromFloatVector2(const FloatVector2& vector);
		void loadFromFloatVector3(const FloatVector3& vector);
		void loadFromFloatVector4(const FloatVector4& vector);

		void saveToFloatVector2(FloatVector2& vector) const;
		void saveToFloatVector3(FloatVector3& vector) const;
		void saveToFloatVector4(FloatVector4& vector) const;

		FloatVector2 getFloatVector2() const;
		FloatVector3 getFloatVector3() const;
		FloatVector4 getFloatVector4() const;
	};

	ComputeVector computeVectorFromPoint(const FloatVector2& position);
	ComputeVector computeVectorFromPoint(const FloatVector3& position);

	ComputeVector negateVector(const ComputeVector& vector);
	ComputeVector normalizeVector(const ComputeVector& vector);
	ComputeVector reciprocalVector(const ComputeVector& vector);

	ComputeVector vectorMin(const ComputeVector& vector1, const ComputeVector& vector2);
	ComputeVector vectorMax(const ComputeVector& vector1, const ComputeVector& vector2);

	float vectorLength2(const ComputeVector& vector);
	float vectorLength3(const ComputeVector& vector);
	float vectorLength4(const ComputeVector& vector);
	float vectorLength2Sqr(const ComputeVector& vector);
	float vectorLength3Sqr(const ComputeVector& vector);
	float vectorLength4Sqr(const ComputeVector& vector);

	float vectorLength(const ComputeVector& vector);
	float vectorLengthSqr(const ComputeVector& vector);

	float dotVector2(const ComputeVector& vector1, const ComputeVector& vector2);
	float dotVector3(const ComputeVector& vector1, const ComputeVector& vector2);
	float dotVector4(const ComputeVector& vector1, const ComputeVector& vector2);

	ComputeVector crossVector2(const ComputeVector& vector1, const ComputeVector& vector2);
	ComputeVector crossVector3(const ComputeVector& vector1, const ComputeVector& vector2);

	ComputeVector operator+(const ComputeVector& vector1, const ComputeVector& vector2);
	ComputeVector operator-(const ComputeVector& vector1, const ComputeVector& vector2);
	ComputeVector operator*(float val, const ComputeVector& vector);
	ComputeVector operator*(const ComputeVector& vector, float val);
	ComputeVector operator/(const ComputeVector& vector, float val);
}
