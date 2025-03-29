#pragma once

#include "EdgeCommon/Math/ComputeMatrix33.h"

#include "EdgePhysics/Physics/Entity/PhysicsEntity.h"

namespace Edge
{
	class AxisRotationConstraintPart final
	{
	private:
		ComputeMatrix3x3 m_invIner1 = ComputeMatrix3x3Zero;
		ComputeMatrix3x3 m_invIner2 = ComputeMatrix3x3Zero;

		ComputeMatrix2x2 m_invEffectiveMass = ComputeMatrix2x2Zero;

		ComputeVector3 m_totalLambda = ComputeVector3Zero;

		ComputeVector3 m_axis1 = ComputeVector3Zero;
		ComputeVector3 m_axisOrtho1 = ComputeVector3Zero;
		ComputeVector3 m_axisOrtho2 = ComputeVector3Zero;

		PhysicsEntityReference m_entity1;
		PhysicsEntityReference m_entity2;

		void deactivate();

		void applyVelocity(const ComputeVector3& lambda) const;
		void applyPosition(const ComputeVector3& lambda) const;

	public:
		AxisRotationConstraintPart(const PhysicsEntityReference& entity1, const PhysicsEntityReference& entity2)
			: m_entity1(entity1), m_entity2(entity2) {}

		void preSolve(const ComputeVector3& axis1, const ComputeVector3& axis2);
		void warmUp();
		void solveVelocity();
		void solvePosition();

		bool isActive() const;
	};
}
