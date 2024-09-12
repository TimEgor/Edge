#pragma once

#include "EdgePhysics/Visualizer/DebugVisualizationDataController.h"

#include "EdgeFramework/Graphics/GraphicPlatform/GraphicObject/Texture.h"
#include "EdgeFramework/Graphics/Render/Renderer.h"

#include "RenderDatas.h"

namespace Edge {
	class AssetsDirectoryController;

	class GraphicDevice;

	class DeferredGraphicContext;

	class GPUBuffer;

	class RasterizationState;
}

namespace EdgeDefRender
{
	class DefaultRenderer final : public Edge::Renderer
	{
		struct CameraShaderData final
		{
			CameraTransforms m_transforms;
			Edge::Texture2DSize m_screenSize;
		};

	private:
		Edge::DeferredGraphicContext* m_graphicContext = nullptr;
		
		Edge::RasterizationState* m_baseRasterizationState = nullptr;

		Edge::Texture2D* m_depthBuffer = nullptr;

		Edge::GPUBuffer* m_cameraTransformBuffer = nullptr;

		CameraShaderData m_cameraShaderData;

		PointRenderData m_pointRenderData;
		LineRenderData m_lineRenderData;
		PolygonRenderData m_polygonRenderData;
		PlaneRenderData m_planeRenderData;
		PlaneRenderData m_wireframePlaneRenderData;
		BoxRenderData m_boxRenderData;
		BoxRenderData m_wireframeBoxRenderData;
		SphereRenderData m_sphereRenderData;
		SphereRenderData m_wireframeSphereRenderData;

		//init
		bool initPointRenderData(Edge::GraphicDevice& device, const Edge::AssetsDirectoryController& assetsDirectoryController);
		bool initLineRenderData(Edge::GraphicDevice& device, const Edge::AssetsDirectoryController& assetsDirectoryController);

		bool initPolygonRenderData(Edge::GraphicDevice& device, const Edge::AssetsDirectoryController& assetsDirectoryController);

		bool initPlaneRenderData(Edge::GraphicDevice& device, const Edge::AssetsDirectoryController& assetsDirectoryController);
		bool initWireframePlaneRenderData(Edge::GraphicDevice& device, const Edge::AssetsDirectoryController& assetsDirectoryController);

		bool initBoxRenderData(Edge::GraphicDevice& device, const Edge::AssetsDirectoryController& assetsDirectoryController);
		bool initWireframeBoxRenderData(Edge::GraphicDevice& device, const Edge::AssetsDirectoryController& assetsDirectoryController);

		bool initSphereRenderData(Edge::GraphicDevice& device, const Edge::AssetsDirectoryController& assetsDirectoryController);
		bool initWireframeSphereRenderData(Edge::GraphicDevice& device, const Edge::AssetsDirectoryController& assetsDirectoryController);

		//releasing
		void releasePointRenderData();
		void releaseLineRenderData();

		void releasePolygonRenderData();

		void releasePlaneRenderData();
		void releaseWireframePlaneRenderData();

		void releaseBoxRenderData();
		void releaseWireframeBoxRenderData();

		void releaseSphereRenderData();
		void releaseWireframeSphereRenderData();

		//preparation
		void preparePointRenderData(float deltaTime, const Edge::DebugVisualizationDataController& visualizationData);
		void prepareLineRenderData(float deltaTime, const Edge::DebugVisualizationDataController& visualizationData);

		void preparePolygonRenderData(float deltaTime, const Edge::DebugVisualizationDataController& visualizationData);

		void preparePlaneRenderData(float deltaTime, const Edge::DebugVisualizationDataController& visualizationData);
		void prepareWireframePlaneRenderData(float deltaTime, const Edge::DebugVisualizationDataController& visualizationData);

		void prepareBoxRenderData(float deltaTime, const Edge::DebugVisualizationDataController& visualizationData);
		void prepareWireframeBoxRenderData(float deltaTime, const Edge::DebugVisualizationDataController& visualizationData);

		void prepareSphereRenderData(float deltaTime, const Edge::DebugVisualizationDataController& visualizationData);
		void prepareWireframeSphereRenderData(float deltaTime, const Edge::DebugVisualizationDataController& visualizationData);

		static Edge::FloatVector3 calculateArrowHeadPerpendicular(const Edge::FloatVector3& arrowDirection);

		void prepareDepthBuffer(const Edge::Texture2DSize& bufferSize);

		//drawing
		void drawPoints();
		void drawLines();

		void drawPolygons();

		void drawPlanes();
		void drawWireframePlanes();

		void drawBoxes();
		void drawWireframeBoxes();

		void drawSpheres();
		void drawWireframeSpheres();

	public:
		DefaultRenderer() = default;

		virtual bool init() override;
		virtual void release() override;

		virtual void prepareData(const CameraTransforms& cameraTransforms, const Edge::DebugVisualizationDataController& visualizationData) override;
		virtual void render(Edge::Texture2D& targetTexture) override;
	};
}
