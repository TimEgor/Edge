#include "D3D11SamplerState.h"

EdgeD3D11::D3D11SamplerState::D3D11SamplerState(const D3D11DeviceComPtr& device)
{
	D3D11_SAMPLER_DESC d3d11SamplerDesc;
	ZeroMemory(&d3d11SamplerDesc, sizeof(d3d11SamplerDesc));
	d3d11SamplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	d3d11SamplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	d3d11SamplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	d3d11SamplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	d3d11SamplerDesc.MipLODBias = 0;
	d3d11SamplerDesc.MaxAnisotropy = 1;

	device->CreateSamplerState(&d3d11SamplerDesc, m_state.GetAddressOf());
}

void EdgeD3D11::D3D11SamplerState::setName(const char* name)
{
	if (!m_state)
	{
		return;
	}

	m_state->SetPrivateData(WKPDID_D3DDebugObjectName, strlen(name) - 1, name);
}
