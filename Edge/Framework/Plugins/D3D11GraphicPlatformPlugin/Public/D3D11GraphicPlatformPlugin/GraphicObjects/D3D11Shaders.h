#pragma once

#include "EdgeFramework/Graphics/GraphicPlatform/GraphicObject/Shader.h"

#include "D3D11GraphicPlatformPlugin/D3D11ComPtrDefinitions.h"

namespace EdgeD3D11
{
	class D3D11ShaderBase
	{
	private:
		D3DBlobComPtr m_code;

	public:
		D3D11ShaderBase(const D3DBlobComPtr& code)
			: m_code(code) {}
		virtual ~D3D11ShaderBase() = default;

		const D3DBlobComPtr& getCode() const { return m_code; }
	};

	class D3D11VertexShader final : public D3D11ShaderBase, public Edge::VertexShader
	{
	private:
		D3D11VertexShaderComPtr m_shader;

	public:
		D3D11VertexShader(const D3D11DeviceComPtr& device, const D3DBlobComPtr& code);

		const D3D11VertexShaderComPtr& getShaderHandle() const { return m_shader; }

		virtual void* getNativeHandle() const override { return m_shader.Get(); }

		virtual void setName(const char* name) override;
	};

	class D3D11PixelShader final : public D3D11ShaderBase, public Edge::PixelShader
	{
	private:
		D3D11PixelShaderComPtr m_shader;

	public:
		D3D11PixelShader(const D3D11DeviceComPtr& device, const D3DBlobComPtr& code);

		const D3D11PixelShaderComPtr& getShaderHandle() const { return m_shader; }

		virtual void* getNativeHandle() const override { return m_shader.Get(); }

		virtual void setName(const char* name) override;
	};

	class D3D11ComputeShader final : public D3D11ShaderBase, public Edge::ComputeShader
	{
	private:
		D3D11ComputeShaderComPtr m_shader;

	public:
		D3D11ComputeShader(const D3D11DeviceComPtr& device, const D3DBlobComPtr& code);

		const D3D11ComputeShaderComPtr& getShaderHandle() const { return m_shader; }

		virtual void* getNativeHandle() const override { return m_shader.Get(); }

		virtual void setName(const char* name) override;
	};
}
