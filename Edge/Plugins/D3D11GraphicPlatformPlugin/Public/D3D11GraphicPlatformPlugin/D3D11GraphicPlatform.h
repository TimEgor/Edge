#pragma once

#include "TinySimFramework/Graphics/GraphicPlatform/GraphicPlatform.h"

#define TS_D3D11_GRAPHIC_PLATFORM_TYPE

namespace TS_D3D11
{
	class D3D11GraphicDevice;

	class D3D11GraphicPlatform final : public TS::GraphicPlatform
	{
	private:
		D3D11GraphicDevice* m_d3d11Device = nullptr;

	public:
		D3D11GraphicPlatform() = default;

		virtual bool init() override;
		virtual void release() override;

		virtual TS::GraphicDevice& getGraphicDevice() override;

		TS_GRAPHIC_PLATFORM_TYPE(TS_D3D11_GRAPHIC_PLATFORM_TYPE)
	};
}
