#pragma once

#include "ComputeMath.h"
#include "EdgeCommon/Math/Vector.h"

#if defined(EDGE_MATH_DX)
#include "DirectXMath.h"
#endif

namespace Edge
{
	namespace ComputeMath
	{
#if defined(EDGE_MATH_DX)
		using Vector = DirectX::XMVECTOR;
		using Quaternion = Vector;
#else
		static_assert("Compute vector isn't defined");
#endif

		//Loading
		Vector vector2Load(const FloatVector2& vec);
		Vector vector3Load(const FloatVector3& vec);
		Vector vector4Load(const FloatVector4& vec);
		Vector vector4Load(float x = 0.0f, float y = 0.0f, float z = 0.0f, float w = 0.0f);

		//Saving
		FloatVector2 vector2Save(const Vector& vec);
		FloatVector3 vector3Save(const Vector& vec);
		FloatVector4 vector4Save(const Vector& vec);
		void vector2Save(const Vector& vec, FloatVector2& result);
		void vector3Save(const Vector& vec, FloatVector3& result);
		void vector4Save(const Vector& vec, FloatVector4& result);

		//Arithmetic
		Vector vectorAbs(const Vector& vec);
		Vector vectorAdd(const Vector& vec1, const Vector& vec2);
		Vector vectorClamp(const Vector& vec, const Vector& minVec, const Vector& maxVec);
		Vector vectorDivide(const Vector& vec1, const Vector& vec2);
		Vector vectorMax(const Vector& vec1, const Vector& vec2);
		Vector vectorMin(const Vector& vec1, const Vector& vec2);
		Vector vectorMultiply(const Vector& vec1, const Vector& vec2);
		Vector vectorNegate(const Vector& vec);
		Vector vectorReciprocal(const Vector& vec);
		Vector vectorReciprocalSqrt(const Vector& vec);
		Vector vectorSaturate(const Vector& vec);
		Vector vectorScale(const Vector& vec, float factor);
		Vector vectorSqrt(const Vector& vec);
		Vector vectorSubtract(const Vector& vec1, const Vector& vec2);

		//Comparison
		Vector vectorEqualV(const Vector& vec1, const Vector& vec2);
		Vector vectorGreaterV(const Vector& vec1, const Vector& vec2);
		Vector vectorGreaterOrEqualV(const Vector& vec1, const Vector& vec2);
		Vector vectorLessV(const Vector& vec1, const Vector& vec2);
		Vector vectorLessOrEqualV(const Vector& vec1, const Vector& vec2);
		Vector vectorNearEqualV(const Vector& vec1, const Vector& vec2, const Vector& epsilon);

		bool vector3Equal(const Vector& vec1, const Vector& vec2);
		bool vector3Greater(const Vector& vec1, const Vector& vec2);
		bool vector3GreaterOrEqual(const Vector& vec1, const Vector& vec2);
		bool vector3Less(const Vector& vec1, const Vector& vec2);
		bool vector3LessOrEqual(const Vector& vec1, const Vector& vec2);
		bool vector3NearEqual(const Vector& vec1, const Vector& vec2, const Vector& epsilon);

		bool vector3AnyEqual(const Vector& vec1, const Vector& vec2);
		bool vector3AnyGreater(const Vector& vec1, const Vector& vec2);
		bool vector3AnyGreaterOrEqual(const Vector& vec1, const Vector& vec2);
		bool vector3AnyLess(const Vector& vec1, const Vector& vec2);
		bool vector3AnyLessOrEqual(const Vector& vec1, const Vector& vec2);

		bool vector4Equal(const Vector& vec1, const Vector& vec2);
		bool vector4Greater(const Vector& vec1, const Vector& vec2);
		bool vector4GreaterOrEqual(const Vector& vec1, const Vector& vec2);
		bool vector4Less(const Vector& vec1, const Vector& vec2);
		bool vector4LessOrEqual(const Vector& vec1, const Vector& vec2);
		bool vector4NearEqual(const Vector& vec1, const Vector& vec2, const Vector& epsilon);

		bool vector4AnyEqual(const Vector& vec1, const Vector& vec2);
		bool vector4AnyGreater(const Vector& vec1, const Vector& vec2);
		bool vector4AnyGreaterOrEqual(const Vector& vec1, const Vector& vec2);
		bool vector4AnyLess(const Vector& vec1, const Vector& vec2);
		bool vector4AnyLessOrEqual(const Vector& vec1, const Vector& vec2);

		Vector vectorIsNanV(const Vector& vec);
		Vector vectorIsInfiniteV(const Vector& vec);

		bool vector3IsNan(const Vector& vec);
		bool vector3IsInfinite(const Vector& vec);
		bool vector4IsNan(const Vector& vec);
		bool vector4IsInfinite(const Vector& vec);

		//Geometric
		Vector vectorLerp(const Vector& vec1, const Vector& vec2, float t);
		Vector vectorLerpV(const Vector& vec1, const Vector& vec2, const Vector& t);

		Vector vector2LengthV(const Vector& vec);
		Vector vector2LengthSqrV(const Vector& vec);
		Vector vector3LengthV(const Vector& vec);
		Vector vector3LengthSqrV(const Vector& vec);
		Vector vector4LengthV(const Vector& vec);
		Vector vector4LengthSqrV(const Vector& vec);

		float vector2Length(const Vector& vec);
		float vector2LengthSqr(const Vector& vec);
		float vector3Length(const Vector& vec);
		float vector3LengthSqr(const Vector& vec);
		float vector4Length(const Vector& vec);
		float vector4LengthSqr(const Vector& vec);

		Vector vector2DotV(const Vector& vec1, const Vector& vec2);
		float vector2Dot(const Vector& vec1, const Vector& vec2);
		Vector vector3DotV(const Vector& vec1, const Vector& vec2);
		float vector3Dot(const Vector& vec1, const Vector& vec2);
		Vector vector4DotV(const Vector& vec1, const Vector& vec2);
		float vector4Dot(const Vector& vec1, const Vector& vec2);
		
		Vector vector2Normalize(const Vector& vec);
		Vector vector3Normalize(const Vector& vec);
		Vector vector4Normalize(const Vector& vec);

		Vector vector2Orthogonal(const Vector& vec);
		Vector vector3Orthogonal(const Vector& vec);
		Vector vector4Orthogonal(const Vector& vec);

		Vector vector2Cross(const Vector& vec1, const Vector& vec2);
		Vector vector3Cross(const Vector& vec1, const Vector& vec2);

		Vector vector3Rotate(const Vector& vec, const Quaternion& quat);

		//
		Vector vectorSwizzle(const Vector& vec, uint32_t e0, uint32_t e1, uint32_t e2, uint32_t e3);
		float vectorGetX(const Vector& vec);
		float vectorGetY(const Vector& vec);
		float vectorGetZ(const Vector& vec);
		float vectorGetW(const Vector& vec);

		void vectorSetX(Vector& vec, float val);
		void vectorSetY(Vector& vec, float val);
		void vectorSetZ(Vector& vec, float val);
		void vectorSetW(Vector& vec, float val);
	}
}
