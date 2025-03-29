#pragma once

#include "EdgeCommon/Math/Matrix.h"
#include "EdgeCommon/Math/Transform.h"

namespace Edge
{
	class DebugVisualizationDataController;
	class Texture2D;

	class Renderer
	{
	public:
		struct CameraParams final
		{
			float m_FoV = 90.0f;
			float m_ratio = 1.0f;
			float m_nearPlaneDistance = 0.05f;
			float m_farPlaneDistance = 1000.0f;
		};

		Renderer() = default;
		virtual ~Renderer() = default;

		virtual bool init() = 0;
		virtual void release() = 0;

		virtual void prepareData(const CameraParams& cameraParams, const Transform& cameraTransform, const DebugVisualizationDataController& visualizationData) = 0;
		virtual void render(Texture2D& targetTexture) = 0;
	};
}
