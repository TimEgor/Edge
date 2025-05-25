#pragma once

#include "EdgePhysics/Physics/Entity/PhysicsBody.h"

#include "EdgeDemoFramework/Demo/PreInitedDemo.h"

namespace EdgeDemo
{
	class TestBoxStackCollisionDemo final : public PreInitedDemo
	{
	private:
		std::vector<Edge::PhysicsBodyReference> m_boxes;

	public:
		TestBoxStackCollisionDemo() = default;

		virtual bool initDemo() override;
		virtual void releaseDemo() override;

		virtual void updateDemoLogic(float deltaTime) override;
	};
}
