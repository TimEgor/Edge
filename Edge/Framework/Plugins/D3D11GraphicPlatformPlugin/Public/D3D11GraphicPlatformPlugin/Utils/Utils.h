#pragma once

#include "EdgeFramework/Graphics/GraphicPlatform/GraphicObject/Format.h"

#include "D3D11GraphicPlatformPlugin/D3D11Core.h"

namespace EdgeD3D11
{
	uint32_t GetEdgeFormatBitCount(Edge::GraphicResourceFormat format);
}