#include "D3D11Textures.h"

#include "D3D11GraphicPlatformPlugin/Utils/Converter.h"

EdgeD3D11::D3D11Texture2D::D3D11Texture2D(const Edge::Texture2DDesc& desc, const D3D11DeviceComPtr& device)
	: Texture2D(desc)
{
	D3D11_TEXTURE2D_DESC d3d11TextureDesc{};
	d3d11TextureDesc.Width = desc.m_size.m_x;
	d3d11TextureDesc.Height = desc.m_size.m_y;
	d3d11TextureDesc.MipLevels = 1;
	d3d11TextureDesc.ArraySize = 1;
	d3d11TextureDesc.Format = convertTSFormatToDXGI(desc.m_format);
	d3d11TextureDesc.SampleDesc.Count = 1;
	d3d11TextureDesc.SampleDesc.Quality = 0;
	d3d11TextureDesc.Usage = convertTSResourceAccessToD3D11(desc.m_access);
	d3d11TextureDesc.BindFlags = convertTSTextureUsageToD3D11(desc.m_usage);
	d3d11TextureDesc.CPUAccessFlags = convertTSCPUAccessToD3D11(desc.m_access);
	d3d11TextureDesc.MiscFlags = 0;

	device->CreateTexture2D(&d3d11TextureDesc, nullptr, m_d3d11Texture.GetAddressOf());

	createViews(desc);
}

EdgeD3D11::D3D11Texture2D::D3D11Texture2D(const Edge::Texture2DDesc& desc, const D3D11Texture2DComPtr& texture)
	: Texture2D(desc), m_d3d11Texture(texture)
{
	createViews(desc);
}

void EdgeD3D11::D3D11Texture2D::createViews(const Edge::Texture2DDesc& desc)
{
	if (!m_d3d11Texture)
	{
		return;
	}

	D3D11DeviceComPtr d3d11Device;
	m_d3d11Texture->GetDevice(d3d11Device.GetAddressOf());

	if (desc.m_usage & Edge::TEXTURE_USAGE_RENDER_TARGET)
	{
		D3D11_RENDER_TARGET_VIEW_DESC d3d11RTVDesc{};
		d3d11RTVDesc.Format = convertTSFormatToDXGI(desc.m_format);
		d3d11RTVDesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;
		d3d11RTVDesc.Texture2D.MipSlice = 0;

		d3d11Device->CreateRenderTargetView(m_d3d11Texture.Get(), &d3d11RTVDesc, m_d3d11RTV.GetAddressOf());
	}

	if (desc.m_usage & Edge::TEXTURE_USAGE_DEPTH_STENCIL)
	{
		D3D11_DEPTH_STENCIL_VIEW_DESC d3d11DSVDesc{};
		d3d11DSVDesc.Format = convertTSFormatToDXGI(desc.m_format);
		d3d11DSVDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
		d3d11DSVDesc.Texture2D.MipSlice = 0;

		d3d11Device->CreateDepthStencilView(m_d3d11Texture.Get(), &d3d11DSVDesc, m_d3d11DSV.GetAddressOf());
	}
}