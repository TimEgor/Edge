#pragma once

#include "EdgeCommon/Math/ComputeMatrix44.h"

#include "EdgePhysics/Physics/Entity/PhysicsEntity.h"

namespace Edge
{
	class KeepPositionConstraintPart final
	{
	private:
		ComputeMatrix3x3 m_invEffectiveMass = ComputeMatrix3x3Identity;
		ComputeVector3 m_totalLambda = ComputeVector3Zero;

		ComputeVector3 m_r1 = FloatVector3Zero;
		ComputeVector3 m_r2 = FloatVector3Zero;

		PhysicsEntityReference m_entity1;
		PhysicsEntityReference m_entity2;

		void deactivate();

		void applyVelocity(const ComputeVector3& lambda) const;
		void applyPosition(const ComputeVector3& lambda) const;

	public:
		KeepPositionConstraintPart(const PhysicsEntityReference& entity1, const PhysicsEntityReference& entity2)
			: m_entity1(entity1), m_entity2(entity2) {}

		void preSolve(const ComputeVector3& anchor1, const ComputeVector3& anchor2);
		void warmUp();
		void solveVelocity();
		void solvePosition();

		bool isActive() const;
	};
}
