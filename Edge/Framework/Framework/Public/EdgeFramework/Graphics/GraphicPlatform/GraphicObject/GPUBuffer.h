#pragma once

#include "GraphicResource.h"

#define EDGE_GRAPHIC_RESOURCE_BUFFER_TYPE

namespace Edge
{
	enum GPUBufferUsage : GraphicResourceUsageValueType
	{
		GPU_BUFFER_USAGE_VERTEX_BUFFER = GRAPHIC_RESOURCE_MAX_USAGE << 1,
		GPU_BUFFER_USAGE_INDEX_BUFFER = GRAPHIC_RESOURCE_MAX_USAGE << 2,
		GPU_BUFFER_USAGE_CONSTANT_BUFFER = GRAPHIC_RESOURCE_MAX_USAGE << 3
	};

	struct GPUBufferDesc final
	{
		uint32_t m_size = 0;
		uint32_t m_stride = 0;
		GraphicResourceUsageValueType m_usage = GRAPHIC_RESOURCE_USAGE_UNDEFINED;
		GraphicResourceAccessValueType m_access = GRAPHIC_RESOURCE_ACCESS_UNDEFINED;
	};

	class GPUBuffer : public GraphicResource
	{
	private:
		const GPUBufferDesc m_desc;

	public:
		GPUBuffer(const GPUBufferDesc& desc)
			: m_desc(desc) {}

		const GPUBufferDesc& getDesc() const { return m_desc; }

		EDGE_GRAPHIC_RESOURCE_TYPE(EDGE_GRAPHIC_RESOURCE_BUFFER_TYPE)
	};
}
