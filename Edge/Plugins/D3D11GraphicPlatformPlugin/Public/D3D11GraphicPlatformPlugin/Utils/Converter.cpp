#include "Converter.h"

#include "TinySimFramework/Graphics/GraphicPlatform/GraphicObject/GPUBuffer.h"
#include "TinySimFramework/Graphics/GraphicPlatform/GraphicObject/Texture.h"

DXGI_FORMAT TS_D3D11::convertTSFormatToDXGI(TS::GraphicResourceFormat format)
{
	switch (format)
	{
	case TS::GraphicResourceFormat::R8_UNORM:
		return DXGI_FORMAT_R8_UNORM;
	case TS::GraphicResourceFormat::R8_SNORM:
		return DXGI_FORMAT_R8_SNORM;
	case TS::GraphicResourceFormat::R8_UINT:
		return DXGI_FORMAT_R8_UINT;
	case TS::GraphicResourceFormat::R8_SINT:
		return DXGI_FORMAT_R8_SINT;

	case TS::GraphicResourceFormat::R8G8_UNORM:
		return DXGI_FORMAT_R8G8_UNORM;
	case TS::GraphicResourceFormat::R8G8_SNORM:
		return DXGI_FORMAT_R8G8_SNORM;
	case TS::GraphicResourceFormat::R8G8_UINT:
		return DXGI_FORMAT_R8G8_UINT;
	case TS::GraphicResourceFormat::R8G8_SINT:
		return DXGI_FORMAT_R8G8_SINT;

	case TS::GraphicResourceFormat::R8G8B8A8_UNORM:
		return DXGI_FORMAT_R8G8B8A8_UNORM;
	case TS::GraphicResourceFormat::R8G8B8A8_SNORM:
		return DXGI_FORMAT_R8G8B8A8_SNORM;
	case TS::GraphicResourceFormat::R8G8B8A8_UINT:
		return DXGI_FORMAT_R8G8B8A8_UINT;
	case TS::GraphicResourceFormat::R8G8B8A8_SINT:
		return DXGI_FORMAT_R8G8B8A8_SINT;

	case TS::GraphicResourceFormat::R16_UNORM:
		return DXGI_FORMAT_R16_UNORM;
	case TS::GraphicResourceFormat::R16_SNORM:
		return DXGI_FORMAT_R16_SNORM;
	case TS::GraphicResourceFormat::R16_UINT:
		return DXGI_FORMAT_R16_UINT;
	case TS::GraphicResourceFormat::R16_SINT:
		return DXGI_FORMAT_R16_SINT;
	case TS::GraphicResourceFormat::R16_SFLOAT:
		return DXGI_FORMAT_R16_FLOAT;

	case TS::GraphicResourceFormat::R16G16_UNORM:
		return DXGI_FORMAT_R16G16_UNORM;
	case TS::GraphicResourceFormat::R16G16_SNORM:
		return DXGI_FORMAT_R16G16_SNORM;
	case TS::GraphicResourceFormat::R16G16_UINT:
		return DXGI_FORMAT_R16G16_UINT;
	case TS::GraphicResourceFormat::R16G16_SINT:
		return DXGI_FORMAT_R16G16_SINT;
	case TS::GraphicResourceFormat::R16G16_SFLOAT:
		return DXGI_FORMAT_R16G16_FLOAT;

	case TS::GraphicResourceFormat::R16G16B16A16_UNORM:
		return DXGI_FORMAT_R16G16B16A16_UNORM;
	case TS::GraphicResourceFormat::R16G16B16A16_SNORM:
		return DXGI_FORMAT_R16G16B16A16_SNORM;
	case TS::GraphicResourceFormat::R16G16B16A16_UINT:
		return DXGI_FORMAT_R16G16B16A16_UINT;
	case TS::GraphicResourceFormat::R16G16B16A16_SINT:
		return DXGI_FORMAT_R16G16B16A16_SINT;
	case TS::GraphicResourceFormat::R16G16B16A16_SFLOAT:
		return DXGI_FORMAT_R16G16B16A16_FLOAT;

	case TS::GraphicResourceFormat::R32_UINT:
		return DXGI_FORMAT_R32_UINT;
	case TS::GraphicResourceFormat::R32_SINT:
		return DXGI_FORMAT_R32_SINT;
	case TS::GraphicResourceFormat::R32_SFLOAT:
		return DXGI_FORMAT_R32_FLOAT;

	case TS::GraphicResourceFormat::R32G32_UINT:
		return DXGI_FORMAT_R32G32_UINT;
	case TS::GraphicResourceFormat::R32G32_SINT:
		return DXGI_FORMAT_R32G32_SINT;
	case TS::GraphicResourceFormat::R32G32_SFLOAT:
		return DXGI_FORMAT_R32G32_FLOAT;

	case TS::GraphicResourceFormat::R32G32B32_UINT:
		return DXGI_FORMAT_R32G32B32A32_UINT;
	case TS::GraphicResourceFormat::R32G32B32_SINT:
		return DXGI_FORMAT_R32G32B32_SINT;
	case TS::GraphicResourceFormat::R32G32B32_SFLOAT:
		return DXGI_FORMAT_R32G32B32_FLOAT;

	case TS::GraphicResourceFormat::R32G32B32A32_UINT:
		return DXGI_FORMAT_R32G32B32A32_UINT;
	case TS::GraphicResourceFormat::R32G32B32A32_SINT:
		return DXGI_FORMAT_R32G32B32A32_SINT;
	case TS::GraphicResourceFormat::R32G32B32A32_SFLOAT:
		return DXGI_FORMAT_R32G32B32A32_FLOAT;

	case TS::GraphicResourceFormat::D24_UNORM_S8_UINT:
		return DXGI_FORMAT_D24_UNORM_S8_UINT;
	case TS::GraphicResourceFormat::D32_SFLOAT_S8_UINT:
		return DXGI_FORMAT_D32_FLOAT_S8X24_UINT;

	case TS::GraphicResourceFormat::Undefined:
	default:
		return DXGI_FORMAT_UNKNOWN;
	}
}

D3D11_PRIMITIVE_TOPOLOGY TS_D3D11::convertTSPrimitiveTopologyToD3D11(TS::PrimitiveTopology topology)
{
	switch (topology)
	{
	case TS::PrimitiveTopology::PointList:
		return D3D11_PRIMITIVE_TOPOLOGY_POINTLIST;
	case TS::PrimitiveTopology::LineList:
		return D3D11_PRIMITIVE_TOPOLOGY_LINELIST;
	case TS::PrimitiveTopology::LineStrip:
		return D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP;
	case TS::PrimitiveTopology::TriangleList:
		return D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
	case TS::PrimitiveTopology::TriangleStrip:
		return D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP;
	case TS::PrimitiveTopology::Undefined:
	default:
		return D3D11_PRIMITIVE_TOPOLOGY_UNDEFINED;
	}
}

D3D11_CULL_MODE TS_D3D11::convertTSRasterizationCullModeToD3D11(TS::RasterizationCullMode mode)
{
	switch (mode)
	{
	case TS::RasterizationCullMode::BackFace:
		return D3D11_CULL_BACK;
	case TS::RasterizationCullMode::FrontFace:
		return D3D11_CULL_FRONT;
	case TS::RasterizationCullMode::None:
	default:
		return D3D11_CULL_NONE;
	}
}

D3D11_FILL_MODE TS_D3D11::convertTSRasterizationFillModeToD3D11(TS::RasterizationFillMode mode)
{
	switch (mode)
	{
	case TS::RasterizationFillMode::Wireframe:
		return D3D11_FILL_WIREFRAME;
	case TS::RasterizationFillMode::Solid:
	default:
		return D3D11_FILL_SOLID;
	}
}

D3D11_USAGE TS_D3D11::convertTSResourceAccessToD3D11(TS::GraphicResourceAccessValueType access)
{
	if (access == (TS::GRAPHIC_RESOURCE_ACCESS_GPU_READ | TS::GRAPHIC_RESOURCE_ACCESS_GPU_WRITE))
	{
		return D3D11_USAGE_DEFAULT;
	}

	if (access == TS::GRAPHIC_RESOURCE_ACCESS_GPU_READ)
	{
		return D3D11_USAGE_IMMUTABLE;
	}

	if (access == (TS::GRAPHIC_RESOURCE_ACCESS_CPU_WRITE | TS::GRAPHIC_RESOURCE_ACCESS_GPU_READ))
	{
		return D3D11_USAGE_DYNAMIC;
	}

	if (access == TS::GRAPHIC_RESOURCE_ACCESS_CPU_READ)
	{
		return D3D11_USAGE_STAGING;
	}

	assert(false && "Invalid graphic resource access");

	return D3D11_USAGE_DEFAULT;
}

UINT TS_D3D11::convertTSCPUAccessToD3D11(TS::GraphicResourceAccessValueType access)
{
	UINT d3d11CPUAccess = 0;

	if (access & TS::GRAPHIC_RESOURCE_ACCESS_CPU_READ)
	{
		d3d11CPUAccess |= D3D11_CPU_ACCESS_READ;
	}

	if (access & TS::GRAPHIC_RESOURCE_ACCESS_CPU_WRITE)
	{
		d3d11CPUAccess |= D3D11_CPU_ACCESS_WRITE;
	}

	return d3d11CPUAccess;
}

UINT TS_D3D11::convertTSBufferUsageToD3D11(TS::GraphicResourceUsageValueType usage)
{
	UINT d3d11Usage = 0;

	if (usage & TS::GRAPHIC_RESOURCE_USAGE_ALLOW_UNORDERED_ACCESS)
	{
		d3d11Usage |= D3D11_BIND_UNORDERED_ACCESS;
	}

	if (usage & TS::GRAPHIC_RESOURCE_USAGE_SHADER_RESOURCE)
	{
		d3d11Usage |= D3D11_BIND_SHADER_RESOURCE;
	}

	if (usage & TS::GPU_BUFFER_USAGE_VERTEX_BUFFER)
	{
		d3d11Usage |= D3D11_BIND_VERTEX_BUFFER;
	}

	if (usage & TS::GPU_BUFFER_USAGE_INDEX_BUFFER)
	{
		d3d11Usage |= D3D11_BIND_INDEX_BUFFER;
	}

	if (usage & TS::GPU_BUFFER_USAGE_CONSTANT_BUFFER)
	{
		d3d11Usage |= D3D11_BIND_CONSTANT_BUFFER;
	}

	return d3d11Usage;
}

UINT TS_D3D11::convertTSTextureUsageToD3D11(TS::GraphicResourceUsageValueType usage)
{
	UINT d3d11Usage = 0;

	if (usage & TS::GRAPHIC_RESOURCE_USAGE_ALLOW_UNORDERED_ACCESS)
	{
		d3d11Usage |= D3D11_BIND_UNORDERED_ACCESS;
	}

	if (usage & TS::GRAPHIC_RESOURCE_USAGE_SHADER_RESOURCE)
	{
		d3d11Usage |= D3D11_BIND_SHADER_RESOURCE;
	}

	if (usage & TS::TEXTURE_USAGE_RENDER_TARGET)
	{
		d3d11Usage |= D3D11_BIND_RENDER_TARGET;
	}

	if (usage & TS::TEXTURE_USAGE_DEPTH_STENCIL)
	{
		d3d11Usage |= D3D11_BIND_DEPTH_STENCIL;
	}

	return d3d11Usage;
}

D3D11_INPUT_CLASSIFICATION TS_D3D11::convertInputLayoutBindingTypeTStoD3D11(TS::InputLayoutBindingType bindingType)
{
	switch (bindingType)
	{
	case TS::InputLayoutBindingType::VertexBinding:
		return D3D11_INPUT_PER_VERTEX_DATA;
	case TS::InputLayoutBindingType::InstanceBinding:
		return D3D11_INPUT_PER_INSTANCE_DATA;
	default:
		return static_cast<D3D11_INPUT_CLASSIFICATION>(-1);
	}
}

void TS_D3D11::convertTSMapParamsToD3D11(TS::GraphicResourceMappingType type, TS::GraphicResourceMappingFlag flag,
	D3D11_MAP& d3d11Map, UINT& d3d11Flags)
{
	d3d11Map = static_cast<D3D11_MAP>(0);

	if (type == TS::GRAPHIC_RESOURCE_MAPPING_TYPE_READ)
	{
		d3d11Map = D3D11_MAP_READ;
	}
	else if (type == TS::GRAPHIC_RESOURCE_MAPPING_TYPE_WRITE)
	{
		if (flag == TS::GRAPHIC_RESOURCE_MAPPING_FLAG_DISCARD)
		{
			d3d11Map = D3D11_MAP_WRITE_DISCARD;
		}
		else if (flag == TS::GRAPHIC_RESOURCE_MAPPING_FLAG_NO_OVERWRITE)
		{
			d3d11Map = D3D11_MAP_WRITE_NO_OVERWRITE;
		}
		else
		{
			d3d11Map = D3D11_MAP_WRITE;
		}
	}
	else if (type == (TS::GRAPHIC_RESOURCE_MAPPING_TYPE_READ & TS::GRAPHIC_RESOURCE_MAPPING_TYPE_WRITE))
	{
		d3d11Map = D3D11_MAP_READ_WRITE;
	}

	d3d11Flags = 0;
	if (flag & TS::GRAPHIC_RESOURCE_MAPPING_FLAG_DO_NOT_WAIT)
	{
		d3d11Flags |= D3D11_MAP_FLAG_DO_NOT_WAIT;
	}
}

DXGI_FORMAT TS_D3D11::convertInputLayoutFormatTStoDXGI(TS::InputLayoutElementType type, uint32_t componentsNum)
{
	switch (type)
	{
	case TS::InputLayoutElementType::Float16:
	{
		switch (componentsNum)
		{
		case 1:
			return DXGI_FORMAT_R16_FLOAT;
		case 2:
			return DXGI_FORMAT_R16G16_FLOAT;
		case 4:
			return DXGI_FORMAT_R16G16B16A16_FLOAT;
		default:
			return DXGI_FORMAT_UNKNOWN;
		}
	}

	case TS::InputLayoutElementType::Float32:
	{
		switch (componentsNum)
		{
		case 1:
			return DXGI_FORMAT_R32_FLOAT;
		case 2:
			return DXGI_FORMAT_R32G32_FLOAT;
		case 3:
			return DXGI_FORMAT_R32G32B32_FLOAT;
		case 4:
			return DXGI_FORMAT_R32G32B32A32_FLOAT;
		default:
			return DXGI_FORMAT_UNKNOWN;
		}
	}

	case TS::InputLayoutElementType::Int32:
	{
		switch (componentsNum)
		{
		case 1:
			return DXGI_FORMAT_R32_SINT;
		case 2:
			return DXGI_FORMAT_R32G32_SINT;
		case 3:
			return DXGI_FORMAT_R32G32B32_SINT;
		case 4:
			return DXGI_FORMAT_R32G32B32A32_SINT;
		default:
			return DXGI_FORMAT_UNKNOWN;
		}
	}

	case TS::InputLayoutElementType::UInt32:
	{
		switch (componentsNum)
		{
		case 1:
			return DXGI_FORMAT_R32_UINT;
		case 2:
			return DXGI_FORMAT_R32G32_UINT;
		case 3:
			return DXGI_FORMAT_R32G32B32_UINT;
		case 4:
			return DXGI_FORMAT_R32G32B32A32_UINT;
		default:
			return DXGI_FORMAT_UNKNOWN;
		}
	}

	case TS::InputLayoutElementType::Int16:
	{
		switch (componentsNum)
		{
		case 1:
			return DXGI_FORMAT_R16_SINT;
		case 2:
			return DXGI_FORMAT_R16G16_SINT;
		case 4:
			return DXGI_FORMAT_R16G16B16A16_SINT;
		default:
			return DXGI_FORMAT_UNKNOWN;
		}
	}

	case TS::InputLayoutElementType::UInt16:
	{
		switch (componentsNum)
		{
		case 1:
			return DXGI_FORMAT_R16_UINT;
		case 2:
			return DXGI_FORMAT_R16G16_UINT;
		case 4:
			return DXGI_FORMAT_R16G16B16A16_UINT;
		default:
			return DXGI_FORMAT_UNKNOWN;
		}
	}

	case TS::InputLayoutElementType::Int8:
	{
		switch (componentsNum)
		{
		case 1:
			return DXGI_FORMAT_R8_SINT;
		case 2:
			return DXGI_FORMAT_R8G8_SINT;
		case 4:
			return DXGI_FORMAT_R8G8B8A8_SINT;
		default:
			return DXGI_FORMAT_UNKNOWN;
		}
	}

	case TS::InputLayoutElementType::UInt8:
	{
		switch (componentsNum)
		{
		case 1:
			return DXGI_FORMAT_R8_UINT;
		case 2:
			return DXGI_FORMAT_R8G8_UINT;
		case 4:
			return DXGI_FORMAT_R8G8B8A8_UINT;
		default:
			return DXGI_FORMAT_UNKNOWN;
		}
	}

	default:
		return DXGI_FORMAT_UNKNOWN;
	}
}

void TS_D3D11::convertInputLayoutTStoD3D11(const TS::InputLayoutDesc& desc,
                                           std::vector<D3D11_INPUT_ELEMENT_DESC>& d3d11Descs)
{
	const size_t elementsCount = desc.m_elements.size();
	d3d11Descs.resize(elementsCount);

	for (size_t elementIndex = 0; elementIndex < elementsCount; ++elementIndex)
	{
		const TS::InputLayoutElementDesc& elementDesc = desc.m_elements[elementIndex];
		const TS::InputLayoutBindingDesc& elementBindingDesc = desc.m_bindings[elementDesc.m_slot];

		D3D11_INPUT_ELEMENT_DESC& d3d11ElementDesc = d3d11Descs[elementIndex];
		d3d11ElementDesc.SemanticName = elementDesc.m_semanticName;
		d3d11ElementDesc.SemanticIndex = elementDesc.m_index;
		d3d11ElementDesc.Format = convertInputLayoutFormatTStoDXGI(elementDesc.m_type, elementDesc.m_componentsCount);
		d3d11ElementDesc.InputSlot = elementDesc.m_slot;
		d3d11ElementDesc.AlignedByteOffset = elementDesc.m_offset;
		d3d11ElementDesc.InputSlotClass = convertInputLayoutBindingTypeTStoD3D11(elementBindingDesc.m_type);
		d3d11ElementDesc.InstanceDataStepRate = elementBindingDesc.m_type == TS::InputLayoutBindingType::InstanceBinding ? 1 : 0;
	}
}
