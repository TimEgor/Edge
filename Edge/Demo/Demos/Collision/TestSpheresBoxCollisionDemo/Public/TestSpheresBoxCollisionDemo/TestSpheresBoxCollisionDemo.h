#pragma once

#include "EdgePhysics/Physics/Entity/PhysicsBody.h"

#include "EdgeDemoFramework/Demo/PreInitedDemo.h"

namespace EdgeDemo
{
	class TestSpheresBoxCollisionDemo final : public PreInitedDemo
	{
	private:
		std::vector<Edge::PhysicsBodyReference> m_spheres;
		std::vector<Edge::PhysicsBodyReference> m_staticBoxes;

		bool initStaticBoxes();

		void updateSphereSpawningLogic(float deltaTime);

		static constexpr float SpawningDelay = 1.0f;
		static constexpr uint32_t MaxSphereCount = 50;
		float m_spawningDelay = 0.0f;

	public:
		TestSpheresBoxCollisionDemo() = default;

		virtual bool initDemo() override;
		virtual void releaseDemo() override;

		virtual void updateDemoLogic(float deltaTime) override;
	};
}
