#pragma once

#include "EdgeCommon/Math/Vector.h"

#include <vector>

namespace Edge
{
	namespace ClippingPoly
	{
		void ClipPolyVsPlane(const std::vector<FloatVector3>& inPolygonToClip, const FloatVector3& inPlaneOrigin, const FloatVector3& inPlaneNormal, std::vector<FloatVector3>& outClippedPolygon);
		void ClipPolyVsPoly(const std::vector<FloatVector3>& inPolygonToClip, const std::vector<FloatVector3>& inClippingPolygon, const FloatVector3& inClippingPolygonNormal, std::vector<FloatVector3>& outClippedPolygon);
		void ClipPolyVsEdge(const std::vector<FloatVector3>& inPolygonToClip, const FloatVector3& inEdgeVertex1, const FloatVector3& inEdgeVertex2, const FloatVector3& inClippingEdgeNormal, std::vector<FloatVector3>& outClippedPolygon);
	}
}
