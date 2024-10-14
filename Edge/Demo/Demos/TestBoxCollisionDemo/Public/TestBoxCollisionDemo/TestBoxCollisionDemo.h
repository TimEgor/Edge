#pragma once

#include "EdgePhysics/Physics/Entity/PhysicsBody.h"

#include "EdgeDemoFramework/Demo/PreInitedDemo.h"

namespace EdgeDemo
{
	class TestBoxCollisionDemo final : public PreInitedDemo
	{
	private:
		Edge::PhysicsBodyReference m_staticBox;
		Edge::PhysicsBodyReference m_dynamicBox;

		void updateDynamicBoxTransform(float deltaTime);

	public:
		TestBoxCollisionDemo() = default;

		virtual bool initDemo() override;
		virtual void releaseDemo() override;

		virtual void updateDemoLogic(float deltaTime) override;
	};
}
