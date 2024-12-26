#pragma once

#include "EdgeCommon/Math/Matrix.h"
#include "EdgeCommon/Math/Vector.h"

#include "EdgePhysics/Physics/Entity/PhysicsEntity.h"

namespace Edge
{
	class KeepPositionConstraintPart final
	{
	private:
		FloatMatrix4x4 m_invInerR1 = FloatMatrix4x4Zero;
		FloatMatrix4x4 m_invInerR2 = FloatMatrix4x4Zero;

		FloatMatrix4x4 m_invEffectiveMass = FloatMatrix4x4Identity;
		FloatVector3 m_totalLambda = FloatVector3Zero;

		FloatVector3 m_r1 = FloatVector3Zero;
		FloatVector3 m_r2 = FloatVector3Zero;

		PhysicsEntityReference m_entity1;
		PhysicsEntityReference m_entity2;

		void deactivate();

		void applyVelocity(const FloatVector3& lambda) const;
		void applyPosition(const FloatVector3& lambda) const;

	public:
		KeepPositionConstraintPart(const PhysicsEntityReference& entity1, const PhysicsEntityReference& entity2)
			: m_entity1(entity1), m_entity2(entity2) {}

		void preSolve(const FloatVector3& anchor1, const FloatVector3& anchor2);
		void warmUp();
		void solveVelocity();
		void solvePosition();

		bool isActive() const;
	};
}
