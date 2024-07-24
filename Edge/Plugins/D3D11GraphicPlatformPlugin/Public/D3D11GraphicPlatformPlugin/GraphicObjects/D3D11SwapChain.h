#pragma once

#include "TinySimFramework/Graphics/GraphicPlatform/GraphicObject/SwapChain.h"
#include "TinySimFramework/WindowController/Window.h"

#include "D3D11Textures.h"
#include "D3D11GraphicPlatformPlugin/D3D11ComPtrDefinitions.h"

namespace TS_D3D11
{
	class D3D11SwapChain final : public TS::SwapChain
	{
	private:
		DXGISwapChainComPtr m_dxgiSwapChain;
		D3D11Texture2D* m_targetTexture = nullptr;

	public:
		D3D11SwapChain(const TS::SwapChainDesc& desc, const D3D11DeviceComPtr& d3d11Device, const DXGIFactoryComPtr& dxgiFactory, const TS::Window& window);
		~D3D11SwapChain();

		virtual TS::Texture2D* getTargetTexture() override;

		virtual void present() override;

		virtual void* getNativeHandle() const override { return m_dxgiSwapChain.Get(); }
	};
}
