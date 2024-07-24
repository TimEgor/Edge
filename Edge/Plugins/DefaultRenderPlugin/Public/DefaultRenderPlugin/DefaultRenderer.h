#pragma once

#include "TinySimFramework/Graphics/GraphicPlatform/GraphicObject/Texture.h"
#include "TinySimFramework/Graphics/Render/Renderer.h"
#include "TinySimPhysics/Visualizer/IDebugVisualizationDataController.h"

#include "RenderDatas.h"

namespace TS {
	class AssetsDirectoryController;

	class GraphicDevice;

	class DeferredGraphicContext;

	class GPUBuffer;

	class RasterizationState;
}

namespace TS_DEF_RENDERER
{
	class DefaultRenderer final : public TS::Renderer
	{
		struct CameraShaderData final
		{
			CameraTransforms m_transforms;
			TS::Texture2DSize m_screenSize;
		};

	private:
		TS::DeferredGraphicContext* m_graphicContext = nullptr;
		
		TS::RasterizationState* m_baseRasterizationState = nullptr;

		TS::Texture2D* m_depthBuffer = nullptr;

		TS::GPUBuffer* m_cameraTransformBuffer = nullptr;

		CameraShaderData m_cameraShaderData;

		PointRenderData m_pointRenderData;
		LineRenderData m_lineRenderData;
		PlaneRenderData m_planeRenderData;
		PlaneRenderData m_wireframePlaneRenderData;
		BoxRenderData m_boxRenderData;
		BoxRenderData m_wireframeBoxRenderData;
		SphereRenderData m_sphereRenderData;
		SphereRenderData m_wireframeSphereRenderData;

		bool initPointRenderData(TS::GraphicDevice& device, const TS::AssetsDirectoryController& assetsDirectoryController);
		bool initLineRenderData(TS::GraphicDevice& device, const TS::AssetsDirectoryController& assetsDirectoryController);
		bool initPlaneRenderData(TS::GraphicDevice& device, const TS::AssetsDirectoryController& assetsDirectoryController);
		bool initWireframePlaneRenderData(TS::GraphicDevice& device, const TS::AssetsDirectoryController& assetsDirectoryController);
		bool initBoxRenderData(TS::GraphicDevice& device, const TS::AssetsDirectoryController& assetsDirectoryController);
		bool initWireframeBoxRenderData(TS::GraphicDevice& device, const TS::AssetsDirectoryController& assetsDirectoryController);
		bool initSphereRenderData(TS::GraphicDevice& device, const TS::AssetsDirectoryController& assetsDirectoryController);
		bool initWireframeSphereRenderData(TS::GraphicDevice& device, const TS::AssetsDirectoryController& assetsDirectoryController);

		void releasePointRenderData();
		void releaseLineRenderData();
		void releasePlaneRenderData();
		void releaseWireframePlaneRenderData();
		void releaseBoxRenderData();
		void releaseWireframeBoxRenderData();
		void releaseSphereRenderData();
		void releaseWireframeSphereRenderData();

		void preparePointRenderData(float deltaTime, const TS::IDebugVisualizationDataController& visualizationData);
		void prepareLineRenderData(float deltaTime, const TS::IDebugVisualizationDataController& visualizationData);
		void preparePlaneRenderData(float deltaTime, const TS::IDebugVisualizationDataController& visualizationData);
		void prepareWireframePlaneRenderData(float deltaTime, const TS::IDebugVisualizationDataController& visualizationData);
		void prepareBoxRenderData(float deltaTime, const TS::IDebugVisualizationDataController& visualizationData);
		void prepareWireframeBoxRenderData(float deltaTime, const TS::IDebugVisualizationDataController& visualizationData);
		void prepareSphereRenderData(float deltaTime, const TS::IDebugVisualizationDataController& visualizationData);
		void prepareWireframeSphereRenderData(float deltaTime, const TS::IDebugVisualizationDataController& visualizationData);

		static TS::FloatVector3 calculateArrowHeadPerpendicular(const TS::FloatVector3& arrowDirection);

		void drawPoints();
		void drawLines();
		void drawPlanes();
		void drawWireframePlanes();
		void drawBoxes();
		void drawWireframeBoxes();
		void drawSpheres();
		void drawWireframeSpheres();

		void prepareDepthBuffer(const TS::Texture2DSize& bufferSize);

	public:
		DefaultRenderer() = default;

		virtual bool init() override;
		virtual void release() override;

		virtual void prepareData(const CameraTransforms& cameraTransforms, const TS::IDebugVisualizationDataController& visualizationData) override;
		virtual void render(TS::Texture2D& targetTexture) override;
	};
}
