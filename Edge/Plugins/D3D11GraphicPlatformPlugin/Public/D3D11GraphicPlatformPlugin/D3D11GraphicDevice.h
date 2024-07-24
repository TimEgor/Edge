#pragma once

#include "TinySimFramework/Graphics/GraphicPlatform/GraphicDevice.h"

#include "D3D11ComPtrDefinitions.h"

namespace TS_D3D11
{
	class D3D11GraphicDevice final : public TS::GraphicDevice
	{
	private:
		DXGIFactoryComPtr m_dxgiFactory;

		D3D11DeviceComPtr m_d3d11Device;
		D3D11DeviceContextComPtr m_d3d11ImmediateDeviceContext;

#ifdef GRAPHIC_DEBUG
		D3D11DebugComPtr m_d3d11Debug;
#endif // GRAPHIC_DEBUG

		D3DBlobComPtr compileShader(const void* srcs, size_t size, const char* entryPoint, const char* shaderModel);
		D3DBlobComPtr compileShader(const TS::FileName& srcFilePath, const char* entryPoint, const char* shaderModel);

	public:
		D3D11GraphicDevice();
		~D3D11GraphicDevice();

		virtual TS::DeferredGraphicContext* createDeferredGraphicContext() override;

		virtual void executeGraphicContext(const TS::DeferredGraphicContext& context) override;

		virtual TS::SwapChain* createSwapChain(const TS::SwapChainDesc& desc, const TS::Window& window) override;

		virtual TS::GPUBuffer* createBuffer(const TS::GPUBufferDesc& desc, const TS::InitialGPUBufferData* initialData) override;

		virtual TS::Texture2D* createTexture2D(const TS::Texture2DDesc& desc) override;

		virtual TS::VertexShader* createVertexShaderFromSources(const void* srcs, size_t size) override;
		virtual TS::PixelShader* createPixelShaderFromSources(const void* srcs, size_t size) override;
		virtual TS::ComputeShader* createComputeShaderFromSources(const void* srcs, size_t size) override;

		virtual TS::VertexShader* createVertexShaderFromFile(const TS::FileName& shaderFile) override;
		virtual TS::PixelShader* createPixelShaderFromFile(const TS::FileName& shaderFile) override;
		virtual TS::ComputeShader* createComputeShaderFromFile(const TS::FileName& shaderFile) override;

		virtual TS::InputLayout* createInputLayout(const TS::InputLayoutDesc& desc, const TS::VertexShader& shader) override;

		virtual TS::RasterizationState* createRasterizationState(const TS::RasterizationStateDesc& desc) override;

		D3D11DeviceComPtr getD3D11Device() const { return m_d3d11Device; }
	};
}
