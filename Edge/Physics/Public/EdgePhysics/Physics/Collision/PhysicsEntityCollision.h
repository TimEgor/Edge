#pragma once

#include "EdgeCommon/Math/AABB.h"
#include "EdgeCommon/Reference/MTCountableObjectBase.h"

#include "EdgePhysics/Physics/Entity/PhysicsEntityTransform.h"
#include "EdgePhysics/Physics/Scene/PhysicsSceneReference.h"

#include "PhysicsCollisionQuery.h"
#include "PhysicsEntityCollisionShape.h"
#include "PhysicsSceneCollisionManagerReference.h"

namespace Edge
{
	using PhysicsEntityCollisionSceneContextType = HashedType::Type;

	class PhysicsEntityCollisionSceneContext : public HashedType, public DefaultDestroyingMTCountableObjectBase
	{
	public:
		PhysicsEntityCollisionSceneContext() = default;
		virtual ~PhysicsEntityCollisionSceneContext() = default;

		virtual PhysicsSceneCollisionManagerWeakReference getCollisionManager() const = 0;

		virtual PhysicsEntityCollisionSceneContextType getType() const = 0;
	};

	EDGE_MT_REFERENCE(PhysicsEntityCollisionSceneContext);

#define EDGE_PHYSICS_ENTITY_COLLISION_SCENE_CONTEXT_TYPE(PHYSICS_ENTITY_COLLISION_SCENE_CONTEXT_TYPE)	\
	EDGE_HASH_TYPE(#PHYSICS_ENTITY_COLLISION_SCENE_CONTEXT_TYPE, Edge::PhysicsEntityCollisionSceneContextType, PhysicsEntityCollisionSceneContext)

	class PhysicsEntityCollision : public PhysicsEntityWeakLinkObject, public PhysicsCollisionQuery, public DefaultDestroyingMTCountableObjectBase
	{
	private:
		PhysicsEntityCollisionSceneContextReference m_sceneContext;

		PhysicsEntityCollisionShapeReference m_shape;

		PhysicsEntityTransformReference getTransform() const;

	public:
		PhysicsEntityCollision() = default;

		PhysicsEntityCollisionShapeReference getShape() const { return m_shape; }
		void setShape(const PhysicsEntityCollisionShapeReference& shape);

		virtual AABB3 getWorldShapeAABB() const;

		virtual bool rayCast(const FloatVector3& origin, const FloatVector3& end, PointCastingResult& result) const override;

		PhysicsEntityCollisionSceneContextReference getSceneContext() const { return m_sceneContext; }
		void setSceneContext(const PhysicsEntityCollisionSceneContextReference& context);
	};

	EDGE_MT_REFERENCE(PhysicsEntityCollision);
}
