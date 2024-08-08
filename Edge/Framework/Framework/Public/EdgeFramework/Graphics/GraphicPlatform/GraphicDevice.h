#pragma once

namespace Edge
{
	class FileName;

	class Window;

	class DeferredGraphicContext;

	struct SwapChainDesc;
	class SwapChain;

	struct GPUBufferDesc;
	struct InitialGPUBufferData;
	class GPUBuffer;

	struct Texture2DDesc;
	class Texture2D;

	class VertexShader;
	class PixelShader;
	class ComputeShader;

	struct InputLayoutDesc;
	class InputLayout;

	struct RasterizationStateDesc;
	class RasterizationState;

	class GraphicDevice
	{
	public:
		GraphicDevice() = default;
		virtual ~GraphicDevice() = default;

		virtual DeferredGraphicContext* createDeferredGraphicContext() = 0;

		virtual void executeGraphicContext(const DeferredGraphicContext& context) = 0;

		virtual SwapChain* createSwapChain(const SwapChainDesc& desc, const Window& window) = 0;

		virtual GPUBuffer* createBuffer(const GPUBufferDesc& desc, const InitialGPUBufferData* initialData) = 0;

		virtual Texture2D* createTexture2D(const Texture2DDesc& desc) = 0;

		virtual VertexShader* createVertexShaderFromSources(const void* srcs, size_t size) = 0;
		virtual PixelShader* createPixelShaderFromSources(const void* srcs, size_t size) = 0;
		virtual ComputeShader* createComputeShaderFromSources(const void* srcs, size_t size) = 0;

		virtual VertexShader* createVertexShaderFromFile(const FileName& shaderFile) = 0;
		virtual PixelShader* createPixelShaderFromFile(const FileName& shaderFile) = 0;
		virtual ComputeShader* createComputeShaderFromFile(const FileName& shaderFile) = 0;

		virtual InputLayout* createInputLayout(const InputLayoutDesc& desc, const VertexShader& shader) = 0;

		virtual RasterizationState* createRasterizationState(const RasterizationStateDesc& desc) = 0;
	};
}
