#pragma once

#include "EdgePhysics/Physics/Entity/PhysicsEntity.h"

#include <vector>

namespace Edge
{
	class PhysicsSceneActiveEntityCollection final
	{
		friend class PhysicsSceneActiveEntityCollectionIterator;

	public:
		using EntityCollection = std::vector<PhysicsSceneEntityID>;

	private:
		EntityCollection m_ids;

		PhysicsSceneWeakReference m_scene;

	public:
		PhysicsSceneActiveEntityCollection() = default;
		~PhysicsSceneActiveEntityCollection() { release(); }

		bool init(const PhysicsSceneReference& scene);
		void release();

		void addEntity(const PhysicsEntityReference& entity);
		void removeEntity(const PhysicsEntityReference& entity);

		const EntityCollection& getEntities() const { return m_ids; }
	};
}
