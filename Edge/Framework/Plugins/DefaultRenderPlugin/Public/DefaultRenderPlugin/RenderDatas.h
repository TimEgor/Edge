#pragma once

#include "PackedColor.h"
#include "RenderDataBufferCache.h"

namespace Edge
{
	class GPUBuffer;

	class VertexShader;
	class PixelShader;

	class InputLayout;
}

namespace EdgeDefRender
{
	struct PointRenderData final
	{
		struct PointData final
		{
			Edge::FloatVector3 m_position = Edge::FloatVector3Zero;
			PackedColor m_color;

			PointData() = default;

			PointData(const Edge::FloatVector3& position, const Edge::FloatVector4& color)
				: m_position(position),
				  m_color(color) {}
		};

		Edge::VertexShader* m_vertexShader = nullptr;
		Edge::PixelShader* m_pixelShader = nullptr;

		Edge::InputLayout* m_inputLayout = nullptr;

		RenderDataBufferCache m_pointData;

		uint32_t m_pointCount = 0;
	};

	struct LineRenderData final
	{
		struct VertexData final
		{
			Edge::FloatVector3 m_position = Edge::FloatVector3Zero;
			PackedColor m_color;


			VertexData() = default;

			VertexData(const Edge::FloatVector3& position, const Edge::FloatVector4& color)
				: m_position(position),
				  m_color(color) {}
		};

		struct LineData final
		{
			VertexData m_point1;
			VertexData m_point2;
		};

		Edge::VertexShader* m_vertexShader = nullptr;
		Edge::PixelShader* m_pixelShader = nullptr;

		Edge::InputLayout* m_inputLayout = nullptr;

		RenderDataBufferCache m_lineData;

		uint32_t m_lineCount = 0;
	};

	struct PolygonRenderData final
	{
		struct VertexData final
		{
			Edge::FloatVector3 m_position = Edge::FloatVector3Zero;
			Edge::FloatVector3 m_normal = Edge::FloatVector3Zero;
			Edge::FloatVector2 m_uv = Edge::FloatVector2Zero;
			PackedColor m_color;


			VertexData() = default;

			VertexData(
				const Edge::FloatVector3& position,
				const Edge::FloatVector4& color,
				const Edge::FloatVector3& normal,
				const Edge::FloatVector2& uv
			)
				: m_position(position),
				  m_normal(normal),
				  m_color(color),
				  m_uv(uv) {}
		};

		struct PolygonData final
		{
			VertexData m_point1;
			VertexData m_point2;
			VertexData m_point3;
		};

		Edge::VertexShader* m_vertexShader = nullptr;
		Edge::PixelShader* m_pixelShader = nullptr;

		Edge::InputLayout* m_inputLayout = nullptr;

		RenderDataBufferCache m_polygonData;

		uint32_t m_polygonCount = 0;
	};

	struct PlaneRenderData final
	{
		struct PlaneData final
		{
			Edge::FloatVector3 m_position = Edge::FloatVector3Zero;
			float m_sizeX = 0.0f;
			Edge::FloatVector3 m_normal = Edge::FloatVector3UnitY;
			float m_sizeY = 0.0f;
			Edge::FloatVector3 m_directionRight = Edge::FloatVector3UnitX;
			PackedColor m_color;

			PlaneData() = default;

			PlaneData(
				const Edge::FloatVector3& position,
				const Edge::FloatVector3& normal,
				const Edge::FloatVector3& directionRight,
				const Edge::FloatVector2& size,
				const Edge::FloatVector4& color
			)
				: m_position(position),
				  m_sizeX(size.m_x),
				  m_normal(normal),
				  m_sizeY(size.m_y),
				  m_directionRight(directionRight),
				  m_color(color) {}
		};

		Edge::VertexShader* m_vertexShader = nullptr;
		Edge::PixelShader* m_pixelShader = nullptr;

		Edge::InputLayout* m_inputLayout = nullptr;

		RenderDataBufferCache m_planeData;

		uint32_t m_planeCount = 0;
	};

	struct BoxRenderData final
	{
		Edge::VertexShader* m_vertexShader = nullptr;
		Edge::PixelShader* m_pixelShader = nullptr;

		Edge::InputLayout* m_inputLayout = nullptr;

		Edge::GPUBuffer* m_vertexBuffer = nullptr;
		Edge::GPUBuffer* m_indexBuffer = nullptr;

		RenderDataBufferCache m_transformData;

		uint32_t m_boxCount = 0;
	};

	struct SphereRenderData final
	{
		struct SphereData final
		{
			Edge::FloatVector3 m_position = Edge::FloatVector3Zero;
			Edge::FloatVector3 m_directionForward = Edge::FloatVector3Zero;
			Edge::FloatVector3 m_directionUp = Edge::FloatVector3Zero;
			float m_radius;
			PackedColor m_color;

			SphereData() = default;

			SphereData(
				const Edge::FloatVector3& position,
				const Edge::FloatVector3& directionForward,
				const Edge::FloatVector3& directionUp,
				float radius,
				const Edge::FloatVector4& color
			)
				: m_position(position),
				  m_directionForward(directionForward),
				  m_directionUp(directionUp),
				  m_color(color),
				  m_radius(radius) {}
		};

		Edge::VertexShader* m_vertexShader = nullptr;
		Edge::PixelShader* m_pixelShader = nullptr;

		Edge::InputLayout* m_inputLayout = nullptr;

		Edge::GPUBuffer* m_vertexBuffer = nullptr;
		Edge::GPUBuffer* m_indexBuffer = nullptr;

		RenderDataBufferCache m_sphereData;

		uint32_t m_sphereCount = 0;
		uint32_t m_indexCountPerSphere = 0;
	};

	struct TextRenderData final
	{
		struct VertexData final
		{
			Edge::FloatVector3 m_position = Edge::FloatVector3Zero;
			Edge::FloatVector2 m_uv = Edge::FloatVector2Zero;
			PackedColor m_color;

			VertexData() = default;

			VertexData(const Edge::FloatVector3& position, const Edge::FloatVector2& uv, const Edge::FloatVector4& color)
				: m_position(position),
				  m_uv(uv),
				  m_color(color) {}
		};

		struct GlyphData final
		{
			VertexData m_vertex1;
			VertexData m_vertex2;
			VertexData m_vertex3;

			VertexData m_vertex4;
			VertexData m_vertex5;
			VertexData m_vertex6;

			GlyphData() = default;

			GlyphData(
				const VertexData& v1,
				const VertexData& v2,
				const VertexData& v3,
				const VertexData& v4
			)
				: m_vertex1(v1),
				  m_vertex2(v2),
				  m_vertex3(v3),
				  m_vertex4(v3),
				  m_vertex5(v2),
				  m_vertex6(v4) {}
		};

		Edge::VertexShader* m_vertexShader = nullptr;
		Edge::PixelShader* m_pixelShader = nullptr;

		Edge::InputLayout* m_inputLayout = nullptr;

		RenderDataBufferCache m_glyphData;

		uint32_t m_glyphCount = 0;
	};
}
