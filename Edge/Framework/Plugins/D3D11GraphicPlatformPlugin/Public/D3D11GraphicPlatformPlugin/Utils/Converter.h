#pragma once

#include <vector>

#include "EdgeFramework/Graphics/GraphicPlatform/DefferedGraphicContext.h"
#include "EdgeFramework/Graphics/GraphicPlatform/GraphicObject/Format.h"
#include "EdgeFramework/Graphics/GraphicPlatform/GraphicObject/GraphicResource.h"
#include "EdgeFramework/Graphics/GraphicPlatform/GraphicObject/InputLayout.h"
#include "EdgeFramework/Graphics/GraphicPlatform/GraphicObject/RasterizationState.h"

#include "D3D11GraphicPlatformPlugin/D3D11Core.h"

namespace EdgeD3D11
{
	DXGI_FORMAT convertTSFormatToDXGI(Edge::GraphicResourceFormat format);

	D3D11_PRIMITIVE_TOPOLOGY convertTSPrimitiveTopologyToD3D11(Edge::PrimitiveTopology topology);
	D3D11_CULL_MODE convertTSRasterizationCullModeToD3D11(Edge::RasterizationCullMode mode);
	D3D11_FILL_MODE convertTSRasterizationFillModeToD3D11(Edge::RasterizationFillMode mode);

	D3D11_USAGE convertTSResourceAccessToD3D11(Edge::GraphicResourceAccessValueType access);
	UINT convertTSCPUAccessToD3D11(Edge::GraphicResourceAccessValueType access);
	UINT convertTSBufferUsageToD3D11(Edge::GraphicResourceUsageValueType usage);
	UINT convertTSTextureUsageToD3D11(Edge::GraphicResourceUsageValueType usage);

	void convertTSMapParamsToD3D11(Edge::GraphicResourceMappingType type, Edge::GraphicResourceMappingFlag flag,
		D3D11_MAP& d3d11Map, UINT& d3d11Flags);

	D3D11_INPUT_CLASSIFICATION convertInputLayoutBindingTypeTStoD3D11(Edge::InputLayoutBindingType bindingType);
	DXGI_FORMAT convertInputLayoutFormatTStoDXGI(Edge::InputLayoutElementType type, uint32_t componentsNum);

	void convertInputLayoutTStoD3D11(const Edge::InputLayoutDesc& desc, std::vector<D3D11_INPUT_ELEMENT_DESC>& d3d11Descs);
}
