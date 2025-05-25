#include "ClippingPoly.h"

void Edge::ClippingPoly::ClipPolyVsPlane(const std::vector<ComputeVector3>& inPolygonToClip,
	const ComputeVector3& inPlaneOrigin, const ComputeVector3& inPlaneNormal, std::vector<ComputeVector3>& outClippedPolygon)
{
	const uint32_t inPolygonSize = inPolygonToClip.size();

	EDGE_ASSERT(inPolygonSize >= 2);
	EDGE_ASSERT(outClippedPolygon.empty());

	ComputeVector3 e1 = inPolygonToClip[inPolygonSize - 1];
	ComputeValueType prev_num = DotComputeVector3((inPlaneOrigin - e1), inPlaneNormal);
	bool prev_inside = prev_num < ComputeValueType(0.0);

	for (uint32_t polyIndex = 0; polyIndex < inPolygonSize; ++polyIndex)
	{
		const ComputeVector3 e2 = inPolygonToClip[polyIndex];
		const ComputeValueType num = DotComputeVector3(inPlaneOrigin - e2, inPlaneNormal);
		bool cur_inside = num < 0.0f;

		if (cur_inside != prev_inside)
		{
			const ComputeVector3 e12 = e2 - e1;
			const ComputeValueType denom = DotComputeVector3(e12, inPlaneNormal);
			if (denom != ComputeValueType(0.0))
			{
				outClippedPolygon.push_back(e1 + (prev_num / denom) * e12);
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

void Edge::ClippingPoly::ClipPolyVsPoly(const std::vector<ComputeVector3>& inPolygonToClip,
	const std::vector<ComputeVector3>& inClippingPolygon, const ComputeVector3& inClippingPolygonNormal,
	std::vector<ComputeVector3>& outClippedPolygon)
{
	const uint32_t inPolygonSize = inClippingPolygon.size();

	EDGE_ASSERT(inPolygonToClip.size() >= 2);
	EDGE_ASSERT(inPolygonSize >= 3);

	std::vector<ComputeVector3> tmp_vertices[2];
	int tmp_vertices_idx = 0;

	for (uint32_t polyIndex = 0; polyIndex < inPolygonSize; ++polyIndex)
	{
		const ComputeVector3 clip_e1 = inClippingPolygon[polyIndex];
		const ComputeVector3 clip_e2 = inClippingPolygon[(polyIndex + 1) % inPolygonSize];
		const ComputeVector3 clip_normal = CrossComputeVector3(inClippingPolygonNormal, clip_e2 - clip_e1);

		const std::vector<ComputeVector3>& src_polygon = (polyIndex == 0) ? inPolygonToClip : tmp_vertices[tmp_vertices_idx];
		tmp_vertices_idx ^= 1;
		std::vector<ComputeVector3>& tgt_polygon = (polyIndex == inPolygonSize - 1) ? outClippedPolygon : tmp_vertices[tmp_vertices_idx];
		tgt_polygon.clear();

		ClipPolyVsPlane(src_polygon, clip_e1, clip_normal, tgt_polygon);

		if (tgt_polygon.size() < 3)
		{
			outClippedPolygon.clear();
			break;
		}
	}
}

void Edge::ClippingPoly::ClipPolyVsEdge(const std::vector<ComputeVector3>& inPolygonToClip,
	const ComputeVector3& inEdgeVertex1, const ComputeVector3& inEdgeVertex2,
	const ComputeVector3& inClippingEdgeNormal, std::vector<ComputeVector3>& outClippedPolygon)
{
	const uint32_t inPolygonSize = inPolygonToClip.size();

	EDGE_ASSERT(inPolygonSize >= 3);
	EDGE_ASSERT(outClippedPolygon.empty());

	const ComputeVector3 edge = inEdgeVertex2 - inEdgeVertex1;
	const ComputeVector3 edgeNormal = CrossComputeVector3(inClippingEdgeNormal, edge);

	const ComputeVector3 polygonNormal = CrossComputeVector3(inPolygonToClip[2] - inPolygonToClip[0], inPolygonToClip[1] - inPolygonToClip[0]);
	const ComputeValueType polygonNormalLenSq = polygonNormal.getLength();

	const ComputeVector3 v1 = DotComputeVector3(inEdgeVertex1 + polygonNormal, inPolygonToClip[0] - inEdgeVertex1) * polygonNormal / polygonNormalLenSq;
	const ComputeVector3 v2 = DotComputeVector3(inEdgeVertex2 + polygonNormal, inPolygonToClip[0] - inEdgeVertex2) * polygonNormal / polygonNormalLenSq;

	const ComputeVector3 v12 = v2 - v1;
	const ComputeValueType v12_len_sq = v12.getLength();

	ComputeVector3 e1 = inPolygonToClip[inPolygonSize - 1];

	ComputeValueType prev_num = DotComputeVector3(inEdgeVertex1 - e1, edgeNormal);
	bool prev_inside = prev_num < ComputeValueType(0.0);

	for (uint32_t polyIndex = 0; polyIndex < inPolygonSize; ++polyIndex)
	{
		const ComputeVector3 e2 = inPolygonToClip[polyIndex];
		const ComputeValueType num = DotComputeVector3(inEdgeVertex1 - e2, edgeNormal);
		const bool cur_inside = num < ComputeValueType(0.0);

		if (cur_inside != prev_inside)
		{
			const ComputeVector3 e12 = e2 - e1;
			const ComputeValueType denom = DotComputeVector3(e12, edgeNormal);
			const ComputeVector3 clipped_point = denom != ComputeValueType(0.0) ? e1 + (prev_num / denom) * e12 : e1;

			const ComputeValueType projection = DotComputeVector3(clipped_point - v1, v12);
			if (projection < 0.0f)
			{
				outClippedPolygon.push_back(v1);
			}
			else if (projection > v12_len_sq)
			{
				outClippedPolygon.push_back(v2);
			}
			else
			{
				outClippedPolygon.push_back(clipped_point);
			}
		}

		prev_num = num;
		prev_inside = cur_inside;
		e1 = e2;
	}
}
