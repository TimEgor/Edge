#pragma once

#include "EdgeCommon/FileName/FileName.h"

#include "EdgeFramework/PluginController/PluginHandle.h"

#include "Renderer.h"

namespace Edge
{
	class Texture2D;
	class DebugVisualizationDataController;

	class RenderController final
	{
	private:
		Renderer* m_renderer = nullptr;
		PluginHandleReference m_rendererPluginHandle;

	public:
		RenderController() = default;

		bool init(const FileName& rendererPluginPath);
		void release();

		void prepareData(
			const Texture2D& texture,
			const Renderer::CameraParams& cameraTransforms,
			const Transform& cameraTransform,
			const DebugVisualizationDataController& visualizationData
		);
		void render(Texture2D& texture);
	};
}
