#pragma once

#include "EdgeFramework/Graphics/GraphicPlatform/GraphicObject/SamplerState.h"

#include "D3D11GraphicPlatformPlugin/D3D11ComPtrDefinitions.h"

namespace EdgeD3D11
{
	class D3D11SamplerState final : public Edge::SamplerState {
	private:
		D3D11SamplerStateComPtr m_state;

	public:
		D3D11SamplerState(const D3D11DeviceComPtr& device);

		const D3D11SamplerStateComPtr& getStateHandle() const { return m_state; }

		virtual void* getNativeHandle() const override { return m_state.Get(); }

		virtual void setName(const char* name) override;

	};
}