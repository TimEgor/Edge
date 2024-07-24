#pragma once

#include "EdgeEngine/Core/FileName/FileName.h"

#include "IRender.h"

namespace Edge
{
	class ITexture2D;

	class IRenderController
	{
	public:
		IRenderController() = default;
		virtual ~IRenderController() = default;

		virtual bool init(const FileName& renderPluginPath) = 0;
		virtual void release() = 0;

		virtual void prepareData(const IRender::CameraTransforms& cameraTransforms, const IVisualizationDataController& visualizationData) = 0;
		virtual void render(ITexture2D& texture) = 0;
	};
}
