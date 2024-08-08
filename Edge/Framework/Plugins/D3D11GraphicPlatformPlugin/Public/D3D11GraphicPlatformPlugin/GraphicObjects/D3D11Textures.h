#pragma once

#include "EdgeFramework/Graphics/GraphicPlatform/GraphicObject/Texture.h"

#include "D3D11GraphicPlatformPlugin/D3D11ComPtrDefinitions.h"

namespace EdgeD3D11
{
	class D3D11Texture2D final : public Edge::Texture2D
	{
	private:
		D3D11Texture2DComPtr m_d3d11Texture;

		D3D11RenderTargetViewComPtr m_d3d11RTV;
		D3D11DepthStencilViewComPtr m_d3d11DSV;

		void createViews(const Edge::Texture2DDesc& desc);

	public:
		D3D11Texture2D(const Edge::Texture2DDesc& desc, const D3D11DeviceComPtr& device);
		D3D11Texture2D(const Edge::Texture2DDesc& desc, const D3D11Texture2DComPtr& texture);

		const D3D11RenderTargetViewComPtr& getRTV() const { return m_d3d11RTV; }
		const D3D11DepthStencilViewComPtr& getDSV() const { return m_d3d11DSV; }

		virtual void* getNativeHandle() const override { return m_d3d11Texture.Get(); }
	};
}
