#pragma once

#include "EdgeCommon/ObjectPool/ObjectPool.h"
#include "EdgeCommon/ObjectPool/ObjectPoolHandle.h"

#include "EdgePhysics/Physics/Constraint/PhysicsConstraint.h"

#include "PhysicsConstraintSceneContextCollection.h"
#include "PhysicsConstraintSceneContextTypes.h"

namespace Edge
{
	class DefaultPhysicsConstraintSceneContext;

	class DefaultPhysicsConstraintSceneContextCollection : public PhysicsConstraintSceneContextCollection
	{
		using EntitySceneContextHandle = ObjectPoolHandle32;
		using EntitySceneContextPool = ObjectPool<DefaultPhysicsConstraintSceneContext, EntitySceneContextHandle>;

		EntitySceneContextPool m_pool;

	public:
		DefaultPhysicsConstraintSceneContextCollection() = default;

		bool init();
		void release();

		virtual PhysicsConstraintSceneContext* createContext() override;
		virtual void destroyContext(PhysicsConstraintSceneContext* context) override;

		DefaultPhysicsConstraintSceneContext* createDefaultContext();
		void destroyDefaultContext(DefaultPhysicsConstraintSceneContext* context);
	};

	EDGE_MT_REFERENCE(DefaultPhysicsConstraintSceneContextCollection);

	class PhysicsSceneConstraintCollection final
	{
	private:
		using EntityHandle = ObjectPoolHandle32;
		using EntityPool = ObjectPool<PhysicsConstraintReference, EntityHandle>;

		EntityPool m_entityPool;

		DefaultPhysicsConstraintSceneContextCollectionReference m_sceneContextManager;

		PhysicsSceneConstraintManagerWeakReference m_constraintManager;

	public:
		PhysicsSceneConstraintCollection() = default;
		~PhysicsSceneConstraintCollection() { release(); }

		bool init(const PhysicsSceneConstraintManagerReference& constraintManager);
		void release();

		PhysicsSceneConstraintID addConstraint(const PhysicsConstraintReference& constraint);
		void removeConstraint(const PhysicsConstraintReference& constraint);
		PhysicsConstraintReference getConstraint(PhysicsSceneConstraintID constraintID) const;
	};
}
