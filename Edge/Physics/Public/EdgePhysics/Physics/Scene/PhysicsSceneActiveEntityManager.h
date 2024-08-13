#pragma once

#include "EdgeCommon/Multithreading/Mutex.h"

#include "EdgePhysics/Physics/Entity/PhysicsEntity.h"

#include <vector>

namespace Edge
{
	class PhysicsSceneActiveEntityCollection final
	{
		friend class PhysicsSceneActiveEntityCollectionIterator;

	private:
		struct EntityPage final
		{
			PhysicsEntityReference* m_entities = nullptr;
			PhysicsSceneActivationContextEntityIndex m_size = 0;
		};

		mutable SharedMutex m_mutex;

		using EntityPageCollection = std::vector<EntityPage>;

		EntityPageCollection m_entityPages;
		PhysicsSceneActivationContextEntityIndex m_currentPage = 0;

		PhysicsSceneActivationContextEntityIndex m_pageSize = 0;
		PhysicsSceneActivationContextEntityIndex m_maxFreePageCount = 0;

	public:
		PhysicsSceneActiveEntityCollection() = default;
		~PhysicsSceneActiveEntityCollection() { release(); }

		bool init(PhysicsSceneActivationContextEntityIndex pageSize = 4096, PhysicsSceneActivationContextEntityIndex maxFreePageCount = 2);
		void release();

		void addEntity(const PhysicsEntityReference& entity);
		void removeEntity(const PhysicsEntityReference& entity);
	};

	class PhysicsSceneActiveEntityCollectionIterator final
	{
	private:
		const PhysicsSceneActiveEntityCollection& m_collection;

		PhysicsEntityReference m_currentEntity = nullptr;

		uint32_t m_currentPageIndex = 0;
		uint32_t m_currentEntityIndex = -1;

	public:
		PhysicsSceneActiveEntityCollectionIterator(const PhysicsSceneActiveEntityCollection& collection);

		operator bool() const;

		PhysicsEntityReference getCurrentEntity() const;
		bool next();
	};
}
