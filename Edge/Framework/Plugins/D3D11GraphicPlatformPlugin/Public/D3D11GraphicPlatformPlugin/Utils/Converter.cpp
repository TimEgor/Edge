#include "Converter.h"

#include "EdgeFramework/Graphics/GraphicPlatform/GraphicObject/GPUBuffer.h"
#include "EdgeFramework/Graphics/GraphicPlatform/GraphicObject/Texture.h"

DXGI_FORMAT EdgeD3D11::ConvertEdgeFormatToDXGI(Edge::GraphicResourceFormat format)
{
	switch (format)
	{
	case Edge::GraphicResourceFormat::R8_UNORM:
		return DXGI_FORMAT_R8_UNORM;
	case Edge::GraphicResourceFormat::R8_SNORM:
		return DXGI_FORMAT_R8_SNORM;
	case Edge::GraphicResourceFormat::R8_UINT:
		return DXGI_FORMAT_R8_UINT;
	case Edge::GraphicResourceFormat::R8_SINT:
		return DXGI_FORMAT_R8_SINT;

	case Edge::GraphicResourceFormat::R8G8_UNORM:
		return DXGI_FORMAT_R8G8_UNORM;
	case Edge::GraphicResourceFormat::R8G8_SNORM:
		return DXGI_FORMAT_R8G8_SNORM;
	case Edge::GraphicResourceFormat::R8G8_UINT:
		return DXGI_FORMAT_R8G8_UINT;
	case Edge::GraphicResourceFormat::R8G8_SINT:
		return DXGI_FORMAT_R8G8_SINT;

	case Edge::GraphicResourceFormat::R8G8B8A8_UNORM:
		return DXGI_FORMAT_R8G8B8A8_UNORM;
	case Edge::GraphicResourceFormat::R8G8B8A8_SNORM:
		return DXGI_FORMAT_R8G8B8A8_SNORM;
	case Edge::GraphicResourceFormat::R8G8B8A8_UINT:
		return DXGI_FORMAT_R8G8B8A8_UINT;
	case Edge::GraphicResourceFormat::R8G8B8A8_SINT:
		return DXGI_FORMAT_R8G8B8A8_SINT;

	case Edge::GraphicResourceFormat::R16_UNORM:
		return DXGI_FORMAT_R16_UNORM;
	case Edge::GraphicResourceFormat::R16_SNORM:
		return DXGI_FORMAT_R16_SNORM;
	case Edge::GraphicResourceFormat::R16_UINT:
		return DXGI_FORMAT_R16_UINT;
	case Edge::GraphicResourceFormat::R16_SINT:
		return DXGI_FORMAT_R16_SINT;
	case Edge::GraphicResourceFormat::R16_SFLOAT:
		return DXGI_FORMAT_R16_FLOAT;

	case Edge::GraphicResourceFormat::R16G16_UNORM:
		return DXGI_FORMAT_R16G16_UNORM;
	case Edge::GraphicResourceFormat::R16G16_SNORM:
		return DXGI_FORMAT_R16G16_SNORM;
	case Edge::GraphicResourceFormat::R16G16_UINT:
		return DXGI_FORMAT_R16G16_UINT;
	case Edge::GraphicResourceFormat::R16G16_SINT:
		return DXGI_FORMAT_R16G16_SINT;
	case Edge::GraphicResourceFormat::R16G16_SFLOAT:
		return DXGI_FORMAT_R16G16_FLOAT;

	case Edge::GraphicResourceFormat::R16G16B16A16_UNORM:
		return DXGI_FORMAT_R16G16B16A16_UNORM;
	case Edge::GraphicResourceFormat::R16G16B16A16_SNORM:
		return DXGI_FORMAT_R16G16B16A16_SNORM;
	case Edge::GraphicResourceFormat::R16G16B16A16_UINT:
		return DXGI_FORMAT_R16G16B16A16_UINT;
	case Edge::GraphicResourceFormat::R16G16B16A16_SINT:
		return DXGI_FORMAT_R16G16B16A16_SINT;
	case Edge::GraphicResourceFormat::R16G16B16A16_SFLOAT:
		return DXGI_FORMAT_R16G16B16A16_FLOAT;

	case Edge::GraphicResourceFormat::R32_UINT:
		return DXGI_FORMAT_R32_UINT;
	case Edge::GraphicResourceFormat::R32_SINT:
		return DXGI_FORMAT_R32_SINT;
	case Edge::GraphicResourceFormat::R32_SFLOAT:
		return DXGI_FORMAT_R32_FLOAT;

	case Edge::GraphicResourceFormat::R32G32_UINT:
		return DXGI_FORMAT_R32G32_UINT;
	case Edge::GraphicResourceFormat::R32G32_SINT:
		return DXGI_FORMAT_R32G32_SINT;
	case Edge::GraphicResourceFormat::R32G32_SFLOAT:
		return DXGI_FORMAT_R32G32_FLOAT;

	case Edge::GraphicResourceFormat::R32G32B32_UINT:
		return DXGI_FORMAT_R32G32B32A32_UINT;
	case Edge::GraphicResourceFormat::R32G32B32_SINT:
		return DXGI_FORMAT_R32G32B32_SINT;
	case Edge::GraphicResourceFormat::R32G32B32_SFLOAT:
		return DXGI_FORMAT_R32G32B32_FLOAT;

	case Edge::GraphicResourceFormat::R32G32B32A32_UINT:
		return DXGI_FORMAT_R32G32B32A32_UINT;
	case Edge::GraphicResourceFormat::R32G32B32A32_SINT:
		return DXGI_FORMAT_R32G32B32A32_SINT;
	case Edge::GraphicResourceFormat::R32G32B32A32_SFLOAT:
		return DXGI_FORMAT_R32G32B32A32_FLOAT;

	case Edge::GraphicResourceFormat::D24_UNORM_S8_UINT:
		return DXGI_FORMAT_D24_UNORM_S8_UINT;
	case Edge::GraphicResourceFormat::D32_SFLOAT_S8_UINT:
		return DXGI_FORMAT_D32_FLOAT_S8X24_UINT;

	case Edge::GraphicResourceFormat::Undefined:
	default:
		return DXGI_FORMAT_UNKNOWN;
	}
}

D3D11_PRIMITIVE_TOPOLOGY EdgeD3D11::ConvertEdgePrimitiveTopologyToD3D11(Edge::PrimitiveTopology topology)
{
	switch (topology)
	{
	case Edge::PrimitiveTopology::PointList:
		return D3D11_PRIMITIVE_TOPOLOGY_POINTLIST;
	case Edge::PrimitiveTopology::LineList:
		return D3D11_PRIMITIVE_TOPOLOGY_LINELIST;
	case Edge::PrimitiveTopology::LineStrip:
		return D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP;
	case Edge::PrimitiveTopology::TriangleList:
		return D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
	case Edge::PrimitiveTopology::TriangleStrip:
		return D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP;
	case Edge::PrimitiveTopology::Undefined:
	default:
		return D3D11_PRIMITIVE_TOPOLOGY_UNDEFINED;
	}
}

D3D11_CULL_MODE EdgeD3D11::ConvertEdgeRasterizationCullModeToD3D11(Edge::RasterizationCullMode mode)
{
	switch (mode)
	{
	case Edge::RasterizationCullMode::BackFace:
		return D3D11_CULL_BACK;
	case Edge::RasterizationCullMode::FrontFace:
		return D3D11_CULL_FRONT;
	case Edge::RasterizationCullMode::None:
	default:
		return D3D11_CULL_NONE;
	}
}

D3D11_FILL_MODE EdgeD3D11::ConvertEdgeRasterizationFillModeToD3D11(Edge::RasterizationFillMode mode)
{
	switch (mode)
	{
	case Edge::RasterizationFillMode::Wireframe:
		return D3D11_FILL_WIREFRAME;
	case Edge::RasterizationFillMode::Solid:
	default:
		return D3D11_FILL_SOLID;
	}
}

D3D11_USAGE EdgeD3D11::ConvertEdgeResourceAccessToD3D11(Edge::GraphicResourceAccessValueType access)
{
	if (access == (Edge::GRAPHIC_RESOURCE_ACCESS_GPU_READ | Edge::GRAPHIC_RESOURCE_ACCESS_GPU_WRITE))
	{
		return D3D11_USAGE_DEFAULT;
	}

	if (access == Edge::GRAPHIC_RESOURCE_ACCESS_GPU_READ)
	{
		return D3D11_USAGE_IMMUTABLE;
	}

	if (access == (Edge::GRAPHIC_RESOURCE_ACCESS_CPU_WRITE | Edge::GRAPHIC_RESOURCE_ACCESS_GPU_READ))
	{
		return D3D11_USAGE_DYNAMIC;
	}

	if (access == Edge::GRAPHIC_RESOURCE_ACCESS_CPU_READ)
	{
		return D3D11_USAGE_STAGING;
	}

	assert(false && "Invalid graphic resource access");

	return D3D11_USAGE_DEFAULT;
}

UINT EdgeD3D11::ConvertEdgeCpuAccessToD3D11(Edge::GraphicResourceAccessValueType access)
{
	UINT d3d11CPUAccess = 0;

	if (access & Edge::GRAPHIC_RESOURCE_ACCESS_CPU_READ)
	{
		d3d11CPUAccess |= D3D11_CPU_ACCESS_READ;
	}

	if (access & Edge::GRAPHIC_RESOURCE_ACCESS_CPU_WRITE)
	{
		d3d11CPUAccess |= D3D11_CPU_ACCESS_WRITE;
	}

	return d3d11CPUAccess;
}

UINT EdgeD3D11::ConvertEdgeBufferUsageToD3D11(Edge::GraphicResourceUsageValueType usage)
{
	UINT d3d11Usage = 0;

	if (usage & Edge::GRAPHIC_RESOURCE_USAGE_ALLOW_UNORDERED_ACCESS)
	{
		d3d11Usage |= D3D11_BIND_UNORDERED_ACCESS;
	}

	if (usage & Edge::GRAPHIC_RESOURCE_USAGE_SHADER_RESOURCE)
	{
		d3d11Usage |= D3D11_BIND_SHADER_RESOURCE;
	}

	if (usage & Edge::GPU_BUFFER_USAGE_VERTEX_BUFFER)
	{
		d3d11Usage |= D3D11_BIND_VERTEX_BUFFER;
	}

	if (usage & Edge::GPU_BUFFER_USAGE_INDEX_BUFFER)
	{
		d3d11Usage |= D3D11_BIND_INDEX_BUFFER;
	}

	if (usage & Edge::GPU_BUFFER_USAGE_CONSTANT_BUFFER)
	{
		d3d11Usage |= D3D11_BIND_CONSTANT_BUFFER;
	}

	return d3d11Usage;
}

UINT EdgeD3D11::ConvertEdgeTextureUsageToD3D11(Edge::GraphicResourceUsageValueType usage)
{
	UINT d3d11Usage = 0;

	if (usage & Edge::GRAPHIC_RESOURCE_USAGE_ALLOW_UNORDERED_ACCESS)
	{
		d3d11Usage |= D3D11_BIND_UNORDERED_ACCESS;
	}

	if (usage & Edge::GRAPHIC_RESOURCE_USAGE_SHADER_RESOURCE)
	{
		d3d11Usage |= D3D11_BIND_SHADER_RESOURCE;
	}

	if (usage & Edge::TEXTURE_USAGE_RENDER_TARGET)
	{
		d3d11Usage |= D3D11_BIND_RENDER_TARGET;
	}

	if (usage & Edge::TEXTURE_USAGE_DEPTH_STENCIL)
	{
		d3d11Usage |= D3D11_BIND_DEPTH_STENCIL;
	}

	return d3d11Usage;
}

D3D11_INPUT_CLASSIFICATION EdgeD3D11::ConvertEdgeInputLayoutBindingTypeToD3D11(Edge::InputLayoutBindingType bindingType)
{
	switch (bindingType)
	{
	case Edge::InputLayoutBindingType::VertexBinding:
		return D3D11_INPUT_PER_VERTEX_DATA;
	case Edge::InputLayoutBindingType::InstanceBinding:
		return D3D11_INPUT_PER_INSTANCE_DATA;
	default:
		return static_cast<D3D11_INPUT_CLASSIFICATION>(-1);
	}
}

void EdgeD3D11::ConvertEdgeMapParamsToD3D11(Edge::GraphicResourceMappingType type, Edge::GraphicResourceMappingFlag flag,
	D3D11_MAP& d3d11Map, UINT& d3d11Flags)
{
	d3d11Map = static_cast<D3D11_MAP>(0);

	if (type == Edge::GRAPHIC_RESOURCE_MAPPING_TYPE_READ)
	{
		d3d11Map = D3D11_MAP_READ;
	}
	else if (type == Edge::GRAPHIC_RESOURCE_MAPPING_TYPE_WRITE)
	{
		if (flag == Edge::GRAPHIC_RESOURCE_MAPPING_FLAG_DISCARD)
		{
			d3d11Map = D3D11_MAP_WRITE_DISCARD;
		}
		else if (flag == Edge::GRAPHIC_RESOURCE_MAPPING_FLAG_NO_OVERWRITE)
		{
			d3d11Map = D3D11_MAP_WRITE_NO_OVERWRITE;
		}
		else
		{
			d3d11Map = D3D11_MAP_WRITE;
		}
	}
	else if (type == (Edge::GRAPHIC_RESOURCE_MAPPING_TYPE_READ & Edge::GRAPHIC_RESOURCE_MAPPING_TYPE_WRITE))
	{
		d3d11Map = D3D11_MAP_READ_WRITE;
	}

	d3d11Flags = 0;
	if (flag & Edge::GRAPHIC_RESOURCE_MAPPING_FLAG_DO_NOT_WAIT)
	{
		d3d11Flags |= D3D11_MAP_FLAG_DO_NOT_WAIT;
	}
}

DXGI_FORMAT EdgeD3D11::ConvertEdgeInputLayoutFormatToDxgi(Edge::InputLayoutElementType type, uint32_t componentsNum)
{
	switch (type)
	{
	case Edge::InputLayoutElementType::Float16:
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

	case Edge::InputLayoutElementType::Float32:
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

	case Edge::InputLayoutElementType::Int32:
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

	case Edge::InputLayoutElementType::UInt32:
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

	case Edge::InputLayoutElementType::Int16:
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

	case Edge::InputLayoutElementType::UInt16:
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

	case Edge::InputLayoutElementType::Int8:
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

	case Edge::InputLayoutElementType::UInt8:
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

void EdgeD3D11::ConvertEdgeInputLayoutToD3D11(const Edge::InputLayoutDesc& desc,
                                           std::vector<D3D11_INPUT_ELEMENT_DESC>& d3d11Descs)
{
	const size_t elementsCount = desc.m_elements.size();
	d3d11Descs.resize(elementsCount);

	for (size_t elementIndex = 0; elementIndex < elementsCount; ++elementIndex)
	{
		const Edge::InputLayoutElementDesc& elementDesc = desc.m_elements[elementIndex];
		const Edge::InputLayoutBindingDesc& elementBindingDesc = desc.m_bindings[elementDesc.m_slot];

		D3D11_INPUT_ELEMENT_DESC& d3d11ElementDesc = d3d11Descs[elementIndex];
		d3d11ElementDesc.SemanticName = elementDesc.m_semanticName;
		d3d11ElementDesc.SemanticIndex = elementDesc.m_index;
		d3d11ElementDesc.Format = ConvertEdgeInputLayoutFormatToDxgi(elementDesc.m_type, elementDesc.m_componentsCount);
		d3d11ElementDesc.InputSlot = elementDesc.m_slot;
		d3d11ElementDesc.AlignedByteOffset = elementDesc.m_offset;
		d3d11ElementDesc.InputSlotClass = ConvertEdgeInputLayoutBindingTypeToD3D11(elementBindingDesc.m_type);
		d3d11ElementDesc.InstanceDataStepRate = elementBindingDesc.m_type == Edge::InputLayoutBindingType::InstanceBinding ? 1 : 0;
	}
}
