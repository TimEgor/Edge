#pragma once

#include "EdgeEngine/Graphic/Render/IRenderController.h"
#include "EdgeEngine/Plugin/PluginHandle.h"

namespace Edge
{
	class RenderController final : public IRenderController
	{
	private:
		IRender* m_render = nullptr;
		PluginHandleReference m_renderPluginHandle;

	public:
		RenderController() = default;

		virtual bool init(const FileName& rendererPluginPath) override;
		virtual void release() override;

		virtual void prepareData(const IRender::CameraTransforms& cameraTransforms, const IVisualizationDataController& visualizationData) override;
		virtual void render(ITexture2D& texture) override;
	};
}
