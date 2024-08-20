#pragma once

#include "EdgePhysics/Physics/Entity/PhysicsBody.h"

#include "EdgeDemoFramework/Demo/PreInitedDemo.h"

namespace EdgeDemo
{
	class TestCastDemo final : public PreInitedDemo
	{
	private:
		Edge::PhysicsBodyReference m_testShapeEntity1;
		Edge::PhysicsBodyReference m_testShapeEntity2;
		Edge::PhysicsBodyReference m_testShapeEntity3;

		float m_localTime = 0.0f;

		void updateLocalTime(float deltaTime);

	public:
		TestCastDemo() = default;

		virtual bool initDemo() override;
		virtual void releaseDemo() override;

		virtual void updateDemoLogic(float deltaTime) override;
	};
}
