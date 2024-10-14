#include "VoronoiSimplex.h"

void Edge::VoronoiSimplex::addPoint(const Point& point)
{
	EDGE_ASSERT(m_pointCount < 4);

	for (uint32_t pointIndex = m_pointCount; pointIndex > 0; pointIndex--) {
		m_points[pointIndex] = m_points[pointIndex - 1];
	}

	m_points[0] = point;

	++m_pointCount;
}

void Edge::VoronoiSimplex::setPoint(const Point& point)
{
	m_pointCount = 1;
	m_points[0] = point;
}

void Edge::VoronoiSimplex::setPoints(const Point& point1, const Point& point2)
{
	m_pointCount = 2;
	m_points[0] = point1;
	m_points[1] = point2;
}

void Edge::VoronoiSimplex::setPoints(const Point& point1, const Point& point2, const Point& point3)
{
	m_pointCount = 3;
	m_points[0] = point1;
	m_points[1] = point2;
	m_points[2] = point3;
}

void Edge::VoronoiSimplex::setPoints(const Point& point1, const Point& point2, const Point& point3, const Point& point4)
{
	m_pointCount = 4;
	m_points[0] = point1;
	m_points[1] = point2;
	m_points[2] = point3;
	m_points[3] = point4;
}

const Edge::VoronoiSimplex::Point& Edge::VoronoiSimplex::getPoint(uint32_t index) const
{
	EDGE_ASSERT(index <= 4);

	return m_points[index];
}

void Edge::VoronoiSimplex::clear()
{
	m_pointCount = 0;
}
