#pragma once

#include "EdgeFramework/Graphics/GraphicPlatform/GraphicDevice.h"

#include "D3D11ComPtrDefinitions.h"

namespace EdgeD3D11
{
	class D3D11GraphicDevice final : public Edge::GraphicDevice
	{
	private:
		DXGIFactoryComPtr m_dxgiFactory;

		D3D11DeviceComPtr m_d3d11Device;
		D3D11DeviceContextComPtr m_d3d11ImmediateDeviceContext;

#ifdef GRAPHIC_DEBUG
		D3D11DebugComPtr m_d3d11Debug;
#endif // GRAPHIC_DEBUG

		D3DBlobComPtr compileShader(const void* srcs, size_t size, const char* entryPoint, const char* shaderModel);
		D3DBlobComPtr compileShader(const Edge::FileName& srcFilePath, const char* entryPoint, const char* shaderModel);

	public:
		D3D11GraphicDevice();
		~D3D11GraphicDevice();

		virtual Edge::DeferredGraphicContext* createDeferredGraphicContext() override;

		virtual void executeGraphicContext(const Edge::DeferredGraphicContext& context) override;

		virtual Edge::SwapChain* createSwapChain(const Edge::SwapChainDesc& desc, const Edge::Window& window) override;

		virtual Edge::GPUBuffer* createBuffer(const Edge::GPUBufferDesc& desc, const Edge::InitialGraphicResourceData* initialData) override;

		virtual Edge::Texture2D* createTexture2D(const Edge::Texture2DDesc& desc, const Edge::InitialGraphicResourceData* initialData) override;

		virtual Edge::VertexShader* createVertexShaderFromSources(const void* srcs, size_t size) override;
		virtual Edge::PixelShader* createPixelShaderFromSources(const void* srcs, size_t size) override;
		virtual Edge::ComputeShader* createComputeShaderFromSources(const void* srcs, size_t size) override;

		virtual Edge::VertexShader* createVertexShaderFromFile(const Edge::FileName& shaderFile) override;
		virtual Edge::PixelShader* createPixelShaderFromFile(const Edge::FileName& shaderFile) override;
		virtual Edge::ComputeShader* createComputeShaderFromFile(const Edge::FileName& shaderFile) override;

		virtual Edge::InputLayout* createInputLayout(const Edge::InputLayoutDesc& desc, const Edge::VertexShader& shader) override;

		virtual Edge::RasterizationState* createRasterizationState(const Edge::RasterizationStateDesc& desc) override;
		virtual Edge::SamplerState* createSamplerState() override;
		virtual Edge::BlendState* createBlendState(Edge::BlendMode mode) override;
		virtual Edge::DepthStencilState* createDepthStencilState(const Edge::DepthStencilStateDesc& desc) override;

		D3D11DeviceComPtr getD3D11Device() const { return m_d3d11Device; }
	};
}
