#pragma once

#include "TinySimDemoFramework/Demo/PreInitedDemo.h"

namespace TS_DEMO
{
	class FireworksParticleController;

	class FireworksDemo final : public PreInitedDemo
	{
	private:
		FireworksParticleController* m_fireworksParticleController = nullptr;

	public:
		FireworksDemo() = default;

		virtual bool initDemo() override;
		virtual void releaseDemo() override;

		virtual void updateDemoLogic(float deltaTime) override;
	};
}
