#pragma once

#include "EdgePhysics/Physics/Entity/PhysicsBody.h"

#include "EdgeDemoFramework/Demo/PreInitedDemo.h"

namespace EdgeDemo
{
	class TestFixConstraintDemo final : public PreInitedDemo
	{
	private:
		std::vector<Edge::PhysicsBodyReference> m_bodies;
		std::vector<Edge::PhysicsConstraintReference> m_constraints;

		void drawSphere(const Edge::PhysicsBodyReference& body) const;

	public:
		TestFixConstraintDemo() = default;

		virtual bool initDemo() override;
		virtual void releaseDemo() override;

		virtual void updateDemoLogic(float deltaTime) override;
	};
}
