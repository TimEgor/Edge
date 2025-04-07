#pragma once


#include "EdgeCommon/HashedType.h"

#include "GraphicObject.h"

#include <cstdint>

namespace Edge
{
	using GraphicResourceUsageValueType = uint32_t;
	enum CommonGraphicResourceUsage : GraphicResourceUsageValueType
	{
		GRAPHIC_RESOURCE_USAGE_UNDEFINED = 0,

		GRAPHIC_RESOURCE_USAGE_ALLOW_UNORDERED_ACCESS = 1,
		GRAPHIC_RESOURCE_USAGE_SHADER_RESOURCE = 1 << 1,

		GRAPHIC_RESOURCE_MAX_USAGE = GRAPHIC_RESOURCE_USAGE_SHADER_RESOURCE
	};

	using GraphicResourceAccessValueType = uint32_t;
	enum CommonGraphicResourceAccess
	{
		GRAPHIC_RESOURCE_ACCESS_UNDEFINED = 0,

		GRAPHIC_RESOURCE_ACCESS_CPU_READ = 1,
		GRAPHIC_RESOURCE_ACCESS_CPU_WRITE = 1 << 1,
		GRAPHIC_RESOURCE_ACCESS_GPU_READ = 1 << 2,
		GRAPHIC_RESOURCE_ACCESS_GPU_WRITE = 1 << 3
	};

	struct InitialGraphicResourceData final
	{
		const void* m_data = nullptr;
		uint32_t m_dataSize = 0;

		InitialGraphicResourceData(const void* data, uint32_t dataSize)
			: m_data(data), m_dataSize(dataSize) {}

		bool isValid() const { return m_data && m_dataSize; }
	};

	using GraphicResourceType = HashedType::Type;

	class GraphicResource : public GraphicObject, public HashedType
	{
	public:
		GraphicResource() = default;

		virtual GraphicResourceType getType() const = 0;
	};
}

#define EDGE_GRAPHIC_RESOURCE_TYPE(GRAPHIC_RESOURCE_TYPE) EDGE_HASH_TYPE(#GRAPHIC_RESOURCE_TYPE, Edge::GraphicResourceType, GraphicResource)
