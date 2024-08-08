#pragma once

namespace Edge
{
	struct Transform;
	class DebugVisualizationDataController;
}

namespace EdgeDemo
{
	class Demo
	{
	public:
		Demo() = default;
		virtual ~Demo() = default;

		virtual bool init() { return true; }
		virtual void release() {}

		//call once per frame before phys update
		virtual void updateLogic(float deltaTime) {}
		//call before every phys step
		virtual void prePhysStepUpdate(float deltaTime) {}

		virtual void physUpdate(float deltaTime) = 0;

		virtual Edge::DebugVisualizationDataController& getDebugVisualizationData() = 0;
		virtual const Edge::Transform& getCameraTransform() const = 0;
	};
}
