#pragma once

#include "EdgePhysics/Physics/Entity/PhysicsBody.h"

#include "EdgeDemoFramework/Demo/PreInitedDemo.h"

namespace EdgeDemo
{
	class TestCastDemo final : public PreInitedDemo
	{
	private:
		Edge::PhysicsBodyReference m_testBox1;
		Edge::PhysicsBodyReference m_testBox2;

		Edge::PhysicsBodyReference m_testSphere1;
		Edge::PhysicsBodyReference m_testSphere2;

		Edge::PhysicsBodyReference m_testTriangle1;
		Edge::PhysicsBodyReference m_testTriangle2;

		float m_localTime = 0.0f;

		void updateLocalTime(float deltaTime);

	public:
		TestCastDemo() = default;

		virtual bool initDemo() override;
		virtual void releaseDemo() override;

		virtual void updateDemoLogic(float deltaTime) override;
	};
}
