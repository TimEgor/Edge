#include "RenderDataBufferCache.h"

#include "TinySimCommon/Core/UtilsMacros.h"

#include "TinySimFramework/FrameworkCore.h"
#include "TinySimFramework/Graphics/GraphicPlatform/DefferedGraphicContext.h"
#include "TinySimFramework/Graphics/GraphicPlatform/GraphicDevice.h"
#include "TinySimFramework/Graphics/GraphicPlatform/GraphicPlatform.h"

bool TS_DEF_RENDERER::RenderDataBufferCache::init(const BufferDesc& bufferDesc, uint32_t perBufferElementCount)
{
	m_bufferDesc.m_size = bufferDesc.m_stride * perBufferElementCount;
	m_bufferDesc.m_stride = bufferDesc.m_stride;
	m_bufferDesc.m_access = bufferDesc.m_access;
	m_bufferDesc.m_usage = bufferDesc.m_usage;

	m_perBufferElementCount = perBufferElementCount;

	return true;
}

void TS_DEF_RENDERER::RenderDataBufferCache::release()
{
	m_buffers = BufferCollection();
	m_unusedBufferCount = 0;
}

void TS_DEF_RENDERER::RenderDataBufferCache::updateBuffers(float deltaTime, uint32_t requiredElementCount)
{
	addDelayTime(deltaTime);
	updateBufferSpaces(requiredElementCount);
	freeUnusedBuffers();
}

uint32_t TS_DEF_RENDERER::RenderDataBufferCache::getBufferCount() const
{
	return m_buffers.size() - m_unusedBufferCount;
}

TS::GPUBuffer& TS_DEF_RENDERER::RenderDataBufferCache::getBuffer(uint32_t index) const
{
	return *m_buffers[index].m_buffer;
}

TS_DEF_RENDERER::RenderDataBufferCache::BufferData::~BufferData()
{
	TS_SAFE_DESTROY(m_buffer);
}

TS::GPUBuffer* TS_DEF_RENDERER::RenderDataBufferCache::createNewBuffer() const
{
	const TS::Application& application = TS::FrameworkCore::getInstance().getApplication();
	TS::GraphicDevice& device = application.getGraphicPlatform().getGraphicDevice();

	return device.createBuffer(m_bufferDesc, nullptr);
}

void TS_DEF_RENDERER::RenderDataBufferCache::addDelayTime(float deltaTime)
{
	const uint32_t bufferCount = m_buffers.size();
	for (uint32_t bufferIndex = bufferCount - m_unusedBufferCount; bufferIndex < bufferCount; ++bufferIndex)
	{
		BufferData& bufferData = m_buffers[bufferIndex];
		bufferData.m_unusingTime += deltaTime;
	}
}

void TS_DEF_RENDERER::RenderDataBufferCache::updateBufferSpaces(uint32_t requiredElementCount)
{
	const uint32_t requiredBufferCount = ceilf(static_cast<float>(requiredElementCount) / m_perBufferElementCount);
	const uint32_t currentBufferCount = m_buffers.size();

	const uint32_t usedBufferCount = currentBufferCount - m_unusedBufferCount;
	const uint32_t reusedBufferLimitIndex = std::min(requiredBufferCount, currentBufferCount);
	for (uint32_t bufferIndex = usedBufferCount; bufferIndex < reusedBufferLimitIndex; ++bufferIndex)
	{
		BufferData& bufferData = m_buffers[bufferIndex];
		bufferData.m_unusingTime = -1.0f;
	}

	m_unusedBufferCount -= reusedBufferLimitIndex - usedBufferCount;

	if (requiredBufferCount >= currentBufferCount)
	{
		const uint32_t newBufferCount = requiredBufferCount - currentBufferCount;
		for (uint32_t bufferIndex = 0; bufferIndex < newBufferCount; ++bufferIndex)
		{
			TS::GPUBuffer* newBuffer = createNewBuffer();
			m_buffers.emplace_back(newBuffer);
		}
	}
	else
	{
		const uint32_t freedBufferLimitIndex = currentBufferCount - m_unusedBufferCount;
		for (uint32_t bufferIndex = requiredBufferCount + 1; bufferIndex < freedBufferLimitIndex; ++bufferIndex)
		{
			BufferData& bufferData = m_buffers[bufferIndex];
			bufferData.m_unusingTime = 0.0f;

			++m_unusedBufferCount;
		}
	}
}

void TS_DEF_RENDERER::RenderDataBufferCache::freeUnusedBuffers()
{
	const uint32_t bufferCount = m_buffers.size();
	uint32_t releasingBufferIndex = bufferCount;

	for (uint32_t bufferIndex = bufferCount - m_unusedBufferCount; bufferIndex < bufferCount; ++bufferIndex)
	{
		BufferData& bufferData = m_buffers[bufferIndex];
		if (bufferData.m_unusingTime >= BufferReleasingDelay)
		{
			releasingBufferIndex = bufferIndex;
			break;
		}
	}

	m_unusedBufferCount -= bufferCount - releasingBufferIndex;

	m_buffers.resize(releasingBufferIndex);
}

TS_DEF_RENDERER::RenderDataBufferCacheIterator::RenderDataBufferCacheIterator(const RenderDataBufferCache& bufferCache, TS::DeferredGraphicContext& graphicContext)
	: m_bufferCache(bufferCache), m_graphicContext(graphicContext)
{
	next();
}

TS_DEF_RENDERER::RenderDataBufferCacheIterator::~RenderDataBufferCacheIterator()
{
	if (m_currentElement && m_currentBufferIndex < m_bufferCache.getBufferCount())
	{
		m_graphicContext.unmapBuffer(m_bufferCache.getBuffer(m_currentBufferIndex));
	}
}

bool TS_DEF_RENDERER::RenderDataBufferCacheIterator::next()
{
	const uint32_t perBufferElementCount = m_bufferCache.getElementCountPerBuffer();

	++m_currentElementIndex;

	if (m_currentElement && m_currentElementIndex >= perBufferElementCount)
	{
		m_graphicContext.unmapBuffer(m_bufferCache.getBuffer(m_currentBufferIndex));

		m_currentElement = nullptr;

		++m_currentBufferIndex;
	}

	if (!m_currentElement && m_currentBufferIndex < m_bufferCache.getBufferCount())
	{
		m_graphicContext.mapBuffer(m_bufferCache.getBuffer(m_currentBufferIndex),
			TS::GRAPHIC_RESOURCE_MAPPING_TYPE_WRITE, TS::GRAPHIC_RESOURCE_MAPPING_FLAG_DISCARD, &m_currentElement);

		m_currentElementIndex = 0;
	}
	else if (m_currentElement)
	{
		m_currentElement = static_cast<uint8_t*>(m_currentElement) + m_bufferCache.getBufferDesc().m_stride;
	}

	return m_currentElement != nullptr;
}
