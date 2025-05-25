#pragma once

#include "EdgeCommon/Math/Matrix.h"
#include "EdgeCommon/Math/Vector.h"

#include "EdgePhysics/Physics/Entity/PhysicsEntity.h"

namespace Edge
{
	class KeepRotationConstraintPart final
	{
	private:
		ComputeMatrix3x3 m_invEffectiveMass = ComputeMatrix3x3Identity;
		ComputeVector3 m_totalLambda = ComputeVector3Zero;

		PhysicsEntityReference m_entity1;
		PhysicsEntityReference m_entity2;

		void deactivate();

		void applyVelocity(const ComputeVector3& lambda) const;
		void applyPosition(const ComputeVector3& lambda) const;

	public:
		KeepRotationConstraintPart(const PhysicsEntityReference& entity1, const PhysicsEntityReference& entity2)
			: m_entity1(entity1), m_entity2(entity2) {}

		void preSolve();
		void warmUp();
		void solveVelocity();
		void solvePosition(const ComputeQuaternion& invInitialDeltaOrientation);

		bool isActive() const;
	};
}