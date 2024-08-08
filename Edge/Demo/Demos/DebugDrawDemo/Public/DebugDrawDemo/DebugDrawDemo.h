#pragma once

#include "EdgeDemoFramework/Demo/PreInitedDemo.h"

namespace EdgeDemo
{
	class DebugDrawDemo final : public PreInitedDemo
	{
	public:
		DebugDrawDemo() = default;

		virtual void updateDemoLogic(float deltaTime) override;
	};
}
