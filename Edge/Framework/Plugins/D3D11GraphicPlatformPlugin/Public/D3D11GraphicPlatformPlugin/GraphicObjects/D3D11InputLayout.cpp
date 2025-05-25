#include "D3D11InputLayout.h"

#include "D3D11GraphicPlatformPlugin/Utils/Converter.h"

EdgeD3D11::D3D11InputLayout::D3D11InputLayout(const Edge::InputLayoutDesc& desc,
	const D3D11DeviceComPtr& device, const D3DBlobComPtr& shaderCode)
	: InputLayout(desc)
{
	std::vector<D3D11_INPUT_ELEMENT_DESC> d3d11InputElementDescs;
	ConvertEdgeInputLayoutToD3D11(desc, d3d11InputElementDescs);

	device->CreateInputLayout(d3d11InputElementDescs.data(), d3d11InputElementDescs.size(),
		shaderCode->GetBufferPointer(), shaderCode->GetBufferSize(), m_inputLayout.GetAddressOf());
}

void EdgeD3D11::D3D11InputLayout::setName(const char* name)
{
	if (!m_inputLayout)
	{
		return;
	}

	m_inputLayout->SetPrivateData(WKPDID_D3DDebugObjectName, strlen(name) - 1, name);
}
