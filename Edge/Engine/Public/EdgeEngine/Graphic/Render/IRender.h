#pragma once

#include "EdgeEngine/Core/Math/Matrix.h"

namespace Edge
{
	class IVisualizationDataController;
	class ITexture2D;

	class IRender
	{
	public:
		struct CameraTransforms final
		{
			FloatMatrix4x4 m_viewTransform = FloatMatrix4x4Identity;
			FloatMatrix4x4 m_projTransform = FloatMatrix4x4Identity;
		};

		IRender() = default;
		virtual ~IRender() = default;

		virtual bool init() = 0;
		virtual void release() = 0;

		virtual void prepareData(const CameraTransforms& cameraTransforms, const IVisualizationDataController& visualizationData) = 0;
		virtual void render(ITexture2D& targetTexture) = 0;
	};
}
