#pragma once

#include "EdgeFramework/Graphics/GraphicPlatform/DefferedGraphicContext.h"
#include "EdgeFramework/Graphics/GraphicPlatform/GraphicObject/Format.h"
#include "EdgeFramework/Graphics/GraphicPlatform/GraphicObject/GraphicResource.h"
#include "EdgeFramework/Graphics/GraphicPlatform/GraphicObject/InputLayout.h"
#include "EdgeFramework/Graphics/GraphicPlatform/GraphicObject/RasterizationState.h"

#include "D3D11GraphicPlatformPlugin/D3D11Core.h"

#include <vector>

namespace EdgeD3D11
{
	DXGI_FORMAT ConvertEdgeFormatToDXGI(Edge::GraphicResourceFormat format);

	D3D11_PRIMITIVE_TOPOLOGY ConvertEdgePrimitiveTopologyToD3D11(Edge::PrimitiveTopology topology);
	D3D11_CULL_MODE ConvertEdgeRasterizationCullModeToD3D11(Edge::RasterizationCullMode mode);
	D3D11_FILL_MODE ConvertEdgeRasterizationFillModeToD3D11(Edge::RasterizationFillMode mode);

	D3D11_USAGE ConvertEdgeResourceAccessToD3D11(Edge::GraphicResourceAccessValueType access);
	UINT ConvertEdgeCpuAccessToD3D11(Edge::GraphicResourceAccessValueType access);
	UINT ConvertEdgeBufferUsageToD3D11(Edge::GraphicResourceUsageValueType usage);
	UINT ConvertEdgeTextureUsageToD3D11(Edge::GraphicResourceUsageValueType usage);

	void ConvertEdgeMapParamsToD3D11(
		Edge::GraphicResourceMappingType type,
		Edge::GraphicResourceMappingFlag flag,
		D3D11_MAP& d3d11Map,
		UINT& d3d11Flags
	);

	D3D11_INPUT_CLASSIFICATION ConvertEdgeInputLayoutBindingTypeToD3D11(Edge::InputLayoutBindingType bindingType);
	DXGI_FORMAT ConvertEdgeInputLayoutFormatToDxgi(Edge::InputLayoutElementType type, uint32_t componentsNum);

	void ConvertEdgeInputLayoutToD3D11(const Edge::InputLayoutDesc& desc, std::vector<D3D11_INPUT_ELEMENT_DESC>& d3d11Descs);
}
