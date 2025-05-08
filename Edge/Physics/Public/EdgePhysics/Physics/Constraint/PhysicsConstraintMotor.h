#pragma once

#include "PhysicsConstraint.h"

namespace Edge
{
	using PhysicsConstraintMotorType = HashedType::Type;

	class PhysicsConstraintMotor : public NonCopyable, public HashedType, public DefaultDestroyingMTCountableObjectBase
	{
	private:
		PhysicsConstraint* m_constraint = nullptr;
		bool m_isEnabled = true;

	public:
		PhysicsConstraintMotor() = default;

		virtual void preSolve(float deltaTime) = 0;
		virtual void warmUp() = 0;
		virtual void solveVelocity() = 0;
		virtual void solvePosition() = 0;

		bool isEnabled() const;
		void setEnabled(bool isEnabled);

		void setConstraintContext(const PhysicsConstraintReference& constraint);
		PhysicsConstraint* getConstraintContext() const;

		virtual PhysicsConstraintMotorType getType() const = 0;
	};

#define EDGE_PHYSICS_CONSTRAINT_MOTOR_TYPE(PHYSICS_CONSTRAINT_MOTOR_TYPE) EDGE_HASH_TYPE(#PHYSICS_CONSTRAINT_MOTOR_TYPE, Edge::PhysicsConstraintMotorType, PhysicsConstraintMotor)

	EDGE_REFERENCE(PhysicsConstraintMotor);
}
