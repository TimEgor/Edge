#pragma once

#include "GraphicResource.h"

#define EDGE_GRAPHIC_RESOURCE_SHADER_TYPE

namespace Edge
{
	enum class ShaderStage
	{
		Vertex,
		Pixel,

		Compute
	};

	class Shader : public GraphicResource
	{
	public:
		Shader() = default;

		virtual ShaderStage getShaderStage() const = 0;

		EDGE_GRAPHIC_RESOURCE_TYPE(EDGE_GRAPHIC_RESOURCE_SHADER_TYPE)
	};

	class VertexShader : public Shader
	{
	public:
		VertexShader() = default;

		virtual ShaderStage getShaderStage() const override { return ShaderStage::Vertex; }
	};

	class PixelShader : public Shader
	{
	public:
		PixelShader() = default;

		virtual ShaderStage getShaderStage() const override { return ShaderStage::Pixel; }
	};

	class ComputeShader : public Shader
	{
	public:
		ComputeShader() = default;

		virtual ShaderStage getShaderStage() const override { return ShaderStage::Compute; }
	};
}
