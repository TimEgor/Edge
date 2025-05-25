#pragma once

#include "EdgePhysics/Physics/Constraint/PhysicsConstraint.h"

#include "PhysicsConstraintSceneContextCollection.h"
#include "PhysicsConstraintSceneContextTypes.h"
#include "PhysicsSceneConstraintManagerReference.h"

namespace Edge
{
	class DefaultPhysicsConstraintSceneContext final : public PhysicsConstraintSceneContext
	{
	private:
		PhysicsSceneConstraintManagerWeakReference m_constraintManager;
		PhysicsConstraintSceneContextCollectionReference m_collection;

		PhysicsSceneConstraintID m_sceneConstraintID = InvalidPhysicsSceneConstraintID;
		PhysicsSceneConstraintID m_sceneContextID = InvalidPhysicsSceneConstraintID;

		PhysicsSceneActivationContextConstraintIndex m_activationContextIndex = InvalidPhysicsSceneActivationContextConstraintIndex;

		virtual void selfDestroy() override;

	public:
		DefaultPhysicsConstraintSceneContext() = default;

		virtual PhysicsSceneConstraintManagerWeakReference getConstraintManager() const override;
		PhysicsSceneConstraintID getSceneConstraintID() const { return m_sceneConstraintID; }
		void setConstraintManager(const PhysicsSceneConstraintManagerReference& manager, PhysicsSceneConstraintID id);

		PhysicsSceneConstraintID getSceneContextID() const { return m_sceneContextID; }
		void setContextCollection(const PhysicsConstraintSceneContextCollectionReference& collection, PhysicsSceneConstraintID id);

		PhysicsSceneActivationContextConstraintIndex getActivationContextIndex() const { return m_activationContextIndex; }
		void setActivationContextIndex(PhysicsSceneActivationContextConstraintIndex index) { m_activationContextIndex = index; }

		virtual bool isActive() const override;

		EDGE_RTTI_VIRTUAL(DefaultPhysicsConstraintSceneContext)
	};
}

EDGE_RTTI(Edge::DefaultPhysicsConstraintSceneContext)