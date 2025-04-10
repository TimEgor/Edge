#pragma once

#include "EdgeFramework/Graphics/GraphicPlatform/GraphicObject/DepthStencilState.h"

#include "D3D11GraphicPlatformPlugin/D3D11ComPtrDefinitions.h"

namespace EdgeD3D11
{
	class D3D11DepthStencilState final : public Edge::DepthStencilState {
	private:
		D3D11DepthStencilStateComPtr m_state;

	public:
		D3D11DepthStencilState(const Edge::DepthStencilStateDesc& desc, const D3D11DeviceComPtr& device);

		const D3D11DepthStencilStateComPtr& getStateHandle() const { return m_state; }

		virtual void* getNativeHandle() const override { return m_state.Get(); }

		virtual void setName(const char* name) override;

	};
}
