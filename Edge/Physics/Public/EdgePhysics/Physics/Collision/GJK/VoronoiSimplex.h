#pragma once

#include "EdgeCommon/Math/ComputeVector3.h"

namespace Edge
{
	class VoronoiSimplex final
	{
	public:
		struct Point final
		{
			ComputeVector3 m_minkowskiDiff = ComputeVector3Zero;
			ComputeVector3 m_pointCollision1 = ComputeVector3Zero;
			ComputeVector3 m_pointCollision2 = ComputeVector3Zero;
		};

	private:
		Point m_points[4];
		uint32_t m_pointCount = 0;

	public:
		VoronoiSimplex() = default;

		void addPoint(const Point& point);
		void setPoint(const Point& point);
		void setPoints(const Point& point1, const Point& point2);
		void setPoints(const Point& point1, const Point& point2, const Point& point3);
		void setPoints(const Point& point1, const Point& point2, const Point& point3, const Point& point4);

		uint32_t getPointCount() const { return m_pointCount; }

		const Point& getPoint(uint32_t index) const;

		void clear();
	};
}
