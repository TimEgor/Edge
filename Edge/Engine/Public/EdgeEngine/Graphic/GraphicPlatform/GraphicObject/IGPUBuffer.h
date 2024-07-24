#pragma once

#include "IGraphicResource.h"

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

	struct InitialGPUBufferData final
	{
		const void* m_data = nullptr;
		uint32_t m_dataSize = 0;

		InitialGPUBufferData(const void* data, uint32_t dataSize)
			: m_data(data), m_dataSize(dataSize) {}

		bool isValid() const { return m_data && m_dataSize; }
	};

	class IGPUBuffer : public IGraphicResource
	{
	public:
		IGPUBuffer() = default;

		virtual const GPUBufferDesc& getDesc() const = 0;

		EDGE_GRAPHIC_RESOURCE_TYPE(EDGE_GRAPHIC_RESOURCE_BUFFER_TYPE)
	};

	class GPUBufferBase : public IGPUBuffer
	{
	private:
		const GPUBufferDesc m_desc;

	public:
		GPUBufferBase(const GPUBufferDesc& desc)
			: m_desc(desc) {}

		virtual const GPUBufferDesc& getDesc() const override { return m_desc; }
	};
}
