#pragma once

#include "EdgeCommon/Multithreading/Mutex.h"
#include "EdgeCommon/ObjectPool/ObjectPool.h"
#include "EdgeCommon/ObjectPool/ObjectPoolHandle.h"

#include "EdgePhysics/Physics/Entity/PhysicsEntityReference.h"

#include "PhysicsEntitySceneContextCollection.h"
#include "PhysicsSceneReference.h"

namespace Edge
{
	class DefaultPhysicsEntitySceneContext;

	class DefaultPhysicsEntitySceneContextCollection : public PhysicsEntitySceneContextCollection
	{
		using EntitySceneContextHandle = ObjectPoolHandle32;
		using EntitySceneContextPool = ObjectPool<DefaultPhysicsEntitySceneContext, EntitySceneContextHandle>;

		EntitySceneContextPool m_pool;

	public:
		DefaultPhysicsEntitySceneContextCollection() = default;

		bool init();
		void release();

		virtual PhysicsEntitySceneContext* createContext() override;
		virtual void destroyContext(PhysicsEntitySceneContext* context) override;

		DefaultPhysicsEntitySceneContext* createDefaultContext();
		void destroyDefaultContext(DefaultPhysicsEntitySceneContext* context);
	};

	EDGE_MT_REFERENCE(DefaultPhysicsEntitySceneContextCollection);

	class PhysicsSceneEntityCollection final
	{
	private:
		using EntityHandle = ObjectPoolHandle32;
		using EntityPool = ObjectPool<PhysicsEntityReference, EntityHandle>;

		EntityPool m_entityPool;

		DefaultPhysicsEntitySceneContextCollectionReference m_sceneContextManager;

		PhysicsSceneWeakReference m_scene;

	public:
		PhysicsSceneEntityCollection() = default;
		~PhysicsSceneEntityCollection() { release(); }

		bool init(const PhysicsSceneReference& scene);
		void release();

		PhysicsSceneEntityID addEntity(const PhysicsEntityReference& entity);
		void removeEntity(const PhysicsEntityReference& entity);
		PhysicsEntityReference getEntity(PhysicsSceneEntityID entityID) const;
	};
}
