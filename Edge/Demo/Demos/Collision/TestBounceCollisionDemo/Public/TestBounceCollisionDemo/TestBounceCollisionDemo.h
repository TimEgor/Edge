#pragma once

#include "EdgePhysics/Physics/Entity/PhysicsBody.h"

#include "EdgeDemoFramework/Demo/PreInitedDemo.h"

namespace EdgeDemo
{
	class TestBounceCollisionDemo final : public PreInitedDemo
	{
	private:
		Edge::PhysicsBodyReference m_staticBody;

		Edge::PhysicsBodyReference m_dynamicBody1;
		Edge::PhysicsBodyReference m_dynamicBody2;

		Edge::PhysicsBodyReference m_dynamicBody3;
		Edge::PhysicsBodyReference m_dynamicBody4;

		void drawDynamicSphere(const Edge::PhysicsBodyReference& body) const;

	public:
		TestBounceCollisionDemo() = default;

		virtual bool initDemo() override;
		virtual void releaseDemo() override;

		virtual void updateDemoLogic(float deltaTime) override;
	};
}
