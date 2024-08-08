#include "EdgeCommon/Assert/AssertCore.h"
#include "EdgeCommon/Memory.h"
#include "EdgeCommon/UtilsMacros.h"

namespace Edge
{
	template <typename ValType, typename HandleType>
	ObjectPool<ValType, HandleType>::Page::Page(Page&& page)
		: m_mem(nullptr),
		m_valsMem(nullptr),
		m_versionMem(nullptr),
		m_aliveMem(nullptr),
		m_capacity(page.m_capacity),
		m_size(page.m_size)
	{
		std::swap(m_mem, page.m_mem);
		std::swap(m_valsMem, page.m_valsMem);
		std::swap(m_versionMem, page.m_versionMem);
		std::swap(m_aliveMem, page.m_aliveMem);
		page.m_capacity = 0;
		page.m_size = 0;
	}

	template <typename ValType, typename HandleType>
	void ObjectPool<ValType, HandleType>::Page::allocate(size_t capacity)
	{
		size_t valueMemSize = Align(sizeof(ValType) * capacity, sizeof(void*));
		size_t versionMemSize = Align(sizeof(VersionType) * capacity, sizeof(void*));
		size_t aliveMemSize = sizeof(bool) * capacity;

		size_t memSize = Align(valueMemSize + versionMemSize + aliveMemSize, sizeof(void*));
		uint8_t* mem = new uint8_t[memSize];

		m_mem = mem;
		m_valsMem = reinterpret_cast<ValType*>(mem);
		m_versionMem = reinterpret_cast<VersionType*>(mem + valueMemSize);
		m_aliveMem = reinterpret_cast<bool*>(mem + valueMemSize + versionMemSize);

		m_capacity = capacity;
		m_size = 0;

		EDGE_ASSERT(m_mem);
		EDGE_ASSERT(capacity);

		memset(m_versionMem, InvalidVersion, versionMemSize);
		memset(m_aliveMem, 0, aliveMemSize);
	}

	template <typename ValType, typename HandleType>
	void ObjectPool<ValType, HandleType>::Page::deallocate()
	{
		EDGE_SAFE_DESTROY_ARRAY(m_mem);

		m_valsMem = nullptr;
		m_versionMem = nullptr;
		m_aliveMem = nullptr;
		m_capacity = 0;
		m_size = 0;
	}

	template <typename ValType, typename HandleType>
	bool ObjectPool<ValType, HandleType>::Page::isAllocated() const
	{
		return m_mem;
	}

	template <typename ValType, typename HandleType>
	bool ObjectPool<ValType, HandleType>::checkElementLocation(const ElementLocation& location) const
	{
		return location.elementIndex < m_pageSize;
	}

	template <typename ValType, typename HandleType>
	bool ObjectPool<ValType, HandleType>::checkElementLocationWithPage(const ElementLocation& location) const
	{
		return checkElementLocation(location) && location.pageIndex < m_pages.size();
	}

	template <typename ValType, typename HandleType>
	typename ObjectPool<ValType, HandleType>::ElementLocation ObjectPool<ValType, HandleType>::getElementLocation(IndexType index) const
	{
		ElementLocation location;
		location.pageIndex = index / m_pageSize;
		location.elementIndex = index % m_pageSize;

		return location;
	}

	template <typename ValType, typename HandleType>
	ValType* ObjectPool<ValType, HandleType>::getElementInternal(HandleType handle)
	{
		EDGE_ASSERT(m_pageSize != 0);

		VersionType version = handle.getVersion();
		if (version == InvalidVersion)
		{
			return nullptr;
		}

		IndexType index = handle.getIndex();
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

		VersionType lastElementVersion = page.m_versionMem[elementLocation.elementIndex];

		if (lastElementVersion != version)
		{
			return nullptr;
		}

		return &page.m_valsMem[elementLocation.elementIndex];
	}

	template <typename ValType, typename HandleType>
	ObjectPool<ValType, HandleType>::ObjectPool(ObjectPool&& pool)
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

	template <typename ValType, typename HandleType>
	bool ObjectPool<ValType, HandleType>::init(size_t pageSize, size_t maxFreePageCount, size_t minFreeIndexCount)
	{
		EDGE_ASSERT(m_pageSize == 0);

		m_pageSize = pageSize;
		m_maxFreePageCount = maxFreePageCount;
		m_minFreeIndexCount = minFreeIndexCount;

		m_pages.reserve(1);

		return true;
	}

	template <typename ValType, typename HandleType>
	void ObjectPool<ValType, HandleType>::clear()
	{
		for (auto& page : m_pages)
		{
			if (!page.isAllocated())
			{
				continue;
			}

			for (size_t elementIndex = 0; elementIndex < page.m_size; ++elementIndex)
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

	template <typename ValType, typename HandleType>
	bool ObjectPool<ValType, HandleType>::isValid(HandleType handle) const
	{
		EDGE_ASSERT(m_pageSize != 0);

		VersionType version = handle.getVersion();
		if (version == InvalidVersion)
		{
			return false;
		}

		IndexType index = handle.getIndex();
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

		VersionType lastElementVersion = page.m_versionMem[elementLocation.elementIndex];

		return lastElementVersion == version;
	}

	template <typename ValType, typename HandleType>
	void ObjectPool<ValType, HandleType>::addElementRaw(NewElementInfo& info)
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

		VersionType& version = page.m_versionMem[elementLocation.elementIndex];

		++version;
		if (version == InvalidVersion)
		{
			++version;
		}

		aliveState = true;

		info = NewElementInfo{ HandleType(index, version), val };
	}

	template <typename ValType, typename HandleType>
	typename ObjectPool<ValType, HandleType>::NewElementInfo ObjectPool<ValType, HandleType>::addElementRaw()
	{
		NewElementInfo info;
		addElementRaw(info);

		return info;
	}

	template <typename ValType, typename HandleType>
	template <typename ... Args>
	void ObjectPool<ValType, HandleType>::addElement(NewElementInfo& info, Args&&... args)
	{
		addElementRaw(info);
		new (info.m_elementPtr) ValType(args...);
	}

	template <typename ValType, typename HandleType>
	template <typename ... Args>
	typename ObjectPool<ValType, HandleType>::NewElementInfo ObjectPool<ValType, HandleType>::addElement(Args&&... args)
	{
		NewElementInfo info = addElementRaw();
		new (info.m_elementPtr) ValType(args...);

		return info;
	}

	template <typename ValType, typename HandleType>
	void ObjectPool<ValType, HandleType>::removeElement(HandleType handle)
	{
		EDGE_ASSERT(m_pageSize != 0);

		VersionType version = handle.getVersion();
		if (version == InvalidVersion)
		{
			return;
		}

		IndexType index = handle.getIndex();
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

		VersionType lastElementVersion = page.m_versionMem[elementLocation.elementIndex];
		if (lastElementVersion != version)
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
