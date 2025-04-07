#include "D3D11SwapChain.h"

#include "EdgeCommon/UtilsMacros.h"

#include "D3D11GraphicPlatformPlugin/Utils/Converter.h"

EdgeD3D11::D3D11SwapChain::D3D11SwapChain(const Edge::SwapChainDesc& desc, const D3D11DeviceComPtr& d3d11Device,
	const DXGIFactoryComPtr& dxgiFactory, const Edge::Window& window)
	: SwapChain(desc)
{
	const Edge::WindowSize& windowSize = window.getClientAreaSize();

	DXGI_SWAP_CHAIN_DESC1 dxgiSwapChainDesc{};
	dxgiSwapChainDesc.Width = windowSize.m_x;
	dxgiSwapChainDesc.Height = windowSize.m_y;
	dxgiSwapChainDesc.Format = ConvertEdgeFormatToDXGI(desc.m_format);
	dxgiSwapChainDesc.SampleDesc.Count = 1;
	dxgiSwapChainDesc.SampleDesc.Quality = 0;
	dxgiSwapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	dxgiSwapChainDesc.BufferCount = desc.m_bufferCount;
	dxgiSwapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
	dxgiSwapChainDesc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

	auto windowHandle = reinterpret_cast<HWND>(window.getNativeHandle());

	dxgiFactory->CreateSwapChainForHwnd(d3d11Device.Get(), windowHandle, &dxgiSwapChainDesc,
		nullptr, nullptr, m_dxgiSwapChain.GetAddressOf());

	m_targetTexture = EDGE_ALLOCATE_RAW(D3D11Texture2D, sizeof(D3D11Texture2D));

	const Edge::Texture2DDesc targetBufferDesc{ { windowSize.m_x, windowSize.m_y }, desc.m_format, Edge::TextureUsage::TEXTURE_USAGE_RENDER_TARGET };

	ID3D11Texture2D* targetBuffer = nullptr;
	m_dxgiSwapChain->GetBuffer(0, EDGE_IID(targetBuffer), EDGE_PPV(targetBuffer));

	new (m_targetTexture) D3D11Texture2D(targetBufferDesc, D3D11Texture2DComPtr(targetBuffer));
}

EdgeD3D11::D3D11SwapChain::~D3D11SwapChain()
{
	EDGE_SAFE_DEALLOCATE_RAW(m_targetTexture, D3D11Texture2D);
}

Edge::Texture2D* EdgeD3D11::D3D11SwapChain::getTargetTexture()
{
	assert(m_targetTexture);
	return m_targetTexture;
}

void EdgeD3D11::D3D11SwapChain::present()
{
	m_dxgiSwapChain->Present(1, 0);
}

void EdgeD3D11::D3D11SwapChain::setName(const char* name)
{
	if (!m_dxgiSwapChain)
	{
		return;
	}

	m_dxgiSwapChain->SetPrivateData(WKPDID_D3DDebugObjectName, strlen(name) - 1, name);
}
