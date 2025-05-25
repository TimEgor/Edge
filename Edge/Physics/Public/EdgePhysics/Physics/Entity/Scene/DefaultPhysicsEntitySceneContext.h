#pragma once

#include "EdgePhysics/Physics/Entity/PhysicsEntity.h"

#include "PhysicsEntitySceneContextCollection.h"
#include "PhysicsEntitySceneContextTypes.h"

namespace Edge
{
	class DefaultPhysicsEntitySceneContext final : public PhysicsEntitySceneContext
	{
	private:
		PhysicsSceneEntityManagerWeakReference m_manager;
		PhysicsEntitySceneContextCollectionReference m_collection;

		PhysicsSceneEntityID m_sceneEntityID = InvalidPhysicsSceneEntityID;
		PhysicsSceneEntityID m_sceneContextID = InvalidPhysicsSceneEntityID;

		PhysicsSceneActivationContextEntityIndex m_activationContextIndex = InvalidPhysicsSceneActivationContextEntityIndex;

		virtual void selfDestroy() override;

	public:
		DefaultPhysicsEntitySceneContext() = default;

		virtual PhysicsSceneEntityManagerWeakReference getManager() const override { return m_manager; }
		PhysicsSceneEntityID getSceneEntityID() const { return m_sceneEntityID; }
		void setManager(const PhysicsSceneEntityManagerReference& manager, PhysicsSceneEntityID id);

		PhysicsSceneEntityID getSceneContextID() const { return m_sceneContextID; }
		void setContextCollection(const PhysicsEntitySceneContextCollectionReference& collection, PhysicsSceneEntityID id);

		PhysicsSceneActivationContextEntityIndex getActivationContextIndex() const { return m_activationContextIndex; }
		void setActivationContextIndex(PhysicsSceneActivationContextEntityIndex index);

		virtual bool isActive() const override;

		EDGE_RTTI_VIRTUAL(DefaultPhysicsEntitySceneContext, PhysicsEntitySceneContext)
	};
}
