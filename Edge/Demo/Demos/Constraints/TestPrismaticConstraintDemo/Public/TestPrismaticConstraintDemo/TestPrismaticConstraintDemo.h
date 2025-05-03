#pragma once

#include "EdgePhysics/Physics/Constraint/Constraints/LimitedPrismaticConstraint.h"
#include "EdgePhysics/Physics/Entity/PhysicsBody.h"

#include "EdgeDemoFramework/Demo/PreInitedDemo.h"

namespace EdgeDemo
{
	class TestPrismaticConstraintDemo final : public PreInitedDemo
	{
	private:
		Edge::PhysicsBodyReference m_staticBody;
		Edge::PhysicsBodyReference m_dynamicBody;
		Edge::LimitedPrismaticConstraintReference m_constraint;

		Edge::FloatQuaternion m_testRotation = Edge::FloatQuaternionIdentity;

		void drawBox(const Edge::PhysicsBodyReference& body, bool isDynamic) const;

	public:
		TestPrismaticConstraintDemo() = default;

		virtual bool initDemo() override;
		virtual void releaseDemo() override;

		virtual void updateDemoLogic(float deltaTime) override;
	};
}
