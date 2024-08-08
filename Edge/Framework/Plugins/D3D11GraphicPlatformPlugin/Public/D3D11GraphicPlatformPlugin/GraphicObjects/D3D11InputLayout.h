#pragma once

#include "D3D11GraphicPlatformPlugin/D3D11ComPtrDefinitions.h"
#include "EdgeFramework/Graphics/GraphicPlatform/GraphicObject/InputLayout.h"

namespace EdgeD3D11
{
	class D3D11InputLayout final : public Edge::InputLayout
	{
	private:
		D3D11InputLayoutComPtr m_d3d11InputLayout;

	public:
		D3D11InputLayout(const Edge::InputLayoutDesc& desc, const D3D11DeviceComPtr& device, const D3DBlobComPtr& shaderCode);

		virtual void* getNativeHandle() const override { return m_d3d11InputLayout.Get(); }

		const D3D11InputLayoutComPtr& getInputLayoutHandle() const { return m_d3d11InputLayout; }
	};
}