#pragma once

#include "EdgeCommon/Math/Transform.h"

#include "EdgeFramework/Application/Application.h"
#include "EdgeFramework/Graphics/Render/Renderer.h"

namespace EdgeDemo
{
	class Demo;

	class DemoApplication final : public Edge::Application
	{
	private:
		Edge::PluginHandleReference m_demoPluginHandle;
		Demo* m_demo = nullptr;

		bool initDemo();

		void update(float deltaTime);
		void prepareCameraData(Edge::Renderer::CameraParams& cameraParams, Edge::Transform& cameraTransform) const;

		virtual Edge::JobGraphReference getMainLoopJobGraph() override;

	public:
		DemoApplication() = default;

		virtual bool init() override;
		virtual void release() override;
	}; 
}
