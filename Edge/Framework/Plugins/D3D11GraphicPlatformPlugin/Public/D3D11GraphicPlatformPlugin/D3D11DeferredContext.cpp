#include "D3D11DeferredContext.h"

#include "GraphicObjects/D3D11BlendState.h"
#include "GraphicObjects/D3D11GPUBuffer.h"
#include "GraphicObjects/D3D11InputLayout.h"
#include "GraphicObjects/D3D11RasterizationState.h"
#include "GraphicObjects/D3D11SamplerState.h"
#include "GraphicObjects/D3D11Shaders.h"
#include "GraphicObjects/D3D11Textures.h"

#include "Utils/Converter.h"

EdgeD3D11::D3D11DeferredGraphicContext::D3D11DeferredGraphicContext(const D3D11DeviceComPtr& device)
{
	device->CreateDeferredContext(0, m_context.GetAddressOf());
}

void EdgeD3D11::D3D11DeferredGraphicContext::clearRenderTarget(const Edge::Texture2D& targetTexture, const Edge::FloatVector4& color)
{
	const D3D11Texture2D& d3d11Texture = static_cast<const D3D11Texture2D&>(targetTexture);
	const D3D11RenderTargetViewComPtr& d3d11RTV = d3d11Texture.getRTV();

	m_context->ClearRenderTargetView(d3d11RTV.Get(), color.m_values);
}

void EdgeD3D11::D3D11DeferredGraphicContext::clearDepthStencil(const Edge::Texture2D& depthTexture)
{
	const D3D11Texture2D& d3d11Texture = static_cast<const D3D11Texture2D&>(depthTexture);
	const D3D11DepthStencilViewComPtr& d3d11DSV = d3d11Texture.getDSV();

	m_context->ClearDepthStencilView(d3d11DSV.Get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
}

void EdgeD3D11::D3D11DeferredGraphicContext::setRenderTarget(const Edge::Texture2D& targetTexture, const Edge::Texture2D* depthTexture)
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

	m_context->OMSetRenderTargets(1, d3d11RTV.GetAddressOf(), dsv);
}

void EdgeD3D11::D3D11DeferredGraphicContext::setViewport(const Edge::Viewport& viewport)
{
	D3D11_VIEWPORT d3d11Viewport{};
	d3d11Viewport.TopLeftX = static_cast<float>(viewport.m_x);
	d3d11Viewport.TopLeftY = static_cast<float>(viewport.m_y);
	d3d11Viewport.Width = static_cast<float>(viewport.m_width);
	d3d11Viewport.Height = static_cast<float>(viewport.m_height);
	d3d11Viewport.MaxDepth = D3D11_MAX_DEPTH;
	d3d11Viewport.MinDepth = D3D11_MIN_DEPTH;

	m_context->RSSetViewports(1, &d3d11Viewport);
}

void EdgeD3D11::D3D11DeferredGraphicContext::setInputLayout(const Edge::InputLayout& inputLayout)
{
	const D3D11InputLayout& d3d11InputLayout = static_cast<const D3D11InputLayout&>(inputLayout);

	m_context->IASetInputLayout(d3d11InputLayout.getInputLayoutHandle().Get());
}

void EdgeD3D11::D3D11DeferredGraphicContext::setVertexShader(const Edge::VertexShader& shader)
{
	const D3D11VertexShader& d3d11VertexShader = static_cast<const D3D11VertexShader&>(shader);

	m_context->VSSetShader(d3d11VertexShader.getShaderHandle().Get(), nullptr, 0);
}

void EdgeD3D11::D3D11DeferredGraphicContext::setPixelShader(const Edge::PixelShader& shader)
{
	const D3D11PixelShader& d3d11PixelShader = static_cast<const D3D11PixelShader&>(shader);

	m_context->PSSetShader(d3d11PixelShader.getShaderHandle().Get(), nullptr, 0);
}

void EdgeD3D11::D3D11DeferredGraphicContext::setPrimitiveTopology(Edge::PrimitiveTopology topology)
{
	D3D11_PRIMITIVE_TOPOLOGY d3d11Topology = ConvertEdgePrimitiveTopologyToD3D11(topology);

	m_context->IASetPrimitiveTopology(d3d11Topology);
}

void EdgeD3D11::D3D11DeferredGraphicContext::setRasterizationState(const Edge::RasterizationState& state)
{
	const D3D11RasterizationState& d3d11RasterizationState = static_cast<const D3D11RasterizationState&>(state);

	m_context->RSSetState(d3d11RasterizationState.getStateHandle().Get());
}

void EdgeD3D11::D3D11DeferredGraphicContext::setSamplerState(
	const Edge::SamplerState& state,
	uint32_t slot,
	Edge::GraphicContextBindingShaderStage shaderStages
)
{
	const D3D11SamplerState& d3d11SamplerState = static_cast<const D3D11SamplerState&>(state);

	if (shaderStages & Edge::GRAPHIC_CONTEXT_BINDING_SHADER_STAGE_VERTEX)
	{
		m_context->VSSetSamplers(slot, 1, d3d11SamplerState.getStateHandle().GetAddressOf());
	}

	if (shaderStages & Edge::GRAPHIC_CONTEXT_BINDING_SHADER_STAGE_PIXEL)
	{
		m_context->PSSetSamplers(slot, 1, d3d11SamplerState.getStateHandle().GetAddressOf());
	}
}

void EdgeD3D11::D3D11DeferredGraphicContext::setBlendState(const Edge::BlendState& state)
{
	const D3D11BlendState& d3d11BlendState = static_cast<const D3D11BlendState&>(state);

	m_context->OMSetBlendState(d3d11BlendState.getStateHandle().Get(), nullptr, UINT_MAX);
}

void EdgeD3D11::D3D11DeferredGraphicContext::setConstantBuffer(
	const Edge::GPUBuffer& buffer,
	uint32_t slot,
	Edge::GraphicContextBindingShaderStage shaderStages
)
{
	const D3D11GPUBuffer& d3d11Buffer = static_cast<const D3D11GPUBuffer&>(buffer);

	if (shaderStages & Edge::GRAPHIC_CONTEXT_BINDING_SHADER_STAGE_VERTEX)
	{
		m_context->VSSetConstantBuffers(slot, 1, d3d11Buffer.getBufferHandle().GetAddressOf());
	}

	if (shaderStages & Edge::GRAPHIC_CONTEXT_BINDING_SHADER_STAGE_PIXEL)
	{
		m_context->PSSetConstantBuffers(slot, 1, d3d11Buffer.getBufferHandle().GetAddressOf());
	}
}

void EdgeD3D11::D3D11DeferredGraphicContext::setVertexBuffers(uint32_t bufferCount, Edge::GPUBuffer** buffers, const Edge::InputLayoutDesc& inputLayoutDesc)
{
	ID3D11Buffer* d3d11Buffers[D3D11_IA_VERTEX_INPUT_RESOURCE_SLOT_COUNT];
	uint32_t offsets[D3D11_IA_VERTEX_INPUT_RESOURCE_SLOT_COUNT];
	uint32_t strides[D3D11_IA_VERTEX_INPUT_RESOURCE_SLOT_COUNT];

	for (uint32_t slotIndex = 0; slotIndex < bufferCount; ++slotIndex)
	{
		const D3D11GPUBuffer& d3d11Buffer = static_cast<const D3D11GPUBuffer&>(*buffers[slotIndex]);
		const Edge::InputLayoutBindingDesc& bindingDesc = inputLayoutDesc.m_bindings[slotIndex];

		d3d11Buffers[slotIndex] = d3d11Buffer.getBufferHandle().Get();
		offsets[slotIndex] = 0;
		strides[slotIndex] = bindingDesc.m_stride;
	}

	m_context->IASetVertexBuffers(0, bufferCount, d3d11Buffers, strides, offsets);
}

void EdgeD3D11::D3D11DeferredGraphicContext::setIndexBuffer(Edge::GPUBuffer& buffer)
{
	D3D11GPUBuffer& d3d11Buffer = static_cast<D3D11GPUBuffer&>(buffer);

	m_context->IASetIndexBuffer(d3d11Buffer.getBufferHandle().Get(), DXGI_FORMAT_R16_UINT, 0);
}

void EdgeD3D11::D3D11DeferredGraphicContext::setShaderResource(
	const Edge::Texture2D& texture,
	uint32_t slot,
	Edge::GraphicContextBindingShaderStage shaderStages
)
{
	const D3D11Texture2D& d3d11Texture = static_cast<const D3D11Texture2D&>(texture);
	const D3D11ShaderResourceViewComPtr& d3d11SRV = d3d11Texture.getSRV();

	if (shaderStages & Edge::GRAPHIC_CONTEXT_BINDING_SHADER_STAGE_VERTEX)
	{
		m_context->VSSetShaderResources(slot, 1, d3d11SRV.GetAddressOf());
	}

	if (shaderStages & Edge::GRAPHIC_CONTEXT_BINDING_SHADER_STAGE_PIXEL)
	{
		m_context->PSSetShaderResources(slot, 1, d3d11SRV.GetAddressOf());
	}
}

void EdgeD3D11::D3D11DeferredGraphicContext::mapBuffer(
	Edge::GPUBuffer& buffer,
	Edge::GraphicResourceMappingType type,
	Edge::GraphicResourceMappingFlag flag,
	void** data
)
{
	D3D11GPUBuffer& d3d11Buffer = static_cast<D3D11GPUBuffer&>(buffer);

	D3D11_MAP d3d11Map;
	UINT d3d11MapFlag;

	ConvertEdgeMapParamsToD3D11(type, flag, d3d11Map, d3d11MapFlag);

	D3D11_MAPPED_SUBRESOURCE mappedSubresource;

	m_context->Map(d3d11Buffer.getBufferHandle().Get(), 0, d3d11Map, d3d11MapFlag, &mappedSubresource);

	*data = mappedSubresource.pData;
}

void EdgeD3D11::D3D11DeferredGraphicContext::unmapBuffer(Edge::GPUBuffer& buffer)
{
	D3D11GPUBuffer& d3d11Buffer = static_cast<D3D11GPUBuffer&>(buffer);
	m_context->Unmap(d3d11Buffer.getBufferHandle().Get(), 0);
}

void EdgeD3D11::D3D11DeferredGraphicContext::draw(uint32_t vertexCount)
{
	m_context->Draw(vertexCount, 0);
}

void EdgeD3D11::D3D11DeferredGraphicContext::drawIndexed(uint32_t indexCount)
{
	m_context->DrawIndexed(indexCount, 0, 0);
}

void EdgeD3D11::D3D11DeferredGraphicContext::drawInstanced(uint32_t vertexCount, uint32_t instanceCount)
{
	m_context->DrawInstanced(vertexCount, instanceCount, 0, 0);
}

void EdgeD3D11::D3D11DeferredGraphicContext::drawIndexedInstanced(uint32_t indexCount, uint32_t instanceCount)
{
	m_context->DrawIndexedInstanced(indexCount, instanceCount, 0, 0, 0);
}

void EdgeD3D11::D3D11DeferredGraphicContext::prepareMatrixForShader(const Edge::FloatMatrix4x4& originalMatrix, Edge::FloatMatrix4x4& destinationMatrix)
{
	Edge::FloatComputeMatrix4x4 computeMatr = originalMatrix;
	computeMatr.transpose();
	computeMatr.getFloatMatrix4x4(destinationMatrix);
}

void EdgeD3D11::D3D11DeferredGraphicContext::prepareMatrixForShader(Edge::FloatMatrix4x4& matrix)
{
	prepareMatrixForShader(matrix, matrix);
}

void EdgeD3D11::D3D11DeferredGraphicContext::prepareViewTransform(
	const Edge::FloatVector3& viewPosition,
	const Edge::FloatVector3& viewDirection,
	const Edge::FloatVector3& upDirection,
	Edge::FloatMatrix4x4& destinationMatrix
)
{
	const DirectX::XMMATRIX dxViewMatrix = DirectX::XMMatrixLookToLH(
		DirectX::XMLoadFloat3(reinterpret_cast<const DirectX::XMFLOAT3*>(&viewPosition)),
		DirectX::XMLoadFloat3(reinterpret_cast<const DirectX::XMFLOAT3*>(&viewDirection)),
		DirectX::XMLoadFloat3(reinterpret_cast<const DirectX::XMFLOAT3*>(&upDirection))
	);

	DirectX::XMStoreFloat4x4(reinterpret_cast<DirectX::XMFLOAT4X4*>(&destinationMatrix), dxViewMatrix);
}

void EdgeD3D11::D3D11DeferredGraphicContext::preparePerspectiveProjTransform(
	float angle,
	float aspectRatio,
	float nearPlaneZ,
	float farPlaneZ,
	Edge::FloatMatrix4x4& destinationMatrix
)
{
	const DirectX::XMMATRIX dxProjMatrix = DirectX::XMMatrixPerspectiveFovLH(angle, aspectRatio, nearPlaneZ, farPlaneZ);

	DirectX::XMStoreFloat4x4(reinterpret_cast<DirectX::XMFLOAT4X4*>(&destinationMatrix), dxProjMatrix);
}

void EdgeD3D11::D3D11DeferredGraphicContext::setName(const char* name)
{
	if (!m_context)
	{
		return;
	}

	m_context->SetPrivateData(WKPDID_D3DDebugObjectName, strlen(name) - 1, name);
}
