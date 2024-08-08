#pragma once

#include <type_traits>
#include <vector>
#include <deque>


namespace Edge
{
	template <typename ValType, typename IndexType>
	class IndexObjectPool final
	{
		static_assert(std::is_integral<IndexType>::value);

		static constexpr IndexType InvalidIndex = 0;

		struct Page final
		{
			void* m_mem = nullptr;
			ValType* m_valsMem = nullptr;
			bool* m_aliveMem = nullptr;

			size_t m_capacity = 0;
			size_t m_size = 0;

			Page() = default;
			Page(const Page&) = delete;
			Page(Page&& page);

			~Page() { deallocate(); }

			Page& operator=(const Page&) = delete;
			Page& operator=(Page&&) = delete;

			void allocate(size_t capacity);
			void deallocate();

			bool isAllocated() const;
		};

	public:
		struct NewElementInfo final
		{
			IndexType m_elementIndex = InvalidIndex;
			ValType* m_elementPtr = nullptr;
		};

	private:
		std::vector<Page> m_pages;
		std::deque<IndexType> m_freeIndices;
		size_t m_size = 0;
		size_t m_emptyPages = 0;
		IndexType m_maxUsedIndex = 0;

		size_t m_pageSize = 0;
		size_t m_maxFreePageCount = 0;
		size_t m_minFreeIndexCount = 0;

		struct ElementLocation final
		{
			size_t pageIndex = -1;
			size_t elementIndex = -1;
		};

		bool checkElementLocation(const ElementLocation& location) const;
		bool checkElementLocationWithPage(const ElementLocation& location) const;

		ElementLocation getElementLocation(IndexType index) const;
		ValType* getElementInternal(IndexType index);

	public:
		IndexObjectPool() = default;
		IndexObjectPool(const IndexObjectPool&) = delete;
		IndexObjectPool(IndexObjectPool&& pool);
		~IndexObjectPool() { release(); }


		bool init(size_t pageSize = 4096, size_t maxFreePageCount = 2, size_t minFreeIndexCount = 64);
		void release() { clear(); }

		void clear();

		bool isValid(IndexType index) const;

		const ValType* getElement(IndexType index) const { return getElementInternal(index); }
		ValType* getElement(IndexType index) { return getElementInternal(index); }

		void addElementRaw(NewElementInfo& info);

		NewElementInfo addElementRaw();

		template <typename... Args>
		void addElement(NewElementInfo& info, Args&&... args);

		template <typename... Args>
		NewElementInfo addElement(Args&&... args);

		void removeElement(IndexType index);
	};
}

#include "IndexObjectPool.hpp"
