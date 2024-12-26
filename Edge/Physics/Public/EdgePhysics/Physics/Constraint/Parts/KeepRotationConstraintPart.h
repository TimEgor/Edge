#pragma once

#include "EdgeCommon/Math/Matrix.h"
#include "EdgeCommon/Math/Vector.h"

#include "EdgePhysics/Physics/Entity/PhysicsEntity.h"

namespace Edge
{
	class KeepRotationConstraintPart final
	{
	private:
		FloatMatrix4x4 m_invIner1 = FloatMatrix4x4Zero;
		FloatMatrix4x4 m_invIner2 = FloatMatrix4x4Zero;

		FloatMatrix4x4 m_invEffectiveMass = FloatMatrix4x4Identity;
		FloatVector3 m_totalLambda = FloatVector3Zero;

		PhysicsEntityReference m_entity1;
		PhysicsEntityReference m_entity2;

		void deactivate();

		void applyVelocity(const FloatVector3& lambda) const;
		void applyPosition(const FloatVector3& lambda) const;

	public:
		KeepRotationConstraintPart(const PhysicsEntityReference& entity1, const PhysicsEntityReference& entity2)
			: m_entity1(entity1), m_entity2(entity2) {}

		void preSolve();
		void warmUp();
		void solveVelocity();
		void solvePosition(const FloatQuaternion& invInitialDeltaOrientation);

		bool isActive() const;
	};
}