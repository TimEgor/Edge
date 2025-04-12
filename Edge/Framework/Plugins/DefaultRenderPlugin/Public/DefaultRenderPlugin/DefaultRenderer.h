#pragma once

#include "EdgePhysics/Visualizer/DebugVisualizationDataController.h"

#include "EdgeFramework/Graphics/GraphicPlatform/GraphicObject/Texture.h"
#include "EdgeFramework/Graphics/Render/Renderer.h"

#include "Font/FontController.h"

#include "RenderDatas.h"

namespace Edge
{
	class AssetsDirectoryController;

	class GraphicDevice;

	class DeferredGraphicContext;

	class GPUBuffer;

	class RasterizationState;
	class SamplerState;
	class BlendState;
	class DepthStencilState;
}

namespace EdgeDefRender
{
	class DefaultRenderer final : public Edge::Renderer
	{
		struct CameraProjectionTransformData final
		{
			Edge::FloatMatrix4x4 m_projTransform = Edge::FloatMatrix4x4Identity;
		};

		struct CameraTransformData final
		{
			Edge::FloatMatrix4x4 m_viewTransform = Edge::FloatMatrix4x4Identity;
			Edge::Texture2DSize m_screenSize;
		};

	private:
		CameraProjectionTransformData m_perspectiveShaderData;
		CameraProjectionTransformData m_orthogonalShaderData;
		CameraTransformData m_cameraShaderData;

		PointRenderData m_pointRenderData;
		LineRenderData m_lineRenderData;
		PolygonRenderData m_polygonRenderData;
		PlaneRenderData m_planeRenderData;
		PlaneRenderData m_wireframePlaneRenderData;
		BoxRenderData m_boxRenderData;
		BoxRenderData m_wireframeBoxRenderData;
		SphereRenderData m_sphereRenderData;
		SphereRenderData m_wireframeSphereRenderData;
		TextRenderData m_orientedWorldTextRenderData;
		TextRenderData m_worldTextRenderData;
		TextRenderData m_screenTextRenderData;

		Font m_defaultFont;

		Edge::DeferredGraphicContext* m_graphicContext = nullptr;

		Edge::RasterizationState* m_baseRasterizationState = nullptr;
		Edge::RasterizationState* m_orthogonalRasterizationState = nullptr;
		Edge::SamplerState* m_baseSamplerState = nullptr;
		Edge::BlendState* m_alphaBlendState = nullptr;
		Edge::DepthStencilState* m_depthTestEnableState = nullptr;
		Edge::DepthStencilState* m_depthTestDisableState = nullptr;
		Edge::Texture2D* m_depthBuffer = nullptr;
		Edge::GPUBuffer* m_perspectiveTransformBuffer = nullptr;
		Edge::GPUBuffer* m_orthogonalTransformBuffer = nullptr;
		Edge::GPUBuffer* m_cameraTransformBuffer = nullptr;

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

		bool initTextRenderData(
			Edge::GraphicDevice& device,
			const Edge::AssetsDirectoryController& assetsDirectoryController,
			TextRenderData& textRenderData,
			bool isOrthoProj
		);

		bool initCameraTransformBuffers(Edge::GraphicDevice& device);
		bool initDefaultFont(Edge::GraphicDevice& device);

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

		void releaseTextRenderData(TextRenderData& textRenderData);

		void releaseCameraTransformBuffers();
		void releaseDefaultFont();

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

		void buildStringVertexBuffer(
			RenderDataBufferCacheIterator& cacheIterator,
			const std::string& text,
			const Edge::FloatComputeMatrix4x4& transform,
			PackedColor color
		);
		void prepareOrientedWorldTextRenderData(float deltaTime, const Edge::DebugVisualizationDataController& visualizationData);
		void prepareWorldTextRenderData(
			float deltaTime,
			const Edge::DebugVisualizationDataController& visualizationData,
			const Edge::Transform& cameraTransform
		);
		void prepareScreenTextRenderData(
			float deltaTime,
			const Edge::DebugVisualizationDataController& visualizationData,
			const Edge::Texture2DSize& textureSize
		);

		void prepareDepthBuffer(const Edge::Texture2DSize& bufferSize);
		void prepareCameraData() const;

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

		void drawTexts(const TextRenderData& worldRenderData);

		static constexpr char DefaultFontName[] = "Consolas";
		static constexpr uint32_t DefaultFontHeight = 50;
		static Edge::FloatComputeVector3 CalculateArrowHeadPerpendicular(const Edge::FloatComputeVector3& arrowDirection);

	public:
		DefaultRenderer() = default;

		virtual bool init() override;
		virtual void release() override;

		virtual void prepareData(
			const Edge::Texture2D& targetTexture,
			const CameraParams& cameraParams,
			const Edge::Transform& cameraTransform,
			const Edge::DebugVisualizationDataController& visualizationData
		) override;
		virtual void render(Edge::Texture2D& targetTexture) override;
	};
}
