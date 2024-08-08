#pragma once

#include "EdgeFramework/Graphics/GraphicPlatform/DefferedGraphicContext.h"

#include "D3D11ComPtrDefinitions.h"

namespace EdgeD3D11
{
	class D3D11DeferredGraphicContext final : public Edge::DeferredGraphicContext
	{
	private:
		D3D11DeviceContextComPtr m_d3d11Context;

	public:
		D3D11DeferredGraphicContext(const D3D11DeviceComPtr& device);

		virtual void clearRenderTarget(const Edge::Texture2D& targetTexture, const Edge::FloatVector4& color) override;
		virtual void clearDepthStencil(const Edge::Texture2D& depthTexture) override;

		virtual void setRenderTarget(const Edge::Texture2D& targetTexture, const Edge::Texture2D* depthTexture) override;
		virtual void setViewport(const Edge::Viewport& viewport) override;

		virtual void setInputLayout(const Edge::InputLayout& inputLayout) override;

		virtual void setVertexShader(const Edge::VertexShader& shader) override;
		virtual void setPixelShader(const Edge::PixelShader& shader) override;

		virtual void setPrimitiveTopology(Edge::PrimitiveTopology topology) override;
		virtual void setRasterizationState(const Edge::RasterizationState& state) override;

		virtual void setConstantBuffer(const Edge::GPUBuffer& buffer, uint32_t slot, Edge::GraphicContextBindingShaderStage shaderStages) override;

		virtual void setVertexBuffers(uint32_t bufferCount, Edge::GPUBuffer** buffers, const Edge::InputLayoutDesc& inputLayoutDesc) override;
		virtual void setIndexBuffer(Edge::GPUBuffer& buffer) override;

		virtual void mapBuffer(Edge::GPUBuffer& buffer, Edge::GraphicResourceMappingType type, Edge::GraphicResourceMappingFlag flag, void** data) override;
		virtual void unmapBuffer(Edge::GPUBuffer& buffer) override;

		virtual void draw(uint32_t vertexCount) override;
		virtual void drawIndexed(uint32_t indexCount) override;

		virtual void drawInstanced(uint32_t vertexCount, uint32_t instanceCount) override;
		virtual void drawIndexedInstanced(uint32_t indexCount, uint32_t instanceCount) override;

		virtual void prepareMatrixForShader(const Edge::FloatMatrix4x4& originalMatrix, Edge::FloatMatrix4x4& destinationMatrix) override;
		virtual void prepareMatrixForShader(const Edge::ComputeMatrix& originalMatrix, Edge::FloatMatrix4x4& destinationMatrix) override;

		virtual void* getNativeHandle() const override { return m_d3d11Context.Get(); }
	};
}
