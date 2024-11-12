#pragma once

#include "EdgePhysics/Physics/Entity/PhysicsBody.h"

#include "EdgeDemoFramework/Demo/PreInitedDemo.h"

namespace EdgeDemo
{
	class TestKeepDistanceConstraintDemo final : public PreInitedDemo
	{
	private:
		Edge::PhysicsBodyReference m_staticBody;
		Edge::PhysicsBodyReference m_dynamicBody;

		Edge::PhysicsConstraintReference m_constraint;

		void drawSphere(const Edge::PhysicsBodyReference& body) const;

	public:
		TestKeepDistanceConstraintDemo() = default;

		virtual bool initDemo() override;
		virtual void releaseDemo() override;

		virtual void updateDemoLogic(float deltaTime) override;
	};
}
