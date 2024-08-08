#pragma once

#include "EdgeFramework/Graphics/GraphicPlatform/GraphicPlatform.h"

#define EDGE_D3D11_GRAPHIC_PLATFORM_TYPE

namespace EdgeD3D11
{
	class D3D11GraphicDevice;

	class D3D11GraphicPlatform final : public Edge::GraphicPlatform
	{
	private:
		D3D11GraphicDevice* m_d3d11Device = nullptr;

	public:
		D3D11GraphicPlatform() = default;

		virtual bool init() override;
		virtual void release() override;

		virtual Edge::GraphicDevice& getGraphicDevice() override;

		EDGE_GRAPHIC_PLATFORM_TYPE(EDGE_D3D11_GRAPHIC_PLATFORM_TYPE)
	};
}
