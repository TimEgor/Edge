#pragma once

#include "EdgeCommon/Job/JobGraph.h"

#include "EdgePhysics/Physics/Constraint/Parts/ContactFrictionAxleConstraintPart.h"
#include "EdgePhysics/Physics/Constraint/Parts/ContactPenetrationAxleConstraintPart.h"

namespace Edge
{
	struct PhysicsCollisionContactPoint;

	class PhysicsCollisionConstraintManager final
	{
	private:
		struct ContactConstraints final
		{
			PhysicsEntityReference m_entity1;
			PhysicsEntityReference m_entity2;

			ContactFrictionAxleConstraintPart m_frictionPart1;
			ContactFrictionAxleConstraintPart m_frictionPart2;
			ContactPenetrationAxleConstraintPart m_penetrationPart;

			FloatVector3 m_frictionTangent1 = FloatVector3Zero;
			FloatVector3 m_frictionTangent2 = FloatVector3Zero;
			FloatVector3 m_contactPosition = FloatVector3Zero;

			const PhysicsCollisionContactPoint& m_contactPoint;

			ContactConstraints(const PhysicsEntityReference& entity1, const PhysicsEntityReference& entity2,
				const PhysicsCollisionContactPoint& contactPoint);

			void preSolve(float deltaTime);
			void warmUp();
			void solvePenetrationPartVelocity();
			void solveFrictionPartsVelocity();
			void solvePenetrationPartPosition();

			void preSolveFrictionParts();
			void preSolvePenetrationPart();
		};

		using ConstraintCollection = std::vector<ContactConstraints>;

		ConstraintCollection m_constraintCollection;

		void preSolve(float deltaTime);
		void warmUp();
		void solveVelocity();
		void solvePosition();

	public:
		PhysicsCollisionConstraintManager() = default;

		JobGraphReference getPreSolvingJobGraph(float deltaTime);
		JobGraphReference getVelocitySolvingJobGraph();
		JobGraphReference getPositionSolvingJobGraph();

		void prepareCollection(uint32_t contactPointCount);

		void addContact(const PhysicsEntityReference& entity1, const PhysicsEntityReference& entity2,
			const PhysicsCollisionContactPoint& contactPoint);
	};
}
