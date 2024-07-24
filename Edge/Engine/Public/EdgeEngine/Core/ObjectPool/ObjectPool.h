#pragma once

#include "ObjectPoolHandle.h"

#include <deque>
#include <vector>


namespace Edge
{
	template <typename ValType, typename HandleType>
	class ObjectPool final
	{
		using KeyType = typename HandleType::KeyType;
		using IndexType = typename HandleType::IndexType;
		using VersionType = typename HandleType::VersionType;

		static constexpr VersionType InvalidKey = typename HandleType::InvalidKey;
		static constexpr VersionType InvalidVersion = typename HandleType::InvalidVersion;
		static constexpr HandleType InvalidHandle = HandleType(InvalidKey);

		struct Page final
		{
			void* m_mem = nullptr;
			ValType* m_valsMem = nullptr;
			VersionType* m_versionMem = nullptr;
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
		using HandleElementType = HandleType;

		struct NewElementInfo final
		{
			HandleType m_elementHandle = InvalidHandle;
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

		ValType* getElementInternal(HandleType handle);

	public:
		ObjectPool() = default;
		ObjectPool(const ObjectPool&) = delete;
		ObjectPool(ObjectPool&& pool);
		~ObjectPool() { release(); }


		bool init(size_t pageSize = 4096, size_t maxFreePageCount = 2, size_t minFreeIndexCount = 64);
		void release() { clear(); }

		void clear();

		bool isValid(HandleType handle) const;

		const ValType* getElement(HandleType handle) const { return const_cast<ObjectPool*>(this)->getElementInternal(handle); }
		ValType* getElement(HandleType handle) { return getElementInternal(handle); }

		void addElementRaw(NewElementInfo& info);

		NewElementInfo addElementRaw();

		template <typename... Args>
		void addElement(NewElementInfo& info, Args&&... args);

		template <typename... Args>
		NewElementInfo addElement(Args&&... args);

		void removeElement(HandleType handle);
	};
}

#include "ObjectPool.hpp"