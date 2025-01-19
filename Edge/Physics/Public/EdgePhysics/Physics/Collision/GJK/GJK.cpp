#include "GJK.h"

#include "EdgePhysics/Physics/Collision/PhysicsEntityCollision.h"

#include "VoronoiSimplex.h"

Edge::VoronoiSimplex::Point Edge::MinkowskiSumBaseAlgorithmUtils::Support(
	const PhysicsEntityCollision& collision1, const PhysicsEntityCollision& collision2, const FloatVector3& direction)
{
	VoronoiSimplex::Point result;

	const ComputeVector point1 = collision1.getFurthestKeyPoint(direction);
	const ComputeVector point2 = collision2.getFurthestKeyPoint(NegateVector(direction).getFloatVector3());

	const ComputeVector delta = point1 - point2;

	delta.saveToFloatVector3(result.m_minkowskiDiff);
	point1.saveToFloatVector3(result.m_pointCollision1);
	point2.saveToFloatVector3(result.m_pointCollision2);

	return result;
}

bool Edge::MinkowskiSumBaseAlgorithmUtils::HasSimplexPoint(const VoronoiSimplex& simplex, const FloatVector3& minkowskiDiff)
{
	const uint32_t pointCount = simplex.getPointCount();
	for (uint32_t pointIndex = 0; pointIndex < pointCount; ++pointIndex)
	{
		const FloatVector3& pointMinkowskiDiff = simplex.getPoint(pointIndex).m_minkowskiDiff;
		if (IsVectorEqual(minkowskiDiff, pointMinkowskiDiff))
		{
			return true;
		}
	}

	return false;
}

bool Edge::MinkowskiSumBaseAlgorithmUtils::CheckCodirection(const ComputeVector& direction, const ComputeVector& vector)
{
	return DotVector3(direction, vector) > Math::Epsilon;
	//return DotVector3(direction, vector) > 0.0f;
}

bool Edge::GJK::checkAndIterateSimplex(VoronoiSimplex& simplex, FloatVector3& direction) const
{
	switch (simplex.getPointCount())
	{
	case 2: return checkSimplex1D(simplex, direction);
	case 3: return checkSimplex2D(simplex, direction);
	case 4: return checkSimplex3D(simplex, direction);
	}

	return false;
}

bool Edge::GJK::checkSimplex1D(VoronoiSimplex& simplex, FloatVector3& direction) const
{
	const VoronoiSimplex::Point a = simplex.getPoint(0);
	const VoronoiSimplex::Point b = simplex.getPoint(1);

	const ComputeVector ab = b.m_minkowskiDiff - a.m_minkowskiDiff;
	const ComputeVector ao = NegateVector(a.m_minkowskiDiff);

	if (MinkowskiSumBaseAlgorithmUtils::CheckCodirection(ab, ao))
	{
		CrossVector3(CrossVector3(ab, ao), ab).saveToFloatVector3(direction);
	}
	else
	{
		simplex.setPoint(a);
		ao.saveToFloatVector3(direction);
	}

	return false;
}

bool Edge::GJK::checkSimplex2D(VoronoiSimplex& simplex, FloatVector3& direction) const
{
	const VoronoiSimplex::Point a = simplex.getPoint(0);
	const VoronoiSimplex::Point b = simplex.getPoint(1);
	const VoronoiSimplex::Point c = simplex.getPoint(2);

	const ComputeVector ab = b.m_minkowskiDiff - a.m_minkowskiDiff;
	const ComputeVector ac = c.m_minkowskiDiff - a.m_minkowskiDiff;
	const ComputeVector ao = NegateVector(a.m_minkowskiDiff);

	const ComputeVector abcNormal = CrossVector3(ab, ac);
	const ComputeVector abNormal = CrossVector3(ab, abcNormal);
	const ComputeVector acNormal = CrossVector3(abcNormal, ac);

	if (MinkowskiSumBaseAlgorithmUtils::CheckCodirection(acNormal, ao))
	{
		if (MinkowskiSumBaseAlgorithmUtils::CheckCodirection(ac, ao))
		{
			CrossVector3(CrossVector3(ac, ao), ac).saveToFloatVector3(direction);
			simplex.setPoints(a, c);
		}
		else
		{
			if (MinkowskiSumBaseAlgorithmUtils::CheckCodirection(ab, ao))
			{
				CrossVector3(CrossVector3(ab, ao), ab).saveToFloatVector3(direction);
				simplex.setPoints(a, b);
			}
			else
			{
				ao.saveToFloatVector3(direction);
				simplex.setPoint(a);
			}
		}
	}
	else
	{
		if (MinkowskiSumBaseAlgorithmUtils::CheckCodirection(abNormal, ao))
		{
			if (MinkowskiSumBaseAlgorithmUtils::CheckCodirection(ab, ao))
			{
				CrossVector3(CrossVector3(ab, ao), ab).saveToFloatVector3(direction);
				simplex.setPoints(a, b);
			}
			else
			{
				ao.saveToFloatVector3(direction);
				simplex.setPoint(a);
			}
		}
		else
		{
			if (MinkowskiSumBaseAlgorithmUtils::CheckCodirection(abcNormal, ao))
			{
				abcNormal.saveToFloatVector3(direction);
			}
			else
			{
				NegateVector(abcNormal).saveToFloatVector3(direction);
				simplex.setPoints(a, c, b);
			}
		}
	}

	return false;
}

bool Edge::GJK::checkSimplex3D(VoronoiSimplex& simplex, FloatVector3& direction) const
{
	const VoronoiSimplex::Point a = simplex.getPoint(0);
	const VoronoiSimplex::Point b = simplex.getPoint(1);
	const VoronoiSimplex::Point c = simplex.getPoint(2);
	const VoronoiSimplex::Point d = simplex.getPoint(3);

	const ComputeVector ab = b.m_minkowskiDiff - a.m_minkowskiDiff;
	const ComputeVector ac = c.m_minkowskiDiff - a.m_minkowskiDiff;
	const ComputeVector ad = d.m_minkowskiDiff - a.m_minkowskiDiff;
	const ComputeVector ao = NegateVector(a.m_minkowskiDiff);

	const ComputeVector abcNormal = CrossVector3(ab, ac);
	const ComputeVector acdNormal = CrossVector3(ac, ad);
	const ComputeVector adbNormal = CrossVector3(ad, ab);

	if (MinkowskiSumBaseAlgorithmUtils::CheckCodirection(abcNormal, ao)) {
		simplex.setPoints(a, b, c);

		return checkSimplex2D(simplex, direction);
	}

	if (MinkowskiSumBaseAlgorithmUtils::CheckCodirection(acdNormal, ao)) {
		simplex.setPoints(a, c, d);

		return checkSimplex2D(simplex, direction);
	}

	if (MinkowskiSumBaseAlgorithmUtils::CheckCodirection(adbNormal, ao)) {
		simplex.setPoints(a, d, b);

		return checkSimplex2D(simplex, direction);
	}

	return true;
}

Edge::GJK::Result Edge::GJK::test(const PhysicsEntityCollision& collision1, const PhysicsEntityCollision& collision2, uint32_t maxIterationCount) const
{
	VoronoiSimplex simplex;

	FloatVector3 direction;
	(collision2.getTransform()->getPosition() - collision1.getTransform()->getPosition()).normalize().saveToFloatVector3(direction);

	VoronoiSimplex::Point supportPoint = MinkowskiSumBaseAlgorithmUtils::Support(collision1, collision2, direction);
	simplex.addPoint(supportPoint);

	if (Vector3LengthSqr(supportPoint.m_minkowskiDiff) <= Math::EpsilonSqr)
	{
		return Result(simplex, Result::TestResult::Contact);
	}

	direction = NegateVector(supportPoint.m_minkowskiDiff).getFloatVector3();

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

		NormalizeVector(direction).saveToFloatVector3(direction);

		if (Vector3LengthSqr(direction) <= Math::EpsilonSqr)
		{
			testResult = Result::TestResult::FailedTesting;
			break;
		}

		supportPoint = MinkowskiSumBaseAlgorithmUtils::Support(collision1, collision2, direction);

		if (Vector3LengthSqr(supportPoint.m_minkowskiDiff) <= Math::EpsilonSqr)
		{
			testResult = Result::TestResult::Contact;
			break;
		}


		if (MinkowskiSumBaseAlgorithmUtils::HasSimplexPoint(simplex, supportPoint.m_minkowskiDiff))
		{
			break;
		}

		if (!MinkowskiSumBaseAlgorithmUtils::CheckCodirection(direction, supportPoint.m_minkowskiDiff))
		{
			break;
		}

		simplex.addPoint(supportPoint);

		if (checkAndIterateSimplex(simplex, direction))
		{
			testResult = Result::TestResult::Intersection;
			break;
		}
	}

	return Result(simplex, testResult);
}

Edge::EPA::PolytopeFace::PolytopeFace(const VoronoiSimplex::Point& point1, const VoronoiSimplex::Point& point2, const VoronoiSimplex::Point& point3)
{
	m_points[0] = point1;
	m_points[1] = point2;
	m_points[2] = point3;

	CrossVector3(
		point2.m_minkowskiDiff - point1.m_minkowskiDiff,
		point3.m_minkowskiDiff - point1.m_minkowskiDiff
	).normalize().saveToFloatVector3(m_normal);
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
		if (IsVectorEqual(iterator->m_points[0].m_minkowskiDiff, point2.m_minkowskiDiff)
			&& IsVectorEqual(iterator->m_points[1].m_minkowskiDiff, point1.m_minkowskiDiff))
		{
			edgeCollection.erase(iterator);
			return;
		}
	}

	edgeCollection.emplace_back(point1, point2);
}

void Edge::EPA::fillPointContactPointData(const PhysicsEntityCollision& collision1, const PhysicsEntityCollision& collision2,
	const GJK::Result& gjkResult, PhysicsCollisionContactPoint& contactPoint) const
{
	contactPoint.m_position1 = gjkResult.m_simplex.getPoint(gjkResult.m_simplex.getPointCount() - 1).m_pointCollision1;
	contactPoint.m_position2 = gjkResult.m_simplex.getPoint(gjkResult.m_simplex.getPointCount() - 1).m_pointCollision2;

	(collision2.getTransform()->getPosition() - collision1.getTransform()->getPosition())
		.normalize().saveToFloatVector3(contactPoint.m_normal);
	contactPoint.m_depth = 0.0f;
}

void Edge::EPA::fillFaceContactPointData(const PolytopeFace& face, PhysicsCollisionContactPoint& contactPoint) const
{
	const FloatVector4 barycentricCoords = getBarycentricFaceProjection(face);

	((barycentricCoords.m_x * face.m_points[0].m_pointCollision1)
		+ (barycentricCoords.m_y * face.m_points[1].m_pointCollision1)
		+ (barycentricCoords.m_z * face.m_points[2].m_pointCollision1)
		).saveToFloatVector3(contactPoint.m_position1);

	((barycentricCoords.m_x * face.m_points[0].m_pointCollision2)
		+ (barycentricCoords.m_y * face.m_points[1].m_pointCollision2)
		+ (barycentricCoords.m_z * face.m_points[2].m_pointCollision2)
		).saveToFloatVector3(contactPoint.m_position2);

	contactPoint.m_normal = face.m_normal;
	contactPoint.m_depth = barycentricCoords.m_w;
}

Edge::FloatVector4 Edge::EPA::getBarycentricFaceProjection(const PolytopeFace& face) const
{
	const float distanceFromOrigin = DotVector3(face.m_normal, face.m_points[0].m_minkowskiDiff);
	const ComputeVector point = face.m_normal * distanceFromOrigin;

	const ComputeVector v0 = face.m_points[1].m_minkowskiDiff - face.m_points[0].m_minkowskiDiff;
	const ComputeVector v1 = face.m_points[2].m_minkowskiDiff - face.m_points[0].m_minkowskiDiff;
	const ComputeVector v2 = point - face.m_points[0].m_minkowskiDiff;

	const float d00 = DotVector3(v0, v0);
	const float d01 = DotVector3(v0, v1);
	const float d11 = DotVector3(v1, v1);
	const float d20 = DotVector3(v2, v0);
	const float d21 = DotVector3(v2, v1);

	const float denom = d00 * d11 - d01 * d01;

	const float v = (d11 * d20 - d01 * d21) / denom;
	const float w = (d00 * d21 - d01 * d20) / denom;
	const float u = 1.0f - v - w;

	return FloatVector4(u, v, w, distanceFromOrigin);
}

bool Edge::EPA::calcEPAContact(const PhysicsEntityCollision& collision1, const PhysicsEntityCollision& collision2,
	const GJK::Result& gjkResult, uint32_t maxIterationCount, PhysicsCollisionContactPoint& contactPointData) const
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

		float minDistance = Math::FltMax;

		std::list<PolytopeFace>::iterator closestFace = polytopeFaces.begin();

		for (auto iterator = polytopeFaces.begin(); iterator != polytopeFaces.end(); ++iterator)
		{
			const float distance = DotVector3(iterator->m_normal, iterator->m_points[0].m_minkowskiDiff);
			if (distance < minDistance)
			{
				minDistance = distance;
				closestFace = iterator;
			}
		}

		const VoronoiSimplex::Point supportPoint = MinkowskiSumBaseAlgorithmUtils::Support(collision1, collision2, closestFace->m_normal);

		if (DotVector3(closestFace->m_normal, supportPoint.m_minkowskiDiff) - minDistance < 0.0001f)
		{
			fillFaceContactPointData(*closestFace, contactPointData);

			return true;
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

bool Edge::EPA::getContactPoint(const PhysicsEntityCollision& collision1, const PhysicsEntityCollision& collision2,
                                const GJK::Result& gjkResult, uint32_t maxIterationCount, PhysicsCollisionContactPoint& contactPointData) const
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
