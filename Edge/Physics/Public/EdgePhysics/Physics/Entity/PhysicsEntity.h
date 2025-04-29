#pragma once

#include "EdgeCommon/HashedType.h"
#include "EdgeCommon/Reference/MTCountableObjectBase.h"

#include "EdgePhysics/Physics/Collision/PhysicsEntityCollision.h"
#include "EdgePhysics/Physics/Scene/PhysicsSceneReference.h"

#include "PhysicsEntityMotion.h"
#include "PhysicsEntityReference.h"
#include "Scene/PhysicsSceneEntityManagerReference.h"

namespace Edge
{
	using PhysicsEntitySceneContextType = HashedType::Type;

	class PhysicsEntitySceneContext : public HashedType, public PhysicsEntityWeakLinkObject, public DefaultDestroyingMTCountableObjectBase
	{
	public:
		PhysicsEntitySceneContext() = default;

		virtual PhysicsSceneEntityManagerWeakReference getManager() const = 0;
		virtual bool isActive() const = 0;

		virtual PhysicsEntitySceneContextType getType() const = 0;
	};

	EDGE_REFERENCE(PhysicsEntitySceneContext);

#define EDGE_PHYSICS_ENTITY_SCENE_CONTEXT_TYPE(PHYSICS_ENTITY_SCENE_CONTEXT_TYPE) EDGE_HASH_TYPE(#PHYSICS_ENTITY_SCENE_CONTEXT_TYPE, Edge::PhysicsEntitySceneContextType, PhysicsEntitySceneContext)

	class PhysicsEntity : public NonCopyable, public HashedType, public DefaultDestroyingMTCountableObjectBase
	{
	private:
		PhysicsEntitySceneContextReference m_sceneContext;

	protected:
		PhysicsEntityTransformReference m_transform;
		PhysicsEntityMotionReference m_motion;

		PhysicsEntityCollisionReference m_collision;

		void updateEntityLinks(PhysicsEntityWeakLinkObject* oldObject, PhysicsEntityWeakLinkObject* newObject);

		void updateMotion(const PhysicsEntityMotionReference& newMotion);

	public:
		PhysicsEntity(const PhysicsEntityTransformReference& transform);
		~PhysicsEntity();

		PhysicsEntityTransformReference getTransform() const { return m_transform; }
		PhysicsEntityMotionReference getMotion() const { return m_motion; }

		PhysicsEntityCollisionReference getCollision() const { return m_collision; }
		void setCollision(const PhysicsEntityCollisionReference& collision);

		virtual void updateTransformWithMotion(float deltaTime) = 0;

		PhysicsEntitySceneContextReference getSceneContext() const { return m_sceneContext; }
		void setSceneContext(const PhysicsEntitySceneContextReference& context);

		void makeTransformChangingNotification();

		PhysicsSceneReference getScene() const;
		PhysicsSceneEntityManagerReference getManager() const;
		bool isActive() const;

		virtual PhysicsEntityType getType() const = 0;
	};

#define EDGE_PHYSICS_ENTITY_TYPE(PHYSICS_ENTITY_TYPE) EDGE_HASH_TYPE(#PHYSICS_ENTITY_TYPE, Edge::PhysicsEntityType, PhysicsEntity)
}
