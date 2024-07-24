#pragma once

#include "PackedColor.h"
#include "RenderDataBufferCache.h"

namespace TS {
	class GPUBuffer;

	class VertexShader;
	class PixelShader;

	class InputLayout;
}

namespace TS_DEF_RENDERER
{
	struct PointRenderData final
	{
		struct PointData final
		{
			TS::FloatVector3 m_position = TS::FloatVector3Zero;
			PackedColor m_color;

			PointData() = default;
			PointData(const TS::FloatVector3& position, const TS::FloatVector4& color)
				: m_position(position), m_color(color) {}
		};

		TS::VertexShader* m_vertexShader = nullptr;
		TS::PixelShader* m_pixelShader = nullptr;

		TS::InputLayout* m_inputLayout = nullptr;

		RenderDataBufferCache m_pointData;

		uint32_t m_pointCount = 0;
	};

	struct LineRenderData final
	{
		struct VertexData final
		{
			TS::FloatVector3 m_position = TS::FloatVector3Zero;
			PackedColor m_color;


			VertexData() = default;
			VertexData(const TS::FloatVector3& position, const TS::FloatVector4& color)
				: m_position(position), m_color(color) {}
		};

		struct LineData final
		{
			VertexData m_point1;
			VertexData m_point2;
		};

		TS::VertexShader* m_vertexShader = nullptr;
		TS::PixelShader* m_pixelShader = nullptr;

		TS::InputLayout* m_inputLayout = nullptr;

		RenderDataBufferCache m_lineData;

		uint32_t m_lineCount = 0;
	};

	struct PlaneRenderData final
	{
		struct PlaneData final
		{
			TS::FloatVector3 m_position = TS::FloatVector3Zero;
			float m_sizeX = 0.0f;
			TS::FloatVector3 m_normal = TS::FloatVector3UnitY;
			float m_sizeY = 0.0f;
			TS::FloatVector3 m_directionRight = TS::FloatVector3UnitX;
			PackedColor m_color;

			PlaneData() = default;
			PlaneData(const TS::FloatVector3& position, const TS::FloatVector3& normal, const TS::FloatVector3& directionRight,
				const TS::FloatVector2& size, const TS::FloatVector4& color)
				: m_position(position), m_sizeX(size.m_x), m_normal(normal),
				m_sizeY(size.m_y), m_directionRight(directionRight), m_color(color) {}
		};

		TS::VertexShader* m_vertexShader = nullptr;
		TS::PixelShader* m_pixelShader = nullptr;

		TS::InputLayout* m_inputLayout = nullptr;

		RenderDataBufferCache m_planeData;

		uint32_t m_planeCount = 0;
	};

	struct BoxRenderData final
	{
		TS::VertexShader* m_vertexShader = nullptr;
		TS::PixelShader* m_pixelShader = nullptr;

		TS::InputLayout* m_inputLayout = nullptr;

		TS::GPUBuffer* m_vertexBuffer = nullptr;
		TS::GPUBuffer* m_indexBuffer = nullptr;

		RenderDataBufferCache m_transformData;

		uint32_t m_boxCount = 0;
	};

	struct SphereRenderData final
	{
		struct SphereData final
		{
			TS::FloatVector3 m_position = TS::FloatVector3Zero;
			TS::FloatVector3 m_directionForward = TS::FloatVector3Zero;
			TS::FloatVector3 m_directionUp = TS::FloatVector3Zero;
			float m_radius;
			PackedColor m_color;

			SphereData() = default;
			SphereData(const TS::FloatVector3& position, const TS::FloatVector3& directionForward,
				const TS::FloatVector3& directionUp, float radius, const TS::FloatVector4& color)
				: m_position(position), m_directionForward(directionForward),
				m_directionUp(directionUp), m_color(color), m_radius(radius) {}
		};

		TS::VertexShader* m_vertexShader = nullptr;
		TS::PixelShader* m_pixelShader = nullptr;

		TS::InputLayout* m_inputLayout = nullptr;

		TS::GPUBuffer* m_vertexBuffer = nullptr;
		TS::GPUBuffer* m_indexBuffer = nullptr;

		RenderDataBufferCache m_sphereData;

		uint32_t m_sphereCount = 0;
		uint32_t m_indexCountPerSphere = 0;
	};
}
