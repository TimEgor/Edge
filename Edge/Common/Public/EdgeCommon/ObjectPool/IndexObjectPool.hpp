#include "EdgeEngine/Core/UtilsMacros.h"

#include "EdgeCommon/Assert/AssertCore.h"

namespace Edge
{
	template <typename ValType, typename IndexType>
	IndexObjectPool<ValType, IndexType>::Page::Page(Page&& page)
	: m_mem(nullptr),
		m_valsMem(nullptr),
		m_aliveMem(nullptr),
		m_capacity(page.m_capacity),
		m_size(page.m_size)
	{
		std::swap(m_mem, page.m_mem);
		std::swap(m_valsMem, page.m_valsMem);
		std::swap(m_aliveMem, page.m_aliveMem);
		page.m_capacity = 0;
		page.m_size = 0;
	}

	template <typename ValType, typename IndexType>
	void IndexObjectPool<ValType, IndexType>::Page::allocate(size_t capacity)
	{
		size_t valueMemSize = align(sizeof(ValType) * capacity, sizeof(void*));
		size_t aliveMemSize = sizeof(bool) * capacity;

		size_t memSize = align(valueMemSize + aliveMemSize, sizeof(void*));
		uint8_t* mem = new uint8_t[memSize];

		m_mem = mem;
		m_valsMem = reinterpret_cast<ValType*>(mem);
		m_aliveMem = reinterpret_cast<bool*>(mem + valueMemSize);

		m_capacity = capacity;
		m_size = 0;

		EDGE_ASSERT(m_mem);
		EDGE_ASSERT(capacity);

		memset(m_aliveMem, 0, aliveMemSize);
	}

	template <typename ValType, typename IndexType>
	void IndexObjectPool<ValType, IndexType>::Page::deallocate()
	{
		EDGE_SAFE_DESTROY_ARRAY(m_mem);

		m_valsMem = nullptr;
		m_aliveMem = nullptr;
		m_capacity = 0;
		m_size = 0;
	}

	template <typename ValType, typename IndexType>
	bool IndexObjectPool<ValType, IndexType>::Page::isAllocated() const
	{
		return m_mem;
	}

	template <typename ValType, typename IndexType>
	bool IndexObjectPool<ValType, IndexType>::checkElementLocation(const ElementLocation& location) const
	{
		return location.elementIndex < m_pageSize;
	}

	template <typename ValType, typename IndexType>
	bool IndexObjectPool<ValType, IndexType>::checkElementLocationWithPage(const ElementLocation& location) const
	{
		return checkElementLocation(location) && location.pageIndex < m_pages.size();
	}

	template <typename ValType, typename IndexType>
	typename IndexObjectPool<ValType, IndexType>::ElementLocation IndexObjectPool<ValType, IndexType>::getElementLocation(IndexType index) const
	{
		ElementLocation location;
		location.pageIndex = index / m_pageSize;
		location.elementIndex = index % m_pageSize;

		return location;
	}

	template <typename ValType, typename IndexType>
	ValType* IndexObjectPool<ValType, IndexType>::getElementInternal(IndexType index)
	{
		EDGE_ASSERT(m_pageSize != 0);

		ElementLocation elementLocation = getElementLocation(index);

		if (!checkElementLocationWithPage(elementLocation))
		{
			return nullptr;
		}

		const Page& page = m_pages[elementLocation.pageIndex];
		if (!page.isAllocated() || !page.m_aliveMem[elementLocation.elementIndex])
		{
			return nullptr;
		}

		return &page.m_valsMem[elementLocation.elementIndex];
	}

	template <typename ValType, typename IndexType>
	IndexObjectPool<ValType, IndexType>::IndexObjectPool(IndexObjectPool&& pool)
		: m_size(pool.m_size),
		m_emptyPages(pool.m_emptyPages),
		m_maxUsedIndex(pool.m_maxUsedIndex),
		m_pageSize(pool.m_pageSize),
		m_maxFreePageCount(pool.m_maxFreePageCount),
		m_minFreeIndexCount(pool.m_minFreeIndexCount)
	{
		std::swap(m_pages, pool.m_pages);
		std::swap(m_freeIndices, pool.m_freeIndices);
		pool.m_size = 0;
		pool.m_emptyPages = 0;
		pool.m_maxUsedIndex = 0;

		pool.m_pageSize = 0;
		pool.m_maxFreePageCount = 0;
		pool.m_minFreeIndexCount = 0;
	}

	template <typename ValType, typename IndexType>
	bool IndexObjectPool<ValType, IndexType>::init(size_t pageSize, size_t maxFreePageCount, size_t minFreeIndexCount)
	{
		EDGE_ASSERT(m_pageSize == 0);

		m_pageSize = pageSize;
		m_maxFreePageCount = maxFreePageCount;
		m_minFreeIndexCount = minFreeIndexCount;

		m_pages.reserve(1);

		return true;
	}

	template <typename ValType, typename IndexType>
	void IndexObjectPool<ValType, IndexType>::clear()
	{
		for (auto& page : m_pages)
		{
			if (!page.isAllocated())
			{
				continue;
			}

			for (size_t elementIndex = 0; elementIndex < page.m_capacity; ++elementIndex)
			{
				if (!page.m_aliveMem[elementIndex])
				{
					continue;
				}

				if constexpr (!std::is_trivially_destructible<ValType>::value)
				{
					ValType* val = &page.m_valsMem[elementIndex];
					val->~ValType();
				}
			}

			page.deallocate();
		}
	}

	template <typename ValType, typename IndexType>
	bool IndexObjectPool<ValType, IndexType>::isValid(IndexType index) const
	{
		EDGE_ASSERT(m_pageSize != 0);

		ElementLocation elementLocation = getElementLocation(index);

		if (!checkElementLocationWithPage(elementLocation))
		{
			return false;
		}

		const Page& page = m_pages[elementLocation.pageIndex];
		if (!page.isAllocated() || !page.m_aliveMem[elementLocation.elementIndex])
		{
			return false;
		}

		return true;
	}

	template <typename ValType, typename IndexType>
	void IndexObjectPool<ValType, IndexType>::addElementRaw(NewElementInfo& info)
	{
		EDGE_ASSERT(m_pageSize != 0);

		IndexType index;

		if (m_freeIndices.size() > m_minFreeIndexCount)
		{
			index = m_freeIndices.front();
			m_freeIndices.pop_front();
		}
		else
		{
			index = m_maxUsedIndex;
			++m_maxUsedIndex;
		}

		ElementLocation elementLocation = getElementLocation(index);
		if (!checkElementLocation(elementLocation))
		{
			EDGE_ASSERT_FAIL_MESSAGE("ObjectPool::addElement() : Element indicing invalidation.");
			info = NewElementInfo();
			return;
		}

		Page* pagePtr = nullptr;

		size_t pagesCount = m_pages.size();
		if (pagesCount <= elementLocation.pageIndex)
		{
			if (elementLocation.pageIndex - pagesCount < 2)
			{
				pagePtr = &m_pages.emplace_back();
			}
		}
		else
		{
			pagePtr = &m_pages[elementLocation.pageIndex];
		}

		if (!pagePtr)
		{
			EDGE_ASSERT_FAIL_MESSAGE("ObjectPool::addElement() : Page indicing invalidation.");
			info = NewElementInfo();
			return;
		}

		Page& page = *pagePtr;
		if (!page.isAllocated())
		{
			page.allocate(m_pageSize);
		}
		EDGE_ASSERT(page.m_size < page.m_capacity);

		bool& aliveState = page.m_aliveMem[elementLocation.elementIndex];
		if (aliveState)
		{
			EDGE_ASSERT_FAIL_MESSAGE("ObjectPool::addElement() : Reusing alive element.");
			info = NewElementInfo();
			return;
		}

		++page.m_size;

		ValType* val = &page.m_valsMem[elementLocation.elementIndex];

		aliveState = true;

		info = NewElementInfo{ index, val };
	}

	template <typename ValType, typename IndexType>
	typename IndexObjectPool<ValType, IndexType>::NewElementInfo IndexObjectPool<ValType, IndexType>::addElementRaw()
	{
		NewElementInfo info;
		addElementRaw(info);

		return info;
	}

	template <typename ValType, typename IndexType>
	template <typename ... Args>
	void IndexObjectPool<ValType, IndexType>::addElement(NewElementInfo& info, Args&&... args)
	{
		addElementRaw(info);
		new (info.m_elementPtr) ValType(args...);
	}

	template <typename ValType, typename IndexType>
	template <typename ... Args>
	typename IndexObjectPool<ValType, IndexType>::NewElementInfo IndexObjectPool<ValType, IndexType>::addElement(Args&&... args)
	{
		NewElementInfo info = addElementRaw();
		new (info.m_elementPtr) ValType(args...);

		return info;
	}

	template <typename ValType, typename IndexType>
	void IndexObjectPool<ValType, IndexType>::removeElement(IndexType index)
	{
		EDGE_ASSERT(m_pageSize != 0);

		ElementLocation elementLocation = getElementLocation(index);

		if (!checkElementLocationWithPage(elementLocation))
		{
			return;
		}

		Page& page = m_pages[elementLocation.pageIndex];
		if (!page.isAllocated())
		{
			return;
		}

		bool& aliveState = page.m_aliveMem[elementLocation.elementIndex];
		if (!aliveState)
		{
			return;
		}

		if constexpr (!std::is_trivially_destructible<ValType>::value)
		{
			ValType* val = &page.m_valsMem[elementLocation.elementIndex];
			val->~ValType();
		}

		m_freeIndices.push_back(index);
		aliveState = false;

		EDGE_ASSERT(page.m_size > 0);

		--page.m_size;
		if (page.m_size == 0)
		{
			++m_emptyPages;
			if (m_emptyPages > m_maxFreePageCount)
			{
				page.deallocate();
			}
		}
	}
}
