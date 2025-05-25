#include "D3D11RasterizationState.h"

#include "D3D11GraphicPlatformPlugin/Utils/Converter.h"

EdgeD3D11::D3D11RasterizationState::D3D11RasterizationState(const Edge::RasterizationStateDesc& desc, const D3D11DeviceComPtr& device)
	: RasterizationState(desc)
{
	D3D11_RASTERIZER_DESC d3d11RasterizerDesc{};
	d3d11RasterizerDesc.CullMode = ConvertEdgeRasterizationCullModeToD3D11(desc.m_cullMode);
	d3d11RasterizerDesc.FillMode = ConvertEdgeRasterizationFillModeToD3D11(desc.m_fillMode);
	d3d11RasterizerDesc.FrontCounterClockwise = desc.m_frontCounterClockwise;
	d3d11RasterizerDesc.DepthClipEnable = desc.m_depthClip;

	device->CreateRasterizerState(&d3d11RasterizerDesc, m_state.GetAddressOf());
}

void EdgeD3D11::D3D11RasterizationState::setName(const char* name)
{
	if (!m_state)
	{
		return;
	}

	m_state->SetPrivateData(WKPDID_D3DDebugObjectName, strlen(name) - 1, name);
}
