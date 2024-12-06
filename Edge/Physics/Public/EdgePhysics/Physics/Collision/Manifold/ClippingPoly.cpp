#include "ClippingPoly.h"

#include "EdgeCommon/Math/ComputeVector.h"

void Edge::ClippingPoly::ClipPolyVsPlane(const std::vector<FloatVector3>& inPolygonToClip,
	const FloatVector3& inPlaneOrigin, const FloatVector3& inPlaneNormal, std::vector<FloatVector3>& outClippedPolygon)
{
	const uint32_t inPolygonSize = inPolygonToClip.size();

	EDGE_ASSERT(inPolygonSize >= 2);
	EDGE_ASSERT(outClippedPolygon.empty());

	FloatVector3 e1 = inPolygonToClip[inPolygonSize - 1];
	float prev_num = DotVector3((inPlaneOrigin - e1), inPlaneNormal);
	bool prev_inside = prev_num < 0.0f;

	for (uint32_t polyIndex = 0; polyIndex < inPolygonSize; ++polyIndex)
	{
		const FloatVector3 e2 = inPolygonToClip[polyIndex];
		const float num = DotVector3(inPlaneOrigin - e2, inPlaneNormal);
		bool cur_inside = num < 0.0f;

		if (cur_inside != prev_inside)
		{
			const ComputeVector e12 = e2 - e1;
			const float denom = DotVector3(e12, inPlaneNormal);
			if (denom != 0.0f)
			{
				outClippedPolygon.push_back((e1 + (prev_num / denom) * e12).getFloatVector3());
			}
			else
			{
				cur_inside = prev_inside;
			}
		}

		if (cur_inside)
		{
			outClippedPolygon.push_back(e2);
		}

		prev_num = num;
		prev_inside = cur_inside;
		e1 = e2;
	}
}

void Edge::ClippingPoly::ClipPolyVsPoly(const std::vector<FloatVector3>& inPolygonToClip,
	const std::vector<FloatVector3>& inClippingPolygon, const FloatVector3& inClippingPolygonNormal,
	std::vector<FloatVector3>& outClippedPolygon)
{
	const uint32_t inPolygonSize = inClippingPolygon.size();

	EDGE_ASSERT(inPolygonToClip.size() >= 2);
	EDGE_ASSERT(inPolygonSize >= 3);

	std::vector<FloatVector3> tmp_vertices[2];
	int tmp_vertices_idx = 0;

	for (uint32_t polyIndex = 0; polyIndex < inPolygonSize; ++polyIndex)
	{
		const ComputeVector clip_e1 = inClippingPolygon[polyIndex];
		const ComputeVector clip_e2 = inClippingPolygon[(polyIndex + 1) % inPolygonSize];
		const ComputeVector clip_normal = CrossVector3(inClippingPolygonNormal, clip_e2 - clip_e1);

		const std::vector<FloatVector3>& src_polygon = (polyIndex == 0) ? inPolygonToClip : tmp_vertices[tmp_vertices_idx];
		tmp_vertices_idx ^= 1;
		std::vector<FloatVector3>& tgt_polygon = (polyIndex == inPolygonSize - 1) ? outClippedPolygon : tmp_vertices[tmp_vertices_idx];
		tgt_polygon.clear();

		ClipPolyVsPlane(src_polygon, clip_e1.getFloatVector3(), clip_normal.getFloatVector3(), tgt_polygon);

		if (tgt_polygon.size() < 3)
		{
			outClippedPolygon.clear();
			break;
		}
	}
}

void Edge::ClippingPoly::ClipPolyVsEdge(const std::vector<FloatVector3>& inPolygonToClip,
	const FloatVector3& inEdgeVertex1, const FloatVector3& inEdgeVertex2,
	const FloatVector3& inClippingEdgeNormal, std::vector<FloatVector3>& outClippedPolygon)
{
	const uint32_t inPolygonSize = inPolygonToClip.size();

	EDGE_ASSERT(inPolygonSize >= 3);
	EDGE_ASSERT(outClippedPolygon.empty());

	const ComputeVector edge = inEdgeVertex2 - inEdgeVertex1;
	const ComputeVector edgeNormal = CrossVector3(inClippingEdgeNormal, edge);

	const ComputeVector polygonNormal = CrossVector3(inPolygonToClip[2] - inPolygonToClip[0], inPolygonToClip[1] - inPolygonToClip[0]);
	const float polygonNormalLenSq = polygonNormal.getLength3Sqr();

	const ComputeVector v1 = DotVector3(inEdgeVertex1 + polygonNormal, inPolygonToClip[0] - inEdgeVertex1) * polygonNormal / polygonNormalLenSq;
	const ComputeVector v2 = DotVector3(inEdgeVertex2 + polygonNormal, inPolygonToClip[0] - inEdgeVertex2) * polygonNormal / polygonNormalLenSq;

	const ComputeVector v12 = v2 - v1;
	const float v12_len_sq = v12.getLength3Sqr();

	ComputeVector e1 = inPolygonToClip[inPolygonSize - 1];

	float prev_num = DotVector3(inEdgeVertex1 - e1, edgeNormal);
	bool prev_inside = prev_num < 0.0f;

	for (uint32_t polyIndex = 0; polyIndex < inPolygonSize; ++polyIndex)
	{
		const ComputeVector e2 = inPolygonToClip[polyIndex];
		const float num = DotVector3(inEdgeVertex1 - e2, edgeNormal);
		const bool cur_inside = num < 0.0f;

		if (cur_inside != prev_inside)
		{
			const ComputeVector e12 = e2 - e1;
			const float denom = DotVector3(e12, edgeNormal);
			const ComputeVector clipped_point = denom != 0.0f ? e1 + (prev_num / denom) * e12 : e1;

			const float projection = DotVector3(clipped_point - v1, v12);
			if (projection < 0.0f)
			{
				outClippedPolygon.push_back(v1.getFloatVector3());
			}
			else if (projection > v12_len_sq)
			{
				outClippedPolygon.push_back(v2.getFloatVector3());
			}
			else
			{
				outClippedPolygon.push_back(clipped_point.getFloatVector3());
			}
		}

		prev_num = num;
		prev_inside = cur_inside;
		e1 = e2;
	}
}
