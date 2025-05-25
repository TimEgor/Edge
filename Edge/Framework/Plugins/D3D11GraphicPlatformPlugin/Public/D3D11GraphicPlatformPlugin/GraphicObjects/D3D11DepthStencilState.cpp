#include "D3D11DepthStencilState.h"

EdgeD3D11::D3D11DepthStencilState::D3D11DepthStencilState(const Edge::DepthStencilStateDesc& desc, const D3D11DeviceComPtr& device)
	: DepthStencilState(desc)
{
	D3D11_DEPTH_STENCIL_DESC d3d11DepthStencilDesc;
	ZeroMemory(&d3d11DepthStencilDesc, sizeof(D3D11_DEPTH_STENCIL_DESC));

	d3d11DepthStencilDesc.DepthEnable = desc.m_depthTestEnable;
	d3d11DepthStencilDesc.DepthWriteMask = desc.m_depthTestEnable && desc.m_depthWrite ? D3D11_DEPTH_WRITE_MASK_ALL : D3D11_DEPTH_WRITE_MASK_ZERO;
	d3d11DepthStencilDesc.DepthFunc = D3D11_COMPARISON_LESS;
	d3d11DepthStencilDesc.StencilEnable = false;

	device->CreateDepthStencilState(&d3d11DepthStencilDesc, m_state.GetAddressOf());
}

void EdgeD3D11::D3D11DepthStencilState::setName(const char* name)
{
	if (!m_state)
	{
		return;
	}

	m_state->SetPrivateData(WKPDID_D3DDebugObjectName, strlen(name) - 1, name);
}
