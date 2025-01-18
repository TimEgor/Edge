#pragma once

#include "EdgeCommon/Math/Matrix.h"
#include "EdgeCommon/Math/Vector.h"

#include "EdgePhysics/Physics/Entity/PhysicsEntity.h"

namespace Edge
{
	class AxisRotationConstraintPart final
	{
	private:
		FloatMatrix4x4 m_invIner1 = FloatMatrix4x4Zero;
		FloatMatrix4x4 m_invIner2 = FloatMatrix4x4Zero;

		FloatMatrix2x2 m_invEffectiveMass = FloatMatrix2x2Zero;

		FloatVector3 m_totalLambda = FloatVector2Zero;

		FloatVector3 m_axis1 = FloatVector3Zero;
		FloatVector3 m_axisOrtho1 = FloatVector3Zero;
		FloatVector3 m_axisOrtho2 = FloatVector3Zero;

		PhysicsEntityReference m_entity1;
		PhysicsEntityReference m_entity2;

		void deactivate();

		void applyVelocity(const FloatVector3& lambda) const;
		void applyPosition(const FloatVector3& lambda) const;

	public:
		AxisRotationConstraintPart(const PhysicsEntityReference& entity1, const PhysicsEntityReference& entity2)
			: m_entity1(entity1), m_entity2(entity2) {}

		void preSolve(const FloatVector3& axis1, const FloatVector3& axis2);
		void warmUp();
		void solveVelocity();
		void solvePosition();

		bool isActive() const;
	};
}
