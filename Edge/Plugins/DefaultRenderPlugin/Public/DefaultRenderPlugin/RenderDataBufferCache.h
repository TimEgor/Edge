#pragma once

#include "TinySimFramework/Graphics/GraphicPlatform/GraphicObject/GPUBuffer.h"

#include <vector>

namespace TS
{
	class DeferredGraphicContext;
}

namespace TS_DEF_RENDERER
{
	class RenderDataBufferCache final
	{
	public:
		struct BufferDesc final
		{
			uint32_t m_stride = 0;
			TS::GraphicResourceUsageValueType m_usage = TS::GRAPHIC_RESOURCE_USAGE_UNDEFINED;
			TS::GraphicResourceAccessValueType m_access = TS::GRAPHIC_RESOURCE_ACCESS_UNDEFINED;
		};

	private:
		struct BufferData final
		{
			TS::GPUBuffer* m_buffer = nullptr;
			float m_unusingTime = 0.0f;

			BufferData() = default;
			BufferData(TS::GPUBuffer* buffer) : m_buffer(buffer) {}
			~BufferData();
		};

		using BufferCollection = std::vector<BufferData>;

		BufferCollection m_buffers;
		TS::GPUBufferDesc m_bufferDesc;
		uint32_t m_perBufferElementCount = 0;

		uint32_t m_unusedBufferCount = 0;

		static constexpr float BufferReleasingDelay = 2.0f;

		TS::GPUBuffer* createNewBuffer() const;

		void addDelayTime(float deltaTime);
		void updateBufferSpaces(uint32_t requiredElementCount);
		void freeUnusedBuffers();

	public:
		RenderDataBufferCache() = default;
		~RenderDataBufferCache() { release(); }

		bool init(const BufferDesc& bufferDesc, uint32_t perBufferElementCount);
		void release();

		void updateBuffers(float deltaTime, uint32_t requiredElementCount);

		uint32_t getElementCountPerBuffer() const { return m_perBufferElementCount; }
		uint32_t getBufferCount() const;
		TS::GPUBuffer& getBuffer(uint32_t index) const;

		const TS::GPUBufferDesc& getBufferDesc() const { return m_bufferDesc; }
	};

	class RenderDataBufferCacheIterator final
	{
	private:
		const RenderDataBufferCache& m_bufferCache;
		TS::DeferredGraphicContext& m_graphicContext;

		void* m_currentElement = nullptr;

		uint32_t m_currentBufferIndex = 0;
		uint32_t m_currentElementIndex = 0;

	public:
		RenderDataBufferCacheIterator(const RenderDataBufferCache& bufferCache, TS::DeferredGraphicContext& graphicContext);
		~RenderDataBufferCacheIterator();

		void* getCurrentElement() const { return m_currentElement; }
		template <typename T>
		T* getCurrentTypedElement() const { return static_cast<T*>(m_currentElement); }

		bool next();
	};
}
