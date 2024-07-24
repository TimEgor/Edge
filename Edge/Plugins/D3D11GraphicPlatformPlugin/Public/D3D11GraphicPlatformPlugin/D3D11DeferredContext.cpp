#include "D3D11DeferredContext.h"

#include "TinySimCommon/Math/ComputeMatrix.h"
#include "TinySimCommon/Math/ComputeMath/ComputeMatrix.h"

#include "GraphicObjects/D3D11GPUBuffer.h"
#include "GraphicObjects/D3D11InputLayout.h"
#include "GraphicObjects/D3D11RasterizationState.h"
#include "GraphicObjects/D3D11Shaders.h"
#include "GraphicObjects/D3D11Textures.h"

#include "Utils/Converter.h"

TS_D3D11::D3D11DeferredGraphicContext::D3D11DeferredGraphicContext(const D3D11DeviceComPtr& device)
{
	device->CreateDeferredContext(0, m_d3d11Context.GetAddressOf());
}

void TS_D3D11::D3D11DeferredGraphicContext::clearRenderTarget(const TS::Texture2D& targetTexture, const TS::FloatVector4& color)
{
	const D3D11Texture2D& d3d11Texture = static_cast<const D3D11Texture2D&>(targetTexture);
	const D3D11RenderTargetViewComPtr& d3d11RTV = d3d11Texture.getRTV();

	m_d3d11Context->ClearRenderTargetView(d3d11RTV.Get(), color.m_values);
}

void TS_D3D11::D3D11DeferredGraphicContext::clearDepthStencil(const TS::Texture2D& depthTexture)
{
	const D3D11Texture2D& d3d11Texture = static_cast<const D3D11Texture2D&>(depthTexture);
	const D3D11DepthStencilViewComPtr& d3d11DSV = d3d11Texture.getDSV();

	m_d3d11Context->ClearDepthStencilView(d3d11DSV.Get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
}

void TS_D3D11::D3D11DeferredGraphicContext::setRenderTarget(const TS::Texture2D& targetTexture, const TS::Texture2D* depthTexture)
{
	const D3D11Texture2D& d3d11TargetTexture = static_cast<const D3D11Texture2D&>(targetTexture);
	const D3D11RenderTargetViewComPtr& d3d11RTV = d3d11TargetTexture.getRTV();

	ID3D11DepthStencilView* dsv = nullptr;

	if (depthTexture)
	{
		const D3D11Texture2D& d3d11DepthTexture = static_cast<const D3D11Texture2D&>(*depthTexture);
		const D3D11DepthStencilViewComPtr& d3d11DSV = d3d11DepthTexture.getDSV();

		if (d3d11DSV)
		{
			dsv = d3d11DepthTexture.getDSV().Get();
		}
	}

	m_d3d11Context->OMSetRenderTargets(1, d3d11RTV.GetAddressOf(), dsv);
}

void TS_D3D11::D3D11DeferredGraphicContext::setViewport(const TS::Viewport& viewport)
{
	D3D11_VIEWPORT d3d11Viewport{};
	d3d11Viewport.TopLeftX = static_cast<float>(viewport.m_x);
	d3d11Viewport.TopLeftY = static_cast<float>(viewport.m_y);
	d3d11Viewport.Width = static_cast<float>(viewport.m_width);
	d3d11Viewport.Height = static_cast<float>(viewport.m_height);
	d3d11Viewport.MaxDepth = D3D11_MAX_DEPTH;
	d3d11Viewport.MinDepth = D3D11_MIN_DEPTH;

	m_d3d11Context->RSSetViewports(1, &d3d11Viewport);
}

void TS_D3D11::D3D11DeferredGraphicContext::setInputLayout(const TS::InputLayout& inputLayout)
{
	const D3D11InputLayout& d3d11InputLayout = static_cast<const D3D11InputLayout&>(inputLayout);

	m_d3d11Context->IASetInputLayout(d3d11InputLayout.getInputLayoutHandle().Get());
}

void TS_D3D11::D3D11DeferredGraphicContext::setVertexShader(const TS::VertexShader& shader)
{
	const D3D11VertexShader& d3d11VertexShader = static_cast<const D3D11VertexShader&>(shader);

	m_d3d11Context->VSSetShader(d3d11VertexShader.getShaderHandle().Get(), nullptr, 0);
}

void TS_D3D11::D3D11DeferredGraphicContext::setPixelShader(const TS::PixelShader& shader)
{
	const D3D11PixelShader& d3d11PixelShader = static_cast<const D3D11PixelShader&>(shader);

	m_d3d11Context->PSSetShader(d3d11PixelShader.getShaderHandle().Get(), nullptr, 0);
}

void TS_D3D11::D3D11DeferredGraphicContext::setPrimitiveTopology(TS::PrimitiveTopology topology)
{
	D3D11_PRIMITIVE_TOPOLOGY d3d11Topology = convertTSPrimitiveTopologyToD3D11(topology);

	m_d3d11Context->IASetPrimitiveTopology(d3d11Topology);
}

void TS_D3D11::D3D11DeferredGraphicContext::setRasterizationState(const TS::RasterizationState& state)
{
	const D3D11RasterizationState& d3d11RasterizationState = static_cast<const D3D11RasterizationState&>(state);

	m_d3d11Context->RSSetState(d3d11RasterizationState.getStateHandle().Get());
}

void TS_D3D11::D3D11DeferredGraphicContext::setConstantBuffer(const TS::GPUBuffer& buffer, uint32_t slot, TS::GraphicContextBindingShaderStage shaderStages)
{
	const D3D11GPUBuffer& d3d11Buffer = static_cast<const D3D11GPUBuffer&>(buffer);

	if (shaderStages & TS::GRAPHIC_CONTEXT_BINDING_SHADER_STAGE_VERTEX)
	{
		m_d3d11Context->VSSetConstantBuffers(slot, 1, d3d11Buffer.getBufferHandle().GetAddressOf());
	}

	if (shaderStages & TS::GRAPHIC_CONTEXT_BINDING_SHADER_STAGE_PIXEL)
	{
		m_d3d11Context->PSSetConstantBuffers(slot, 1, d3d11Buffer.getBufferHandle().GetAddressOf());
	}
}

void TS_D3D11::D3D11DeferredGraphicContext::setVertexBuffers(uint32_t bufferCount, TS::GPUBuffer** buffers, const TS::InputLayoutDesc& inputLayoutDesc)
{
	ID3D11Buffer* d3d11Buffers[D3D11_IA_VERTEX_INPUT_RESOURCE_SLOT_COUNT];
	uint32_t offsets[D3D11_IA_VERTEX_INPUT_RESOURCE_SLOT_COUNT];
	uint32_t strides[D3D11_IA_VERTEX_INPUT_RESOURCE_SLOT_COUNT];

	for (uint32_t slotIndex = 0; slotIndex < bufferCount; ++slotIndex)
	{
		const D3D11GPUBuffer& d3d11Buffer = static_cast<const D3D11GPUBuffer&>(*buffers[slotIndex]);
		const TS::InputLayoutBindingDesc& bindingDesc = inputLayoutDesc.m_bindings[slotIndex];

		d3d11Buffers[slotIndex] = d3d11Buffer.getBufferHandle().Get();
		offsets[slotIndex] = 0;
		strides[slotIndex] = bindingDesc.m_stride;
	}

	m_d3d11Context->IASetVertexBuffers(0, bufferCount, d3d11Buffers, strides, offsets);
}

void TS_D3D11::D3D11DeferredGraphicContext::setIndexBuffer(TS::GPUBuffer& buffer)
{
	D3D11GPUBuffer& d3d11Buffer = static_cast<D3D11GPUBuffer&>(buffer);

	m_d3d11Context->IASetIndexBuffer(d3d11Buffer.getBufferHandle().Get(), DXGI_FORMAT_R16_UINT, 0);
}

void TS_D3D11::D3D11DeferredGraphicContext::mapBuffer(TS::GPUBuffer& buffer, TS::GraphicResourceMappingType type, TS::GraphicResourceMappingFlag flag, void** data)
{
	D3D11GPUBuffer& d3d11Buffer = static_cast<D3D11GPUBuffer&>(buffer);

	D3D11_MAP d3d11Map;
	UINT d3d11MapFlag;
	convertTSMapParamsToD3D11(type, flag, d3d11Map, d3d11MapFlag);

	D3D11_MAPPED_SUBRESOURCE mappedSubresource;

	m_d3d11Context->Map(d3d11Buffer.getBufferHandle().Get(), 0, d3d11Map, d3d11MapFlag, &mappedSubresource);

	*data = mappedSubresource.pData;
}

void TS_D3D11::D3D11DeferredGraphicContext::unmapBuffer(TS::GPUBuffer& buffer)
{
	D3D11GPUBuffer& d3d11Buffer = static_cast<D3D11GPUBuffer&>(buffer);
	m_d3d11Context->Unmap(d3d11Buffer.getBufferHandle().Get(), 0);
}

void TS_D3D11::D3D11DeferredGraphicContext::draw(uint32_t vertexCount)
{
	m_d3d11Context->Draw(vertexCount, 0);
}

void TS_D3D11::D3D11DeferredGraphicContext::drawIndexed(uint32_t indexCount)
{
	m_d3d11Context->DrawIndexed(indexCount, 0, 0);
}

void TS_D3D11::D3D11DeferredGraphicContext::drawInstanced(uint32_t vertexCount, uint32_t instanceCount)
{
	m_d3d11Context->DrawInstanced(vertexCount, instanceCount, 0, 0);
}

void TS_D3D11::D3D11DeferredGraphicContext::drawIndexedInstanced(uint32_t indexCount, uint32_t instanceCount)
{
	m_d3d11Context->DrawIndexedInstanced(indexCount, instanceCount, 0, 0, 0);
}

void TS_D3D11::D3D11DeferredGraphicContext::prepareMatrixForShader(const TS::FloatMatrix4x4& originalMatrix, TS::FloatMatrix4x4& destinationMatrix)
{
	prepareMatrixForShader(TS::ComputeMatrix(originalMatrix), destinationMatrix);
}

void TS_D3D11::D3D11DeferredGraphicContext::prepareMatrixForShader(const TS::ComputeMatrix& originalMatrix,
	TS::FloatMatrix4x4& destinationMatrix)
{
	TS::ComputeMatrix destinationComputeMatrix = originalMatrix;
	destinationComputeMatrix.transpose();

	destinationComputeMatrix.saveToMatrix4x4(destinationMatrix);
}