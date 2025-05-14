#pragma once

#include "PhysicsConstraint.h"
#include "EdgeCommon/RTTI/RTTI.h"

namespace Edge
{
	class PhysicsConstraintMotor : public NonCopyable, public DefaultDestroyingMTCountableObjectBase
	{
	private:
		PhysicsConstraint* m_constraint = nullptr;
		bool m_isEnabled = true;

	public:
		PhysicsConstraintMotor() = default;

		bool isEnabled() const;
		void setEnabled(bool isEnabled);

		void setConstraintContext(const PhysicsConstraintReference& constraint);
		PhysicsConstraint* getConstraintContext() const;

		EDGE_RTTI_VIRTUAL_BASE(PhysicsConstraintMotor)
	};

	EDGE_REFERENCE(PhysicsConstraintMotor);
}