#pragma once

#include "EdgeFramework/Graphics/GraphicPlatform/GraphicObject/SwapChain.h"
#include "EdgeFramework/WindowController/Window.h"

#include "D3D11Textures.h"
#include "D3D11GraphicPlatformPlugin/D3D11ComPtrDefinitions.h"

namespace EdgeD3D11
{
	class D3D11SwapChain final : public Edge::SwapChain
	{
	private:
		DXGISwapChainComPtr m_dxgiSwapChain;
		D3D11Texture2D* m_targetTexture = nullptr;

	public:
		D3D11SwapChain(const Edge::SwapChainDesc& desc, const D3D11DeviceComPtr& d3d11Device, const DXGIFactoryComPtr& dxgiFactory, const Edge::Window& window);
		~D3D11SwapChain();

		virtual Edge::Texture2D* getTargetTexture() override;

		virtual void present() override;

		virtual void* getNativeHandle() const override { return m_dxgiSwapChain.Get(); }

		virtual void setName(const char* name) override;
	};
}
