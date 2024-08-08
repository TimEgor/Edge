#pragma once

#include "Format.h"
#include "GraphicObject.h"

#include <cstdint>

#define EDGE_GRAPHIC_RESOURCE_SWAP_CHAIN_TYPE

namespace Edge
{
	class Texture2D;

	struct SwapChainDesc final
	{
		GraphicResourceFormat m_format = GraphicResourceFormat::Undefined;
		uint32_t m_bufferCount = 0;
	};

	class SwapChain : public GraphicObject
	{
	private:
		const SwapChainDesc m_desc;

	public:
		SwapChain(const SwapChainDesc& desc)
			: m_desc(desc) {}

		virtual Texture2D* getTargetTexture() = 0;

		virtual void present() = 0;

		const SwapChainDesc& getDesc() const { return m_desc; }
	};
}
