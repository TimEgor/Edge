#pragma once

#include "EdgeCommon/Math/ComputeVector.h"
#include "EdgeCommon/Patterns/NonInstanceable.h"

#include "EdgePhysics/Physics/Collision/PhysicsCollisionContact.h"

#include "VoronoiSimplex.h"

#include <list>

namespace Edge
{
	class PhysicsEntityCollision;

	namespace MinkowskiSumBaseAlgorithmUtils
	{
		VoronoiSimplex::Point Support(const PhysicsEntityCollision& collision1, const PhysicsEntityCollision& collision2, const FloatVector3& direction);

		bool HasSimplexPoint(const VoronoiSimplex& simplex, const FloatVector3& minkowskiDiff);

		bool CheckCodirection(const ComputeVector& direction, const ComputeVector& vector);
	};

	class GJK final
	{
	public:
		struct Result final
		{
			enum class TestResult
			{
				Contact,
				Intersection,
				NoIntersection,

				FailedTesting,

				OverIterationTesting
			};

			VoronoiSimplex m_simplex;
			TestResult m_testResult = TestResult::NoIntersection;

			Result(const VoronoiSimplex& simplex, TestResult result)
				: m_simplex(simplex), m_testResult(result) {}
		};

	private:
		bool checkAndIterateSimplex(VoronoiSimplex& simplex, FloatVector3& direction) const;
		bool checkSimplex1D(VoronoiSimplex& simplex, FloatVector3& direction) const; //Line
		bool checkSimplex2D(VoronoiSimplex& simplex, FloatVector3& direction) const; //Triangle
		bool checkSimplex3D(VoronoiSimplex& simplex, FloatVector3& direction) const; //Tetrahedron

	public:
		GJK() = default;

		Result operator()(const PhysicsEntityCollision& collision1, const PhysicsEntityCollision& collision2, uint32_t maxIterationCount) const { return test(collision1, collision2, maxIterationCount); }

		Result test(const PhysicsEntityCollision& collision1, const PhysicsEntityCollision& collision2, uint32_t maxIterationCount) const;
	};

	class EPA final
	{
	private:
		struct PolytopeFace final
		{
			VoronoiSimplex::Point m_points[3];
			FloatVector3 m_normal;

			PolytopeFace(const VoronoiSimplex::Point& point1, const VoronoiSimplex::Point& point2, const VoronoiSimplex::Point& point3);
		};

		struct PolytopeEdge final
		{
			VoronoiSimplex::Point m_points[2];

			PolytopeEdge(const VoronoiSimplex::Point& point1, const VoronoiSimplex::Point& point2);
		};

		void addUniqueEdge(std::list<PolytopeEdge>& edgeCollection, const VoronoiSimplex::Point& point1, const VoronoiSimplex::Point& point2) const;

		void fillPointContactPointData(const PhysicsEntityCollision& collision1, const PhysicsEntityCollision& collision2, const GJK::Result& gjkResult, PhysicsCollisionContactPoint& contactPoint) const;
		void fillFaceContactPointData(const PolytopeFace& face, PhysicsCollisionContactPoint& contactPoint) const;
		FloatVector4 getBarycentricFaceProjection(const PolytopeFace& face) const; //xyz - barycentricCoords, w - distance to face

		bool calcEPAContact(const PhysicsEntityCollision& collision1, const PhysicsEntityCollision& collision2,
			const GJK::Result& gjkResult, uint32_t maxIterationCount, PhysicsCollisionContactPoint& contactPointData) const;

	public:
		EPA() = default;

		bool operator()(const PhysicsEntityCollision& collision1, const PhysicsEntityCollision& collision2,
			const GJK::Result& gjkResult, uint32_t maxIterationCount, PhysicsCollisionContactPoint& contactPointData) const {
			return getContactPoint(collision1, collision2, gjkResult, maxIterationCount, contactPointData);
		}

		bool getContactPoint(const PhysicsEntityCollision& collision1, const PhysicsEntityCollision& collision2,
			const GJK::Result& gjkResult, uint32_t maxIterationCount, PhysicsCollisionContactPoint& contactPointData) const;
	};
}