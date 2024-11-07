#pragma once

#include "EdgePhysics/Physics/Entity/PhysicsEntity.h"

#include "PhysicsEntitySceneContextTypes.h"

#include <vector>

namespace Edge
{
	class PhysicsSceneActiveEntityCollection final
	{
	public:
		using EntityCollection = std::vector<PhysicsSceneEntityID>;

	private:
		EntityCollection m_ids;

		PhysicsSceneEntityManagerWeakReference m_manager;

	public:
		PhysicsSceneActiveEntityCollection() = default;
		~PhysicsSceneActiveEntityCollection() { release(); }

		bool init(const PhysicsSceneEntityManagerReference& manager);
		void release();

		void addEntity(const PhysicsEntityReference& entity);
		void removeEntity(const PhysicsEntityReference& entity);

		const EntityCollection& getEntities() const { return m_ids; }
	};
}
