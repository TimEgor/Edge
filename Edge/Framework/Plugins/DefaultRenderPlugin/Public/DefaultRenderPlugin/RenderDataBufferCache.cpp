#include "RenderDataBufferCache.h"

#include "EdgeCommon/UtilsMacros.h"

#include "EdgeFramework/FrameworkCore.h"
#include "EdgeFramework/Graphics/GraphicPlatform/DefferedGraphicContext.h"
#include "EdgeFramework/Graphics/GraphicPlatform/GraphicDevice.h"
#include "EdgeFramework/Graphics/GraphicPlatform/GraphicPlatform.h"

bool EdgeDefRender::RenderDataBufferCache::init(const BufferDesc& bufferDesc, uint32_t perBufferElementCount)
{
	m_bufferDesc.m_size = bufferDesc.m_stride * perBufferElementCount;
	m_bufferDesc.m_stride = bufferDesc.m_stride;
	m_bufferDesc.m_access = bufferDesc.m_access;
	m_bufferDesc.m_usage = bufferDesc.m_usage;

	m_perBufferElementCount = perBufferElementCount;

	return true;
}

void EdgeDefRender::RenderDataBufferCache::release()
{
	m_buffers = BufferCollection();
	m_unusedBufferCount = 0;
}

void EdgeDefRender::RenderDataBufferCache::updateBuffers(float deltaTime, uint32_t requiredElementCount)
{
	addDelayTime(deltaTime);
	prepareSpace(requiredElementCount);
	freeUnusedSpace();
}

void EdgeDefRender::RenderDataBufferCache::updateBuffers(float deltaTime)
{
	addDelayTime(deltaTime);
}

uint32_t EdgeDefRender::RenderDataBufferCache::getBufferCount() const
{
	return m_buffers.size() - m_unusedBufferCount;
}

Edge::GPUBuffer& EdgeDefRender::RenderDataBufferCache::getBuffer(uint32_t index) const
{
	return *m_buffers[index].m_buffer;
}

EdgeDefRender::RenderDataBufferCache::BufferData::BufferData(BufferData&& data) noexcept
	: m_buffer(data.m_buffer),
	m_unusingTime(data.m_unusingTime)
{
	data.m_buffer = nullptr;
}

EdgeDefRender::RenderDataBufferCache::BufferData::~BufferData() noexcept
{
	EDGE_SAFE_DESTROY(m_buffer);
}

Edge::GPUBuffer* EdgeDefRender::RenderDataBufferCache::createNewBuffer() const
{
	const Edge::Application& application = Edge::FrameworkCore::getInstance().getApplication();
	Edge::GraphicDevice& device = application.getGraphicPlatform().getGraphicDevice();

	return device.createBuffer(m_bufferDesc, nullptr);
}

void EdgeDefRender::RenderDataBufferCache::addDelayTime(float deltaTime)
{
	const uint32_t bufferCount = m_buffers.size();
	for (uint32_t bufferIndex = bufferCount - m_unusedBufferCount; bufferIndex < bufferCount; ++bufferIndex)
	{
		BufferData& bufferData = m_buffers[bufferIndex];
		bufferData.m_unusingTime += deltaTime;
	}
}

void EdgeDefRender::RenderDataBufferCache::prepareSpace(uint32_t requiredElementCount)
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
			Edge::GPUBuffer* newBuffer = createNewBuffer();
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

void EdgeDefRender::RenderDataBufferCache::freeUnusedSpace()
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

EdgeDefRender::RenderDataBufferCacheIterator::RenderDataBufferCacheIterator(
	const RenderDataBufferCache& bufferCache,
	Edge::DeferredGraphicContext& graphicContext,
	bool iterOnInit
)
	: m_bufferCache(bufferCache),
	m_graphicContext(graphicContext)
{
	if (iterOnInit)
	{
		next();
	}
}

EdgeDefRender::RenderDataBufferCacheIterator::~RenderDataBufferCacheIterator()
{
	if (m_currentElement && m_currentBufferIndex < m_bufferCache.getBufferCount())
	{
		m_graphicContext.unmapBuffer(m_bufferCache.getBuffer(m_currentBufferIndex));
	}
}

bool EdgeDefRender::RenderDataBufferCacheIterator::isInInitialState() const
{
	return
		m_currentElement == nullptr &&
		m_currentBufferIndex == 0 &&
		m_currentElementIndex == 0;
}

bool EdgeDefRender::RenderDataBufferCacheIterator::next()
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
		m_graphicContext.mapBuffer(
			m_bufferCache.getBuffer(m_currentBufferIndex),
			Edge::GRAPHIC_RESOURCE_MAPPING_TYPE_WRITE,
			Edge::GRAPHIC_RESOURCE_MAPPING_FLAG_DISCARD,
			&m_currentElement
		);

		m_currentElementIndex = 0;
	}
	else if (m_currentElement)
	{
		m_currentElement = static_cast<uint8_t*>(m_currentElement) + m_bufferCache.getBufferDesc().m_stride;
	}

	return m_currentElement != nullptr;
}
