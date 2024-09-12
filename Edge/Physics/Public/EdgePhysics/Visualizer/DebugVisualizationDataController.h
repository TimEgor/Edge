#pragma once

#include "EdgeCommon/Math/Color.h"
#include "EdgeCommon/Math/Transform.h"
#include "EdgeCommon/Math/Vector.h"
#include "EdgeCommon/Multithreading/Mutex.h"
#include "EdgeCommon/Patterns/NonCopyable.h"

#include <vector>


namespace Edge
{
	class DebugVisualizationDataController : public NonCopyable
	{
	public:
		struct PointData final
		{
			FloatVector3 m_position;
			NormalizedColorRGB m_color;

			PointData(const FloatVector3& position, const NormalizedColorRGB& color)
				: m_position(position), m_color(color) {}
		};

		struct LineData final
		{
			FloatVector3 m_position1;
			FloatVector3 m_position2;
			NormalizedColorRGB m_color;

			LineData(const FloatVector3& position1, const FloatVector3& position2, const NormalizedColorRGB& color)
				: m_position1(position1), m_position2(position2), m_color(color) {}
		};

		struct ArrowData final
		{
			FloatVector3 m_position;
			FloatVector3 m_direction;
			NormalizedColorRGB m_color;
			float m_size;

			ArrowData(const FloatVector3& position, const FloatVector3& direction, float size, const NormalizedColorRGB& color)
				: m_position(position), m_direction(direction), m_color(color), m_size(size) {}
		};

		struct PolygonData final
		{
			FloatVector3 m_position1;
			FloatVector3 m_position2;
			FloatVector3 m_position3;
			NormalizedColorRGB m_color;

			PolygonData(const FloatVector3& position1, const FloatVector3& position2, const FloatVector3& position3, const NormalizedColorRGB& color)
				: m_position1(position1), m_position2(position2), m_position3(position3), m_color(color) {}
		};

		struct PlaneData final
		{
			FloatVector3 m_position;
			FloatVector3 m_normal;
			FloatVector3 m_directionRight;
			NormalizedColorRGB m_color;
			FloatVector2 m_size;

			PlaneData(const FloatVector3& position, const FloatVector3& normal, const FloatVector3& directionRight,
				const FloatVector2& size, const NormalizedColorRGB& color)
				: m_position(position), m_normal(normal), m_directionRight(directionRight),
				m_size(size), m_color(color) {}
		};

		struct BoxData final
		{
			Transform m_transform;
			NormalizedColorRGB m_color;

			BoxData(const Transform& transform, const NormalizedColorRGB& color)
				: m_transform(transform), m_color(color) {}
		};

		struct SphereData final
		{
			FloatVector3 m_position;
			FloatVector3 m_directionForward;
			FloatVector3 m_directionUp;
			NormalizedColorRGB m_color;
			float m_radius;

			SphereData(const FloatVector3& position, const FloatVector3& directionForward,
				const FloatVector3& directionUp, float radius, const NormalizedColorRGB& color)
				: m_position(position), m_directionForward(directionForward),
				m_directionUp(directionUp), m_color(color), m_radius(radius) {}
		};

	private:
		using PointContainer = std::vector<PointData>;
		using LineContainer = std::vector<LineData>;
		using ArrowContainer = std::vector<ArrowData>;
		using PolygonContainer = std::vector<PolygonData>;
		using PlaneContainer = std::vector<PlaneData>;
		using BoxContainer = std::vector<BoxData>;
		using SphereContainer = std::vector<SphereData>;

		PointContainer m_points;
		LineContainer m_lines;
		ArrowContainer m_arrows;
		PolygonContainer m_polygons;
		PolygonContainer m_wireframePolygons;
		PlaneContainer m_planes;
		PlaneContainer m_wireframePlanes;
		BoxContainer m_boxes;
		BoxContainer m_wireframeBoxes;
		SphereContainer m_spheres;
		SphereContainer m_wireframeSpheres;

		mutable SharedMutex m_pointMutex;
		mutable SharedMutex m_lineMutex;
		mutable SharedMutex m_arrowMutex;
		mutable SharedMutex m_polygonMutex;
		mutable SharedMutex m_wireframePolygonMutex;
		mutable SharedMutex m_planeMutex;
		mutable SharedMutex m_wireframePlaneMutex;
		mutable SharedMutex m_boxMutex;
		mutable SharedMutex m_wireframeBoxMutex;
		mutable SharedMutex m_sphereMutex;
		mutable SharedMutex m_wireframeSphereMutex;

	public:
		DebugVisualizationDataController() = default;

		void addPoint(const FloatVector3& position, const NormalizedColorRGB& color = NormalizedColorWhite);
		void addLine(const FloatVector3& position1, const FloatVector3& position2, const NormalizedColorRGB& color = NormalizedColorWhite);
		void addArrow(const FloatVector3& position, const FloatVector3& direction, float size, const NormalizedColorRGB& color = NormalizedColorWhite);

		void addPolygon(const FloatVector3& position1, const FloatVector3& position2, const FloatVector3& position3, const NormalizedColorRGB& color = NormalizedColorWhite);
		void addWireframePolygon(const FloatVector3& position1, const FloatVector3& position2, const FloatVector3& position3, const NormalizedColorRGB& color = NormalizedColorWhite);

		void addPlane(const FloatVector3& position, const FloatVector3& normal, const FloatVector3& dir, const FloatVector2& size, const NormalizedColorRGB& color = NormalizedColorWhite);
		void addWireframePlane(const FloatVector3& position, const FloatVector3& normal, const FloatVector3& dir, const FloatVector2& size, const NormalizedColorRGB& color = NormalizedColorWhite);

		void addBox(const Transform& transform, const NormalizedColorRGB& color = NormalizedColorWhite);
		void addWireframeBox(const Transform& transform, const NormalizedColorRGB& color = NormalizedColorWhite);

		void addSphere(const FloatVector3& position, const FloatVector3& directionForward, const FloatVector3& directionUp, float radius, const NormalizedColorRGB& color = NormalizedColorWhite);
		void addWireframeSphere(const FloatVector3& position, const FloatVector3& directionForward, const FloatVector3& directionUp, float radius, const NormalizedColorRGB& color = NormalizedColorWhite);

		void addGrid(const FloatVector3& position, const FloatVector3& normal, const FloatVector3& directionRight, const FloatVector2& areaSize, const UInt32Vector2& gridNums, const NormalizedColorRGB& color = NormalizedColorWhite);

		uint32_t getPointCount() const;
		const PointData& getPoint(uint32_t index) const;

		uint32_t getLineCount() const;
		const LineData& getLine(uint32_t index) const;

		uint32_t getArrowCount() const;
		const ArrowData& getArrow(uint32_t index) const;

		uint32_t getPolygonCount() const;
		const PolygonData& getPolygon(uint32_t index) const;

		uint32_t getWireframePolygonCount() const;
		const PolygonData& getWireframePolygon(uint32_t index) const;

		uint32_t getPlaneCount() const;
		const PlaneData& getPlane(uint32_t index) const;

		uint32_t getWireframePlaneCount() const;
		const PlaneData& getWireframePlane(uint32_t index) const;

		uint32_t getBoxCount() const;
		const BoxData& getBox(uint32_t index) const;

		uint32_t getWireframeBoxCount() const;
		const BoxData& getWireframeBox(uint32_t index) const;

		uint32_t getSphereCount() const;
		const SphereData& getSphere(uint32_t index) const;

		uint32_t getWireframeSphereCount() const;
		const SphereData& getWireframeSphere(uint32_t index) const;

		void clear();
	};
}
