#pragma once

#include "EdgePhysics/Physics/Entity/PhysicsBody.h"

#include "EdgeDemoFramework/Demo/PreInitedDemo.h"

namespace EdgeDemo
{
	class TestSpheresCollisionDemo final : public PreInitedDemo
	{
	private:
		std::vector<Edge::PhysicsBodyReference> m_spheres;

	public:
		TestSpheresCollisionDemo() = default;

		virtual bool initDemo() override;
		virtual void releaseDemo() override;

		virtual void updateDemoLogic(float deltaTime) override;
	};
}
