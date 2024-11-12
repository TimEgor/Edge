#pragma once

#include "EdgeCommon/Math/Matrix.h"
#include "EdgeCommon/Math/Vector.h"

#include "EdgePhysics/Physics/Entity/PhysicsEntity.h"

namespace Edge
{
	class PositionConstraintPart
	{
	private:
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
		PositionConstraintPart(const PhysicsEntityReference& entity1, const PhysicsEntityReference& entity2)
			: m_entity1(entity1), m_entity2(entity2) {}

		void preSolve(const FloatVector3& anchor1, const FloatVector3& anchor2);
		void solveVelocity();
		void solvePosition() const;

		bool isActive() const;
	};
}
