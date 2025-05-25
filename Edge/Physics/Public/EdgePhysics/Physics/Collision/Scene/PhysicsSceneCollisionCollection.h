#pragma once

#include "EdgeCommon/ObjectPool/ObjectPool.h"
#include "EdgeCommon/ObjectPool/ObjectPoolHandle.h"

#include "EdgePhysics/Physics/Collision/PhysicsEntityCollision.h"

#include "DefaultPhysicsEntityCollisionSceneContext.h"
#include "PhysicsEntityCollisionSceneContextCollection.h"

namespace Edge
{
	class DefaultPhysicsEntityCollisionSceneContextCollection : public PhysicsEntityCollisionSceneContextCollection
	{
		using CollisionSceneContextHandle = ObjectPoolHandle32;
		using CollisionSceneContextPool = ObjectPool<DefaultPhysicsEntityCollisionSceneContext, CollisionSceneContextHandle>;

		CollisionSceneContextPool m_pool;

	public:
		DefaultPhysicsEntityCollisionSceneContextCollection() = default;

		bool init();
		void release();

		virtual PhysicsEntityCollisionSceneContext* createContext() override;
		virtual void destroyContext(PhysicsEntityCollisionSceneContext* context) override;

		DefaultPhysicsEntityCollisionSceneContext* createDefaultContext();
		void destroyDefaultContext(DefaultPhysicsEntityCollisionSceneContext* context);
	};

	EDGE_REFERENCE(DefaultPhysicsEntityCollisionSceneContextCollection);

	class PhysicsSceneCollisionCollection final
	{
	private:
		using CollisionHandle = ObjectPoolHandle32;
		using CollisionPool = ObjectPool<PhysicsEntityCollisionReference, CollisionHandle>;

		CollisionPool m_collisionPool;

		DefaultPhysicsEntityCollisionSceneContextCollectionReference m_collisionSceneContextManager;

		PhysicsSceneCollisionManagerWeakReference m_collisionManager;

	public:
		PhysicsSceneCollisionCollection() = default;
		~PhysicsSceneCollisionCollection() { release(); }

		bool init(const PhysicsSceneCollisionManagerReference& collisionManager);
		void release();

		PhysicsSceneCollisionID addCollision(const PhysicsEntityCollisionReference& collision);
		void removeCollision(const PhysicsEntityCollisionReference& collision);
		PhysicsEntityCollisionReference getCollision(PhysicsSceneCollisionID collisionID) const;
	};
}
