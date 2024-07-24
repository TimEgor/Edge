#pragma once

#include <vector>

#include "TinySimFramework/Graphics/GraphicPlatform/DefferedGraphicContext.h"
#include "TinySimFramework/Graphics/GraphicPlatform/GraphicObject/Format.h"
#include "TinySimFramework/Graphics/GraphicPlatform/GraphicObject/GraphicResource.h"
#include "TinySimFramework/Graphics/GraphicPlatform/GraphicObject/InputLayout.h"
#include "TinySimFramework/Graphics/GraphicPlatform/GraphicObject/RasterizationState.h"

#include "D3D11GraphicPlatformPlugin/D3D11Core.h"

namespace TS_D3D11
{
	DXGI_FORMAT convertTSFormatToDXGI(TS::GraphicResourceFormat format);

	D3D11_PRIMITIVE_TOPOLOGY convertTSPrimitiveTopologyToD3D11(TS::PrimitiveTopology topology);
	D3D11_CULL_MODE convertTSRasterizationCullModeToD3D11(TS::RasterizationCullMode mode);
	D3D11_FILL_MODE convertTSRasterizationFillModeToD3D11(TS::RasterizationFillMode mode);

	D3D11_USAGE convertTSResourceAccessToD3D11(TS::GraphicResourceAccessValueType access);
	UINT convertTSCPUAccessToD3D11(TS::GraphicResourceAccessValueType access);
	UINT convertTSBufferUsageToD3D11(TS::GraphicResourceUsageValueType usage);
	UINT convertTSTextureUsageToD3D11(TS::GraphicResourceUsageValueType usage);

	void convertTSMapParamsToD3D11(TS::GraphicResourceMappingType type, TS::GraphicResourceMappingFlag flag,
		D3D11_MAP& d3d11Map, UINT& d3d11Flags);

	D3D11_INPUT_CLASSIFICATION convertInputLayoutBindingTypeTStoD3D11(TS::InputLayoutBindingType bindingType);
	DXGI_FORMAT convertInputLayoutFormatTStoDXGI(TS::InputLayoutElementType type, uint32_t componentsNum);

	void convertInputLayoutTStoD3D11(const TS::InputLayoutDesc& desc, std::vector<D3D11_INPUT_ELEMENT_DESC>& d3d11Descs);
}
