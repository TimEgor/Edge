#include "D3D11GraphicDevice.h"

#include "EdgeCommon/FileName/FileName.h"
#include "EdgeCommon/String/Format.h"
#include "EdgeCommon/String/StringConverter.h"

#include "GraphicObjects/D3D11BlendState.h"
#include "GraphicObjects/D3D11GPUBuffer.h"
#include "GraphicObjects/D3D11InputLayout.h"
#include "GraphicObjects/D3D11RasterizationState.h"
#include "GraphicObjects/D3D11SamplerState.h"
#include "GraphicObjects/D3D11Shaders.h"
#include "GraphicObjects/D3D11SwapChain.h"

#include "D3D11DeferredContext.h"

#include "d3dcompiler.h"
#include "GraphicObjects/D3D11DepthStencilState.h"

EdgeD3D11::D3D11GraphicDevice::D3D11GraphicDevice()
	: GraphicDevice()
{
	CreateDXGIFactory2(0, EDGE_IID_COM(m_dxgiFactory), EDGE_PPV_COM(m_dxgiFactory));

	UINT deviceFlags = 0;
#ifdef GRAPHIC_DEBUG
	deviceFlags = D3D11_CREATE_DEVICE_DEBUG;
#endif // GRAPHIC_DEBUG

	D3D_FEATURE_LEVEL featureLevel;
	D3D11CreateDevice(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, deviceFlags, nullptr, 0,
		D3D11_SDK_VERSION, m_d3d11Device.GetAddressOf(), &featureLevel, m_d3d11ImmediateDeviceContext.GetAddressOf());

#ifdef GRAPHIC_DEBUG
	m_d3d11Device->QueryInterface(EDGE_IID_COM(m_d3d11Debug), EDGE_PPV_COM(m_d3d11Debug));
#endif // GRAPHIC_DEBUG
}

EdgeD3D11::D3D11GraphicDevice::~D3D11GraphicDevice()
{
#ifdef GRAPHIC_DEBUG
	m_d3d11Debug->ReportLiveDeviceObjects(D3D11_RLDO_IGNORE_INTERNAL);
#endif // GRAPHIC_DEBUG
}

Edge::DeferredGraphicContext* EdgeD3D11::D3D11GraphicDevice::createDeferredGraphicContext()
{
	return new D3D11DeferredGraphicContext(m_d3d11Device);
}

Edge::SwapChain* EdgeD3D11::D3D11GraphicDevice::createSwapChain(const Edge::SwapChainDesc& desc, const Edge::Window& window)
{
	return new D3D11SwapChain(desc, m_d3d11Device, m_dxgiFactory, window);
}

Edge::GPUBuffer* EdgeD3D11::D3D11GraphicDevice::createBuffer(const Edge::GPUBufferDesc& desc, const Edge::InitialGraphicResourceData* initialData)
{
	return new D3D11GPUBuffer(desc, m_d3d11Device, initialData);
}

Edge::Texture2D* EdgeD3D11::D3D11GraphicDevice::createTexture2D(const Edge::Texture2DDesc& desc, const Edge::InitialGraphicResourceData* initialData)
{
	return new D3D11Texture2D(desc, m_d3d11Device, initialData);
}

EdgeD3D11::D3DBlobComPtr EdgeD3D11::D3D11GraphicDevice::compileShader(const void* srcs, size_t size,
                                                                    const char* entryPoint, const char* shaderModel)
{
	UINT compilationFlags = D3DCOMPILE_ENABLE_STRICTNESS;
#ifdef SHADER_DEBUG
	compilationFlags |= D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION;
#endif

	D3DBlobComPtr codeBlob;
#ifdef SHADER_COMPILATION_ERROR
	D3DBlobComPtr errorBlob;
#endif // SHADER_COMPILATION_ERROR

	D3D_SHADER_MACRO defines[] = {
		{ "EdgeD3D11", "true" },
		{ nullptr, nullptr }
	};

	HRESULT compilationResult = D3DCompile(srcs, size, nullptr, defines, nullptr,
		entryPoint, shaderModel, compilationFlags, 0, codeBlob.GetAddressOf(),
#ifdef SHADER_COMPILATION_ERROR
		errorBlob.GetAddressOf()
#else
		nullptr
#endif // SHADER_COMPILATION_ERROR
	);

	if (FAILED(compilationResult))
	{
#ifdef SHADER_COMPILATION_ERROR
		if (errorBlob)
		{
#ifdef _MSC_VER
			OutputDebugStringA(Edge::StringFormat("Shader compiler error (%s):\n %s\n", shaderModel, errorBlob->GetBufferPointer()).c_str());
#endif // _MSC_VER
		}
#endif // SHADER_COMPILATION_ERROR

		return nullptr;
	}

	return codeBlob;
}

EdgeD3D11::D3DBlobComPtr EdgeD3D11::D3D11GraphicDevice::compileShader(const Edge::FileName& srcFilePath, const char* entryPoint, const char* shaderModel)
{
	UINT compilationFlags = D3DCOMPILE_ENABLE_STRICTNESS;
#ifdef SHADER_DEBUG
	compilationFlags |= D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION;
#endif

	D3DBlobComPtr codeBlob;
#ifdef SHADER_COMPILATION_ERROR
	D3DBlobComPtr errorBlob;
#endif // SHADER_COMPILATION_ERROR

	D3D_SHADER_MACRO defines[] = {
	{ "EdgeD3D11", "true" },
	{ nullptr, nullptr }
	};

	HRESULT compilationResult = D3DCompileFromFile(Edge::ConvertStringToWString(srcFilePath.c_str()).c_str(), defines,
		D3D_COMPILE_STANDARD_FILE_INCLUDE, entryPoint, shaderModel, compilationFlags, 0, codeBlob.GetAddressOf(),
#ifdef SHADER_COMPILATION_ERROR
		errorBlob.GetAddressOf()
#else
		nullptr
#endif // SHADER_COMPILATION_ERROR
	);

	if (FAILED(compilationResult))
	{
#ifdef SHADER_COMPILATION_ERROR
		if (errorBlob)
		{
#ifdef _MSC_VER
			OutputDebugStringA(Edge::StringFormat("Shader compiler error (%s : %s) :\n %s\n", shaderModel, srcFilePath, errorBlob->GetBufferPointer()).c_str());
#endif // _MSC_VER
		}
#endif // SHADER_COMPILATION_ERROR

		return nullptr;
	}

	return codeBlob;
}

Edge::VertexShader* EdgeD3D11::D3D11GraphicDevice::createVertexShaderFromSources(const void* srcs, size_t size)
{
	D3DBlobComPtr shaderCode = compileShader(srcs, size, "VS", "vs_5_0");
	if (!shaderCode)
	{
		return nullptr;
	}

	return new D3D11VertexShader(m_d3d11Device, shaderCode);
}

Edge::PixelShader* EdgeD3D11::D3D11GraphicDevice::createPixelShaderFromSources(const void* srcs, size_t size)
{
	D3DBlobComPtr shaderCode = compileShader(srcs, size, "PS", "ps_5_0");
	if (!shaderCode)
	{
		return nullptr;
	}

	return new D3D11PixelShader(m_d3d11Device, shaderCode);
}

Edge::ComputeShader* EdgeD3D11::D3D11GraphicDevice::createComputeShaderFromSources(const void* srcs, size_t size)
{
	D3DBlobComPtr shaderCode = compileShader(srcs, size, "CS", "cs_5_0");
	if (!shaderCode)
	{
		return nullptr;
	}

	return new D3D11ComputeShader(m_d3d11Device, shaderCode);
}

Edge::VertexShader* EdgeD3D11::D3D11GraphicDevice::createVertexShaderFromFile(const Edge::FileName& shaderFile)
{
	D3DBlobComPtr shaderCode = compileShader(shaderFile, "VS", "vs_5_0");
	if (!shaderCode)
	{
		return nullptr;
	}

	return new D3D11VertexShader(m_d3d11Device, shaderCode);
}

Edge::PixelShader* EdgeD3D11::D3D11GraphicDevice::createPixelShaderFromFile(const Edge::FileName& shaderFile)
{
	D3DBlobComPtr shaderCode = compileShader(shaderFile, "PS", "ps_5_0");
	if (!shaderCode)
	{
		return nullptr;
	}

	return new D3D11PixelShader(m_d3d11Device, shaderCode);
}

Edge::ComputeShader* EdgeD3D11::D3D11GraphicDevice::createComputeShaderFromFile(const Edge::FileName& shaderFile)
{
	D3DBlobComPtr shaderCode = compileShader(shaderFile, "CS", "cs_5_0");
	if (!shaderCode)
	{
		return nullptr;
	}

	return new D3D11ComputeShader(m_d3d11Device, shaderCode);
}

Edge::InputLayout* EdgeD3D11::D3D11GraphicDevice::createInputLayout(const Edge::InputLayoutDesc& desc,
	const Edge::VertexShader& shader)
{
	const D3D11VertexShader& d3d11VertexShader = static_cast<const D3D11VertexShader&>(shader);

	return new D3D11InputLayout(desc, m_d3d11Device, d3d11VertexShader.getCode());
}

Edge::RasterizationState* EdgeD3D11::D3D11GraphicDevice::createRasterizationState(const Edge::RasterizationStateDesc& desc)
{
	return new D3D11RasterizationState(desc, m_d3d11Device);
}

Edge::SamplerState* EdgeD3D11::D3D11GraphicDevice::createSamplerState()
{
	return new D3D11SamplerState(m_d3d11Device);
}

Edge::BlendState* EdgeD3D11::D3D11GraphicDevice::createBlendState(Edge::BlendMode mode)
{
	return new D3D11BlendState(mode, m_d3d11Device);
}

Edge::DepthStencilState* EdgeD3D11::D3D11GraphicDevice::createDepthStencilState(const Edge::DepthStencilStateDesc& desc)
{
	return new D3D11DepthStencilState(desc, m_d3d11Device);
}

void EdgeD3D11::D3D11GraphicDevice::executeGraphicContext(const Edge::DeferredGraphicContext& context)
{
	ID3D11DeviceContext* d3d11Context = context.getNativeHandleCast<ID3D11DeviceContext>();
	D3D11CommandListComPtr commandList = nullptr;
	d3d11Context->FinishCommandList(false, commandList.GetAddressOf());

	m_d3d11ImmediateDeviceContext->ExecuteCommandList(commandList.Get(), true);
}
