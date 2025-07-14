#pragma once

#include "EdgeCommon/Math/Vector.h"

#include "EdgePhysics/Physics/Entity/PhysicsEntity.h"

namespace Edge
{
	class ContactFrictionAxleConstraintPart final
	{
	private:
		ComputeVector3 m_radiusNorm1 = ComputeVector3Zero;
		ComputeVector3 m_radiusNorm2 = ComputeVector3Zero;

		ComputeVector3 m_invInerRadiusNorm1 = ComputeVector3Zero;
		ComputeVector3 m_invInerRadiusNorm2 = ComputeVector3Zero;

		ComputeValueType m_totalLambda = ComputeValueType(0.0);
		ComputeValueType m_invEffectiveMass = ComputeValueType(0.0);
		ComputeValueType m_friction = ComputeValueType(0.0);

		PhysicsEntityReference m_entity1;
		PhysicsEntityReference m_entity2;

		void deactivate();

	public:
		ContactFrictionAxleConstraintPart(const PhysicsEntityReference& entity1, const PhysicsEntityReference& entity2)
			: m_entity1(entity1), m_entity2(entity2) {}

		void preSolve(const ComputeVector3& contactPosition, const ComputeVector3& normal);
		void warmUp(const ComputeVector3& normal);
		ComputeValueType solveVelocity(const ComputeVector3& normal);
		void applyVelocity(const ComputeVector3& normal, ComputeValueType lambda);

		ComputeValueType getTotalLambda() const;
		void setTotalLambda(ComputeValueType lambda);

		bool isActive() const;
	};
}
