#include "D3D11BlendState.h"

EdgeD3D11::D3D11BlendState::D3D11BlendState(Edge::BlendMode mode, const D3D11DeviceComPtr& device)
	: BlendState(mode)
{
	D3D11_BLEND_DESC d3d11BlendDesc;
	ZeroMemory(&d3d11BlendDesc, sizeof(D3D11_BLEND_DESC));

	switch (mode)
	{
	case Edge::BlendMode::Off:
		d3d11BlendDesc.RenderTarget[0].BlendEnable = FALSE;
		break;
	case Edge::BlendMode::AlphaBlend:
		d3d11BlendDesc.RenderTarget[0].BlendEnable = TRUE;
		d3d11BlendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
		d3d11BlendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
		d3d11BlendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
		d3d11BlendDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ZERO;
		d3d11BlendDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
		d3d11BlendDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
		d3d11BlendDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
		break;
	}

	device->CreateBlendState(&d3d11BlendDesc, m_state.GetAddressOf());
}

void EdgeD3D11::D3D11BlendState::setName(const char* name)
{
	if (!m_state)
	{
		return;
	}

	m_state->SetPrivateData(WKPDID_D3DDebugObjectName, strlen(name) - 1, name);
}
