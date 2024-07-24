#include "D3D11RasterizationState.h"

#include "D3D11GraphicPlatformPlugin/Utils/Converter.h"

TS_D3D11::D3D11RasterizationState::D3D11RasterizationState(const TS::RasterizationStateDesc& desc, const D3D11DeviceComPtr& device)
	: RasterizationState(desc)
{
	D3D11_RASTERIZER_DESC d3d11RasterizerDesc{};
	d3d11RasterizerDesc.CullMode = convertTSRasterizationCullModeToD3D11(desc.m_cullMode);
	d3d11RasterizerDesc.FillMode = convertTSRasterizationFillModeToD3D11(desc.m_fillMode);
	d3d11RasterizerDesc.FrontCounterClockwise = false;

	device->CreateRasterizerState(&d3d11RasterizerDesc, m_state.GetAddressOf());
}
