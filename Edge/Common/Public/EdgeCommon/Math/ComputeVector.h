#pragma once

#include "ComputeMath/ComputeVector.h"

namespace Edge
{
	class ComputeVector final
	{
	public:
		ComputeMath::Vector m_vector;

		ComputeVector() : ComputeVector(FloatVector4Zero) {}
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

		ComputeVector& abs();

		float getX() const;
		float getY() const;
		float getZ() const;
		float getW() const;

		void setX(float x);
		void setY(float y);
		void setZ(float z);
		void setW(float w);

		float getElement(uint32_t index) const;

		uint32_t getLowestComponentIndex() const;
		uint32_t getHighestComponentIndex() const;

		float getLength2() const;
		float getLength3() const;
		float getLength4() const;
		float getLengthSqr2() const;
		float getLengthSqr3() const;
		float getLengthSqr4() const;

		float getLength() const;
		float getLengthSqr() const;

		bool isNan2() const;
		bool isNan3() const;
		bool isNan4() const;

		bool isAnyNan2() const;
		bool isAnyNan3() const;
		bool isAnyNan4() const;

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

	ComputeVector ComputeVectorFromPoint(const FloatVector2& position);
	ComputeVector ComputeVectorFromPoint(const FloatVector3& position);

	ComputeVector NegateVector(const ComputeVector& vector);
	ComputeVector NormalizeVector(const ComputeVector& vector);
	ComputeVector ReciprocalVector(const ComputeVector& vector);

	ComputeVector AbsVector(const ComputeVector& vector);

	ComputeVector MultiplyVector(const ComputeVector& vector1, const ComputeVector& vector2);

	ComputeVector VectorMin(const ComputeVector& vector1, const ComputeVector& vector2);
	ComputeVector VectorMax(const ComputeVector& vector1, const ComputeVector& vector2);

	uint32_t VectorLowestComponentIndex(const ComputeVector& vector);
	uint32_t VectorHighestComponentIndex(const ComputeVector& vector);

	float Vector2Length(const ComputeVector& vector);
	float Vector3Length(const ComputeVector& vector);
	float Vector4Length(const ComputeVector& vector);
	float Vector2LengthSqr(const ComputeVector& vector);
	float Vector3LengthSqr(const ComputeVector& vector);
	float Vector4LengthSqr(const ComputeVector& vector);

	float VectorLength(const ComputeVector& vector);
	float VectorLengthSqr(const ComputeVector& vector);

	float DotVector2(const ComputeVector& vector1, const ComputeVector& vector2);
	float DotVector3(const ComputeVector& vector1, const ComputeVector& vector2);
	float DotVector4(const ComputeVector& vector1, const ComputeVector& vector2);

	float TripleVector3(const ComputeVector& vector1, const ComputeVector& vector2, const ComputeVector& vector3);
	
	ComputeVector Vector2Orthogonal(const ComputeVector& vector);
	ComputeVector Vector3Orthogonal(const ComputeVector& vector);
	ComputeVector Vector4Orthogonal(const ComputeVector& vector);

	ComputeVector CrossVector2(const ComputeVector& vector1, const ComputeVector& vector2);
	ComputeVector CrossVector3(const ComputeVector& vector1, const ComputeVector& vector2);

	ComputeVector RotateVector2(const ComputeVector& vector, float angle);

	ComputeVector operator+(const ComputeVector& vector1, const ComputeVector& vector2);
	ComputeVector operator-(const ComputeVector& vector1, const ComputeVector& vector2);
	ComputeVector operator*(float val, const ComputeVector& vector);
	ComputeVector operator*(const ComputeVector& vector, float val);
	ComputeVector operator/(const ComputeVector& vector, float val);

	bool operator==(const ComputeVector& vector1, const ComputeVector& vector2);
	bool operator!=(const ComputeVector& vector1, const ComputeVector& vector2);

	bool IsVectorEqual(const ComputeVector& vector1, const ComputeVector& vector2);
	bool IsVectorNearEqual(const ComputeVector& vector1, const ComputeVector& vector2, const ComputeVector& epsilon);

	bool IsVector2Nan(const ComputeVector& vector);
	bool IsVector3Nan(const ComputeVector& vector);
	bool IsVector4Nan(const ComputeVector& vector);

	bool IsVector2AnyNan(const ComputeVector& vector);
	bool IsVector3AnyNan(const ComputeVector& vector);
	bool IsVector4AnyNan(const ComputeVector& vector);
}
