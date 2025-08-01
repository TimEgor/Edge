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

	result.m_pointCollision1 = collision1.getSupportingPoint(direction);
	result.m_pointCollision2 = collision2.getSupportingPoint(-direction);

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
	const ComputeVector3& controlPoint,
	const ComputeVector3& checkedPoint
)
{
	const ComputeVector3 n = (point2 - point1).cross(point3 - point1);

	const ComputeValue checkedFaceSign = (checkedPoint - point1).dot(n);
	const ComputeValue controlFaceSign = (controlPoint - point1).dot(n);

	if (controlFaceSign * controlFaceSign < Math::Epsilon)
	{
		return false;
	}

	return checkedFaceSign * controlFaceSign < 0.0_ecv;
}

void Edge::GJK::getSimplexClosestPoint(VoronoiSimplex& simplex, ComputeVector3& delta) const
{
	switch (simplex.getPointCount())
	{
	case 1:
		getSimplex0DClosestPoint(simplex, delta);
		break;
	case 2:
		getSimplex1DClosestPoint(simplex, delta);
		break;
	case 3:
		getSimplex2DClosestPoint(simplex, delta);
		break;
	case 4:
		getSimplex3DClosestPoint(simplex, delta);
		break;
	default:
		EDGE_ASSERT_FAIL();
	}
}

void Edge::GJK::getSimplex0DClosestPoint(VoronoiSimplex& simplex, ComputeVector3& delta) const
{
	const VoronoiSimplex::Point a = simplex.getPoint(0);
	delta = a.m_minkowskiDiff;
}

void Edge::GJK::getSimplex1DClosestPoint(VoronoiSimplex& simplex, ComputeVector3& delta) const
{
	const VoronoiSimplex::Point a = simplex.getPoint(1);
	const VoronoiSimplex::Point b = simplex.getPoint(0);

	const ComputeVector3 ab = b.m_minkowskiDiff - a.m_minkowskiDiff;

	ComputeValue t = (-a.m_minkowskiDiff).dot(ab);
	if (t <= 0.0)
	{
		simplex.setPoint(a);
		delta = a.m_minkowskiDiff;
	}
	else
	{
		const ComputeValue denom = ab.getLengthSqr();

		if (t >= denom)
		{
			simplex.setPoint(b);
			delta = b.m_minkowskiDiff;
		}
		else
		{
			t /= denom;
			delta = a.m_minkowskiDiff + t * ab;
		}
	}
}

void Edge::GJK::getSimplex2DClosestPoint(VoronoiSimplex& simplex, ComputeVector3& delta) const
{
	const VoronoiSimplex::Point a = simplex.getPoint(2);
	const VoronoiSimplex::Point b = simplex.getPoint(1);
	const VoronoiSimplex::Point c = simplex.getPoint(0);

	const ComputeVector3 ab = b.m_minkowskiDiff - a.m_minkowskiDiff;
	const ComputeVector3 ac = c.m_minkowskiDiff - a.m_minkowskiDiff;
	const ComputeVector3 bc = c.m_minkowskiDiff - b.m_minkowskiDiff;

	const ComputeVector3 ao = -a.m_minkowskiDiff;
	const ComputeVector3 bo = -b.m_minkowskiDiff;
	const ComputeVector3 co = -c.m_minkowskiDiff;

	const ComputeValue d1 = ab.dot(ao);
	const ComputeValue d2 = ac.dot(ao);
	if (d1 <= 0 && d2 <= 0)
	{
		simplex.setPoint(a);
		delta = a.m_minkowskiDiff;

		return;
	}

	const ComputeValue d3 = ab.dot(bo);
	const ComputeValue d4 = ac.dot(bo);
	if (d3 >= 0 && d4 <= d3)
	{
		simplex.setPoint(b);
		delta = b.m_minkowskiDiff;

		return;
	}

	const ComputeValue vc = d1 * d4 - d3 * d2;
	if (vc <= 0 && d1 >= 0 && d3 <= 0)
	{
		const ComputeValue v = d1 / (d1 - d3);

		simplex.setPoints(b, a);
		delta = a.m_minkowskiDiff + v * ab;

		return;
	}

	const ComputeValue d5 = ab.dot(co);
	const ComputeValue d6 = ac.dot(co);
	if (d6 >= 0 && d5 <= d6)
	{
		simplex.setPoint(c);
		delta = c.m_minkowskiDiff;

		return;
	}

	const ComputeValue vb = d5 * d2 - d1 * d6;
	if (vb <= 0 && d2 >= 0 && d6 <= 0)
	{
		const ComputeValue w = d2 / (d2 - d6);

		simplex.setPoints(c, a);
		delta = a.m_minkowskiDiff + w * ac;

		return;
	}

	const ComputeValue va = d3 * d6 - d5 * d4;
	if (va <= 0 && (d4 - d3) >= 0 && (d5 - d6) >= 0)
	{
		const ComputeValue w = (d4 - d3) / ((d4 - d3) + (d5 - d6));

		simplex.setPoints(c, b);
		delta = b.m_minkowskiDiff + w * bc;

		return;
	}

	// inside face region
	const ComputeValue denom = 1.0_ecv / (va + vb + vc);
	const ComputeValue v = vb * denom;
	const ComputeValue w = vc * denom;

	delta = a.m_minkowskiDiff + ab * v + ac * w;
}

void Edge::GJK::getSimplex3DClosestPoint(VoronoiSimplex& simplex, ComputeVector3& delta) const
{
	ComputeValue minDistanceSqr = Math::Max;

	VoronoiSimplex computingSimplex = simplex;
	ComputeVector3 computingDirection = delta;

	const VoronoiSimplex::Point a = simplex.getPoint(3);
	const VoronoiSimplex::Point b = simplex.getPoint(2);
	const VoronoiSimplex::Point c = simplex.getPoint(1);
	const VoronoiSimplex::Point d = simplex.getPoint(0);

	if (MinkowskiSumBaseAlgorithmUtils::CheckPlaneSide(
		a.m_minkowskiDiff,
		b.m_minkowskiDiff,
		c.m_minkowskiDiff,
		d.m_minkowskiDiff,
		ComputeVector3Zero
	))
	{
		VoronoiSimplex checkedSimplex;
		checkedSimplex.setPoints(c, b, a);

		ComputeVector3 checkedDistance;

		getSimplex2DClosestPoint(checkedSimplex, checkedDistance);

		const ComputeValue distanceSqr = checkedDistance.getLengthSqr();
		if (minDistanceSqr > distanceSqr)
		{
			minDistanceSqr = distanceSqr;

			computingSimplex = checkedSimplex;
			computingDirection = checkedDistance;
		}
	}

	if (MinkowskiSumBaseAlgorithmUtils::CheckPlaneSide(
		b.m_minkowskiDiff,
		d.m_minkowskiDiff,
		c.m_minkowskiDiff,
		a.m_minkowskiDiff,
		ComputeVector3Zero
	))
	{
		VoronoiSimplex checkedSimplex;
		checkedSimplex.setPoints(c, d, b);

		ComputeVector3 checkedDistance;

		getSimplex2DClosestPoint(checkedSimplex, checkedDistance);

		const ComputeValue distanceSqr = checkedDistance.getLengthSqr();
		if (minDistanceSqr > distanceSqr)
		{
			minDistanceSqr = distanceSqr;

			computingSimplex = checkedSimplex;
			computingDirection = checkedDistance;
		}
	}

	if (MinkowskiSumBaseAlgorithmUtils::CheckPlaneSide(
		a.m_minkowskiDiff,
		c.m_minkowskiDiff,
		b.m_minkowskiDiff,
		b.m_minkowskiDiff,
		ComputeVector3Zero
	))
	{
		VoronoiSimplex checkedSimplex;
		checkedSimplex.setPoints(b, c, a);

		ComputeVector3 checkedDistance;

		getSimplex2DClosestPoint(checkedSimplex, checkedDistance);

		const ComputeValue distanceSqr = checkedDistance.getLengthSqr();
		if (minDistanceSqr > distanceSqr)
		{
			minDistanceSqr = distanceSqr;

			computingSimplex = checkedSimplex;
			computingDirection = checkedDistance;
		}
	}

	if (MinkowskiSumBaseAlgorithmUtils::CheckPlaneSide(
		a.m_minkowskiDiff,
		d.m_minkowskiDiff,
		b.m_minkowskiDiff,
		c.m_minkowskiDiff,
		ComputeVector3Zero
	))
	{
		VoronoiSimplex checkedSimplex;
		checkedSimplex.setPoints(b, d, a);

		ComputeVector3 checkedDistance;

		getSimplex2DClosestPoint(checkedSimplex, checkedDistance);

		const ComputeValue distanceSqr = checkedDistance.getLengthSqr();
		if (minDistanceSqr > distanceSqr)
		{
			minDistanceSqr = distanceSqr;

			computingSimplex = checkedSimplex;
			computingDirection = checkedDistance;
		}
	}

	simplex = computingSimplex;
	delta = computingDirection;
}

Edge::GJK::TestResult Edge::GJK::test(
	const PhysicsEntityCollision& collision1,
	const PhysicsEntityCollision& collision2,
	uint32_t maxIterationCount,
	ComputeValue contactTolerance
) const
{
	const ComputeValue contactToleranceSqr = contactTolerance * contactTolerance;

	const ComputeValue supportRadius1 = collision1.getSupportingRadius();
	const ComputeValue supportRadius2 = collision2.getSupportingRadius();

	const ComputeValue totalSupportRadius = supportRadius1 + supportRadius2;
	const ComputeValue totalSupportRadiusSqr = totalSupportRadius * totalSupportRadius;

	VoronoiSimplex simplex;

	ComputeVector3 delta = collision1.getTransform()->getPosition() - collision2.getTransform()->getPosition();
	Result testResult = Result::NoIntersection;

	ComputeValue currentDistanceSqr = Math::Max;

	uint32_t testIterationCount = 0;
	while (true)
	{
		++testIterationCount;
		if (testIterationCount > maxIterationCount)
		{
			testResult = Result::OverIteration;
			break;
		}

		const VoronoiSimplex::Point supportPoint = MinkowskiSumBaseAlgorithmUtils::Support(collision1, collision2, NormalizeComputeVector3(delta));

		//if (supportPoint.m_minkowskiDiff.dot(delta) < 0.0)
		//{
		//	break;
		//}

		if (MinkowskiSumBaseAlgorithmUtils::HasSimplexPoint(simplex, supportPoint.m_minkowskiDiff))
		{
			break;
		}

		simplex.addPoint(supportPoint);

		const ComputeValue prevDistanceSqr = currentDistanceSqr;
		VoronoiSimplex computeSimplex = simplex;
		ComputeVector3 computeDirection = delta;
		getSimplexClosestPoint(computeSimplex, computeDirection);

		const ComputeValue newDistanceSqr = computeDirection.getLengthSqr();
		if (newDistanceSqr > prevDistanceSqr)
		{
			simplex.removeLastPoint();
			break;
		}

		currentDistanceSqr = newDistanceSqr;

		simplex = computeSimplex;
		delta = computeDirection;

		if (simplex.getPointCount() == 4)
		{
			break;
		}

		if (currentDistanceSqr <= contactToleranceSqr)
		{
			break;
		}

		if (prevDistanceSqr - currentDistanceSqr <= prevDistanceSqr * Math::Epsilon)
		{
			break;
		}

		delta = -delta;
	}

	ComputeVector3 contactPoint1 = ComputeVector3Zero;
	ComputeVector3 contactPoint2 = ComputeVector3Zero;

	switch (simplex.getPointCount())
	{
	case 1:
	{
		const VoronoiSimplex::Point& a = simplex.getPoint(0);

		contactPoint1 = a.m_pointCollision1;
		contactPoint2 = a.m_pointCollision2;
		break;
	}
	case 2:
	{
		ComputeValue u, v;

		const VoronoiSimplex::Point& a = simplex.getPoint(0);
		const VoronoiSimplex::Point& b = simplex.getPoint(1);

		{
			const ComputeVector3 ab = b.m_minkowskiDiff - a.m_minkowskiDiff;

			ComputeValue t = (-a.m_minkowskiDiff).dot(ab);
			if (t <= 0.0)
			{
				u = 1.0;
				v = 0.0;
			}
			else
			{
				const ComputeValue denom = ab.getLengthSqr();

				if (t >= denom)
				{
					u = 0.0;
					v = 1.0;
				}
				else
				{
					t /= denom;

					u = 1.0 - t;
					v = t;
				}
			}
		}

		contactPoint1 = u * a.m_pointCollision1 + v * b.m_pointCollision1;
		contactPoint2 = u * a.m_pointCollision2 + v * b.m_pointCollision2;

		break;
	}
	case 3:
	{
		ComputeValue u, v, w;

		const VoronoiSimplex::Point& a = simplex.getPoint(0);
		const VoronoiSimplex::Point& b = simplex.getPoint(1);
		const VoronoiSimplex::Point& c = simplex.getPoint(2);

		{
			const ComputeVector3 ab = b.m_minkowskiDiff - a.m_minkowskiDiff;
			const ComputeVector3 ac = c.m_minkowskiDiff - a.m_minkowskiDiff;
			const ComputeVector3 ao = -a.m_minkowskiDiff;


			const ComputeValue d00 = ab.getLengthSqr();
			const ComputeValue d01 = DotComputeVector3(ab, ac);
			const ComputeValue d11 = ac.getLengthSqr();
			const ComputeValue d20 = DotComputeVector3(ao, ab);
			const ComputeValue d21 = DotComputeVector3(ao, ac);

			const ComputeValue denom = d00 * d11 - d01 * d01;
			v = (d11 * d20 - d01 * d21) / denom;
			w = (d00 * d21 - d01 * d20) / denom;
			u = 1.0 - v - w;
		}

		contactPoint1 = u * a.m_pointCollision1 + v * b.m_pointCollision1 + w * c.m_pointCollision1;
		contactPoint2 = u * a.m_pointCollision2 + v * b.m_pointCollision2 + w * c.m_pointCollision2;

		break;
	}
	case 4:
	{
		currentDistanceSqr = -1;
		break;
	}
	}

	if (currentDistanceSqr > totalSupportRadiusSqr)
	{
		testResult = Result::NoIntersection;
	}
	else if (currentDistanceSqr > 0.0_ecv)
	{
		testResult = Result::Intersection;

		const ComputeValue distance = sqrt(currentDistanceSqr);

		contactPoint1 += delta * (supportRadius1 / distance);
		contactPoint2 -= delta * (supportRadius2 / distance);
	}
	else
	{
		testResult = Result::Undetermined;
	}

	return TestResult(simplex, testResult, delta, contactPoint1, contactPoint2);
}

Edge::EPA::PolytopeFace::PolytopeFace(const VoronoiSimplex::Point& point1, const VoronoiSimplex::Point& point2, const VoronoiSimplex::Point& point3)
{
	m_points[0] = point1;
	m_points[1] = point2;
	m_points[2] = point3;

	const ComputeVector3 edge1 = point2.m_minkowskiDiff - point1.m_minkowskiDiff;
	const ComputeVector3 edge2 = point3.m_minkowskiDiff - point1.m_minkowskiDiff;

	ComputeVector3 normal = CrossComputeVector3(edge1, edge2);

	if (LengthSqrComputeVector3(normal) < Math::EpsilonSqr)
	{
		const ComputeVector3 axis = (abs(edge1.getX()) < abs(edge1.getY())) ? ComputeVector3UnitX : ComputeVector3UnitY;
		normal = CrossComputeVector3(edge1, axis);

		if (LengthSqrComputeVector3(normal) < Math::EpsilonSqr)
		{
			normal = CrossComputeVector3(edge1, ComputeVector3UnitZ);

			if (LengthSqrComputeVector3(normal) < Math::EpsilonSqr)
			{
				m_distance = -1.0;
				return;
			}
		}
	}

	m_normal = NormalizeComputeVector3(normal);
	m_distance = DotComputeVector3(m_normal, point1.m_minkowskiDiff);

	if (m_distance < 0.0)
	{
		m_normal = -m_normal;
		m_distance = -m_distance;

		const VoronoiSimplex::Point tmp = m_points[1];
		m_points[1] = m_points[2];
		m_points[2] = tmp;
	}
}

bool Edge::EPA::PolytopeFace::operator<(const PolytopeFace& face) const
{
	return m_distance < face.m_distance;
}

Edge::EPA::PolytopeEdge::PolytopeEdge(const VoronoiSimplex::Point& point1, const VoronoiSimplex::Point& point2)
{
	m_points[0] = point1;
	m_points[1] = point2;
}

void Edge::EPA::buildFullSimplex(
	const PhysicsEntityCollision& collision1,
	const PhysicsEntityCollision& collision2,
	VoronoiSimplex& simplex
) const
{
	const uint32_t simplexPointCount = simplex.getPointCount();

	switch (simplexPointCount)
	{
	case 1:
	{
		const VoronoiSimplex::Point& a = simplex.getPoint(0);

		if (a.getDistanceSqr() < Math::EpsilonSqr)
		{
			const VoronoiSimplex::Point b = MinkowskiSumBaseAlgorithmUtils::Support(collision1, collision2, ComputeVector3UnitX);
			const VoronoiSimplex::Point c = MinkowskiSumBaseAlgorithmUtils::Support(collision1, collision2, ComputeVector3UnitY);
			const VoronoiSimplex::Point d = MinkowskiSumBaseAlgorithmUtils::Support(collision1, collision2, ComputeVector3UnitZ);

			simplex.setPoints(a, b, c, d);
		}
		else
		{

			ComputeVector3 dirB = NormalizeComputeVector3(CrossComputeVector3(a.m_minkowskiDiff, ComputeVector3UnitX));
			if (LengthSqrComputeVector3(dirB) < Math::EpsilonSqr)
			{
				dirB = NormalizeComputeVector3(CrossComputeVector3(a.m_minkowskiDiff, ComputeVector3UnitY));
			}

			const VoronoiSimplex::Point b = MinkowskiSumBaseAlgorithmUtils::Support(collision1, collision2, dirB);

			const ComputeVector3 dirC = NormalizeComputeVector3(CrossComputeVector3(dirB, a.m_minkowskiDiff));
			const VoronoiSimplex::Point c = MinkowskiSumBaseAlgorithmUtils::Support(collision1, collision2, dirC);

			const ComputeVector3 dirD = NormalizeComputeVector3(CrossComputeVector3(a.m_minkowskiDiff - b.m_minkowskiDiff, a.m_minkowskiDiff - c.m_minkowskiDiff));
			const VoronoiSimplex::Point d = MinkowskiSumBaseAlgorithmUtils::Support(collision1, collision2, dirD);

			simplex.setPoints(a, b, c, d);
		}

		break;
	}
	case 2:
	{
		const VoronoiSimplex::Point& a = simplex.getPoint(0);
		const VoronoiSimplex::Point& b = simplex.getPoint(1);

		const ComputeVector3 ab = b.m_minkowskiDiff - a.m_minkowskiDiff;

		ComputeVector3 norm = CrossComputeVector3(ab, ComputeVector3UnitX);
		if (LengthSqrComputeVector3(norm) < Math::EpsilonSqr)
		{
			norm = CrossComputeVector3(ab, ComputeVector3UnitY);
		}

		const ComputeVector3 dir = NormalizeComputeVector3(CrossComputeVector3(ab, norm));

		const VoronoiSimplex::Point c = MinkowskiSumBaseAlgorithmUtils::Support(collision1, collision2, dir);
		const VoronoiSimplex::Point d = MinkowskiSumBaseAlgorithmUtils::Support(collision1, collision2, -dir);

		simplex.setPoints(a, b, c, d);

		break;
	}
	case 3:
	{
		const VoronoiSimplex::Point& a = simplex.getPoint(0);
		const VoronoiSimplex::Point& b = simplex.getPoint(1);
		const VoronoiSimplex::Point& c = simplex.getPoint(2);

		const ComputeVector3 norm = NormalizeComputeVector3(
			CrossComputeVector3(b.m_minkowskiDiff - a.m_minkowskiDiff, c.m_minkowskiDiff - a.m_minkowskiDiff)
		);

		VoronoiSimplex::Point d = MinkowskiSumBaseAlgorithmUtils::Support(collision1, collision2, norm);
		if (abs(DotComputeVector3(d.m_minkowskiDiff - a.m_minkowskiDiff, norm)) < Math::EpsilonSqr)
		{
			d = MinkowskiSumBaseAlgorithmUtils::Support(collision1, collision2, -norm);
		}

		simplex.setPoints(a, b, c, d);

		break;
	}
	}
}

void Edge::EPA::getBarycentricFaceProjection(const PolytopeFace& face, ComputeVector4& outProjection) const
{
	const ComputeValue distanceFromOrigin = DotComputeVector3(face.m_normal, face.m_points[0].m_minkowskiDiff);
	const ComputeVector3 point = face.m_normal * distanceFromOrigin;

	const ComputeVector3 v0 = face.m_points[1].m_minkowskiDiff - face.m_points[0].m_minkowskiDiff;
	const ComputeVector3 v1 = face.m_points[2].m_minkowskiDiff - face.m_points[0].m_minkowskiDiff;
	const ComputeVector3 v2 = point - face.m_points[0].m_minkowskiDiff;

	const ComputeValue d00 = DotComputeVector3(v0, v0);
	const ComputeValue d01 = DotComputeVector3(v0, v1);
	const ComputeValue d11 = DotComputeVector3(v1, v1);
	const ComputeValue d20 = DotComputeVector3(v2, v0);
	const ComputeValue d21 = DotComputeVector3(v2, v1);

	const ComputeValue denom = d00 * d11 - d01 * d01;
	if (denom <= 0.0)
	{
		if (LengthSqrComputeVector3(v0) >= LengthSqrComputeVector3(v1))
		{
			const ComputeValue t = DotComputeVector3(v2, v0) / (d00 > Math::Epsilon ? d00 : Math::Epsilon);
			const ComputeValue u = 1.0_ecv - t;
			const ComputeValue v = t;
			const ComputeValue w = 0.0;

			outProjection = ComputeVector4(u, v, w, distanceFromOrigin);
		}
		else
		{
			const ComputeValue t = DotComputeVector3(v2, v1) / (d11 > Math::Epsilon ? d11 : Math::Epsilon);
			const ComputeValue u = 1.0_ecv - t;
			const ComputeValue v = 0.0;
			const ComputeValue w = t;

			outProjection = ComputeVector4(u, v, w, distanceFromOrigin);
		}
	}
	else
	{
		const ComputeValue v = (d11 * d20 - d01 * d21) / denom;
		const ComputeValue w = (d00 * d21 - d01 * d20) / denom;
		const ComputeValue u = 1.0_ecv - v - w;

		outProjection = ComputeVector4(u, v, w, distanceFromOrigin);
	}
}

bool Edge::EPA::calcEPAContact(
	const PhysicsEntityCollision& collision1,
	const PhysicsEntityCollision& collision2,
	const GJK::TestResult& gjkResult,
	uint32_t maxIterationCount,
	PhysicsCollisionContactPoint& contactPointData
) const
{
	VoronoiSimplex simplex = gjkResult.m_simplex;
	buildFullSimplex(collision1, collision2, simplex);

	std::vector<PolytopeFace> faces;

	{
		const VoronoiSimplex::Point& a = simplex.getPoint(0);
		const VoronoiSimplex::Point& b = simplex.getPoint(1);
		const VoronoiSimplex::Point& c = simplex.getPoint(2);
		const VoronoiSimplex::Point& d = simplex.getPoint(3);

		const PolytopeFace faceABC(a, b, c);
		if (faceABC.m_distance >= 0.0)
		{
			faces.emplace_back(faceABC);
		}

		const PolytopeFace faceACD(a, c, d);
		if (faceACD.m_distance >= 0.0)
		{
			faces.emplace_back(faceACD);
		}

		const PolytopeFace faceADB(a, d, b);
		if (faceADB.m_distance >= 0.0)
		{
			faces.emplace_back(faceADB);
		}

		const PolytopeFace faceBDC(b, d, c);
		if (faceBDC.m_distance >= 0.0)
		{
			faces.emplace_back(faceBDC);
		}
	}

	uint32_t testIterationCount = 0;
	while (true)
	{
		++testIterationCount;
		if (testIterationCount > maxIterationCount)
		{
			break;
		}

		const PolytopeFace closest = *std::min_element(faces.begin(), faces.end());

		const VoronoiSimplex::Point p = MinkowskiSumBaseAlgorithmUtils::Support(collision1, collision2, closest.m_normal);
		const ComputeValue d = DotComputeVector3(closest.m_normal, p.m_minkowskiDiff);

		if (d - closest.m_distance < 0.0001)
		{
			ComputeVector4 barycentricCoords;
			getBarycentricFaceProjection(closest, barycentricCoords);

			contactPointData.m_position1 = (
				(barycentricCoords.getX() * closest.m_points[0].m_pointCollision1) +
				(barycentricCoords.getY() * closest.m_points[1].m_pointCollision1) +
				(barycentricCoords.getZ() * closest.m_points[2].m_pointCollision1)
				);

			contactPointData.m_position2 = (
				(barycentricCoords.getX() * closest.m_points[0].m_pointCollision2) +
				(barycentricCoords.getY() * closest.m_points[1].m_pointCollision2) +
				(barycentricCoords.getZ() * closest.m_points[2].m_pointCollision2)
				);

			contactPointData.m_normal = closest.m_normal;
			contactPointData.m_depth = barycentricCoords.getW();

			return true;
		}

		std::vector<PolytopeEdge> border;
		std::vector<PolytopeFace> newFaces;

		for (const PolytopeFace& face : faces)
		{
			if (DotComputeVector3(face.m_normal, p.m_minkowskiDiff - face.m_points[0].m_minkowskiDiff) > 0.0)
			{
				border.emplace_back(face.m_points[0], face.m_points[1]);
				border.emplace_back(face.m_points[1], face.m_points[2]);
				border.emplace_back(face.m_points[2], face.m_points[0]);
			}
			else
			{
				newFaces.push_back(face);
			}
		}

		auto edgeEquals = [](const PolytopeEdge& edge1, const PolytopeEdge& edge2)
			{
				return (
					edge1.m_points[0].m_minkowskiDiff == edge2.m_points[1].m_minkowskiDiff &&
					edge1.m_points[1].m_minkowskiDiff == edge2.m_points[0].m_minkowskiDiff
					);
			};

		std::vector<PolytopeEdge> uniqueEdges;

		for (size_t edgeIndex = 0; edgeIndex < border.size(); ++edgeIndex)
		{
			bool shared = false;
			for (size_t j = 0; j < border.size(); ++j)
			{
				if (edgeIndex != j && edgeEquals(border[edgeIndex], border[j]))
				{
					shared = true;
					break;
				}
			}

			if (!shared)
			{
				uniqueEdges.push_back(border[edgeIndex]);
			}
		}

		for (const PolytopeEdge& edge : uniqueEdges)
		{
			const PolytopeFace newFace(edge.m_points[0], edge.m_points[1], p);
			if (newFace.m_distance >= 0.0)
			{
				newFaces.emplace_back(newFace);
			}
		}

		faces.swap(newFaces);
	}

	return false;
}

bool Edge::EPA::getContactPoint(
	const PhysicsEntityCollision& collision1,
	const PhysicsEntityCollision& collision2,
	const GJK::TestResult& gjkResult,
	uint32_t maxIterationCount,
	PhysicsCollisionContactPoint& contactPointData
) const
{
	if (gjkResult.m_simplex.getPointCount() == 0)
	{
		return false;
	}

	if (gjkResult.m_testResult == GJK::Result::NoIntersection || gjkResult.m_testResult == GJK::Result::OverIteration)
	{
		return false;
	}

	return calcEPAContact(collision1, collision2, gjkResult, maxIterationCount, contactPointData);
}
