#pragma once

#include "EdgeCommon/Math/Matrix.h"

namespace Edge
{
	class DebugVisualizationDataController;
	class Texture2D;

	class Renderer
	{
	public:
		struct CameraTransforms final
		{
			FloatMatrix4x4 m_viewTransform = FloatMatrix4x4Identity;
			FloatMatrix4x4 m_projTransform = FloatMatrix4x4Identity;
		};

		Renderer() = default;
		virtual ~Renderer() = default;

		virtual bool init() = 0;
		virtual void release() = 0;

		virtual void prepareData(const CameraTransforms& cameraTransforms, const DebugVisualizationDataController& visualizationData) = 0;
		virtual void render(Texture2D& targetTexture) = 0;
	};
}
