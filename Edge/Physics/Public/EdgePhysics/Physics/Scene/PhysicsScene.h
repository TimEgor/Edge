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

		FloatVector3 m_gravity = FloatVector3(0.0f, -9.81f, 0.0f);

		PhysicsWorldWeakReference m_world;

		JobGraphReference getUpdateJobGraph(float deltaTime);

		JobGraphReference getConstraintPreparationJobGraph(float deltaTime);
		JobGraphReference getConstraintVelocitySolvingJobGraph();
		JobGraphReference getConstraintPositionSolvingJobGraph();

	public:
		PhysicsScene(const PhysicsWorldReference& world);

		bool init();
		void release();

		void update(float deltaTime);

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
