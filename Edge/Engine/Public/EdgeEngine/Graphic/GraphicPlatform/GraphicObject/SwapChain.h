#pragma once

#include "Format.h"
#include "IGraphicObject.h"

#include <cstdint>

#define EDGE_GRAPHIC_RESOURCE_SWAP_CHAIN_TYPE

namespace Edge
{
	class ITexture2D;

	struct SwapChainDesc final
	{
		GraphicResourceFormat m_format = GraphicResourceFormat::Undefined;
		uint32_t m_bufferCount = 0;
	};

	class ISwapChain : public IGraphicObject
	{
	public:
		ISwapChain() = default;

		virtual ITexture2D* getTargetTexture() = 0;

		virtual void present() = 0;

		virtual const SwapChainDesc& getDesc() const = 0;
	};

	class SwapChainBase : public ISwapChain
	{
	private:
		const SwapChainDesc m_desc;

	public:
		SwapChainBase(const SwapChainDesc& desc)
			: m_desc(desc) {}

		const SwapChainDesc& getDesc() const { return m_desc; }
	};
}
