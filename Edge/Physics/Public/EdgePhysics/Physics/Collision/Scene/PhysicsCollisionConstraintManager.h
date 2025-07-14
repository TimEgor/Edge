#pragma once

#include "EdgeCommon/Job/JobGraph.h"

#include "EdgePhysics/Physics/Constraint/Parts/ContactFrictionAxleConstraintPart.h"
#include "EdgePhysics/Physics/Constraint/Parts/ContactPenetrationAxleConstraintPart.h"

namespace Edge
{
	struct PhysicsCollisionContactPoint;

	class PhysicsCollisionConstraintManager final
	{
	public:
		struct ContactConstraint final
		{
			PhysicsEntityReference m_entity1;
			PhysicsEntityReference m_entity2;

			ContactFrictionAxleConstraintPart m_frictionPart1;
			ContactFrictionAxleConstraintPart m_frictionPart2;
			ContactPenetrationAxleConstraintPart m_penetrationPart;

			ComputeVector3 m_frictionTangent1 = ComputeVector3Zero;
			ComputeVector3 m_frictionTangent2 = ComputeVector3Zero;
			ComputeVector3 m_contactPosition = ComputeVector3Zero;

			PhysicsCollisionContactPoint& m_contactPoint;

			ContactConstraint(
				const PhysicsEntityReference& entity1,
				const PhysicsEntityReference& entity2,
				PhysicsCollisionContactPoint& contactPoint
			);

			void preSolve(ComputeValueType deltaTime);
			void warmUp();
			void solvePenetrationPartVelocity();
			void solveFrictionPartsVelocity();
			void solvePenetrationPartPosition();

			void preSolveFrictionParts();
			void preSolvePenetrationPart();

			void restoreApplyingData();
			void storeApplyingData() const;
		};

	private:
		using ConstraintCollection = std::vector<ContactConstraint>;

		ConstraintCollection m_constraintCollection;

		void preSolve(ComputeValueType deltaTime);
		void warmUp();
		void solveVelocity();
		void solvePosition();

	public:
		PhysicsCollisionConstraintManager() = default;

		JobGraphReference getPreSolvingJobGraph(ComputeValueType deltaTime);
		JobGraphReference getVelocitySolvingJobGraph(ComputeValueType deltaTime);
		JobGraphReference getPositionSolvingJobGraph(ComputeValueType deltaTime);

		void prepareCollection(uint32_t contactPointCount);

		void cacheApplyingData();

		void addContact(
			const PhysicsEntityReference& entity1,
			const PhysicsEntityReference& entity2,
			PhysicsCollisionContactPoint& contactPoint
		);
	};
}
