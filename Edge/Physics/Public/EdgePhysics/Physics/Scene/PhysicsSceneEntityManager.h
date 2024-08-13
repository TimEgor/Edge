#pragma once

#include "EdgeCommon/Multithreading/Mutex.h"
#include "EdgeCommon/ObjectPool/ObjectPool.h"
#include "EdgeCommon/ObjectPool/ObjectPoolHandle.h"

#include "EdgePhysics/Physics/Entity/PhysicsEntityReference.h"

#include "DefaultPhysicsEntitySceneContext.h"
#include "PhysicsSceneReference.h"

namespace Edge
{
	class EntityManager final
	{
	private:
		using EntityHandle = ObjectPoolHandle32;
		using EntityPool = ObjectPool<PhysicsEntityReference, EntityHandle>;
		using EntitySceneContextPool = ObjectPool<DefaultPhysicsEntitySceneContext, EntityHandle>;

		EntityPool m_entityPool;
		EntitySceneContextPool m_sceneContextPool;

		PhysicsSceneWeakReference m_scene;

		mutable SharedMutex m_entityPoolMutex;

	public:
		EntityManager() = default;
		~EntityManager() { release(); }

		bool init(const PhysicsSceneReference& scene);
		void release();

		PhysicsSceneEntityID addEntity(const PhysicsEntityReference& entity);
		void removeEntity(const PhysicsEntityReference& entity);
		void removeEntity(PhysicsSceneEntityID entityID);
		PhysicsEntityReference getEntity(PhysicsSceneEntityID entityID) const;
	};
}
