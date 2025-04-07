#pragma once

#include "EdgeFramework/Graphics/GraphicPlatform/GraphicObject/Texture.h"

#include "D3D11GraphicPlatformPlugin/D3D11ComPtrDefinitions.h"

namespace EdgeD3D11
{
	class D3D11Texture2D final : public Edge::Texture2D
	{
	private:
		D3D11Texture2DComPtr m_texture;

		D3D11RenderTargetViewComPtr m_rtv;
		D3D11DepthStencilViewComPtr m_dsv;

		D3D11ShaderResourceViewComPtr m_srv;

		void createViews(const Edge::Texture2DDesc& desc);

	public:
		D3D11Texture2D(const Edge::Texture2DDesc& desc, const D3D11DeviceComPtr& device, const Edge::InitialGraphicResourceData* initialData);
		D3D11Texture2D(const Edge::Texture2DDesc& desc, const D3D11Texture2DComPtr& texture);

		const D3D11RenderTargetViewComPtr& getRTV() const { return m_rtv; }
		const D3D11DepthStencilViewComPtr& getDSV() const { return m_dsv; }

		const D3D11ShaderResourceViewComPtr& getSRV() const { return m_srv; }

		virtual void* getNativeHandle() const override { return m_texture.Get(); }

		virtual void setName(const char* name) override;
	};
}
