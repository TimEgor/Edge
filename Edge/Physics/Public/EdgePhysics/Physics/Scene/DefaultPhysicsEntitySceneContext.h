#pragma once

#include "EdgePhysics/Physics/Entity/PhysicsEntity.h"

#include "PhysicsEntitySceneContextCollection.h"

namespace Edge
{
	class DefaultPhysicsEntitySceneContext final : public PhysicsEntitySceneContext
	{
	private:
		PhysicsSceneWeakReference m_scene;
		PhysicsEntitySceneContextCollectionReference m_collection;

		PhysicsSceneEntityID m_sceneEntityID = InvalidPhysicsSceneEntityID;
		PhysicsSceneEntityID m_sceneContextID = InvalidPhysicsSceneEntityID;

		PhysicsSceneActivationContextEntityIndex m_activationContextIndex = InvalidPhysicsSceneActivationContextEntityIndex;

		virtual void selfDestroy() override;

	public:
		DefaultPhysicsEntitySceneContext() = default;

		virtual PhysicsSceneWeakReference getScene() const override { return m_scene; }
		PhysicsSceneEntityID getSceneEntityID() const { return m_sceneEntityID; }
		void setScene(const PhysicsSceneReference& scene, PhysicsSceneEntityID id);

		PhysicsSceneEntityID getSceneContextID() const { return m_sceneContextID; }
		void setContextCollection(const PhysicsEntitySceneContextCollectionReference& collection, PhysicsSceneEntityID id);

		PhysicsSceneActivationContextEntityIndex getActivationContextIndex() const { return m_activationContextIndex; }
		void setActivationContextIndex(PhysicsSceneActivationContextEntityIndex index);

		virtual bool isActive() const override;

		EDGE_PHYSICS_ENTITY_SCENE_CONTEXT_TYPE(DEFAULT);
	};
}
