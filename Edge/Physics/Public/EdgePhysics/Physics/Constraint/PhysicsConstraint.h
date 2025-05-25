#pragma once

#include "EdgeCommon/Math/ComputeMath.h"
#include "EdgeCommon/Patterns/NonCopyable.h"
#include "EdgeCommon/Reference/MTCountableObjectBase.h"
#include "EdgeCommon/RTTI/RTTI.h"

#include "Scene/PhysicsSceneConstraintManagerReference.h"

namespace Edge
{
	class PhysicsConstraintSceneContext : public DefaultDestroyingMTCountableObjectBase
	{
	public:
		PhysicsConstraintSceneContext() = default;

		virtual PhysicsSceneConstraintManagerWeakReference getConstraintManager() const = 0;
		virtual bool isActive() const = 0;

		EDGE_RTTI_VIRTUAL_BASE(PhysicsConstraintSceneContext)
	};

	EDGE_REFERENCE(PhysicsConstraintSceneContext);

	class PhysicsConstraint : public NonCopyable, public DefaultDestroyingMTCountableObjectBase
	{
	private:
		PhysicsConstraintSceneContextReference m_sceneContext;

		uint32_t m_velocitySolvingIterationCount = 0;
		uint32_t m_positionSolvingIterationCount = 0;

	public:
		PhysicsConstraint() = default;

		virtual void preSolve(ComputeValueType deltaTime) = 0;
		virtual void warmUp() = 0;
		virtual void solveVelocity(ComputeValueType deltaTime) = 0;
		virtual void solvePosition(ComputeValueType deltaTime) = 0;

		uint32_t getVelocitySolvingIterationCount() const { return m_velocitySolvingIterationCount; }
		void setVelocitySolvingIterationCount(uint32_t iterationCount) { m_velocitySolvingIterationCount = iterationCount; }
		uint32_t getPositionSolvingIterationCount() const { return m_positionSolvingIterationCount; }
		void setPositionSolvingIterationCount(uint32_t iterationCount) { m_positionSolvingIterationCount = iterationCount; }

		PhysicsConstraintSceneContextReference getSceneContext() const { return m_sceneContext; }
		void setSceneContext(const PhysicsConstraintSceneContextReference& context);

		bool isActive() const;

		EDGE_RTTI_VIRTUAL_BASE(PhysicsConstraint)
	};

	EDGE_REFERENCE(PhysicsConstraint);
}