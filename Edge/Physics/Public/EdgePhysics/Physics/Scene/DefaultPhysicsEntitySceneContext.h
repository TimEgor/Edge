#pragma once

#include "EdgePhysics/Physics/Entity/PhysicsEntity.h"

#include "PhysicsScene.h"

namespace Edge
{
	class DefaultPhysicsEntitySceneContext final : public PhysicsEntitySceneContext
	{
	private:
		PhysicsEntity& m_entity;

		PhysicsSceneWeakReference m_scene;
		PhysicsSceneEntityID m_sceneEntityID = InvalidPhysicsSceneEntityID;

		PhysicsSceneActivationContextEntityIndex m_activationContextIndex = InvalidPhysicsSceneActivationContextEntityIndex;

		virtual void selfDestroy() override {}

	public:
		DefaultPhysicsEntitySceneContext(PhysicsEntity& entity);
		~DefaultPhysicsEntitySceneContext();

		virtual PhysicsSceneWeakReference getScene() const override { return m_scene; }
		PhysicsSceneEntityID getSceneEntityID() const { return m_sceneEntityID; }
		void setScene(const PhysicsSceneReference& scene, PhysicsSceneEntityID id);

		PhysicsSceneActivationContextEntityIndex getActivationContextIndex() const { return m_activationContextIndex; }
		void setActivationContextIndex(PhysicsSceneActivationContextEntityIndex index);

		virtual bool isActive() const override;

		EDGE_PHYSICS_ENTITY_SCENE_CONTEXT_TYPE(DEFAULT);
	};
}
