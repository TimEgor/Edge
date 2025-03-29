#include "DebugVisualizationDataController.h"

#include "EdgeCommon/Multithreading/LockGuard.h"

void Edge::DebugVisualizationDataController::addPoint(const FloatVector3& position, const NormalizedColorRGB& color)
{
	LockGuard locker(m_pointMutex);
	m_points.emplace_back(position, color);
}

void Edge::DebugVisualizationDataController::addLine(const FloatVector3& position1, const FloatVector3& position2, const NormalizedColorRGB& color)
{
	LockGuard locker(m_lineMutex);
	m_lines.emplace_back(position1, position2, color);
}

void Edge::DebugVisualizationDataController::addArrow(const FloatVector3& position, const FloatVector3& direction, float size, const NormalizedColorRGB& color)
{
	LockGuard locker(m_arrowMutex);
	m_arrows.emplace_back(position, direction, size, color);
}

void Edge::DebugVisualizationDataController::addPolygon(const FloatVector3& position1, const FloatVector3& position2, const FloatVector3& position3, const NormalizedColorRGB& color)
{
	LockGuard locker(m_polygonMutex);
	m_polygons.emplace_back(position1, position2, position3, color);
}

void Edge::DebugVisualizationDataController::addWireframePolygon(const FloatVector3& position1, const FloatVector3& position2, const FloatVector3& position3, const NormalizedColorRGB& color)
{
	LockGuard locker(m_wireframePolygonMutex);
	m_wireframePolygons.emplace_back(position1, position2, position3, color);
}

void Edge::DebugVisualizationDataController::addPlane(const FloatVector3& position, const FloatVector3& normal, const FloatVector3& dir, const FloatVector2& size, const NormalizedColorRGB& color)
{
	LockGuard locker(m_planeMutex);
	m_planes.emplace_back(position, normal, dir, size, color);
}

void Edge::DebugVisualizationDataController::addWireframePlane(const FloatVector3& position, const FloatVector3& normal, const FloatVector3& dir, const FloatVector2& size, const NormalizedColorRGB& color)
{
	LockGuard locker(m_wireframePlaneMutex);
	m_wireframePlanes.emplace_back(position, normal, dir, size, color);
}

void Edge::DebugVisualizationDataController::addBox(const Transform& transform, const NormalizedColorRGB& color)
{
	LockGuard locker(m_boxMutex);
	m_boxes.emplace_back(transform, color);
}

void Edge::DebugVisualizationDataController::addBox(const Transform& transform, const FloatVector3& size, const NormalizedColorRGB& color)
{
	Transform scaledTransform = transform;

	scaledTransform.setAxisX(transform.getAxisX() * size.m_x);
	scaledTransform.setAxisY(transform.getAxisY() * size.m_y);
	scaledTransform.setAxisZ(transform.getAxisZ() * size.m_z);

	addBox(scaledTransform, color);
}

void Edge::DebugVisualizationDataController::addWireframeBox(const Transform& transform, const NormalizedColorRGB& color)
{
	LockGuard locker(m_wireframeBoxMutex);
	m_wireframeBoxes.emplace_back(transform, color);
}

void Edge::DebugVisualizationDataController::addWireframeBox(const Transform& transform, const FloatVector3& size, const NormalizedColorRGB& color)
{
	Transform scaledTransform = transform;

	scaledTransform.setAxisX(transform.getAxisX() * size.m_x);
	scaledTransform.setAxisY(transform.getAxisY() * size.m_y);
	scaledTransform.setAxisZ(transform.getAxisZ() * size.m_z);

	addWireframeBox(scaledTransform, color);
}

void Edge::DebugVisualizationDataController::addSphere(const FloatVector3& position,
	const FloatVector3& directionForward, const FloatVector3& directionUp, float radius, const NormalizedColorRGB& color)
{
	LockGuard locker(m_sphereMutex);
	m_spheres.emplace_back(position, directionForward, directionUp, radius, color);
}

void Edge::DebugVisualizationDataController::addSphere(const FloatVector3& position, float radius, const NormalizedColorRGB& color)
{
	addSphere(position, FloatVector3UnitZ, FloatVector3UnitY, radius, color);
}

void Edge::DebugVisualizationDataController::addSphere(const Transform& transform, float radius, const NormalizedColorRGB& color)
{
	addSphere(transform.getOrigin().getFloatVector3(), transform.getAxisZ().getFloatVector3(), transform.getAxisY().getFloatVector3(), radius, color);
}

void Edge::DebugVisualizationDataController::addWireframeSphere(const FloatVector3& position,
	const FloatVector3& directionForward, const FloatVector3& directionUp, float radius, const NormalizedColorRGB& color)
{
	LockGuard locker(m_wireframeSphereMutex);
	m_wireframeSpheres.emplace_back(position, directionForward, directionUp, radius, color);
}

void Edge::DebugVisualizationDataController::addWireframeSphere(const FloatVector3& position, float radius, const NormalizedColorRGB& color)
{
	addWireframeSphere(position, FloatVector3UnitZ, FloatVector3UnitY, radius, color);
}

void Edge::DebugVisualizationDataController::addWireframeSphere(const Transform& transform, float radius, const NormalizedColorRGB& color)
{
	addWireframeSphere(transform.getOrigin().getFloatVector3(), transform.getAxisZ().getFloatVector3(), transform.getAxisY().getFloatVector3(), radius, color);
}

void Edge::DebugVisualizationDataController::addGrid(const FloatVector3& position, const FloatVector3& normal, const FloatVector3& directionRight,
	const FloatVector2& areaSize, const UInt32Vector2& gridNums, const NormalizedColorRGB& color)
{
	const FloatComputeVector3 directionUp = CrossComputeVector3(FloatComputeVector3(directionRight), FloatComputeVector3(normal));

	const FloatComputeVector3 baseULinePosition = FloatComputeVector3(position) - FloatComputeVector3(directionRight) * areaSize.m_x * 0.5f;
	const float gridUStep = areaSize.m_x / gridNums.m_x;

	const uint32_t uLineCount = gridNums.m_x + 1;
	for (uint32_t uLineIndex = 0; uLineIndex < uLineCount; ++uLineIndex)
	{
		const FloatComputeVector3 baseLineStepPosition = baseULinePosition + FloatComputeVector3(directionRight) * gridUStep * static_cast<float>(uLineIndex);

		FloatComputeVector3 linePosition1 = baseLineStepPosition + directionUp * areaSize.m_y * 0.5f;
		FloatComputeVector3 linePosition2 = baseLineStepPosition - directionUp * areaSize.m_y * 0.5f;

		addLine(linePosition1.getFloatVector3(), linePosition2.getFloatVector3(), color);
	}

	const FloatComputeVector3 baseVLinePosition = FloatComputeVector3(position) - FloatComputeVector3(directionUp) * areaSize.m_y * 0.5f;
	const float gridVStep = areaSize.m_y / gridNums.m_y;

	const uint32_t vLineCount = gridNums.m_y + 1;
	for (uint32_t vLineIndex = 0; vLineIndex < vLineCount; ++vLineIndex)
	{
		const FloatComputeVector3 baseLineStepPosition = baseVLinePosition + directionUp * gridVStep * static_cast<float>(vLineIndex);

		FloatComputeVector3 linePosition1 = baseLineStepPosition + FloatComputeVector3(directionRight) * areaSize.m_x * 0.5f;
		FloatComputeVector3 linePosition2 = baseLineStepPosition - FloatComputeVector3(directionRight) * areaSize.m_x * 0.5f;

		addLine(linePosition1.getFloatVector3(), linePosition2.getFloatVector3(), color);
	}
}

uint32_t Edge::DebugVisualizationDataController::getPointCount() const
{
	SharedLockGuard locker(m_pointMutex);
	return m_points.size();
}

const Edge::DebugVisualizationDataController::PointData& Edge::DebugVisualizationDataController::getPoint(uint32_t index) const
{
	SharedLockGuard locker(m_pointMutex);
	return m_points[index];
}

uint32_t Edge::DebugVisualizationDataController::getLineCount() const
{
	SharedLockGuard locker(m_lineMutex);
	return m_lines.size();
}

const Edge::DebugVisualizationDataController::LineData& Edge::DebugVisualizationDataController::getLine(uint32_t index) const
{
	SharedLockGuard locker(m_lineMutex);
	return m_lines[index];
}

uint32_t Edge::DebugVisualizationDataController::getArrowCount() const
{
	SharedLockGuard locker(m_arrowMutex);
	return m_arrows.size();
}

const Edge::DebugVisualizationDataController::ArrowData& Edge::DebugVisualizationDataController::getArrow(uint32_t index) const
{
	SharedLockGuard locker(m_arrowMutex);
	return m_arrows[index];
}

uint32_t Edge::DebugVisualizationDataController::getPolygonCount() const
{
	SharedLockGuard locker(m_polygonMutex);
	return m_polygons.size();
}

const Edge::DebugVisualizationDataController::PolygonData& Edge::DebugVisualizationDataController::getPolygon(uint32_t index) const
{
	SharedLockGuard locker(m_polygonMutex);
	return m_polygons[index];
}

uint32_t Edge::DebugVisualizationDataController::getWireframePolygonCount() const
{
	SharedLockGuard locker(m_wireframePolygonMutex);
	return m_wireframePolygons.size();
}

const Edge::DebugVisualizationDataController::PolygonData& Edge::DebugVisualizationDataController::getWireframePolygon(uint32_t index) const
{
	SharedLockGuard locker(m_wireframePolygonMutex);
	return m_wireframePolygons[index];
}

uint32_t Edge::DebugVisualizationDataController::getPlaneCount() const
{
	SharedLockGuard locker(m_planeMutex);
	return m_planes.size();
}

const Edge::DebugVisualizationDataController::PlaneData& Edge::DebugVisualizationDataController::getPlane(uint32_t index) const
{
	SharedLockGuard locker(m_planeMutex);
	return m_planes[index];
}

uint32_t Edge::DebugVisualizationDataController::getWireframePlaneCount() const
{
	SharedLockGuard locker(m_wireframePlaneMutex);
	return m_wireframePlanes.size();
}

const Edge::DebugVisualizationDataController::PlaneData& Edge::DebugVisualizationDataController::getWireframePlane(uint32_t index) const
{
	SharedLockGuard locker(m_wireframePlaneMutex);
	return m_wireframePlanes[index];
}

uint32_t Edge::DebugVisualizationDataController::getBoxCount() const
{
	SharedLockGuard locker(m_boxMutex);
	return m_boxes.size();
}

const Edge::DebugVisualizationDataController::BoxData& Edge::DebugVisualizationDataController::getBox(uint32_t index) const
{
	SharedLockGuard locker(m_boxMutex);
	return m_boxes[index];
}

uint32_t Edge::DebugVisualizationDataController::getWireframeBoxCount() const
{
	SharedLockGuard locker(m_wireframeBoxMutex);
	return m_wireframeBoxes.size();
}

const Edge::DebugVisualizationDataController::BoxData& Edge::DebugVisualizationDataController::getWireframeBox(uint32_t index) const
{
	SharedLockGuard locker(m_wireframeBoxMutex);
	return m_wireframeBoxes[index];
}

uint32_t Edge::DebugVisualizationDataController::getSphereCount() const
{
	SharedLockGuard locker(m_sphereMutex);
	return m_spheres.size();
}

const Edge::DebugVisualizationDataController::SphereData& Edge::DebugVisualizationDataController::getSphere(uint32_t index) const
{
	SharedLockGuard locker(m_sphereMutex);
	return m_spheres[index];
}

uint32_t Edge::DebugVisualizationDataController::getWireframeSphereCount() const
{
	SharedLockGuard locker(m_wireframeSphereMutex);
	return m_wireframeSpheres.size();
}

const Edge::DebugVisualizationDataController::SphereData& Edge::DebugVisualizationDataController::getWireframeSphere(uint32_t index) const
{
	SharedLockGuard locker(m_wireframeSphereMutex);
	return m_wireframeSpheres[index];
}

void Edge::DebugVisualizationDataController::clear()
{
	{
		LockGuard locker(m_pointMutex);
		m_points.clear();
	}

	{
		LockGuard locker(m_lineMutex);
		m_lines.clear();
	}

	{
		LockGuard locker(m_arrowMutex);
		m_arrows.clear();
	}

	{
		LockGuard locker(m_polygonMutex);
		m_polygons.clear();
	}

	{
		LockGuard locker(m_wireframePolygonMutex);
		m_wireframePolygons.clear();
	}

	{
		LockGuard locker(m_planeMutex);
		m_planes.clear();
	}

	{
		LockGuard locker(m_wireframePlaneMutex);
		m_wireframePlanes.clear();
	}

	{
		LockGuard locker(m_boxMutex);
		m_boxes.clear();
	}

	{
		LockGuard locker(m_wireframeBoxMutex);
		m_wireframeBoxes.clear();
	}

	{
		LockGuard locker(m_sphereMutex);
		m_spheres.clear();
	}

	{
		LockGuard locker(m_wireframeSphereMutex);
		m_wireframeSpheres.clear();
	}
}
