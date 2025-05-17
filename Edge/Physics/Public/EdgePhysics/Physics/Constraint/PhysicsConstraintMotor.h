#pragma once

#include "EdgeCommon/Patterns/NonCopyable.h"
#include "EdgeCommon/Reference/Reference.h"
#include "EdgeCommon/RTTI/RTTI.h"

#include "TwoPhysicsEntityConstraint.h"

namespace Edge
{
	class TwoPhysicsEntityConstraint;

	class PhysicsConstraintMotor : public NonCopyable, public DefaultDestroyingMTCountableObjectBase
	{
	private:
		TwoPhysicsEntityConstraint* m_constraint = nullptr;
		bool m_isEnabled = true;

	public:
		PhysicsConstraintMotor() = default;

		bool isEnabled() const;
		void setEnabled(bool isEnabled);

		void setConstraintContext(const TwoPhysicsEntityConstraintReference& constraint);
		TwoPhysicsEntityConstraint* getConstraintContext() const;

		EDGE_RTTI_VIRTUAL_BASE(PhysicsConstraintMotor)
	};

	EDGE_REFERENCE(PhysicsConstraintMotor);
}