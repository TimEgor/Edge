#include "D3D11GPUBuffer.h"

#include "D3D11GraphicPlatformPlugin/Utils/Converter.h"
#include "EdgeCommon/Memory.h"

EdgeD3D11::D3D11GPUBuffer::D3D11GPUBuffer(const Edge::GPUBufferDesc& desc, const D3D11DeviceComPtr& device, const Edge::InitialGraphicResourceData* initialData)
	: GPUBuffer(desc)
{
	D3D11_BUFFER_DESC d3d11Desc{};
	d3d11Desc.ByteWidth = Edge::Align(desc.m_size, 16u);
	d3d11Desc.Usage = ConvertEdgeResourceAccessToD3D11(desc.m_access);
	d3d11Desc.BindFlags = ConvertEdgeBufferUsageToD3D11(desc.m_usage);
	d3d11Desc.CPUAccessFlags = ConvertEdgeCpuAccessToD3D11(desc.m_access);
	d3d11Desc.MiscFlags = 0;
	d3d11Desc.StructureByteStride = desc.m_stride;

	D3D11_SUBRESOURCE_DATA d3d11InitialData{};
	if (initialData && initialData->isValid())
	{
		assert(initialData->m_dataSize <= desc.m_size);

		d3d11InitialData.pSysMem = initialData->m_data;
		d3d11InitialData.SysMemPitch = std::min(initialData->m_dataSize, desc.m_size);
	}

	device->CreateBuffer(&d3d11Desc, initialData ? &d3d11InitialData : nullptr, m_buffer.GetAddressOf());
}

void EdgeD3D11::D3D11GPUBuffer::setName(const char* name)
{
	if (!m_buffer)
	{
		return;
	}

	m_buffer->SetPrivateData(WKPDID_D3DDebugObjectName, strlen(name) - 1, name);
}
