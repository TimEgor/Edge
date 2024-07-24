#include "D3D11Shaders.h"

TS_D3D11::D3D11VertexShader::D3D11VertexShader(const D3D11DeviceComPtr& device, const D3DBlobComPtr& code)
	: D3D11ShaderBase(code)
{
	device->CreateVertexShader(code->GetBufferPointer(), code->GetBufferSize(), nullptr, m_shader.GetAddressOf());
}

TS_D3D11::D3D11PixelShader::D3D11PixelShader(const D3D11DeviceComPtr& device, const D3DBlobComPtr& code)
	: D3D11ShaderBase(code)
{
	device->CreatePixelShader(code->GetBufferPointer(), code->GetBufferSize(), nullptr, m_shader.GetAddressOf());
}

TS_D3D11::D3D11ComputeShader::D3D11ComputeShader(const D3D11DeviceComPtr& device, const D3DBlobComPtr& code)
	: D3D11ShaderBase(code)
{
	device->CreateComputeShader(code->GetBufferPointer(), code->GetBufferSize(), nullptr, m_shader.GetAddressOf());
}
