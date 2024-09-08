#pragma once

#include "EdgeCommon/Patterns/NonCopyable.h"

#include "EdgeCommon/Job/JobGraph.h"
#include "EdgeCommon/Math/Vector.h"

#include "EdgePhysics/Physics/PhysicsWorld.h"
#include "EdgePhysics/Physics/Collision/PhysicsSceneCollisionManager.h"
#include "EdgePhysics/Physics/Entity/PhysicsEntity.h"

#include "PhysicsSceneReference.h"

namespace Edge
{
	class PhysicsSceneEntityCollection;
	class PhysicsSceneActiveEntityCollection;

	class PhysicsSceneCollisionManager;

	class PhysicsScene final : public NonCopyable, public DefaultDestroyingMTCountableObjectBase, public MTWeakReferencableBase<PhysicsScene>
	{
	private:
		PhysicsSceneEntityCollection* m_entityCollection = nullptr;
		PhysicsSceneActiveEntityCollection* m_activeEntityCollection = nullptr;

		PhysicsSceneCollisionManagerReference m_collisionManager;

		FloatVector3 m_gravity = FloatVector3(0.0f, -9.81f, 0.0f);

		PhysicsWorldWeakReference m_world;

		JobGraphReference getUpdateJobGraph(float deltaTime);
		void entityUpdate(float deltaTime);

	public:
		PhysicsScene(const PhysicsWorldReference& world);
		~PhysicsScene() { release(); }

		bool init();
		void release();

		void update(float deltaTime);

		PhysicsSceneEntityID addEntity(const PhysicsEntityReference& entity, bool activate = true);
		void removeEntity(PhysicsSceneEntityID entityID);
		void removeEntity(const PhysicsEntityReference& entity);

		PhysicsEntityReference getEntity(PhysicsSceneEntityID entityID) const;

		void activateEntity(PhysicsSceneEntityID entityID);
		void activateEntity(const PhysicsEntityReference& entity);
		void deactivateEntity(const PhysicsEntityReference& entity);

		void makeTransformChangingNotification(const PhysicsEntityReference& entity);

		PhysicsSceneCollisionManagerReference getCollisionManager() const;

		PhysicsWorldWeakReference getWorld();
	};
}
