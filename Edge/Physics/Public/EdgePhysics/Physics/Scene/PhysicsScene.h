#pragma once

#include "EdgeCommon/Patterns/NonCopyable.h"

#include "EdgeCommon/Job/JobGraph.h"
#include "EdgeCommon/Math/Vector.h"

#include "EdgePhysics/Physics/PhysicsWorld.h"
#include "EdgePhysics/Physics/Entity/PhysicsEntity.h"

#include "PhysicsSceneReference.h"

namespace Edge
{
	class EntityManager;
	class PhysicsSceneActiveEntityCollection;

	class PhysicsScene final : public NonCopyable, public DefaultDestroyingMTCountableObjectBase, public MTWeakReferencableBase<PhysicsScene>
	{
	private:
		EntityManager* m_entityManager = nullptr;
		PhysicsSceneActiveEntityCollection* m_activeEntityCollection = nullptr;

		FloatVector3 m_gravity = FloatVector3(0.0f, -9.81f, 0.0f);

		PhysicsWorldWeakReference m_world;

		JobGraphReference getUpdateJobGraph(float deltaTime);
		void entityUpdate(float deltaTime);

	public:
		PhysicsScene(const PhysicsWorldReference& world);

		bool init();
		void release();

		void update(float deltaTime);

		PhysicsSceneEntityID addEntity(const PhysicsEntityReference& entity, bool activate = true);
		void removeEntity(PhysicsSceneEntityID entityID);
		void removeEntity(const PhysicsEntityReference& entity);

		PhysicsEntityReference getEntity(PhysicsSceneEntityID entityID) const;

		void activateEntity(PhysicsSceneEntityID entityID);
		void activateEntity(PhysicsEntityReference entity);
		void deactivateEntity(PhysicsEntityReference entity);

		PhysicsWorldWeakReference getWorld();
	};
}
