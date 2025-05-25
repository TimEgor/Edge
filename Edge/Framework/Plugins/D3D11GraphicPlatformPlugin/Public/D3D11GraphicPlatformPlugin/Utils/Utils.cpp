#include "Utils.h"

uint32_t EdgeD3D11::GetEdgeFormatBitCount(Edge::GraphicResourceFormat format)
{
	switch (format)
	{
	case Edge::GraphicResourceFormat::R8_UNORM:
	case Edge::GraphicResourceFormat::R8_SNORM:
	case Edge::GraphicResourceFormat::R8_UINT:
	case Edge::GraphicResourceFormat::R8_SINT:
		return 8;
	case Edge::GraphicResourceFormat::R8G8_UNORM:
	case Edge::GraphicResourceFormat::R8G8_SNORM:
	case Edge::GraphicResourceFormat::R8G8_UINT:
	case Edge::GraphicResourceFormat::R8G8_SINT:
	case Edge::GraphicResourceFormat::R16_UNORM:
	case Edge::GraphicResourceFormat::R16_SNORM:
	case Edge::GraphicResourceFormat::R16_UINT:
	case Edge::GraphicResourceFormat::R16_SINT:
	case Edge::GraphicResourceFormat::R16_SFLOAT:
		return 16;
	case Edge::GraphicResourceFormat::R8G8B8A8_UNORM:
	case Edge::GraphicResourceFormat::R8G8B8A8_SNORM:
	case Edge::GraphicResourceFormat::R8G8B8A8_UINT:
	case Edge::GraphicResourceFormat::R8G8B8A8_SINT:
		return 24;
	case Edge::GraphicResourceFormat::R16G16_UNORM:
	case Edge::GraphicResourceFormat::R16G16_SNORM:
	case Edge::GraphicResourceFormat::R16G16_UINT:
	case Edge::GraphicResourceFormat::R16G16_SINT:
	case Edge::GraphicResourceFormat::R16G16_SFLOAT:
	case Edge::GraphicResourceFormat::R32_UINT:
	case Edge::GraphicResourceFormat::R32_SINT:
	case Edge::GraphicResourceFormat::R32_SFLOAT:
	case Edge::GraphicResourceFormat::D24_UNORM_S8_UINT:
		return 32;
	case Edge::GraphicResourceFormat::D32_SFLOAT_S8_UINT:
		return 40;
	case Edge::GraphicResourceFormat::R16G16B16A16_UNORM:
	case Edge::GraphicResourceFormat::R16G16B16A16_SNORM:
	case Edge::GraphicResourceFormat::R16G16B16A16_UINT:
	case Edge::GraphicResourceFormat::R16G16B16A16_SINT:
	case Edge::GraphicResourceFormat::R16G16B16A16_SFLOAT:
	case Edge::GraphicResourceFormat::R32G32_UINT:
	case Edge::GraphicResourceFormat::R32G32_SINT:
	case Edge::GraphicResourceFormat::R32G32_SFLOAT:
		return 64;
	case Edge::GraphicResourceFormat::R32G32B32_UINT:
	case Edge::GraphicResourceFormat::R32G32B32_SINT:
	case Edge::GraphicResourceFormat::R32G32B32_SFLOAT:
		return 96;
	case Edge::GraphicResourceFormat::R32G32B32A32_UINT:
	case Edge::GraphicResourceFormat::R32G32B32A32_SINT:
	case Edge::GraphicResourceFormat::R32G32B32A32_SFLOAT:
		return 128;
	case Edge::GraphicResourceFormat::Undefined:
	default:
		return 0;
	}
}