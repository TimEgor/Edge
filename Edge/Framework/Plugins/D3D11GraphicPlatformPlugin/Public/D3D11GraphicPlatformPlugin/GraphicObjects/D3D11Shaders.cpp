#include "D3D11Shaders.h"

EdgeD3D11::D3D11VertexShader::D3D11VertexShader(const D3D11DeviceComPtr& device, const D3DBlobComPtr& code)
	: D3D11ShaderBase(code)
{
	device->CreateVertexShader(code->GetBufferPointer(), code->GetBufferSize(), nullptr, m_shader.GetAddressOf());
}

void EdgeD3D11::D3D11VertexShader::setName(const char* name)
{
	if (!m_shader)
	{
		return;
	}

	m_shader->SetPrivateData(WKPDID_D3DDebugObjectName, strlen(name) - 1, name);
}

EdgeD3D11::D3D11PixelShader::D3D11PixelShader(const D3D11DeviceComPtr& device, const D3DBlobComPtr& code)
	: D3D11ShaderBase(code)
{
	device->CreatePixelShader(code->GetBufferPointer(), code->GetBufferSize(), nullptr, m_shader.GetAddressOf());
}

void EdgeD3D11::D3D11PixelShader::setName(const char* name)
{
	if (!m_shader)
	{
		return;
	}

	m_shader->SetPrivateData(WKPDID_D3DDebugObjectName, strlen(name) - 1, name);
}

EdgeD3D11::D3D11ComputeShader::D3D11ComputeShader(const D3D11DeviceComPtr& device, const D3DBlobComPtr& code)
	: D3D11ShaderBase(code)
{
	device->CreateComputeShader(code->GetBufferPointer(), code->GetBufferSize(), nullptr, m_shader.GetAddressOf());
}

void EdgeD3D11::D3D11ComputeShader::setName(const char* name)
{
	if (!m_shader)
	{
		return;
	}

	m_shader->SetPrivateData(WKPDID_D3DDebugObjectName, strlen(name) - 1, name);
}
