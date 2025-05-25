#pragma once

#include "EdgeCommon/Math/ComputeMatrix33.h"

#include "EdgePhysics/Physics/Entity/PhysicsEntity.h"

namespace Edge
{
	class AxisPositionConstraintPart final
	{
	private:
		ComputeMatrix2x2 m_invEffectiveMass = ComputeMatrix2x2Zero;

		ComputeVector2 m_totalLambda = ComputeVector2Zero;

		ComputeVector3 m_u = ComputeVector3Zero;

		ComputeVector3 m_n1 = ComputeVector3Zero;
		ComputeVector3 m_n2 = ComputeVector3Zero;

		ComputeVector3 m_r1_u_n1 = ComputeVector3Zero;
		ComputeVector3 m_r1_u_n2 = ComputeVector3Zero;
		ComputeVector3 m_r2_n1 = ComputeVector3Zero;
		ComputeVector3 m_r2_n2 = ComputeVector3Zero;

		PhysicsEntityReference m_entity1;
		PhysicsEntityReference m_entity2;

		void deactivate();

		void applyVelocity(const ComputeVector2& lambda) const;
		void applyPosition(const ComputeVector2& lambda) const;

	public:
		AxisPositionConstraintPart(const PhysicsEntityReference& entity1, const PhysicsEntityReference& entity2)
			: m_entity1(entity1), m_entity2(entity2) {}

		void preSolve(const ComputeVector3& anchor1, const ComputeVector3& anchor2, const ComputeVector3& axis1, const ComputeVector3& axis2);
		void warmUp();
		void solveVelocity();
		void solvePosition();

		bool isActive() const;
	};
}
