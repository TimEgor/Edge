#pragma once

#include "TinySimFramework/Graphics/GraphicPlatform/DefferedGraphicContext.h"

#include "D3D11ComPtrDefinitions.h"

namespace TS_D3D11
{
	class D3D11DeferredGraphicContext final : public TS::DeferredGraphicContext
	{
	private:
		D3D11DeviceContextComPtr m_d3d11Context;

	public:
		D3D11DeferredGraphicContext(const D3D11DeviceComPtr& device);

		virtual void clearRenderTarget(const TS::Texture2D& targetTexture, const TS::FloatVector4& color) override;
		virtual void clearDepthStencil(const TS::Texture2D& depthTexture) override;

		virtual void setRenderTarget(const TS::Texture2D& targetTexture, const TS::Texture2D* depthTexture) override;
		virtual void setViewport(const TS::Viewport& viewport) override;

		virtual void setInputLayout(const TS::InputLayout& inputLayout) override;

		virtual void setVertexShader(const TS::VertexShader& shader) override;
		virtual void setPixelShader(const TS::PixelShader& shader) override;

		virtual void setPrimitiveTopology(TS::PrimitiveTopology topology) override;
		virtual void setRasterizationState(const TS::RasterizationState& state) override;

		virtual void setConstantBuffer(const TS::GPUBuffer& buffer, uint32_t slot, TS::GraphicContextBindingShaderStage shaderStages) override;

		virtual void setVertexBuffers(uint32_t bufferCount, TS::GPUBuffer** buffers, const TS::InputLayoutDesc& inputLayoutDesc) override;
		virtual void setIndexBuffer(TS::GPUBuffer& buffer) override;

		virtual void mapBuffer(TS::GPUBuffer& buffer, TS::GraphicResourceMappingType type, TS::GraphicResourceMappingFlag flag, void** data) override;
		virtual void unmapBuffer(TS::GPUBuffer& buffer) override;

		virtual void draw(uint32_t vertexCount) override;
		virtual void drawIndexed(uint32_t indexCount) override;

		virtual void drawInstanced(uint32_t vertexCount, uint32_t instanceCount) override;
		virtual void drawIndexedInstanced(uint32_t indexCount, uint32_t instanceCount) override;

		virtual void prepareMatrixForShader(const TS::FloatMatrix4x4& originalMatrix, TS::FloatMatrix4x4& destinationMatrix) override;
		virtual void prepareMatrixForShader(const TS::ComputeMatrix& originalMatrix, TS::FloatMatrix4x4& destinationMatrix) override;

		virtual void* getNativeHandle() const override { return m_d3d11Context.Get(); }
	};
}
