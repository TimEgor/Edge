#pragma once

#include "EdgeCommon/Math/Vector.h"

#include "EdgePhysics/Physics/Entity/PhysicsEntity.h"

namespace Edge
{
	class ContactPenetrationAxleConstraintPart final
	{
	private:
		ComputeVector3 m_radiusNorm1 = FloatVector3Zero;
		ComputeVector3 m_radiusNorm2 = FloatVector3Zero;

		ComputeVector3 m_invInerRadiusNorm1 = FloatVector3Zero;
		ComputeVector3 m_invInerRadiusNorm2 = FloatVector3Zero;

		ComputeValueType m_totalLambda = ComputeValueType(0.0);
		ComputeValueType m_invEffectiveMass = ComputeValueType(0.0);
		ComputeValueType m_restitution = ComputeValueType(0.0);

		PhysicsEntityReference m_entity1;
		PhysicsEntityReference m_entity2;

		void deactivate();

		void applyVelocity(const ComputeVector3& normal, ComputeValueType lambda) const;
		void applyPosition(const ComputeVector3& normal, ComputeValueType lambda) const;

	public:
		ContactPenetrationAxleConstraintPart(const PhysicsEntityReference& entity1, const PhysicsEntityReference& entity2)
			: m_entity1(entity1), m_entity2(entity2) {}

		void preSolve(const ComputeVector3& contactPosition, const ComputeVector3& normal);
		void warmUp(const ComputeVector3& normal);
		void solveVelocity(const ComputeVector3& normal);
		void solvePosition(const ComputeVector3& normal, ComputeValueType depth);

		ComputeValueType getTotalLambda() const;
		void setTotalLambda(ComputeValueType lambda);

		bool isActive() const;
	};
}
