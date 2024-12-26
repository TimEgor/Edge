#pragma once

#include "EdgePhysics/Physics/Entity/PhysicsBody.h"

#include "EdgeDemoFramework/Demo/PreInitedDemo.h"

namespace EdgeDemo
{
	class TestFrictionDemo final : public PreInitedDemo
	{
	private:
		Edge::PhysicsBodyReference m_staticBox;
		Edge::PhysicsBodyReference m_dynamicBody;

	public:
		TestFrictionDemo() = default;

		virtual bool initDemo() override;
		virtual void releaseDemo() override;

		virtual void updateDemoLogic(float deltaTime) override;
	};
}
