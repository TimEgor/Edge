#pragma once

#include "D3D11GraphicPlatformPlugin/D3D11ComPtrDefinitions.h"
#include "TinySimFramework/Graphics/GraphicPlatform/GraphicObject/GPUBuffer.h"

namespace TS_D3D11
{
	class D3D11GPUBuffer final : public TS::GPUBuffer
	{
	private:
		D3D11BufferComPtr m_buffer;

	public:
		D3D11GPUBuffer(const TS::GPUBufferDesc& desc, const D3D11DeviceComPtr& device, const TS::InitialGPUBufferData* initialData);

		const D3D11BufferComPtr& getBufferHandle() const { return m_buffer; }

		virtual void* getNativeHandle() const override { return m_buffer.Get(); }
	};
}
