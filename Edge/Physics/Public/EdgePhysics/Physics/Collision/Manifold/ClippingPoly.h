#pragma once

#include "EdgeCommon/Math/ComputeVector3.h"

#include <vector>

namespace Edge
{
	namespace ClippingPoly
	{
		void ClipPolyVsPlane(const std::vector<ComputeVector3>& inPolygonToClip, const ComputeVector3& inPlaneOrigin, const ComputeVector3& inPlaneNormal, std::vector<ComputeVector3>& outClippedPolygon);
		void ClipPolyVsPoly(const std::vector<ComputeVector3>& inPolygonToClip, const std::vector<ComputeVector3>& inClippingPolygon, const ComputeVector3& inClippingPolygonNormal, std::vector<ComputeVector3>& outClippedPolygon);
		void ClipPolyVsEdge(const std::vector<ComputeVector3>& inPolygonToClip, const ComputeVector3& inEdgeVertex1, const ComputeVector3& inEdgeVertex2, const ComputeVector3& inClippingEdgeNormal, std::vector<ComputeVector3>& outClippedPolygon);
	}
}
