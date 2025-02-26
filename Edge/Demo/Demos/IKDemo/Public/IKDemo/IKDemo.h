#pragma once

#include "EdgeDemoFramework/Demo/PreInitedDemo.h"

#include "IK/IkHingeJoint.h"
#include "IK/IkSolver.h"
#include "IK/IkSystem.h"

namespace EdgeDemo
{
	class IkDemo final : public PreInitedDemo
	{
	private:
		std::vector<IkLink> m_ikLinks;
		std::vector<IkHingeJoint> m_ikJoints;

		IkSystem m_ikSystem;
		IkSolver m_ikSolver;

		Edge::FloatVector3 m_target = Edge::FloatVector3Zero;

		void updateTarget(float deltaTime);

	public:
		IkDemo() = default;

		virtual bool initDemo() override;
		virtual void releaseDemo() override;

		virtual void updateDemoLogic(float deltaTime) override;
	};
}
