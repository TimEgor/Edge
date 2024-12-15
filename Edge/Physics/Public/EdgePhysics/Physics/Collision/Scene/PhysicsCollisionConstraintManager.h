#pragma once

#include "EdgeCommon/Job/JobGraph.h"

#include "EdgePhysics/Physics/Constraint/Parts/ContactPenetrationAxleConstraintPart.h"

namespace Edge
{
	struct PhysicsCollisionContactPoint;

	class PhysicsCollisionConstraintManager final
	{
	private:
		struct ContactConstraints final
		{
			ContactPenetrationConstraintPart m_penetrationPart;

			const PhysicsCollisionContactPoint& m_contactPoint;

			ContactConstraints(const PhysicsEntityReference& entity1, const PhysicsEntityReference& entity2,
				const PhysicsCollisionContactPoint& contactPoint)
				: m_penetrationPart(entity1, entity2), m_contactPoint(contactPoint) {}

			void preSolve(float deltaTime);
			void warmUp();
			void solveVelocity();
			void solvePosition();

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
