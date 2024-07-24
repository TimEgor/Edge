#include "D3D11SwapChain.h"

#include "TinySimCommon/Core/UtilsMacros.h"

#include "D3D11GraphicPlatformPlugin/Utils/Converter.h"

TS_D3D11::D3D11SwapChain::D3D11SwapChain(const TS::SwapChainDesc& desc, const D3D11DeviceComPtr& d3d11Device,
	const DXGIFactoryComPtr& dxgiFactory, const TS::Window& window)
	: SwapChain(desc)
{
	const TS::WindowSize& windowSize = window.getClientAreaSize();

	DXGI_SWAP_CHAIN_DESC1 dxgiSwapChainDesc{};
	dxgiSwapChainDesc.Width = windowSize.m_x;
	dxgiSwapChainDesc.Height = windowSize.m_y;
	dxgiSwapChainDesc.Format = convertTSFormatToDXGI(desc.m_format);
	dxgiSwapChainDesc.SampleDesc.Count = 1;
	dxgiSwapChainDesc.SampleDesc.Quality = 0;
	dxgiSwapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	dxgiSwapChainDesc.BufferCount = desc.m_bufferCount;
	dxgiSwapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
	dxgiSwapChainDesc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

	auto windowHandle = reinterpret_cast<HWND>(window.getNativeHandle());

	dxgiFactory->CreateSwapChainForHwnd(d3d11Device.Get(), windowHandle, &dxgiSwapChainDesc,
		nullptr, nullptr, m_dxgiSwapChain.GetAddressOf());

	m_targetTexture = TS_ALLOCATE_RAW(D3D11Texture2D, sizeof(D3D11Texture2D));

	const TS::Texture2DDesc targetBufferDesc{ { windowSize.m_x, windowSize.m_y }, desc.m_format, TS::TextureUsage::TEXTURE_USAGE_RENDER_TARGET };

	ID3D11Texture2D* targetBuffer = nullptr;
	m_dxgiSwapChain->GetBuffer(0, TS_IID(targetBuffer), TS_PPV(targetBuffer));

	new (m_targetTexture) D3D11Texture2D(targetBufferDesc, D3D11Texture2DComPtr(targetBuffer));
}

TS_D3D11::D3D11SwapChain::~D3D11SwapChain()
{
	TS_SAFE_DEALLOCATE_RAW(m_targetTexture, D3D11Texture2D);
}

TS::Texture2D* TS_D3D11::D3D11SwapChain::getTargetTexture()
{
	assert(m_targetTexture);
	return m_targetTexture;
}

void TS_D3D11::D3D11SwapChain::present()
{
	m_dxgiSwapChain->Present(1, 0);
}
