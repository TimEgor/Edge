#pragma once

#include "EdgeCommon/Patterns/NonCopyable.h"

#include "EdgeCommon/Job/JobGraph.h"
#include "EdgeCommon/Math/Vector.h"

#include "EdgePhysics/Physics/PhysicsWorld.h"
#include "EdgePhysics/Physics/Collision/Scene/PhysicsSceneCollisionManager.h"
#include "EdgePhysics/Physics/Constraint/Scene/PhysicsSceneConstraintManager.h"
#include "EdgePhysics/Physics/Entity/Scene/PhysicsSceneEntityManager.h"

#include "PhysicsSceneReference.h"

namespace Edge
{
	class PhysicsSceneCollisionManager;

	class PhysicsScene final : public NonCopyable, public DefaultDestroyingMTCountableObjectBase, public MTWeakReferencableBase<PhysicsScene>
	{
		PhysicsSceneEntityManagerReference m_entityManager;
		PhysicsSceneCollisionManagerReference m_collisionManager;
		PhysicsSceneConstraintManagerReference m_constraintManager;

		ComputeVector3 m_gravity = ComputeVector3(ComputeValueType(0.0), ComputeValueType(-9.81), ComputeValueType(0.0));

		PhysicsWorldWeakReference m_world;

		JobGraphReference getUpdateJobGraph(ComputeValueType deltaTime);

		JobGraphReference getConstraintPreparationJobGraph(ComputeValueType deltaTime);
		JobGraphReference getConstraintVelocitySolvingJobGraph(ComputeValueType deltaTime);
		JobGraphReference getConstraintPositionSolvingJobGraph(ComputeValueType deltaTime);

	public:
		PhysicsScene(const PhysicsWorldReference& world);

		bool init();
		void release();

		void update(ComputeValueType deltaTime);

		PhysicsSceneEntityID addEntity(const PhysicsEntityReference& entity, bool activate = true);
		void removeEntity(PhysicsSceneEntityID entityID);
		void removeEntity(const PhysicsEntityReference& entity);

		PhysicsEntityReference getEntity(PhysicsSceneEntityID entityID) const;

		PhysicsSceneConstraintID addConstraint(const PhysicsConstraintReference& constraint, bool activate = true);
		void removeConstraint(PhysicsSceneConstraintID constraintID);
		void removeConstraint(const PhysicsConstraintReference& constraint);

		PhysicsConstraintReference getConstraint(PhysicsSceneConstraintID constraintID) const;

		void makeTransformChangingNotification(const PhysicsEntityReference& entity);

		PhysicsSceneEntityManagerReference getEntityManager() const;
		PhysicsSceneCollisionManagerReference getCollisionManager() const;

		PhysicsWorldWeakReference getWorld();
	};
}
