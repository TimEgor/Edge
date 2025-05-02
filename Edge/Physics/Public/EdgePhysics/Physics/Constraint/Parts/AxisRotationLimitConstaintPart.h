#pragma once

#include "EdgePhysics/Physics/Entity/PhysicsEntity.h"

namespace Edge
{
	class AxisRotationLimitConstraintPart final
	{
	private:
		ComputeValueType m_invEffectiveMass = 0.0;

		ComputeVector3 m_axis1 = ComputeVector3Zero;
		ComputeValueType m_minLambdaLimit = 0.0;
		ComputeValueType m_maxLambdaLimit = 0.0;

		ComputeValueType m_totalLambda = 0.0;

		PhysicsEntityReference m_entity1;
		PhysicsEntityReference m_entity2;

		void deactivate();

		void applyVelocity(const ComputeVector3& lambda) const;
		void applyPosition(const ComputeVector3& lambda) const;

		void solveLimitPosition(ComputeValueType delta);

	public:
		AxisRotationLimitConstraintPart(const PhysicsEntityReference& entity1, const PhysicsEntityReference& entity2)
			: m_entity1(entity1), m_entity2(entity2) {
		}

		void preSolve(const ComputeVector3& axis1, ComputeValueType deltaAngle, ComputeValueType minLimit, ComputeValueType maxLimit);
		void warmUp();
		void solveVelocity();
		void solvePosition(ComputeValueType deltaAngle, ComputeValueType minLimit, ComputeValueType maxLimit);

		bool isActive() const;
	};
}