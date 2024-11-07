#pragma once

#include "EdgeCommon/Job/JobGraph.h"

#include "EdgePhysics/Physics/Entity/PhysicsEntity.h"
#include "EdgePhysics/Physics/Scene/PhysicsSceneReference.h"

#include "PhysicsEntitySceneContextTypes.h"
#include "PhysicsSceneActiveEntityCollection.h"
#include "PhysicsSceneEntityCollection.h"
#include "PhysicsSceneEntityManagerReference.h"

namespace Edge
{
	class PhysicsSceneEntityManager final : public DefaultDestroyingMTCountableObjectBase, public MTWeakReferencableBase<PhysicsSceneEntityManager>
	{
	private:
		PhysicsSceneEntityCollection* m_entityCollection = nullptr;
		PhysicsSceneActiveEntityCollection* m_activeEntityCollection = nullptr;

		PhysicsSceneWeakReference m_scene;

		void updateEntities(float deltaTime, const FloatVector3& gravity);

	public:
		PhysicsSceneEntityManager() = default;

		bool init(const PhysicsSceneReference& scene);
		void release();

		JobGraphReference getUpdateJobGraph(float deltaTime, const FloatVector3& gravity);

		PhysicsSceneEntityID addEntity(const PhysicsEntityReference& entity, bool activate = true);
		void removeEntity(PhysicsSceneEntityID entityID);
		void removeEntity(const PhysicsEntityReference& entity);

		PhysicsEntityReference getEntity(PhysicsSceneEntityID entityID) const;

		void activateEntity(PhysicsSceneEntityID entityID);
		void activateEntity(const PhysicsEntityReference& entity);
		void deactivateEntity(PhysicsSceneEntityID entityID);
		void deactivateEntity(const PhysicsEntityReference& entity);

		const PhysicsSceneActiveEntityCollection::EntityCollection& getActiveEntities() const;

		PhysicsSceneWeakReference getScene() const;
	};
}
