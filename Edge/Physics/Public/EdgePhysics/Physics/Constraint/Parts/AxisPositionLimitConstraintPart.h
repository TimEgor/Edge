#pragma once

#include "EdgeCommon/Math/ComputeMatrix33.h"

#include "EdgePhysics/Physics/Entity/PhysicsEntity.h"

namespace Edge
{
	class AxisPositionLimitConstraintPart final
	{
	private:
		ComputeVector3 m_a = ComputeVector3Zero;

		ComputeVector3 m_r1_u_a = ComputeVector3Zero;
		ComputeVector3 m_r2_a = ComputeVector3Zero;

		ComputeValueType m_minLambdaLimit = 0.0;
		ComputeValueType m_maxLambdaLimit = 0.0;

		ComputeValueType m_invEffectiveMass = 0.0;

		ComputeValueType m_totalLambda = 0.0;

		PhysicsEntityReference m_entity1;
		PhysicsEntityReference m_entity2;

		void deactivate();

		void applyVelocity(ComputeValueType lambda) const;
		void applyPosition(ComputeValueType lambda) const;

		void solveLimitPosition(ComputeValueType delta);

	public:
		AxisPositionLimitConstraintPart(const PhysicsEntityReference& entity1, const PhysicsEntityReference& entity2)
			: m_entity1(entity1),
			  m_entity2(entity2) {}

		void preSolve(
			const ComputeVector3& anchor1,
			const ComputeVector3& anchor2,
			const ComputeVector3& axis1,
			const ComputeVector3& axis2,
			ComputeValueType deltaOffset,
			ComputeValueType minLimit,
			ComputeValueType maxLimit
		);
		void warmUp();
		void solveVelocity();
		void solvePosition(ComputeValueType deltaOffset, ComputeValueType minLimit, ComputeValueType maxLimit);

		bool isActive() const;
	};
}
