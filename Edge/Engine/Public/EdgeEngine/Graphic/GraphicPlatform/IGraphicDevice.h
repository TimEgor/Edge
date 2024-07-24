#pragma once

namespace Edge
{
	class FileName;

	class IWindow;

	class IDeferredGraphicContext;

	struct SwapChainDesc;
	class ISwapChain;

	struct GPUBufferDesc;
	struct InitialGPUBufferData;
	class IGPUBuffer;

	struct Texture2DDesc;
	class ITexture2D;

	class IVertexShader;
	class IPixelShader;
	class IComputeShader;

	struct InputLayoutDesc;
	class IInputLayout;

	struct RasterizationStateDesc;
	class IRasterizationState;

	class IGraphicDevice
	{
	public:
		IGraphicDevice() = default;
		virtual ~IGraphicDevice() = default;

		virtual IDeferredGraphicContext* createDeferredGraphicContext() = 0;

		virtual void executeGraphicContext(const IDeferredGraphicContext& context) = 0;

		virtual ISwapChain* createSwapChain(const SwapChainDesc& desc, const IWindow& window) = 0;

		virtual IGPUBuffer* createBuffer(const GPUBufferDesc& desc, const InitialGPUBufferData* initialData) = 0;

		virtual ITexture2D* createTexture2D(const Texture2DDesc& desc) = 0;

		virtual IVertexShader* createVertexShaderFromSources(const void* srcs, size_t size) = 0;
		virtual IPixelShader* createPixelShaderFromSources(const void* srcs, size_t size) = 0;
		virtual IComputeShader* createComputeShaderFromSources(const void* srcs, size_t size) = 0;

		virtual IVertexShader* createVertexShaderFromFile(const FileName& shaderFile) = 0;
		virtual IPixelShader* createPixelShaderFromFile(const FileName& shaderFile) = 0;
		virtual IComputeShader* createComputeShaderFromFile(const FileName& shaderFile) = 0;

		virtual IInputLayout* createInputLayout(const InputLayoutDesc& desc, const IVertexShader& shader) = 0;

		virtual IRasterizationState* createRasterizationState(const RasterizationStateDesc& desc) = 0;
	};
}
