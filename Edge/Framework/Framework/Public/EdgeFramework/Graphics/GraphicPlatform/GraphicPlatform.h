#pragma once

#include "EdgeCommon/HashedType.h"

namespace Edge
{
	class GraphicDevice;
	class GraphicDeferredContext;

	using GraphicPlatformType = HashedType::Type;

	class GraphicPlatform : public HashedType
	{
	public:
		GraphicPlatform() = default;

		virtual bool init() = 0;
		virtual void release() = 0;

		virtual GraphicDevice& getGraphicDevice() = 0;

		virtual GraphicPlatformType getType() const = 0;
	};
}

#define EDGE_GRAPHIC_PLATFORM_TYPE(GRAPHIC_PLATFORM_TYPE) EDGE_HASH_TYPE(#GRAPHIC_PLATFORM_TYPE, Edge::GraphicPlatformType, GraphicPlatform)