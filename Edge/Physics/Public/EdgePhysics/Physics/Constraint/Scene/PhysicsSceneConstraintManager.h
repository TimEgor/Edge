#pragma once

#include "EdgeCommon/Job/JobGraph.h"

#include "EdgePhysics/Physics/Constraint/PhysicsConstraint.h"
#include "EdgePhysics/Physics/Scene/PhysicsSceneReference.h"

#include "PhysicsConstraintSceneContextTypes.h"

namespace Edge
{
	class PhysicsSceneConstraintCollection;
	class PhysicsSceneActiveConstraintCollection;

	class PhysicsSceneConstraintManager final : public DefaultDestroyingMTCountableObjectBase, public MTWeakReferencableBase<PhysicsSceneConstraintManager>
	{
	private:
		PhysicsSceneConstraintCollection* m_constraintCollection = nullptr;
		PhysicsSceneActiveConstraintCollection* m_activeConstraintCollection = nullptr;

		PhysicsSceneWeakReference m_scene;

		void preSolve(float deltaTime);
		void warmUp();
		void solveVelocity();
		void solvePosition();

	public:
		PhysicsSceneConstraintManager() = default;

		bool init(const PhysicsSceneReference& scene);
		void release();

		JobGraphReference getPreSolvingJobGraph(float deltaTime);
		JobGraphReference getVelocitySolvingJobGraph();
		JobGraphReference getPositionSolvingJobGraph();

		PhysicsSceneConstraintID addConstraint(const PhysicsConstraintReference& constraint, bool activate = true);
		void removeConstraint(PhysicsSceneConstraintID constraintID);
		void removeConstraint(const PhysicsConstraintReference& constraint);

		PhysicsConstraintReference getConstraint(PhysicsSceneConstraintID constraintID) const;

		void activateConstraint(PhysicsSceneConstraintID constraintID);
		void activateConstraint(const PhysicsConstraintReference& constraint);
		void deactivateConstraint(PhysicsSceneConstraintID constraintID);
		void deactivateConstraint(const PhysicsConstraintReference& constraint);

		PhysicsSceneWeakReference getScene() const;
	};
}
