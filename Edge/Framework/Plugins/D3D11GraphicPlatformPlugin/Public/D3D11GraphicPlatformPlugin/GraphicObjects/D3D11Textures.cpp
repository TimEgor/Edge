#include "D3D11Textures.h"

#include "D3D11GraphicPlatformPlugin/Utils/Converter.h"
#include "D3D11GraphicPlatformPlugin/Utils/Utils.h"

EdgeD3D11::D3D11Texture2D::D3D11Texture2D(
	const Edge::Texture2DDesc& desc,
	const D3D11DeviceComPtr& device,
	const Edge::InitialGraphicResourceData* initialData
)
	: Texture2D(desc)
{
	D3D11_TEXTURE2D_DESC d3d11TextureDesc{};
	d3d11TextureDesc.Width = desc.m_size.m_x;
	d3d11TextureDesc.Height = desc.m_size.m_y;
	d3d11TextureDesc.MipLevels = 1;
	d3d11TextureDesc.ArraySize = 1;
	d3d11TextureDesc.Format = ConvertEdgeFormatToDXGI(desc.m_format);
	d3d11TextureDesc.SampleDesc.Count = 1;
	d3d11TextureDesc.SampleDesc.Quality = 0;
	d3d11TextureDesc.Usage = ConvertEdgeResourceAccessToD3D11(desc.m_access);
	d3d11TextureDesc.BindFlags = ConvertEdgeTextureUsageToD3D11(desc.m_usage);
	d3d11TextureDesc.CPUAccessFlags = ConvertEdgeCpuAccessToD3D11(desc.m_access);
	d3d11TextureDesc.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA d3d11InitialData{};
	if (initialData && initialData->isValid())
	{
		const uint32_t formatSize = std::ceil(GetEdgeFormatBitCount(desc.m_format) / 8.0f);
		const uint32_t size = desc.m_size.m_x * desc.m_size.m_y * formatSize;

		assert(initialData->m_dataSize <= size);

		d3d11InitialData.pSysMem = initialData->m_data;
		d3d11InitialData.SysMemPitch = desc.m_size.m_x * formatSize;
	}

	device->CreateTexture2D(&d3d11TextureDesc, initialData ? &d3d11InitialData : nullptr, m_texture.GetAddressOf());

	createViews(desc);
}

EdgeD3D11::D3D11Texture2D::D3D11Texture2D(const Edge::Texture2DDesc& desc, const D3D11Texture2DComPtr& texture)
	: Texture2D(desc), m_texture(texture)
{
	createViews(desc);
}

void EdgeD3D11::D3D11Texture2D::setName(const char* name)
{
	if (!m_texture)
	{
		return;
	}

	m_texture->SetPrivateData(WKPDID_D3DDebugObjectName, strlen(name) - 1, name);
}

void EdgeD3D11::D3D11Texture2D::createViews(const Edge::Texture2DDesc& desc)
{
	if (!m_texture)
	{
		return;
	}

	D3D11DeviceComPtr d3d11Device;
	m_texture->GetDevice(d3d11Device.GetAddressOf());

	if (desc.m_usage & Edge::TEXTURE_USAGE_RENDER_TARGET)
	{
		D3D11_RENDER_TARGET_VIEW_DESC d3d11RTVDesc{};
		d3d11RTVDesc.Format = ConvertEdgeFormatToDXGI(desc.m_format);
		d3d11RTVDesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;
		d3d11RTVDesc.Texture2D.MipSlice = 0;

		d3d11Device->CreateRenderTargetView(m_texture.Get(), &d3d11RTVDesc, m_rtv.GetAddressOf());
	}

	if (desc.m_usage & Edge::TEXTURE_USAGE_DEPTH_STENCIL)
	{
		D3D11_DEPTH_STENCIL_VIEW_DESC d3d11DSVDesc{};
		d3d11DSVDesc.Format = ConvertEdgeFormatToDXGI(desc.m_format);
		d3d11DSVDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
		d3d11DSVDesc.Texture2D.MipSlice = 0;

		d3d11Device->CreateDepthStencilView(m_texture.Get(), &d3d11DSVDesc, m_dsv.GetAddressOf());
	}

	if (desc.m_usage & Edge::GRAPHIC_RESOURCE_USAGE_SHADER_RESOURCE)
	{
		D3D11_SHADER_RESOURCE_VIEW_DESC d3d11SRVDesc{};
		d3d11SRVDesc.Format = ConvertEdgeFormatToDXGI(desc.m_format);
		d3d11SRVDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
		d3d11SRVDesc.Texture2D.MipLevels = 1;

		d3d11Device->CreateShaderResourceView(m_texture.Get(), &d3d11SRVDesc, m_srv.GetAddressOf());
	}
}
