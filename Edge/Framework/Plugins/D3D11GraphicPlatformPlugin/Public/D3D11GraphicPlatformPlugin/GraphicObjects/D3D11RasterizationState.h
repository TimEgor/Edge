#pragma once

#include "EdgeFramework/Graphics/GraphicPlatform/GraphicObject/RasterizationState.h"

#include "D3D11GraphicPlatformPlugin/D3D11ComPtrDefinitions.h"

namespace EdgeD3D11
{
	class D3D11RasterizationState final : public Edge::RasterizationState {
	private:
		D3D11RasterizerStateComPtr m_state;

	public:
		D3D11RasterizationState(const Edge::RasterizationStateDesc& desc, const D3D11DeviceComPtr& device);

		const D3D11RasterizerStateComPtr& getStateHandle() const { return m_state; }

		virtual void* getNativeHandle() const override { return m_state.Get(); }

		virtual void setName(const char* name) override;

	};
}