#pragma once

#include "EdgePhysics/Physics/Entity/PhysicsBody.h"

#include "EdgeDemoFramework/Demo/PreInitedDemo.h"
#include "EdgePhysics/Physics/Constraint/Constraints/HingeConstraint.h"

namespace EdgeDemo
{
	class TestHingeConstraintDemo final : public PreInitedDemo
	{
	private:
		Edge::PhysicsBodyReference m_staticBody;
		Edge::PhysicsBodyReference m_dynamicBody;
		Edge::HingeConstraintReference m_constraint;

		Edge::FloatQuaternion m_testRotation = Edge::FloatQuaternionIdentity;

		void drawBox(const Edge::PhysicsBodyReference& body, bool isDynamic) const;

	public:
		TestHingeConstraintDemo() = default;

		virtual bool initDemo() override;
		virtual void releaseDemo() override;

		virtual void updateDemoLogic(float deltaTime) override;
	};
}
