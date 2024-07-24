#pragma once

#include "D3D11GraphicPlatformPlugin/D3D11ComPtrDefinitions.h"
#include "TinySimFramework/Graphics/GraphicPlatform/GraphicObject/InputLayout.h"

namespace TS_D3D11
{
	class D3D11InputLayout final : public TS::InputLayout
	{
	private:
		D3D11InputLayoutComPtr m_d3d11InputLayout;

	public:
		D3D11InputLayout(const TS::InputLayoutDesc& desc, const D3D11DeviceComPtr& device, const D3DBlobComPtr& shaderCode);

		virtual void* getNativeHandle() const override { return m_d3d11InputLayout.Get(); }

		const D3D11InputLayoutComPtr& getInputLayoutHandle() const { return m_d3d11InputLayout; }
	};
}