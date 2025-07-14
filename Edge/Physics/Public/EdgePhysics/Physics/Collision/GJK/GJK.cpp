#include "GJK.h"

#include "EdgePhysics/Physics/Collision/PhysicsEntityCollision.h"

#include "VoronoiSimplex.h"

Edge::VoronoiSimplex::Point Edge::MinkowskiSumBaseAlgorithmUtils::Support(
	const PhysicsEntityCollision& collision1,
	const PhysicsEntityCollision& collision2,
	const ComputeVector3& direction
)
{
	VoronoiSimplex::Point result;

	result.m_pointCollision1 = collision1.getFurthestKeyPoint(direction);
	result.m_pointCollision2 = collision2.getFurthestKeyPoint(-direction);

	result.m_minkowskiDiff = result.m_pointCollision1 - result.m_pointCollision2;

	return result;
}

bool Edge::MinkowskiSumBaseAlgorithmUtils::HasSimplexPoint(const VoronoiSimplex& simplex, const ComputeVector3& minkowskiDiff)
{
	const uint32_t pointCount = simplex.getPointCount();
	for (uint32_t pointIndex = 0; pointIndex < pointCount; ++pointIndex)
	{
		const ComputeVector3& pointMinkowskiDiff = simplex.getPoint(pointIndex).m_minkowskiDiff;
		if (minkowskiDiff == pointMinkowskiDiff)
		{
			return true;
		}
	}

	return false;
}

bool Edge::MinkowskiSumBaseAlgorithmUtils::CheckCodirection(const ComputeVector3& direction, const ComputeVector3& vector)
{
	return DotComputeVector3(direction, vector) > Math::Epsilon;
}

bool Edge::MinkowskiSumBaseAlgorithmUtils::CheckPlaneSide(
	const ComputeVector3& point1,
	const ComputeVector3& point2,
	const ComputeVector3& point3,
	const ComputeVector3& checkedPoint
)
{
	const ComputeVector3 edge12 = point2 - point1;
	const ComputeVector3 edge13 = point3 - point1;
	const ComputeVector3 norm = edge12.cross(edge13);

	return norm.dot(checkedPoint - point1) * norm.dot(-point1) > Math::Epsilon;
}

bool Edge::GJK::checkAndIterateSimplex(VoronoiSimplex& simplex, ComputeVector3& direction) const
{
	switch (simplex.getPointCount())
	{
	case 1: return checkSimplex0D(simplex, direction);
	case 2: return checkSimplex1D(simplex, direction);
	case 3: return checkSimplex2D(simplex, direction);
	case 4: return checkSimplex3D(simplex, direction);
	}

	return false;
}

bool Edge::GJK::checkSimplex0D(VoronoiSimplex& simplex, ComputeVector3& direction) const
{
	const VoronoiSimplex::Point a = simplex.getPoint(0);
	direction = -a.m_minkowskiDiff;

	return false;
}

bool Edge::GJK::checkSimplex1D(VoronoiSimplex& simplex, ComputeVector3& direction) const
{
	const VoronoiSimplex::Point a = simplex.getPoint(1);
	const VoronoiSimplex::Point b = simplex.getPoint(0);

	const ComputeVector3 ab = b.m_minkowskiDiff - a.m_minkowskiDiff;
	const ComputeVector3 ao = -a.m_minkowskiDiff;

	direction = CrossComputeVector3(CrossComputeVector3(ab, ao), ab);

	return false;
}

bool Edge::GJK::checkSimplex2D(VoronoiSimplex& simplex, ComputeVector3& direction) const
{
	const VoronoiSimplex::Point a = simplex.getPoint(2);
	const VoronoiSimplex::Point b = simplex.getPoint(1);
	const VoronoiSimplex::Point c = simplex.getPoint(0);

	const ComputeVector3 ab = b.m_minkowskiDiff - a.m_minkowskiDiff;
	const ComputeVector3 ac = c.m_minkowskiDiff - a.m_minkowskiDiff;
	const ComputeVector3 ao = -a.m_minkowskiDiff;

	const ComputeVector3 abcNormal = CrossComputeVector3(ab, ac);

	const ComputeVector3 abNormal = CrossComputeVector3(ab, abcNormal);
	if (MinkowskiSumBaseAlgorithmUtils::CheckCodirection(abNormal, ao))
	{
		simplex.setPoints(b, a);
		direction = CrossComputeVector3(CrossComputeVector3(ab, ao), ab);

		return checkSimplex1D(simplex, direction);
	}

	const ComputeVector3 acNormal = CrossComputeVector3(abcNormal, ac);
	if (MinkowskiSumBaseAlgorithmUtils::CheckCodirection(acNormal, ao))
	{
		simplex.setPoints(c, a);
		direction = CrossComputeVector3(CrossComputeVector3(ac, ao), ac);

		return checkSimplex1D(simplex, direction);
	}

	if (MinkowskiSumBaseAlgorithmUtils::CheckCodirection(abcNormal, ao))
	{
		direction = abcNormal;
	}
	else
	{
		simplex.setPoints(b, c, a);
		direction = -abcNormal;
	}

	return false;
}

bool Edge::GJK::checkSimplex3D(VoronoiSimplex& simplex, ComputeVector3& direction) const
{
	const VoronoiSimplex::Point a = simplex.getPoint(3);
	const VoronoiSimplex::Point b = simplex.getPoint(2);
	const VoronoiSimplex::Point c = simplex.getPoint(1);
	const VoronoiSimplex::Point d = simplex.getPoint(0);

	const ComputeVector3 ab = b.m_minkowskiDiff - a.m_minkowskiDiff;
	const ComputeVector3 ac = c.m_minkowskiDiff - a.m_minkowskiDiff;
	const ComputeVector3 ad = d.m_minkowskiDiff - a.m_minkowskiDiff;
	const ComputeVector3 ao = -a.m_minkowskiDiff;

	const ComputeVector3 abcNormal = CrossComputeVector3(ab, ac);
	const ComputeVector3 acdNormal = CrossComputeVector3(ac, ad);
	const ComputeVector3 adbNormal = CrossComputeVector3(ad, ab);

	if (MinkowskiSumBaseAlgorithmUtils::CheckCodirection(abcNormal, ao))
	{
		simplex.setPoints(c, b, a);
		direction = abcNormal;

		return checkSimplex2D(simplex, direction);
	}

	if (MinkowskiSumBaseAlgorithmUtils::CheckCodirection(acdNormal, ao))
	{
		simplex.setPoints(d, c, a);
		direction = acdNormal;

		return checkSimplex2D(simplex, direction);
	}

	if (MinkowskiSumBaseAlgorithmUtils::CheckCodirection(adbNormal, ao))
	{
		simplex.setPoints(d, b, a);
		direction = adbNormal;

		return checkSimplex2D(simplex, direction);
	}

	return true;
}

Edge::GJK::Result Edge::GJK::test(const PhysicsEntityCollision& collision1, const PhysicsEntityCollision& collision2, uint32_t maxIterationCount) const
{
	VoronoiSimplex simplex;

	ComputeVector3 direction = (collision2.getTransform()->getPosition() - collision1.getTransform()->getPosition()).normalize();

	VoronoiSimplex::Point supportPoint = MinkowskiSumBaseAlgorithmUtils::Support(collision1, collision2, direction);
	simplex.addPoint(supportPoint);

	direction = -supportPoint.m_minkowskiDiff;

	if (direction.getLengthSqr() <= Math::EpsilonSqr)
	{
		return Result(simplex, direction.normalize(), Result::TestResult::Contact);
	}

	direction.normalize();

	Result::TestResult testResult = Result::TestResult::NoIntersection;

	uint32_t testIterationCount = 0;
	while (true)
	{
		++testIterationCount;
		if (testIterationCount > maxIterationCount)
		{
			testResult = Result::TestResult::OverIterationTesting;
			break;
		}

		supportPoint = MinkowskiSumBaseAlgorithmUtils::Support(collision1, collision2, direction);

		if (MinkowskiSumBaseAlgorithmUtils::HasSimplexPoint(simplex, supportPoint.m_minkowskiDiff))
		{
			break;
		}

		if (!MinkowskiSumBaseAlgorithmUtils::CheckCodirection(direction, supportPoint.m_minkowskiDiff))
		{
			break;
		}

		simplex.addPoint(supportPoint);

		if (supportPoint.m_minkowskiDiff.getLengthSqr() <= Math::EpsilonSqr)
		{
			testResult = Result::TestResult::Contact;
			break;
		}

		if (checkAndIterateSimplex(simplex, direction))
		{
			testResult = Result::TestResult::Intersection;
			break;
		}

		if (direction.getLengthSqr() <= Math::EpsilonSqr)
		{
			testResult = Result::TestResult::Contact;
			break;
		}

		direction.normalize();
	}

	return Result(simplex, direction.normalize(), testResult);
}

Edge::EPA::PolytopeFace::PolytopeFace(const VoronoiSimplex::Point& point1, const VoronoiSimplex::Point& point2, const VoronoiSimplex::Point& point3)
{
	m_points[0] = point1;
	m_points[1] = point2;
	m_points[2] = point3;

	m_normal = CrossComputeVector3(
		point2.m_minkowskiDiff - point1.m_minkowskiDiff,
		point3.m_minkowskiDiff - point1.m_minkowskiDiff
	).normalize();
}

Edge::EPA::PolytopeEdge::PolytopeEdge(const VoronoiSimplex::Point& point1, const VoronoiSimplex::Point& point2)
{
	m_points[0] = point1;
	m_points[1] = point2;
}

void Edge::EPA::addUniqueEdge(std::list<PolytopeEdge>& edgeCollection, const VoronoiSimplex::Point& point1, const VoronoiSimplex::Point& point2) const
{
	for (auto iterator = edgeCollection.begin(); iterator != edgeCollection.end(); ++iterator)
	{
		if ((iterator->m_points[0].m_minkowskiDiff == point2.m_minkowskiDiff)
			&& (iterator->m_points[1].m_minkowskiDiff == point1.m_minkowskiDiff))
		{
			edgeCollection.erase(iterator);
			return;
		}
	}

	edgeCollection.emplace_back(point1, point2);
}

void Edge::EPA::fillPointContactPointData(
	const PhysicsEntityCollision& collision1,
	const PhysicsEntityCollision& collision2,
	const GJK::Result& gjkResult,
	PhysicsCollisionContactPoint& contactPoint
) const
{
	contactPoint.m_position1 = gjkResult.m_simplex.getPoint(gjkResult.m_simplex.getPointCount() - 1).m_pointCollision1;
	contactPoint.m_position2 = gjkResult.m_simplex.getPoint(gjkResult.m_simplex.getPointCount() - 1).m_pointCollision2;

	contactPoint.m_normal = (collision2.getTransform()->getPosition() - collision1.getTransform()->getPosition()).normalize();
	contactPoint.m_depth = ComputeValueType(0.0);
}

bool Edge::EPA::fillFaceContactPointData(const PolytopeFace& face, PhysicsCollisionContactPoint& contactPoint) const
{
	ComputeVector4 barycentricCoords;
	const bool isValid = getBarycentricFaceProjection(face, barycentricCoords);
	if (!isValid)
	{
		return false;
	}

	contactPoint.m_position1 = (
		(barycentricCoords.getX() * face.m_points[0].m_pointCollision1) +
		(barycentricCoords.getY() * face.m_points[1].m_pointCollision1) +
		(barycentricCoords.getZ() * face.m_points[2].m_pointCollision1)
	);

	contactPoint.m_position2 = (
		(barycentricCoords.getX() * face.m_points[0].m_pointCollision2) +
		(barycentricCoords.getY() * face.m_points[1].m_pointCollision2) +
		(barycentricCoords.getZ() * face.m_points[2].m_pointCollision2)
	);

	contactPoint.m_normal = face.m_normal;
	contactPoint.m_depth = barycentricCoords.getW();

	return true;
}

bool Edge::EPA::getBarycentricFaceProjection(const PolytopeFace& face, ComputeVector4& outProjection) const
{
	const ComputeValueType distanceFromOrigin = DotComputeVector3(face.m_normal, face.m_points[0].m_minkowskiDiff);
	const ComputeVector3 point = face.m_normal * distanceFromOrigin;

	const ComputeVector3 v0 = face.m_points[1].m_minkowskiDiff - face.m_points[0].m_minkowskiDiff;
	const ComputeVector3 v1 = face.m_points[2].m_minkowskiDiff - face.m_points[0].m_minkowskiDiff;
	const ComputeVector3 v2 = point - face.m_points[0].m_minkowskiDiff;

	const ComputeValueType d00 = DotComputeVector3(v0, v0);
	const ComputeValueType d01 = DotComputeVector3(v0, v1);
	const ComputeValueType d11 = DotComputeVector3(v1, v1);
	const ComputeValueType d20 = DotComputeVector3(v2, v0);
	const ComputeValueType d21 = DotComputeVector3(v2, v1);

	const ComputeValueType denom = d00 * d11 - d01 * d01;
	if (denom <= ComputeValueType(0.0))
	{
		return false;
	}

	const ComputeValueType v = (d11 * d20 - d01 * d21) / denom;
	const ComputeValueType w = (d00 * d21 - d01 * d20) / denom;
	const ComputeValueType u = ComputeValueType(1.0) - v - w;

	outProjection = ComputeVector4(u, v, w, distanceFromOrigin);

	return true;
}

bool Edge::EPA::calcEPAContact(
	const PhysicsEntityCollision& collision1,
	const PhysicsEntityCollision& collision2,
	const GJK::Result& gjkResult,
	uint32_t maxIterationCount,
	PhysicsCollisionContactPoint& contactPointData
) const
{
	const VoronoiSimplex& simplex = gjkResult.m_simplex;

	std::list<PolytopeFace> polytopeFaces;
	std::list<PolytopeEdge> polytopeEdges;

	{
		const VoronoiSimplex::Point& a = simplex.getPoint(0);
		const VoronoiSimplex::Point& b = simplex.getPoint(1);
		const VoronoiSimplex::Point& c = simplex.getPoint(2);
		const VoronoiSimplex::Point& d = simplex.getPoint(3);

		polytopeFaces.emplace_back(a, b, c);
		polytopeFaces.emplace_back(a, c, d);
		polytopeFaces.emplace_back(a, d, b);
		polytopeFaces.emplace_back(b, d, c);
	}

	uint32_t testIterationCount = 0;
	while (true)
	{
		++testIterationCount;
		if (testIterationCount > maxIterationCount)
		{
			break;
		}

		ComputeValueType minDistance = Math::Max;

		std::list<PolytopeFace>::iterator closestFace = polytopeFaces.begin();

		for (auto iterator = polytopeFaces.begin(); iterator != polytopeFaces.end(); ++iterator)
		{
			const ComputeValueType distance = DotComputeVector3(iterator->m_normal, iterator->m_points[0].m_minkowskiDiff);
			if (distance < minDistance)
			{
				minDistance = distance;
				closestFace = iterator;
			}
		}

		const VoronoiSimplex::Point supportPoint = MinkowskiSumBaseAlgorithmUtils::Support(collision1, collision2, closestFace->m_normal);

		if (DotComputeVector3(closestFace->m_normal, supportPoint.m_minkowskiDiff) - minDistance < ComputeValueType(0.0001))
		{
			return fillFaceContactPointData(*closestFace, contactPointData);
		}

		for (auto iterator = polytopeFaces.begin(); iterator != polytopeFaces.end();)
		{
			if (MinkowskiSumBaseAlgorithmUtils::CheckCodirection(iterator->m_normal, supportPoint.m_minkowskiDiff - iterator->m_points[0].m_minkowskiDiff))
			{
				addUniqueEdge(polytopeEdges, iterator->m_points[0], iterator->m_points[1]);
				addUniqueEdge(polytopeEdges, iterator->m_points[1], iterator->m_points[2]);
				addUniqueEdge(polytopeEdges, iterator->m_points[2], iterator->m_points[0]);

				iterator = polytopeFaces.erase(iterator);

				continue;
			}

			++iterator;
		}

		for (auto iterator = polytopeEdges.begin(); iterator != polytopeEdges.end(); ++iterator)
		{
			polytopeFaces.emplace_back(supportPoint, iterator->m_points[0], iterator->m_points[1]);
		}

		polytopeEdges.clear();
	}

	return false;
}

bool Edge::EPA::getContactPoint(
	const PhysicsEntityCollision& collision1,
	const PhysicsEntityCollision& collision2,
	const GJK::Result& gjkResult,
	uint32_t maxIterationCount,
	PhysicsCollisionContactPoint& contactPointData
) const
{
	if (gjkResult.m_simplex.getPointCount() == 0)
	{
		return false;
	}

	if (gjkResult.m_testResult == GJK::Result::TestResult::NoIntersection || gjkResult.m_testResult == GJK::Result::TestResult::OverIterationTesting)
	{
		return false;
	}

	if (gjkResult.m_testResult == GJK::Result::TestResult::Contact || gjkResult.m_testResult == GJK::Result::TestResult::FailedTesting)
	{
		fillPointContactPointData(collision1, collision2, gjkResult, contactPointData);
		return true;
	}

	return calcEPAContact(collision1, collision2, gjkResult, maxIterationCount, contactPointData);
}
