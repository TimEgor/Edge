#pragma once

#include "EdgePhysics/Physics/Entity/PhysicsBody.h"

#include "EdgeDemoFramework/Demo/PreInitedDemo.h"

namespace EdgeDemo
{
	class TestCollisionDemo final : public PreInitedDemo
	{
	private:
		Edge::PhysicsBodyReference m_staticBody;
		Edge::PhysicsBodyReference m_dynamicBody;

	public:
		TestCollisionDemo() = default;

		virtual bool initDemo() override;
		virtual void releaseDemo() override;

		virtual void updateDemoLogic(float deltaTime) override;
	};
}
