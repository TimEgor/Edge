#pragma once

#include "EdgeCommon/Math/ComputeVector4.h"

#include "EdgePhysics/Physics/Collision/PhysicsCollisionContact.h"

#include "VoronoiSimplex.h"

#include <list>

namespace Edge
{
	class PhysicsEntityCollision;

	namespace MinkowskiSumBaseAlgorithmUtils
	{
		VoronoiSimplex::Point Support(const PhysicsEntityCollision& collision1, const PhysicsEntityCollision& collision2, const ComputeVector3& direction);

		bool HasSimplexPoint(const VoronoiSimplex& simplex, const ComputeVector3& minkowskiDiff);

		bool CheckCodirection(const ComputeVector3& direction, const ComputeVector3& vector);
		bool CheckPlaneSide(
			const ComputeVector3& point1,
			const ComputeVector3& point2,
			const ComputeVector3& point3,
			const ComputeVector3& controlPoint,
			const ComputeVector3& checkedPoint
		);
	};

	class GJK final
	{
	public:
		enum class Result
		{
			Intersection,
			NoIntersection,

			Undetermined,

			OverIteration
		};

		struct TestResult final
		{
			VoronoiSimplex m_simplex;
			Result m_testResult = Result::NoIntersection;
			ComputeVector3 m_delta = ComputeVector3Zero;
			ComputeVector3 m_point1 = ComputeVector3Zero;
			ComputeVector3 m_point2 = ComputeVector3Zero;

			TestResult(
				const VoronoiSimplex& simplex,
				Result result,
				const ComputeVector3& delta,
				const ComputeVector3& point1,
				const ComputeVector3& point2
			)
				: m_simplex(simplex),
				  m_testResult(result),
				  m_delta(delta),
				  m_point1(point1),
				  m_point2(point2) {}
		};

	private:
		void getSimplexClosestPoint(VoronoiSimplex& simplex, ComputeVector3& delta) const;
		void getSimplex0DClosestPoint(VoronoiSimplex& simplex, ComputeVector3& delta) const; //Point
		void getSimplex1DClosestPoint(VoronoiSimplex& simplex, ComputeVector3& delta) const; //Line
		void getSimplex2DClosestPoint(VoronoiSimplex& simplex, ComputeVector3& delta) const; //Triangle
		void getSimplex3DClosestPoint(VoronoiSimplex& simplex, ComputeVector3& delta) const; //Tetrahedron

	public:
		GJK() = default;

		TestResult operator()(
			const PhysicsEntityCollision& collision1,
			const PhysicsEntityCollision& collision2,
			uint32_t maxIterationCount,
			ComputeValue contactTolerance
		) const
		{
			return test(collision1, collision2, maxIterationCount, contactTolerance);
		}

		TestResult test(
			const PhysicsEntityCollision& collision1,
			const PhysicsEntityCollision& collision2,
			uint32_t maxIterationCount,
			ComputeValue contactTolerance
		) const;
	};

	class EPA final
	{
	private:
		struct PolytopeFace final
		{
			VoronoiSimplex::Point m_points[3];
			ComputeVector3 m_normal;
			ComputeValue m_distance;

			PolytopeFace(const VoronoiSimplex::Point& point1, const VoronoiSimplex::Point& point2, const VoronoiSimplex::Point& point3);

			bool operator<(const PolytopeFace& face) const;
		};

		struct PolytopeEdge final
		{
			VoronoiSimplex::Point m_points[2];

			PolytopeEdge(const VoronoiSimplex::Point& point1, const VoronoiSimplex::Point& point2);
		};

		void buildFullSimplex(
			const PhysicsEntityCollision& collision1,
			const PhysicsEntityCollision& collision2,
			VoronoiSimplex& simplex
		) const;

		void getBarycentricFaceProjection(const PolytopeFace& face, ComputeVector4& outProjection) const;

		bool calcEPAContact(
			const PhysicsEntityCollision& collision1,
			const PhysicsEntityCollision& collision2,
			const GJK::TestResult& gjkResult,
			uint32_t maxIterationCount,
			PhysicsCollisionContactPoint& contactPointData
		) const;

	public:
		EPA() = default;

		bool operator()(
			const PhysicsEntityCollision& collision1,
			const PhysicsEntityCollision& collision2,
			const GJK::TestResult& gjkResult,
			uint32_t maxIterationCount,
			PhysicsCollisionContactPoint& contactPointData
		) const
		{
			return getContactPoint(collision1, collision2, gjkResult, maxIterationCount, contactPointData);
		}

		bool getContactPoint(
			const PhysicsEntityCollision& collision1,
			const PhysicsEntityCollision& collision2,
			const GJK::TestResult& gjkResult,
			uint32_t maxIterationCount,
			PhysicsCollisionContactPoint& contactPointData
		) const;
	};
}
