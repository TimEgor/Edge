#pragma once

#include "EdgeCommon/Math/AABB.h"
#include "EdgeCommon/Reference/MTCountableObjectBase.h"

#include "EdgePhysics/Physics/Entity/PhysicsEntityTransform.h"
#include "EdgePhysics/Physics/Scene/PhysicsSceneReference.h"

#include "PhysicsCollisionQuery.h"
#include "PhysicsEntityCollisionShape.h"
#include "Scene/PhysicsSceneCollisionManagerReference.h"

namespace Edge
{
	class PhysicsEntityCollisionSceneContext : public DefaultDestroyingMTCountableObjectBase
	{
	public:
		PhysicsEntityCollisionSceneContext() = default;
		virtual ~PhysicsEntityCollisionSceneContext() = default;

		virtual PhysicsSceneCollisionManagerWeakReference getCollisionManager() const = 0;

		EDGE_RTTI_VIRTUAL_BASE(PhysicsEntityCollisionSceneContext)
	};

	EDGE_REFERENCE(PhysicsEntityCollisionSceneContext);

	class PhysicsEntityCollision : public PhysicsEntityWeakLinkObject, public PhysicsCollisionQuery, public DefaultDestroyingMTCountableObjectBase
	{
	private:
		PhysicsEntityCollisionSceneContextReference m_sceneContext;

		PhysicsEntityCollisionShapeReference m_shape;

		ComputeValueType m_friction = ComputeValueType(1.0);
		ComputeValueType m_elasticity = ComputeValueType(0.5);

	public:
		PhysicsEntityCollision() = default;

		PhysicsEntityTransformReference getTransform() const;
		PhysicsEntityCollisionShapeReference getShape() const { return m_shape; }
		void setShape(const PhysicsEntityCollisionShapeReference& shape);

		AABB3 getWorldShapeAABB() const;
		ComputeVector3 getFurthestKeyPoint(const ComputeVector3& direction) const;

		ComputeVector3 getSupportingPoint(const ComputeVector3& direction) const;
		ComputeValue getSupportingRadius() const;
		void getSupportingFace(const ComputeVector3& direction, PhysicsEntityCollisionShape::SupportingFaceVertexCollection& vertices) const;

		virtual bool rayCast(const ComputeVector3& origin, const ComputeVector3& end, PointCastingResult& result) const override;

		PhysicsEntityCollisionSceneContextReference getSceneContext() const { return m_sceneContext; }
		void setSceneContext(const PhysicsEntityCollisionSceneContextReference& context);

		PhysicsSceneCollisionManagerReference getCollisionManager() const;

		ComputeValueType getFriction() const { return m_friction; }
		void setFriction(ComputeValueType friction);

		ComputeValueType getElasticity() const { return m_elasticity; }
		void setElasticity(ComputeValueType elasticity);
	};

	EDGE_REFERENCE(PhysicsEntityCollision);
}