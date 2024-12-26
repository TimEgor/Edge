#pragma once

#include "EdgeCommon/Math/Vector.h"

#include "EdgePhysics/Physics/Entity/PhysicsEntity.h"

namespace Edge
{
	class ContactFrictionAxleConstraintPart final
	{
	private:
		FloatVector3 m_radiusNorm1 = FloatVector3Zero;
		FloatVector3 m_radiusNorm2 = FloatVector3Zero;

		FloatVector3 m_invInerRadiusNorm1 = FloatVector3Zero;
		FloatVector3 m_invInerRadiusNorm2 = FloatVector3Zero;

		float m_totalLambda = 0.0f;
		float m_invEffectiveMass = 0.0f;
		float m_friction = 0.0f;

		PhysicsEntityReference m_entity1;
		PhysicsEntityReference m_entity2;

		void deactivate();

	public:
		ContactFrictionAxleConstraintPart(const PhysicsEntityReference& entity1, const PhysicsEntityReference& entity2)
			: m_entity1(entity1), m_entity2(entity2) {}

		void preSolve(const FloatVector3& contactPosition, const FloatVector3& normal);
		void warmUp(const FloatVector3& normal);
		float solveVelocity(const FloatVector3& normal);
		void applyVelocity(const FloatVector3& normal, float lambda);

		bool isActive() const;
	};
}
