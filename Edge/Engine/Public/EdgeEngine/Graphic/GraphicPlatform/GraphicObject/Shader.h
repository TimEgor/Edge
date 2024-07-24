#pragma once

#include "IGraphicResource.h"

#define EDGE_GRAPHIC_RESOURCE_SHADER_TYPE

namespace Edge
{
	enum class ShaderStage
	{
		Vertex,
		Pixel,

		Compute
	};

	class IShader : public IGraphicResource
	{
	public:
		IShader() = default;

		virtual ShaderStage getShaderStage() const = 0;

		EDGE_GRAPHIC_RESOURCE_TYPE(EDGE_GRAPHIC_RESOURCE_SHADER_TYPE)
	};

	class IVertexShader : public IShader
	{
	public:
		IVertexShader() = default;

		virtual ShaderStage getShaderStage() const override { return ShaderStage::Vertex; }
	};

	class IPixelShader : public IShader
	{
	public:
		IPixelShader() = default;

		virtual ShaderStage getShaderStage() const override { return ShaderStage::Pixel; }
	};

	class IComputeShader : public IShader
	{
	public:
		IComputeShader() = default;

		virtual ShaderStage getShaderStage() const override { return ShaderStage::Compute; }
	};
}
