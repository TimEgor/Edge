#pragma once

#include "EdgeFramework/Graphics/GraphicPlatform/GraphicObject/BlendState.h"

#include "D3D11GraphicPlatformPlugin/D3D11ComPtrDefinitions.h"

namespace EdgeD3D11
{
	class D3D11BlendState final : public Edge::BlendState {
	private:
		D3D11BlendStateComPtr m_state;

	public:
		D3D11BlendState(Edge::BlendMode mode, const D3D11DeviceComPtr& device);

		const D3D11BlendStateComPtr& getStateHandle() const { return m_state; }

		virtual void* getNativeHandle() const override { return m_state.Get(); }

		virtual void setName(const char* name) override;

	};
}
