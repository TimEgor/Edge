#pragma once

#include "EdgeEngine/Core/Math/Vector.h"
#include "EdgeEngine/Core/Math/Matrix.h"

#include "GraphicObject/IGraphicObject.h"

namespace Edge
{
	class ComputeMatrix;

	class IGPUBuffer;

	class ITexture2D;

	struct InputLayoutDesc;
	class IInputLayout;

	class IVertexShader;
	class IPixelShader;

	class IRasterizationState;

	enum class PrimitiveTopology
	{
		Undefined,

		PointList,
		LineList,
		LineStrip,
		TriangleList,
		TriangleStrip
	};

	struct Scissors final
	{
		uint32_t m_left = 0;
		uint32_t m_right = 0;
		uint32_t m_top = 0;
		uint32_t m_bottom = 0;

		Scissors() = default;
		Scissors(uint32_t right, uint32_t bottom)
			: m_right(right), m_bottom(bottom) {}
	};

	struct Viewport final
	{
		uint32_t m_width = 0;
		uint32_t m_height = 0;
		uint32_t m_x = 0;
		uint32_t m_y = 0;

		Viewport() = default;
		Viewport(uint32_t width, uint32_t height)
			: m_width(width), m_height(height) {}
	};

	enum GraphicResourceMappingType
	{
		GRAPHIC_RESOURCE_MAPPING_TYPE_READ = 1,
		GRAPHIC_RESOURCE_MAPPING_TYPE_WRITE = 1 << 1
	};

	enum GraphicResourceMappingFlag
	{
		GRAPHIC_RESOURCE_MAPPING_FLAG_NONE = 0,

		GRAPHIC_RESOURCE_MAPPING_FLAG_DO_NOT_WAIT = 1,
		GRAPHIC_RESOURCE_MAPPING_FLAG_DISCARD = 1 << 1,
		GRAPHIC_RESOURCE_MAPPING_FLAG_NO_OVERWRITE = 1 << 2,
	};

	enum GraphicContextBindingShaderStage
	{
		GRAPHIC_CONTEXT_BINDING_SHADER_STAGE_VERTEX = 1,
		GRAPHIC_CONTEXT_BINDING_SHADER_STAGE_PIXEL = 1 << 1
	};

	class IDeferredGraphicContext : public IGraphicObject
	{
	public:
		IDeferredGraphicContext() = default;

		virtual void clearRenderTarget(const ITexture2D& targetTexture, const FloatVector4& color) = 0;
		virtual void clearDepthStencil(const ITexture2D& depthTexture) = 0;

		virtual void setRenderTarget(const ITexture2D& targetTexture, const ITexture2D* depthTexture) = 0;
		virtual void setViewport(const Viewport& viewport) = 0;

		virtual void setInputLayout(const IInputLayout& inputLayout) = 0;

		virtual void setVertexShader(const IVertexShader& shader) = 0;
		virtual void setPixelShader(const IPixelShader& shader) = 0;

		virtual void setPrimitiveTopology(PrimitiveTopology topology) = 0;
		virtual void setRasterizationState(const IRasterizationState& state) = 0;

		virtual void setConstantBuffer(const IGPUBuffer& buffer, uint32_t slot, GraphicContextBindingShaderStage shaderStages) = 0;

		virtual void setVertexBuffers(uint32_t bufferCount, IGPUBuffer** buffers, const InputLayoutDesc& inputLayoutDesc) = 0;
		virtual void setIndexBuffer(IGPUBuffer& buffer) = 0;

		virtual void mapBuffer(IGPUBuffer& buffer, GraphicResourceMappingType type, GraphicResourceMappingFlag flag, void** data) = 0;
		virtual void unmapBuffer(IGPUBuffer& buffer) = 0;

		virtual void draw(uint32_t vertexCount) = 0;
		virtual void drawIndexed(uint32_t indexCount) = 0;

		virtual void drawInstanced(uint32_t vertexCount, uint32_t instanceCount) = 0;
		virtual void drawIndexedInstanced(uint32_t indexCount, uint32_t instanceCount) = 0;

		virtual void prepareMatrixForShader(const FloatMatrix4x4& originalMatrix, FloatMatrix4x4& destinationMatrix) = 0;
		virtual void prepareMatrixForShader(const ComputeMatrix& originalMatrix, FloatMatrix4x4& destinationMatrix) = 0;
	};
}
