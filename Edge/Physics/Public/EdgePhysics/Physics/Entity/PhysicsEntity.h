#pragma once

#include "EdgeCommon/HashedType.h"
#include "EdgeCommon/Reference/MTCountableObjectBase.h"

#include "EdgePhysics/Physics/Scene/PhysicsSceneReference.h"

#include "PhysicsEntityMotion.h"
#include "PhysicsEntityReference.h"

namespace Edge
{
	using PhysicsEntitySceneContextType = HashedType::Type;

	class PhysicsEntitySceneContext : public HashedType, public DefaultDestroyingMTCountableObjectBase
	{
	public:
		PhysicsEntitySceneContext() = default;
		virtual ~PhysicsEntitySceneContext() = default;

		virtual PhysicsSceneWeakReference getScene() const = 0;
		virtual bool isActive() const = 0;

		virtual PhysicsEntitySceneContextType getType() const = 0;
	};

	EDGE_MT_REFERENCE(PhysicsEntitySceneContext);

#define EDGE_PHYSICS_ENTITY_SCENE_CONTEXT_TYPE(PHYSICS_ENTITY_SCENE_CONTEXT_TYPE) EDGE_HASH_TYPE(#PHYSICS_ENTITY_SCENE_CONTEXT_TYPE, Edge::PhysicsEntitySceneContextType, PhysicsEntitySceneContext)

	class PhysicsEntity : public NonCopyable, public HashedType, public DefaultDestroyingMTCountableObjectBase
	{
	private:
		PhysicsEntitySceneContextReference m_sceneContext;

	protected:
		PhysicsEntityTransformReference m_transform;
		PhysicsEntityMotionReference m_motion;

	public:
		PhysicsEntity(const PhysicsEntityTransformReference& transform);
		virtual ~PhysicsEntity() = default;

		virtual PhysicsEntityTransformReference getTransform() const { return m_transform; }
		virtual PhysicsEntityMotionReference getMotion() const { return m_motion; }

		//virtual PhysicsEntityCollisionReference getCollision() const = 0;

		virtual void updateTransformWithMotion(float deltaTime) = 0;

		PhysicsEntitySceneContextReference getSceneContext() const { return m_sceneContext; }
		void setSceneContext(const PhysicsEntitySceneContextReference& context);

		PhysicsSceneReference getScene() const;
		bool isActive() const;

		virtual PhysicsEntityType getType() const = 0;
	};

#define EDGE_PHYSICS_ENTITY_TYPE(PHYSICS_ENTITY_TYPE) EDGE_HASH_TYPE(#PHYSICS_ENTITY_TYPE, Edge::PhysicsEntityType, PhysicsEntity)
}
