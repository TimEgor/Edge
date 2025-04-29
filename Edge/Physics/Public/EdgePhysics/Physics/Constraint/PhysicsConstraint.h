#pragma once

#include "EdgeCommon/HashedType.h"
#include "EdgeCommon/Patterns/NonCopyable.h"
#include "EdgeCommon/Reference/MTCountableObjectBase.h"

#include "Scene/PhysicsSceneConstraintManagerReference.h"

namespace Edge
{
	using PhysicsConstraintSceneContextType = HashedType::Type;

	class PhysicsConstraintSceneContext : public HashedType, public DefaultDestroyingMTCountableObjectBase
	{
	public:
		PhysicsConstraintSceneContext() = default;

		virtual PhysicsSceneConstraintManagerWeakReference getConstraintManager() const = 0;
		virtual bool isActive() const = 0;

		virtual PhysicsConstraintSceneContextType getType() const = 0;
	};

	EDGE_REFERENCE(PhysicsConstraintSceneContext);

#define EDGE_PHYSICS_CONSTRAINT_SCENE_CONTEXT_TYPE(PHYSICS_CONSTRAINT_SCENE_CONTEXT_TYPE) EDGE_HASH_TYPE(#PHYSICS_CONSTRAINT_SCENE_CONTEXT_TYPE, Edge::PhysicsConstraintSceneContextType, PhysicsConstraintSceneContext)

	using PhysicsConstraintType = HashedType::Type;

	class PhysicsConstraint : public NonCopyable, public HashedType, public DefaultDestroyingMTCountableObjectBase
	{
	private:
		PhysicsConstraintSceneContextReference m_sceneContext;

		uint32_t m_velocitySolvingIterationCount = 0;
		uint32_t m_positionSolvingIterationCount = 0;

	public:
		PhysicsConstraint() = default;

		virtual void preSolve(float deltaTime) = 0;
		virtual void warmUp() = 0;
		virtual void solveVelocity() = 0;
		virtual void solvePosition() = 0;

		uint32_t getVelocitySolvingIterationCount() const { return m_velocitySolvingIterationCount; }
		void setVelocitySolvingIterationCount(uint32_t iterationCount) { m_velocitySolvingIterationCount = iterationCount; }
		uint32_t getPositionSolvingIterationCount() const { return m_positionSolvingIterationCount; }
		void setPositionSolvingIterationCount(uint32_t iterationCount) { m_positionSolvingIterationCount = iterationCount; }

		PhysicsConstraintSceneContextReference getSceneContext() const { return m_sceneContext; }
		void setSceneContext(const PhysicsConstraintSceneContextReference& context);

		bool isActive() const;

		virtual PhysicsConstraintType getType() const = 0;
	};

#define EDGE_PHYSICS_CONSTRAINT_TYPE(PHYSICS_CONSTRAINT_TYPE) EDGE_HASH_TYPE(#PHYSICS_CONSTRAINT_TYPE, Edge::PhysicsConstraintType, PhysicsConstraint)

	EDGE_REFERENCE(PhysicsConstraint);
}
