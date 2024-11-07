#pragma once

#include "EdgeCommon/ObjectPool/ObjectPool.h"
#include "EdgeCommon/ObjectPool/ObjectPoolHandle.h"

#include "EdgePhysics/Physics/Entity/PhysicsEntityReference.h"
#include "EdgePhysics/Physics/Scene/PhysicsSceneReference.h"

#include "PhysicsEntitySceneContextCollection.h"
#include "PhysicsEntitySceneContextTypes.h"
#include "PhysicsSceneEntityManagerReference.h"

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

		PhysicsSceneEntityManagerWeakReference m_manager;

	public:
		PhysicsSceneEntityCollection() = default;
		~PhysicsSceneEntityCollection() { release(); }

		bool init(const PhysicsSceneEntityManagerReference& manager);
		void release();

		PhysicsSceneEntityID addEntity(const PhysicsEntityReference& entity);
		void removeEntity(const PhysicsEntityReference& entity);
		PhysicsEntityReference getEntity(PhysicsSceneEntityID entityID) const;
	};
}
