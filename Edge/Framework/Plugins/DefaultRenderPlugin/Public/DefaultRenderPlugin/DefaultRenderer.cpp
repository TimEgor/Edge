#include "DefaultRenderer.h"

#include "EdgeCommon/UtilsMacros.h"
#include "EdgeCommon/FileName/FileName.h"
#include "EdgeCommon/Math/ComputeMath/ComputeMatrix.h"

#include "EdgePhysics/Visualizer/DebugVisualizationDataController.h"

#include "EdgeFramework/FrameworkCore.h"
#include "EdgeFramework/Application/Application.h"
#include "EdgeFramework/Graphics/GraphicPlatform/DefferedGraphicContext.h"
#include "EdgeFramework/Graphics/GraphicPlatform/GraphicDevice.h"
#include "EdgeFramework/Graphics/GraphicPlatform/GraphicPlatform.h"
#include "EdgeFramework/Graphics/GraphicPlatform/GraphicObject/GPUBuffer.h"
#include "EdgeFramework/Graphics/GraphicPlatform/GraphicObject/InputLayout.h"
#include "EdgeFramework/Graphics/GraphicPlatform/GraphicObject/RasterizationState.h"
#include "EdgeFramework/Graphics/GraphicPlatform/GraphicObject/Shader.h"
#include "EdgeFramework/Graphics/GraphicPlatform/GraphicObject/Texture.h"
#include "EdgeFramework/Recources/AssetsDirectoryController/AssetsDirectoryController.h"

#include "PrimitiveShapes/Cube.h"
#include "PrimitiveShapes/Sphere.h"


bool EdgeDefRender::DefaultRenderer::initPointRenderData(Edge::GraphicDevice& device, const Edge::AssetsDirectoryController& assetsDirectoryController)
{
	m_pointRenderData.m_vertexShader = device.createVertexShaderFromFile(assetsDirectoryController.prepareAssetPath("DefaultRenderPlugin", "Shaders/Point.vshader"));
	EDGE_CHECK_RETURN_FALSE(m_pointRenderData.m_vertexShader);

	m_pointRenderData.m_pixelShader = device.createPixelShaderFromFile(assetsDirectoryController.prepareAssetPath("DefaultRenderPlugin", "Shaders/Point.pshader"));
	EDGE_CHECK_RETURN_FALSE(m_pointRenderData.m_pixelShader);

	Edge::InputLayoutDesc inputLayoutDesc{};
	inputLayoutDesc.m_elements.push_back({ "INST_POSITION", 0, 0, offsetof(PointRenderData::PointData, m_position), 3, Edge::InputLayoutElementType::Float32 });
	inputLayoutDesc.m_elements.push_back({ "INST_COLOR", 0, 0, offsetof(PointRenderData::PointData, m_color), 1, Edge::InputLayoutElementType::UInt32 });
	inputLayoutDesc.m_bindings.push_back({ 0, sizeof(PointRenderData::PointData), Edge::InputLayoutBindingType::InstanceBinding });

	m_pointRenderData.m_inputLayout = device.createInputLayout(inputLayoutDesc, *m_pointRenderData.m_vertexShader);
	EDGE_CHECK_RETURN_FALSE(m_pointRenderData.m_inputLayout);

	RenderDataBufferCache::BufferDesc pointDataBufferDesc{};
	pointDataBufferDesc.m_stride = sizeof(PointRenderData::PointData);
	pointDataBufferDesc.m_usage = Edge::GPU_BUFFER_USAGE_VERTEX_BUFFER;
	pointDataBufferDesc.m_access = Edge::GRAPHIC_RESOURCE_ACCESS_CPU_WRITE | Edge::GRAPHIC_RESOURCE_ACCESS_GPU_READ;

	EDGE_CHECK_RETURN_FALSE(m_pointRenderData.m_pointData.init(pointDataBufferDesc, 512));

	return true;
}

bool EdgeDefRender::DefaultRenderer::initLineRenderData(Edge::GraphicDevice& device, const Edge::AssetsDirectoryController& assetsDirectoryController)
{
	m_lineRenderData.m_vertexShader = device.createVertexShaderFromFile(assetsDirectoryController.prepareAssetPath("DefaultRenderPlugin", "Shaders/Line.vshader"));
	EDGE_CHECK_RETURN_FALSE(m_lineRenderData.m_vertexShader);

	m_lineRenderData.m_pixelShader = device.createPixelShaderFromFile(assetsDirectoryController.prepareAssetPath("DefaultRenderPlugin", "Shaders/Line.pshader"));
	EDGE_CHECK_RETURN_FALSE(m_lineRenderData.m_pixelShader);

	Edge::InputLayoutDesc inputLayoutDesc{};
	inputLayoutDesc.m_elements.push_back({ "POSITION", 0, 0, offsetof(LineRenderData::VertexData, m_position), 3, Edge::InputLayoutElementType::Float32 });
	inputLayoutDesc.m_elements.push_back({ "COLOR", 0, 0, offsetof(LineRenderData::VertexData, m_color), 1, Edge::InputLayoutElementType::UInt32 });
	inputLayoutDesc.m_bindings.push_back({ 0, sizeof(LineRenderData::VertexData), Edge::InputLayoutBindingType::VertexBinding });

	m_lineRenderData.m_inputLayout = device.createInputLayout(inputLayoutDesc, *m_lineRenderData.m_vertexShader);
	EDGE_CHECK_RETURN_FALSE(m_lineRenderData.m_inputLayout);

	RenderDataBufferCache::BufferDesc lineDataBufferDesc{};
	lineDataBufferDesc.m_stride = sizeof(LineRenderData::LineData);
	lineDataBufferDesc.m_usage = Edge::GPU_BUFFER_USAGE_VERTEX_BUFFER;
	lineDataBufferDesc.m_access = Edge::GRAPHIC_RESOURCE_ACCESS_CPU_WRITE | Edge::GRAPHIC_RESOURCE_ACCESS_GPU_READ;

	EDGE_CHECK_RETURN_FALSE(m_lineRenderData.m_lineData.init(lineDataBufferDesc, 512));

	return true;
}

bool EdgeDefRender::DefaultRenderer::initPolygonRenderData(Edge::GraphicDevice& device, const Edge::AssetsDirectoryController& assetsDirectoryController)
{
	m_polygonRenderData.m_vertexShader = device.createVertexShaderFromFile(assetsDirectoryController.prepareAssetPath("DefaultRenderPlugin", "Shaders/Polygon.vshader"));
	EDGE_CHECK_RETURN_FALSE(m_polygonRenderData.m_vertexShader);

	m_polygonRenderData.m_pixelShader = device.createPixelShaderFromFile(assetsDirectoryController.prepareAssetPath("DefaultRenderPlugin", "Shaders/Polygon.pshader"));
	EDGE_CHECK_RETURN_FALSE(m_polygonRenderData.m_pixelShader);

	Edge::InputLayoutDesc inputLayoutDesc{};
	inputLayoutDesc.m_elements.push_back({ "POSITION", 0, 0, offsetof(PolygonRenderData::VertexData, m_position), 3, Edge::InputLayoutElementType::Float32 });
	inputLayoutDesc.m_elements.push_back({ "COLOR", 0, 0, offsetof(PolygonRenderData::VertexData, m_color), 1, Edge::InputLayoutElementType::UInt32 });
	inputLayoutDesc.m_elements.push_back({ "NORMAL", 0, 0, offsetof(PolygonRenderData::VertexData, m_normal), 3, Edge::InputLayoutElementType::Float32 });
	inputLayoutDesc.m_bindings.push_back({ 0, sizeof(PolygonRenderData::VertexData), Edge::InputLayoutBindingType::VertexBinding });

	m_polygonRenderData.m_inputLayout = device.createInputLayout(inputLayoutDesc, *m_polygonRenderData.m_vertexShader);
	EDGE_CHECK_RETURN_FALSE(m_polygonRenderData.m_inputLayout);

	RenderDataBufferCache::BufferDesc polygonDataBufferDesc{};
	polygonDataBufferDesc.m_stride = sizeof(PolygonRenderData::PolygonData);
	polygonDataBufferDesc.m_usage = Edge::GPU_BUFFER_USAGE_VERTEX_BUFFER;
	polygonDataBufferDesc.m_access = Edge::GRAPHIC_RESOURCE_ACCESS_CPU_WRITE | Edge::GRAPHIC_RESOURCE_ACCESS_GPU_READ;

	EDGE_CHECK_RETURN_FALSE(m_polygonRenderData.m_polygonData.init(polygonDataBufferDesc, 256));

	return true;
}

bool EdgeDefRender::DefaultRenderer::initPlaneRenderData(Edge::GraphicDevice& device, const Edge::AssetsDirectoryController& assetsDirectoryController)
{
	m_planeRenderData.m_vertexShader = device.createVertexShaderFromFile(assetsDirectoryController.prepareAssetPath("DefaultRenderPlugin", "Shaders/Plane.vshader"));
	EDGE_CHECK_RETURN_FALSE(m_planeRenderData.m_vertexShader);

	m_planeRenderData.m_pixelShader = device.createPixelShaderFromFile(assetsDirectoryController.prepareAssetPath("DefaultRenderPlugin", "Shaders/Plane.pshader"));
	EDGE_CHECK_RETURN_FALSE(m_planeRenderData.m_pixelShader);

	Edge::InputLayoutDesc inputLayoutDesc{};
	inputLayoutDesc.m_elements.push_back({ "INST_POSITION", 0, 0, offsetof(PlaneRenderData::PlaneData, m_position), 3, Edge::InputLayoutElementType::Float32 });
	inputLayoutDesc.m_elements.push_back({ "INST_SIZE", 0, 0, offsetof(PlaneRenderData::PlaneData, m_sizeX), 1, Edge::InputLayoutElementType::Float32 });
	inputLayoutDesc.m_elements.push_back({ "INST_NORMAL", 0, 0, offsetof(PlaneRenderData::PlaneData, m_normal), 3, Edge::InputLayoutElementType::Float32 });
	inputLayoutDesc.m_elements.push_back({ "INST_SIZE", 1, 0, offsetof(PlaneRenderData::PlaneData, m_sizeY), 1, Edge::InputLayoutElementType::Float32 });
	inputLayoutDesc.m_elements.push_back({ "INST_DIR", 0, 0, offsetof(PlaneRenderData::PlaneData, m_directionRight), 3, Edge::InputLayoutElementType::Float32 });
	inputLayoutDesc.m_elements.push_back({ "INST_COLOR", 0, 0, offsetof(PlaneRenderData::PlaneData, m_color), 1, Edge::InputLayoutElementType::UInt32 });
	inputLayoutDesc.m_bindings.push_back({ 0, sizeof(PlaneRenderData::PlaneData), Edge::InputLayoutBindingType::InstanceBinding });

	m_planeRenderData.m_inputLayout = device.createInputLayout(inputLayoutDesc, *m_planeRenderData.m_vertexShader);
	EDGE_CHECK_RETURN_FALSE(m_planeRenderData.m_inputLayout);

	RenderDataBufferCache::BufferDesc pointDataBufferDesc{};
	pointDataBufferDesc.m_stride = sizeof(PlaneRenderData::PlaneData);
	pointDataBufferDesc.m_usage = Edge::GPU_BUFFER_USAGE_VERTEX_BUFFER;
	pointDataBufferDesc.m_access = Edge::GRAPHIC_RESOURCE_ACCESS_CPU_WRITE | Edge::GRAPHIC_RESOURCE_ACCESS_GPU_READ;

	EDGE_CHECK_RETURN_FALSE(m_planeRenderData.m_planeData.init(pointDataBufferDesc, 64));

	return true;
}

bool EdgeDefRender::DefaultRenderer::initWireframePlaneRenderData(Edge::GraphicDevice& device, const Edge::AssetsDirectoryController& assetsDirectoryController)
{
	m_wireframePlaneRenderData.m_vertexShader = device.createVertexShaderFromFile(assetsDirectoryController.prepareAssetPath("DefaultRenderPlugin", "Shaders/WireframePlane.vshader"));
	EDGE_CHECK_RETURN_FALSE(m_wireframePlaneRenderData.m_vertexShader);

	m_wireframePlaneRenderData.m_pixelShader = device.createPixelShaderFromFile(assetsDirectoryController.prepareAssetPath("DefaultRenderPlugin", "Shaders/WireframePlane.pshader"));
	EDGE_CHECK_RETURN_FALSE(m_wireframePlaneRenderData.m_pixelShader);

	Edge::InputLayoutDesc inputLayoutDesc{};
	inputLayoutDesc.m_elements.push_back({ "INST_POSITION", 0, 0, offsetof(PlaneRenderData::PlaneData, m_position), 3, Edge::InputLayoutElementType::Float32 });
	inputLayoutDesc.m_elements.push_back({ "INST_SIZE", 0, 0, offsetof(PlaneRenderData::PlaneData, m_sizeX), 1, Edge::InputLayoutElementType::Float32 });
	inputLayoutDesc.m_elements.push_back({ "INST_NORMAL", 0, 0, offsetof(PlaneRenderData::PlaneData, m_normal), 3, Edge::InputLayoutElementType::Float32 });
	inputLayoutDesc.m_elements.push_back({ "INST_SIZE", 1, 0, offsetof(PlaneRenderData::PlaneData, m_sizeY), 1, Edge::InputLayoutElementType::Float32 });
	inputLayoutDesc.m_elements.push_back({ "INST_DIR", 0, 0, offsetof(PlaneRenderData::PlaneData, m_directionRight), 3, Edge::InputLayoutElementType::Float32 });
	inputLayoutDesc.m_elements.push_back({ "INST_COLOR", 0, 0, offsetof(PlaneRenderData::PlaneData, m_color), 1, Edge::InputLayoutElementType::UInt32 });
	inputLayoutDesc.m_bindings.push_back({ 0, sizeof(PlaneRenderData::PlaneData), Edge::InputLayoutBindingType::InstanceBinding });

	m_wireframePlaneRenderData.m_inputLayout = device.createInputLayout(inputLayoutDesc, *m_wireframePlaneRenderData.m_vertexShader);
	EDGE_CHECK_RETURN_FALSE(m_wireframePlaneRenderData.m_inputLayout);

	RenderDataBufferCache::BufferDesc pointDataBufferDesc{};
	pointDataBufferDesc.m_stride = sizeof(PlaneRenderData::PlaneData);
	pointDataBufferDesc.m_usage = Edge::GPU_BUFFER_USAGE_VERTEX_BUFFER;
	pointDataBufferDesc.m_access = Edge::GRAPHIC_RESOURCE_ACCESS_CPU_WRITE | Edge::GRAPHIC_RESOURCE_ACCESS_GPU_READ;

	EDGE_CHECK_RETURN_FALSE(m_wireframePlaneRenderData.m_planeData.init(pointDataBufferDesc, 64));

	return true;
}

bool EdgeDefRender::DefaultRenderer::initBoxRenderData(Edge::GraphicDevice& device, const Edge::AssetsDirectoryController& assetsDirectoryController)
{
	m_boxRenderData.m_vertexShader = device.createVertexShaderFromFile(assetsDirectoryController.prepareAssetPath("DefaultRenderPlugin", "Shaders/Box.vshader"));
	EDGE_CHECK_RETURN_FALSE(m_boxRenderData.m_vertexShader);

	m_boxRenderData.m_pixelShader = device.createPixelShaderFromFile(assetsDirectoryController.prepareAssetPath("DefaultRenderPlugin", "Shaders/Box.pshader"));
	EDGE_CHECK_RETURN_FALSE(m_boxRenderData.m_pixelShader);

	Edge::InputLayoutDesc inputLayoutDesc{};
	inputLayoutDesc.m_elements = CubeShape::Vertex::elementsDesc;
	inputLayoutDesc.m_elements.push_back({ "INST_TRANSFORM", 0, 1, offsetof(Edge::FloatMatrix4x4, m_row1), 4, Edge::InputLayoutElementType::Float32 });
	inputLayoutDesc.m_elements.push_back({ "INST_TRANSFORM", 1, 1, offsetof(Edge::FloatMatrix4x4, m_row2), 4, Edge::InputLayoutElementType::Float32 });
	inputLayoutDesc.m_elements.push_back({ "INST_TRANSFORM", 2, 1, offsetof(Edge::FloatMatrix4x4, m_row3), 4, Edge::InputLayoutElementType::Float32 });
	inputLayoutDesc.m_elements.push_back({ "INST_TRANSFORM", 3, 1, offsetof(Edge::FloatMatrix4x4, m_row4), 4, Edge::InputLayoutElementType::Float32 });

	inputLayoutDesc.m_bindings.push_back({ 0, sizeof(CubeShape::Vertex), Edge::InputLayoutBindingType::VertexBinding });
	inputLayoutDesc.m_bindings.push_back({ 1, sizeof(Edge::FloatMatrix4x4), Edge::InputLayoutBindingType::InstanceBinding });

	m_boxRenderData.m_inputLayout = device.createInputLayout(inputLayoutDesc, *m_boxRenderData.m_vertexShader);
	EDGE_CHECK_RETURN_FALSE(m_boxRenderData.m_inputLayout);

	CubeShape boxShape(std::move(CubeShape::create(Edge::FloatVector3One)));

	const CubeShape::VertexCollection& cubeVertices = boxShape.getVertices();

	Edge::GPUBufferDesc boxVertexBufferDesc{};
	boxVertexBufferDesc.m_size = sizeof(CubeShape::Vertex) * cubeVertices.size();
	boxVertexBufferDesc.m_stride = sizeof(CubeShape::Vertex);
	boxVertexBufferDesc.m_usage = Edge::GPU_BUFFER_USAGE_VERTEX_BUFFER;
	boxVertexBufferDesc.m_access = Edge::GRAPHIC_RESOURCE_ACCESS_GPU_READ;

	const Edge::InitialGPUBufferData boxVerticesData(cubeVertices.data(), sizeof(CubeShape::Vertex) * cubeVertices.size());

	m_boxRenderData.m_vertexBuffer = device.createBuffer(boxVertexBufferDesc, &boxVerticesData);
	EDGE_CHECK_RETURN_FALSE(m_boxRenderData.m_vertexBuffer);

	const CubeShape::IndexCollection& cubeIndices = *boxShape.getIndices();

	Edge::GPUBufferDesc boxIndexBufferDesc{};
	boxIndexBufferDesc.m_size = sizeof(CubeShape::VertexIndex) * cubeIndices.size();
	boxIndexBufferDesc.m_stride = sizeof(CubeShape::VertexIndex);
	boxIndexBufferDesc.m_usage = Edge::GPU_BUFFER_USAGE_INDEX_BUFFER;
	boxIndexBufferDesc.m_access = Edge::GRAPHIC_RESOURCE_ACCESS_GPU_READ;

	const Edge::InitialGPUBufferData boxIndicesData(cubeIndices.data(), sizeof(CubeShape::VertexIndex) * cubeIndices.size());

	m_boxRenderData.m_indexBuffer = device.createBuffer(boxIndexBufferDesc, &boxIndicesData);
	EDGE_CHECK_RETURN_FALSE(m_boxRenderData.m_indexBuffer);

	RenderDataBufferCache::BufferDesc boxTransformBufferDesc{};
	boxTransformBufferDesc.m_stride = sizeof(Edge::FloatMatrix4x4);
	boxTransformBufferDesc.m_usage = Edge::GPU_BUFFER_USAGE_VERTEX_BUFFER;
	boxTransformBufferDesc.m_access = Edge::GRAPHIC_RESOURCE_ACCESS_CPU_WRITE | Edge::GRAPHIC_RESOURCE_ACCESS_GPU_READ;

	EDGE_CHECK_RETURN_FALSE(m_boxRenderData.m_transformData.init(boxTransformBufferDesc, 128));

	return true;
}

bool EdgeDefRender::DefaultRenderer::initWireframeBoxRenderData(Edge::GraphicDevice& device, const Edge::AssetsDirectoryController& assetsDirectoryController)
{
	m_wireframeBoxRenderData.m_vertexShader = device.createVertexShaderFromFile(assetsDirectoryController.prepareAssetPath("DefaultRenderPlugin", "Shaders/WireframeBox.vshader"));
	EDGE_CHECK_RETURN_FALSE(m_wireframeBoxRenderData.m_vertexShader);

	m_wireframeBoxRenderData.m_pixelShader = device.createPixelShaderFromFile(assetsDirectoryController.prepareAssetPath("DefaultRenderPlugin", "Shaders/WireframeBox.pshader"));
	EDGE_CHECK_RETURN_FALSE(m_wireframeBoxRenderData.m_pixelShader);

	Edge::InputLayoutDesc inputLayoutDesc{};
	inputLayoutDesc.m_elements = LineCubeShape::Vertex::elementsDesc;
	inputLayoutDesc.m_elements.push_back({ "INST_TRANSFORM", 0, 1, offsetof(Edge::FloatMatrix4x4, m_row1), 4, Edge::InputLayoutElementType::Float32 });
	inputLayoutDesc.m_elements.push_back({ "INST_TRANSFORM", 1, 1, offsetof(Edge::FloatMatrix4x4, m_row2), 4, Edge::InputLayoutElementType::Float32 });
	inputLayoutDesc.m_elements.push_back({ "INST_TRANSFORM", 2, 1, offsetof(Edge::FloatMatrix4x4, m_row3), 4, Edge::InputLayoutElementType::Float32 });
	inputLayoutDesc.m_elements.push_back({ "INST_TRANSFORM", 3, 1, offsetof(Edge::FloatMatrix4x4, m_row4), 4, Edge::InputLayoutElementType::Float32 });

	inputLayoutDesc.m_bindings.push_back({ 0, sizeof(LineCubeShape::Vertex), Edge::InputLayoutBindingType::VertexBinding });
	inputLayoutDesc.m_bindings.push_back({ 1, sizeof(Edge::FloatMatrix4x4), Edge::InputLayoutBindingType::InstanceBinding });

	m_wireframeBoxRenderData.m_inputLayout = device.createInputLayout(inputLayoutDesc, *m_wireframeBoxRenderData.m_vertexShader);
	EDGE_CHECK_RETURN_FALSE(m_wireframeBoxRenderData.m_inputLayout);

	LineCubeShape boxShape(std::move(LineCubeShape::create(Edge::FloatVector3One)));

	const LineCubeShape::VertexCollection& cubeVertices = boxShape.getVertices();

	Edge::GPUBufferDesc boxVertexBufferDesc{};
	boxVertexBufferDesc.m_size = sizeof(LineCubeShape::Vertex) * cubeVertices.size();
	boxVertexBufferDesc.m_stride = sizeof(LineCubeShape::Vertex);
	boxVertexBufferDesc.m_usage = Edge::GPU_BUFFER_USAGE_VERTEX_BUFFER;
	boxVertexBufferDesc.m_access = Edge::GRAPHIC_RESOURCE_ACCESS_GPU_READ;

	const Edge::InitialGPUBufferData boxVerticesData(cubeVertices.data(), sizeof(LineCubeShape::Vertex) * cubeVertices.size());

	m_wireframeBoxRenderData.m_vertexBuffer = device.createBuffer(boxVertexBufferDesc, &boxVerticesData);
	EDGE_CHECK_RETURN_FALSE(m_wireframeBoxRenderData.m_vertexBuffer);

	const LineCubeShape::IndexCollection& cubeIndices = *boxShape.getIndices();

	Edge::GPUBufferDesc boxIndexBufferDesc{};
	boxIndexBufferDesc.m_size = sizeof(LineCubeShape::VertexIndex) * cubeIndices.size();
	boxIndexBufferDesc.m_stride = sizeof(LineCubeShape::VertexIndex);
	boxIndexBufferDesc.m_usage = Edge::GPU_BUFFER_USAGE_INDEX_BUFFER;
	boxIndexBufferDesc.m_access = Edge::GRAPHIC_RESOURCE_ACCESS_GPU_READ;

	const Edge::InitialGPUBufferData boxIndicesData(cubeIndices.data(), sizeof(LineCubeShape::VertexIndex) * cubeIndices.size());

	m_wireframeBoxRenderData.m_indexBuffer = device.createBuffer(boxIndexBufferDesc, &boxIndicesData);
	EDGE_CHECK_RETURN_FALSE(m_wireframeBoxRenderData.m_indexBuffer);

	RenderDataBufferCache::BufferDesc boxTransformBufferDesc{};
	boxTransformBufferDesc.m_stride = sizeof(Edge::FloatMatrix4x4);
	boxTransformBufferDesc.m_usage = Edge::GPU_BUFFER_USAGE_VERTEX_BUFFER;
	boxTransformBufferDesc.m_access = Edge::GRAPHIC_RESOURCE_ACCESS_CPU_WRITE | Edge::GRAPHIC_RESOURCE_ACCESS_GPU_READ;

	EDGE_CHECK_RETURN_FALSE(m_wireframeBoxRenderData.m_transformData.init(boxTransformBufferDesc, 128));

	return true;
}

bool EdgeDefRender::DefaultRenderer::initSphereRenderData(Edge::GraphicDevice& device, const Edge::AssetsDirectoryController& assetsDirectoryController)
{
	m_sphereRenderData.m_vertexShader = device.createVertexShaderFromFile(assetsDirectoryController.prepareAssetPath("DefaultRenderPlugin", "Shaders/Sphere.vshader"));
	EDGE_CHECK_RETURN_FALSE(m_sphereRenderData.m_vertexShader);

	m_sphereRenderData.m_pixelShader = device.createPixelShaderFromFile(assetsDirectoryController.prepareAssetPath("DefaultRenderPlugin", "Shaders/Sphere.pshader"));
	EDGE_CHECK_RETURN_FALSE(m_sphereRenderData.m_pixelShader);

	Edge::InputLayoutDesc inputLayoutDesc{};
	inputLayoutDesc.m_elements = SphereShape::Vertex::elementsDesc;
	inputLayoutDesc.m_elements.push_back({ "INST_POSITION", 0, 1, offsetof(SphereRenderData::SphereData, m_position), 3, Edge::InputLayoutElementType::Float32 });
	inputLayoutDesc.m_elements.push_back({ "INST_DIR", 0, 1, offsetof(SphereRenderData::SphereData, m_directionForward), 3, Edge::InputLayoutElementType::Float32 });
	inputLayoutDesc.m_elements.push_back({ "INST_DIR", 1, 1, offsetof(SphereRenderData::SphereData, m_directionUp), 3, Edge::InputLayoutElementType::Float32 });
	inputLayoutDesc.m_elements.push_back({ "INST_RADIUS", 0, 1, offsetof(SphereRenderData::SphereData, m_radius), 1, Edge::InputLayoutElementType::Float32 });
	inputLayoutDesc.m_elements.push_back({ "INST_COLOR",0, 1, offsetof(SphereRenderData::SphereData, m_color), 1, Edge::InputLayoutElementType::UInt32 });

	inputLayoutDesc.m_bindings.push_back({ 0, sizeof(SphereShape::Vertex), Edge::InputLayoutBindingType::VertexBinding });
	inputLayoutDesc.m_bindings.push_back({ 1, sizeof(SphereRenderData::SphereData), Edge::InputLayoutBindingType::InstanceBinding });

	m_sphereRenderData.m_inputLayout = device.createInputLayout(inputLayoutDesc, *m_sphereRenderData.m_vertexShader);
	EDGE_CHECK_RETURN_FALSE(m_sphereRenderData.m_inputLayout);

	SphereShape sphereShape(std::move(SphereShape::create(1.0f, 8, 12)));

	const SphereShape::VertexCollection& cubeVertices = sphereShape.getVertices();

	Edge::GPUBufferDesc sphereVertexBufferDesc{};
	sphereVertexBufferDesc.m_size = sizeof(SphereShape::Vertex) * cubeVertices.size();
	sphereVertexBufferDesc.m_stride = sizeof(SphereShape::Vertex);
	sphereVertexBufferDesc.m_usage = Edge::GPU_BUFFER_USAGE_VERTEX_BUFFER;
	sphereVertexBufferDesc.m_access = Edge::GRAPHIC_RESOURCE_ACCESS_GPU_READ;

	const Edge::InitialGPUBufferData sphereVerticesData(cubeVertices.data(), sizeof(SphereShape::Vertex) * cubeVertices.size());

	m_sphereRenderData.m_vertexBuffer = device.createBuffer(sphereVertexBufferDesc, &sphereVerticesData);
	EDGE_CHECK_RETURN_FALSE(m_sphereRenderData.m_vertexBuffer);

	const SphereShape::IndexCollection& cubeIndices = *sphereShape.getIndices();

	m_sphereRenderData.m_indexCountPerSphere = cubeIndices.size();

	Edge::GPUBufferDesc sphereIndexBufferDesc{};
	sphereIndexBufferDesc.m_size = sizeof(SphereShape::VertexIndex) * m_sphereRenderData.m_indexCountPerSphere;
	sphereIndexBufferDesc.m_stride = sizeof(SphereShape::VertexIndex);
	sphereIndexBufferDesc.m_usage = Edge::GPU_BUFFER_USAGE_INDEX_BUFFER;
	sphereIndexBufferDesc.m_access = Edge::GRAPHIC_RESOURCE_ACCESS_GPU_READ;

	const Edge::InitialGPUBufferData sphereIndicesData(cubeIndices.data(), sizeof(SphereShape::VertexIndex) * m_sphereRenderData.m_indexCountPerSphere);

	m_sphereRenderData.m_indexBuffer = device.createBuffer(sphereIndexBufferDesc, &sphereIndicesData);
	EDGE_CHECK_RETURN_FALSE(m_sphereRenderData.m_indexBuffer);

	RenderDataBufferCache::BufferDesc sphereTransformBufferDesc{};
	sphereTransformBufferDesc.m_stride = sizeof(SphereRenderData::SphereData);
	sphereTransformBufferDesc.m_usage = Edge::GPU_BUFFER_USAGE_VERTEX_BUFFER;
	sphereTransformBufferDesc.m_access = Edge::GRAPHIC_RESOURCE_ACCESS_CPU_WRITE | Edge::GRAPHIC_RESOURCE_ACCESS_GPU_READ;

	EDGE_CHECK_RETURN_FALSE(m_sphereRenderData.m_sphereData.init(sphereTransformBufferDesc, 128));

	return true;
}

bool EdgeDefRender::DefaultRenderer::initWireframeSphereRenderData(Edge::GraphicDevice& device, const Edge::AssetsDirectoryController& assetsDirectoryController)
{
	m_wireframeSphereRenderData.m_vertexShader = device.createVertexShaderFromFile(assetsDirectoryController.prepareAssetPath("DefaultRenderPlugin", "Shaders/WireframeSphere.vshader"));
	EDGE_CHECK_RETURN_FALSE(m_wireframeSphereRenderData.m_vertexShader);

	m_wireframeSphereRenderData.m_pixelShader = device.createPixelShaderFromFile(assetsDirectoryController.prepareAssetPath("DefaultRenderPlugin", "Shaders/WireframeSphere.pshader"));
	EDGE_CHECK_RETURN_FALSE(m_wireframeSphereRenderData.m_pixelShader);

	Edge::InputLayoutDesc inputLayoutDesc{};
	inputLayoutDesc.m_elements = LineSphereShape::Vertex::elementsDesc;
	inputLayoutDesc.m_elements.push_back({ "INST_POSITION", 0, 1, offsetof(SphereRenderData::SphereData, m_position), 3, Edge::InputLayoutElementType::Float32 });
	inputLayoutDesc.m_elements.push_back({ "INST_DIR",0, 1, offsetof(SphereRenderData::SphereData, m_directionForward), 3, Edge::InputLayoutElementType::Float32 });
	inputLayoutDesc.m_elements.push_back({ "INST_DIR", 1, 1, offsetof(SphereRenderData::SphereData, m_directionUp), 3, Edge::InputLayoutElementType::Float32 });
	inputLayoutDesc.m_elements.push_back({ "INST_RADIUS", 0, 1, offsetof(SphereRenderData::SphereData, m_radius), 1, Edge::InputLayoutElementType::Float32 });
	inputLayoutDesc.m_elements.push_back({ "INST_COLOR", 0, 1, offsetof(SphereRenderData::SphereData, m_color), 1, Edge::InputLayoutElementType::UInt32 });

	inputLayoutDesc.m_bindings.push_back({ 0, sizeof(LineSphereShape::Vertex), Edge::InputLayoutBindingType::VertexBinding });
	inputLayoutDesc.m_bindings.push_back({ 1, sizeof(SphereRenderData::SphereData), Edge::InputLayoutBindingType::InstanceBinding });

	m_wireframeSphereRenderData.m_inputLayout = device.createInputLayout(inputLayoutDesc, *m_wireframeSphereRenderData.m_vertexShader);
	EDGE_CHECK_RETURN_FALSE(m_wireframeSphereRenderData.m_inputLayout);

	LineSphereShape sphereShape(std::move(LineSphereShape::create(1.0f, 8, 12)));

	const LineSphereShape::VertexCollection& cubeVertices = sphereShape.getVertices();

	Edge::GPUBufferDesc sphereVertexBufferDesc{};
	sphereVertexBufferDesc.m_size = sizeof(LineSphereShape::Vertex) * cubeVertices.size();
	sphereVertexBufferDesc.m_stride = sizeof(LineSphereShape::Vertex);
	sphereVertexBufferDesc.m_usage = Edge::GPU_BUFFER_USAGE_VERTEX_BUFFER;
	sphereVertexBufferDesc.m_access = Edge::GRAPHIC_RESOURCE_ACCESS_GPU_READ;

	const Edge::InitialGPUBufferData boxVerticesData(cubeVertices.data(), sizeof(LineSphereShape::Vertex) * cubeVertices.size());

	m_wireframeSphereRenderData.m_vertexBuffer = device.createBuffer(sphereVertexBufferDesc, &boxVerticesData);
	EDGE_CHECK_RETURN_FALSE(m_wireframeSphereRenderData.m_vertexBuffer);

	const LineSphereShape::IndexCollection& cubeIndices = *sphereShape.getIndices();

	m_wireframeSphereRenderData.m_indexCountPerSphere = cubeIndices.size();

	Edge::GPUBufferDesc sphereIndexBufferDesc{};
	sphereIndexBufferDesc.m_size = sizeof(LineSphereShape::VertexIndex) * m_wireframeSphereRenderData.m_indexCountPerSphere;
	sphereIndexBufferDesc.m_stride = sizeof(LineSphereShape::VertexIndex);
	sphereIndexBufferDesc.m_usage = Edge::GPU_BUFFER_USAGE_INDEX_BUFFER;
	sphereIndexBufferDesc.m_access = Edge::GRAPHIC_RESOURCE_ACCESS_GPU_READ;

	const Edge::InitialGPUBufferData boxIndicesData(cubeIndices.data(), sizeof(LineSphereShape::VertexIndex) * m_wireframeSphereRenderData.m_indexCountPerSphere);

	m_wireframeSphereRenderData.m_indexBuffer = device.createBuffer(sphereIndexBufferDesc, &boxIndicesData);
	EDGE_CHECK_RETURN_FALSE(m_wireframeSphereRenderData.m_indexBuffer);

	RenderDataBufferCache::BufferDesc sphereTransformBufferDesc{};
	sphereTransformBufferDesc.m_stride = sizeof(SphereRenderData::SphereData);
	sphereTransformBufferDesc.m_usage = Edge::GPU_BUFFER_USAGE_VERTEX_BUFFER;
	sphereTransformBufferDesc.m_access = Edge::GRAPHIC_RESOURCE_ACCESS_CPU_WRITE | Edge::GRAPHIC_RESOURCE_ACCESS_GPU_READ;

	EDGE_CHECK_RETURN_FALSE(m_wireframeSphereRenderData.m_sphereData.init(sphereTransformBufferDesc, 128));

	return true;
}

void EdgeDefRender::DefaultRenderer::releasePointRenderData()
{
	EDGE_SAFE_DESTROY(m_pointRenderData.m_vertexShader);
	EDGE_SAFE_DESTROY(m_pointRenderData.m_pixelShader);
	EDGE_SAFE_DESTROY(m_pointRenderData.m_inputLayout);

	m_pointRenderData.m_pointData.release();
}

void EdgeDefRender::DefaultRenderer::releaseLineRenderData()
{
	EDGE_SAFE_DESTROY(m_lineRenderData.m_vertexShader);
	EDGE_SAFE_DESTROY(m_lineRenderData.m_pixelShader);
	EDGE_SAFE_DESTROY(m_lineRenderData.m_inputLayout);

	m_lineRenderData.m_lineData.release();
}

void EdgeDefRender::DefaultRenderer::releasePolygonRenderData()
{
	EDGE_SAFE_DESTROY(m_polygonRenderData.m_vertexShader);
	EDGE_SAFE_DESTROY(m_polygonRenderData.m_pixelShader);
	EDGE_SAFE_DESTROY(m_polygonRenderData.m_inputLayout);

	m_polygonRenderData.m_polygonData.release();
}

void EdgeDefRender::DefaultRenderer::releasePlaneRenderData()
{
	EDGE_SAFE_DESTROY(m_planeRenderData.m_vertexShader);
	EDGE_SAFE_DESTROY(m_planeRenderData.m_pixelShader);
	EDGE_SAFE_DESTROY(m_planeRenderData.m_inputLayout);

	m_planeRenderData.m_planeData.release();
}

void EdgeDefRender::DefaultRenderer::releaseWireframePlaneRenderData()
{
	EDGE_SAFE_DESTROY(m_wireframePlaneRenderData.m_vertexShader);
	EDGE_SAFE_DESTROY(m_wireframePlaneRenderData.m_pixelShader);
	EDGE_SAFE_DESTROY(m_wireframePlaneRenderData.m_inputLayout);

	m_wireframePlaneRenderData.m_planeData.release();
}

void EdgeDefRender::DefaultRenderer::releaseBoxRenderData()
{
	EDGE_SAFE_DESTROY(m_boxRenderData.m_vertexShader);
	EDGE_SAFE_DESTROY(m_boxRenderData.m_pixelShader);
	EDGE_SAFE_DESTROY(m_boxRenderData.m_inputLayout);
	EDGE_SAFE_DESTROY(m_boxRenderData.m_vertexBuffer);
	EDGE_SAFE_DESTROY(m_boxRenderData.m_indexBuffer);

	m_boxRenderData.m_transformData.release();
}

void EdgeDefRender::DefaultRenderer::releaseWireframeBoxRenderData()
{
	EDGE_SAFE_DESTROY(m_wireframeBoxRenderData.m_vertexShader);
	EDGE_SAFE_DESTROY(m_wireframeBoxRenderData.m_pixelShader);
	EDGE_SAFE_DESTROY(m_wireframeBoxRenderData.m_inputLayout);
	EDGE_SAFE_DESTROY(m_wireframeBoxRenderData.m_vertexBuffer);
	EDGE_SAFE_DESTROY(m_wireframeBoxRenderData.m_indexBuffer);

	m_wireframeBoxRenderData.m_transformData.release();
}

void EdgeDefRender::DefaultRenderer::releaseSphereRenderData()
{
	EDGE_SAFE_DESTROY(m_sphereRenderData.m_vertexShader);
	EDGE_SAFE_DESTROY(m_sphereRenderData.m_pixelShader);
	EDGE_SAFE_DESTROY(m_sphereRenderData.m_inputLayout);
	EDGE_SAFE_DESTROY(m_sphereRenderData.m_vertexBuffer);
	EDGE_SAFE_DESTROY(m_sphereRenderData.m_indexBuffer);

	m_sphereRenderData.m_sphereData.release();
}

void EdgeDefRender::DefaultRenderer::releaseWireframeSphereRenderData()
{
	EDGE_SAFE_DESTROY(m_wireframeSphereRenderData.m_vertexShader);
	EDGE_SAFE_DESTROY(m_wireframeSphereRenderData.m_pixelShader);
	EDGE_SAFE_DESTROY(m_wireframeSphereRenderData.m_inputLayout);
	EDGE_SAFE_DESTROY(m_wireframeSphereRenderData.m_vertexBuffer);
	EDGE_SAFE_DESTROY(m_wireframeSphereRenderData.m_indexBuffer);

	m_wireframeSphereRenderData.m_sphereData.release();
}

bool EdgeDefRender::DefaultRenderer::init()
{
	const Edge::Application& application = Edge::FrameworkCore::getInstance().getApplication();

	Edge::GraphicDevice& device = application.getGraphicPlatform().getGraphicDevice();

	m_graphicContext = device.createDeferredGraphicContext();
	EDGE_CHECK_INITIALIZATION(m_graphicContext);


	m_baseRasterizationState = device.createRasterizationState(Edge::RasterizationStateDesc{});
	EDGE_CHECK_INITIALIZATION(m_baseRasterizationState);

	Edge::GPUBufferDesc cameraBufferDesc{};
	cameraBufferDesc.m_size = sizeof(CameraShaderData);
	cameraBufferDesc.m_usage = Edge::GPU_BUFFER_USAGE_CONSTANT_BUFFER;
	cameraBufferDesc.m_access = Edge::GRAPHIC_RESOURCE_ACCESS_CPU_WRITE | Edge::GRAPHIC_RESOURCE_ACCESS_GPU_READ;

	m_cameraTransformBuffer = device.createBuffer(cameraBufferDesc, nullptr);
	EDGE_CHECK_INITIALIZATION(m_cameraTransformBuffer);

	const Edge::AssetsDirectoryController& assetsDirectoryController = application.getAssetsDirectoryController();

	EDGE_CHECK_INITIALIZATION(initPointRenderData(device, assetsDirectoryController));
	EDGE_CHECK_INITIALIZATION(initLineRenderData(device, assetsDirectoryController));

	EDGE_CHECK_INITIALIZATION(initPolygonRenderData(device, assetsDirectoryController));

	EDGE_CHECK_INITIALIZATION(initPlaneRenderData(device, assetsDirectoryController));
	EDGE_CHECK_INITIALIZATION(initWireframePlaneRenderData(device, assetsDirectoryController));

	EDGE_CHECK_INITIALIZATION(initBoxRenderData(device, assetsDirectoryController));
	EDGE_CHECK_INITIALIZATION(initWireframeBoxRenderData(device, assetsDirectoryController));

	EDGE_CHECK_INITIALIZATION(initSphereRenderData(device, assetsDirectoryController));
	EDGE_CHECK_INITIALIZATION(initWireframeSphereRenderData(device, assetsDirectoryController));

	return true;
}

void EdgeDefRender::DefaultRenderer::release()
{
	releasePointRenderData();
	releaseLineRenderData();

	releasePolygonRenderData();

	releasePlaneRenderData();
	releaseWireframePlaneRenderData();

	releaseBoxRenderData();
	releaseWireframeBoxRenderData();

	releaseSphereRenderData();
	releaseWireframeSphereRenderData();

	EDGE_SAFE_DESTROY(m_graphicContext);
	EDGE_SAFE_DESTROY(m_baseRasterizationState);
	EDGE_SAFE_DESTROY(m_depthBuffer);
	EDGE_SAFE_DESTROY(m_cameraTransformBuffer);

}

void EdgeDefRender::DefaultRenderer::preparePointRenderData(float deltaTime, const Edge::DebugVisualizationDataController& visualizationData)
{
	const uint32_t pointCount = visualizationData.getPointCount();
	m_pointRenderData.m_pointCount = pointCount;

	m_pointRenderData.m_pointData.updateBuffers(deltaTime, pointCount);

	if (pointCount > 0)
	{
		RenderDataBufferCacheIterator pointDataIter(m_pointRenderData.m_pointData, *m_graphicContext);

		for (uint32_t pointIndex = 0; pointIndex < pointCount; ++pointIndex)
		{
			const Edge::DebugVisualizationDataController::PointData& pointDebugData = visualizationData.getPoint(pointIndex);
			PointRenderData::PointData& pointData = *pointDataIter.getCurrentTypedElement<PointRenderData::PointData>();
			pointData.m_position = pointDebugData.m_position;
			pointData.m_color = PackedColor(pointDebugData.m_color);

			pointDataIter.next();
		}
	}
}

void EdgeDefRender::DefaultRenderer::prepareLineRenderData(float deltaTime, const Edge::DebugVisualizationDataController& visualizationData)
{
	const uint32_t lineCount = visualizationData.getLineCount();
	const uint32_t arrowCount = visualizationData.getArrowCount();
	const uint32_t polygonCount = visualizationData.getWireframePolygonCount(); // TMP
	const uint32_t totalLineCount = lineCount + arrowCount * 3 + polygonCount * 3;

	m_lineRenderData.m_lineCount = totalLineCount;

	m_lineRenderData.m_lineData.updateBuffers(deltaTime, totalLineCount);

	if (totalLineCount > 0)
	{
		RenderDataBufferCacheIterator lineDataIter(m_lineRenderData.m_lineData, *m_graphicContext);

		for (uint32_t lineIndex = 0; lineIndex < lineCount; ++lineIndex)
		{
			const Edge::DebugVisualizationDataController::LineData& lineDebugData = visualizationData.getLine(lineIndex);
			LineRenderData::LineData& lineData = *lineDataIter.getCurrentTypedElement<LineRenderData::LineData>();

			const PackedColor color(lineDebugData.m_color);

			lineData.m_point1.m_position = lineDebugData.m_position1;
			lineData.m_point1.m_color = color;

			lineData.m_point2.m_position = lineDebugData.m_position2;
			lineData.m_point2.m_color = color;

			lineDataIter.next();
		}

		for (uint32_t arrowIndex = 0; arrowIndex < arrowCount; ++arrowIndex)
		{
			const Edge::DebugVisualizationDataController::ArrowData& arrowDebugData = visualizationData.getArrow(arrowIndex);

			const PackedColor color(arrowDebugData.m_color);

			const Edge::ComputeVector endPoint = Edge::ComputeVector(arrowDebugData.m_position) + Edge::ComputeVector(arrowDebugData.m_direction);
			const Edge::ComputeVector normalizeDir = Edge::ComputeVector(arrowDebugData.m_direction).normalize() * arrowDebugData.m_size;
			const Edge::ComputeVector headPerpendicular = Edge::ComputeVector(calculateArrowHeadPerpendicular(arrowDebugData.m_direction)) * arrowDebugData.m_size;

			LineRenderData::LineData& lineData = *lineDataIter.getCurrentTypedElement<LineRenderData::LineData>();

			lineData.m_point1.m_position = arrowDebugData.m_position;
			lineData.m_point1.m_color = color;

			lineData.m_point2.m_position = endPoint.getFloatVector3();
			lineData.m_point2.m_color = color;

			lineDataIter.next();

			if (arrowDebugData.m_size > 0.0f)
			{
				LineRenderData::LineData& headLineData1 = *lineDataIter.getCurrentTypedElement<LineRenderData::LineData>();

				headLineData1.m_point1.m_position = (endPoint - normalizeDir + headPerpendicular).getFloatVector3();
				headLineData1.m_point1.m_color = color;

				headLineData1.m_point2.m_position = lineData.m_point2.m_position;
				headLineData1.m_point2.m_color = color;

				lineDataIter.next();

				LineRenderData::LineData& headLineData2 = *lineDataIter.getCurrentTypedElement<LineRenderData::LineData>();

				headLineData2.m_point1.m_position = (endPoint - normalizeDir - headPerpendicular).getFloatVector3();
				headLineData2.m_point1.m_color = color;

				headLineData2.m_point2.m_position = lineData.m_point2.m_position;
				headLineData2.m_point2.m_color = color;

				lineDataIter.next();
			}
		}

		for (uint32_t polygonIndex = 0; polygonIndex < polygonCount; ++polygonIndex)
		{
			const Edge::DebugVisualizationDataController::PolygonData& polygonDebugData = visualizationData.getWireframePolygon(polygonIndex);
			const PackedColor color(polygonDebugData.m_color);


			LineRenderData::LineData& lineData1 = *lineDataIter.getCurrentTypedElement<LineRenderData::LineData>();
			lineData1.m_point1.m_position = polygonDebugData.m_position1;
			lineData1.m_point1.m_color = color;

			lineData1.m_point2.m_position = polygonDebugData.m_position2;
			lineData1.m_point2.m_color = color;

			lineDataIter.next();

			LineRenderData::LineData& lineData2 = *lineDataIter.getCurrentTypedElement<LineRenderData::LineData>();
			lineData2.m_point1.m_position = polygonDebugData.m_position2;
			lineData2.m_point1.m_color = color;

			lineData2.m_point2.m_position = polygonDebugData.m_position3;
			lineData2.m_point2.m_color = color;

			lineDataIter.next();

			LineRenderData::LineData& lineData3 = *lineDataIter.getCurrentTypedElement<LineRenderData::LineData>();
			lineData3.m_point1.m_position = polygonDebugData.m_position3;
			lineData3.m_point1.m_color = color;

			lineData3.m_point2.m_position = polygonDebugData.m_position1;
			lineData3.m_point2.m_color = color;

			lineDataIter.next();
		}
	}
}

void EdgeDefRender::DefaultRenderer::preparePolygonRenderData(float deltaTime, const Edge::DebugVisualizationDataController& visualizationData)
{
	const uint32_t polygonCount = visualizationData.getPolygonCount();
	m_polygonRenderData.m_polygonCount = polygonCount;

	m_polygonRenderData.m_polygonData.updateBuffers(deltaTime, polygonCount);

	if (polygonCount > 0)
	{
		RenderDataBufferCacheIterator polygonDataIter(m_polygonRenderData.m_polygonData, *m_graphicContext);

		for (uint32_t polygonIndex = 0; polygonIndex < polygonCount; ++polygonIndex)
		{
			const Edge::DebugVisualizationDataController::PolygonData& polygonDebugData = visualizationData.getPolygon(polygonIndex);
			PolygonRenderData::PolygonData& polygonData = *polygonDataIter.getCurrentTypedElement<PolygonRenderData::PolygonData>();

			const PackedColor color(polygonDebugData.m_color);
			const Edge::FloatVector3 normal = CrossVector3(
				polygonDebugData.m_position1 - polygonDebugData.m_position2,
				polygonDebugData.m_position1 - polygonDebugData.m_position3
			).getFloatVector3();

			polygonData.m_point1.m_position = polygonDebugData.m_position1;
			polygonData.m_point1.m_color = color;
			polygonData.m_point1.m_normal = normal;

			polygonData.m_point2.m_position = polygonDebugData.m_position2;
			polygonData.m_point2.m_color = color;
			polygonData.m_point2.m_normal = normal;

			polygonData.m_point3.m_position = polygonDebugData.m_position3;
			polygonData.m_point3.m_color = color;
			polygonData.m_point3.m_normal = normal;

			polygonDataIter.next();
		}
	}
}

void EdgeDefRender::DefaultRenderer::preparePlaneRenderData(float deltaTime, const Edge::DebugVisualizationDataController& visualizationData)
{
	const uint32_t planeCount = visualizationData.getPlaneCount();
	m_planeRenderData.m_planeCount = planeCount;

	m_planeRenderData.m_planeData.updateBuffers(deltaTime, planeCount);

	if (planeCount > 0)
	{
		RenderDataBufferCacheIterator planeDataIter(m_planeRenderData.m_planeData, *m_graphicContext);

		for (uint32_t planeIndex = 0; planeIndex < planeCount; ++planeIndex)
		{
			const Edge::DebugVisualizationDataController::PlaneData& planeDebugData = visualizationData.getPlane(planeIndex);
			PlaneRenderData::PlaneData& planeData = *planeDataIter.getCurrentTypedElement<PlaneRenderData::PlaneData>();
			planeData.m_position = planeDebugData.m_position;
			planeData.m_sizeX = planeDebugData.m_size.m_x;
			planeData.m_normal = planeDebugData.m_normal;
			planeData.m_sizeY = planeDebugData.m_size.m_y;
			planeData.m_directionRight = planeDebugData.m_directionRight;
			planeData.m_color = PackedColor(planeDebugData.m_color);

			planeDataIter.next();
		}
	}
}

void EdgeDefRender::DefaultRenderer::prepareWireframePlaneRenderData(float deltaTime, const Edge::DebugVisualizationDataController& visualizationData)
{
	const uint32_t planeCount = visualizationData.getWireframePlaneCount();
	m_wireframePlaneRenderData.m_planeCount = planeCount;

	m_wireframePlaneRenderData.m_planeData.updateBuffers(deltaTime, planeCount);

	if (planeCount > 0)
	{
		RenderDataBufferCacheIterator planeDataIter(m_wireframePlaneRenderData.m_planeData, *m_graphicContext);

		for (uint32_t planeIndex = 0; planeIndex < planeCount; ++planeIndex)
		{
			const Edge::DebugVisualizationDataController::PlaneData& planeDebugData = visualizationData.getWireframePlane(planeIndex);
			PlaneRenderData::PlaneData& planeData = *planeDataIter.getCurrentTypedElement<PlaneRenderData::PlaneData>();
			planeData.m_position = planeDebugData.m_position;
			planeData.m_sizeX = planeDebugData.m_size.m_x;
			planeData.m_normal = planeDebugData.m_normal;
			planeData.m_sizeY = planeDebugData.m_size.m_y;
			planeData.m_directionRight = planeDebugData.m_directionRight;
			planeData.m_color = PackedColor(planeDebugData.m_color);

			planeDataIter.next();
		}
	}
}

void EdgeDefRender::DefaultRenderer::prepareBoxRenderData(float deltaTime, const Edge::DebugVisualizationDataController& visualizationData)
{
	const uint32_t boxCount = visualizationData.getBoxCount();
	m_boxRenderData.m_boxCount = boxCount;

	m_boxRenderData.m_transformData.updateBuffers(deltaTime, boxCount);

	if (boxCount > 0)
	{
		RenderDataBufferCacheIterator boxDataIter(m_boxRenderData.m_transformData, *m_graphicContext);

		for (uint32_t boxIndex = 0; boxIndex < boxCount; ++boxIndex)
		{
			const Edge::DebugVisualizationDataController::BoxData& boxDebugData = visualizationData.getBox(boxIndex);
			Edge::FloatMatrix4x4& boxTransform = *boxDataIter.getCurrentTypedElement<Edge::FloatMatrix4x4>();
			boxTransform = boxDebugData.m_transform.m_matrix;

			assert(boxTransform.m_row4.m_w == 1.0f);

			const PackedColor color(boxDebugData.m_color);
			boxTransform.m_row4.m_w = *reinterpret_cast<const float*>(&color.m_data);

			//m_graphicContext->prepareMatrixForShader(boxTransform, boxTransform);

			boxDataIter.next();
		}
	}
}

void EdgeDefRender::DefaultRenderer::prepareWireframeBoxRenderData(float deltaTime, const Edge::DebugVisualizationDataController& visualizationData)
{
	const uint32_t boxCount = visualizationData.getWireframeBoxCount();
	m_wireframeBoxRenderData.m_boxCount = boxCount;

	m_wireframeBoxRenderData.m_transformData.updateBuffers(deltaTime, boxCount);

	if (boxCount > 0)
	{
		RenderDataBufferCacheIterator boxDataIter(m_wireframeBoxRenderData.m_transformData, *m_graphicContext);

		for (uint32_t boxIndex = 0; boxIndex < boxCount; ++boxIndex)
		{
			const Edge::DebugVisualizationDataController::BoxData& boxDebugData = visualizationData.getWireframeBox(boxIndex);
			Edge::FloatMatrix4x4& boxTransform = *boxDataIter.getCurrentTypedElement<Edge::FloatMatrix4x4>();
			boxTransform = boxDebugData.m_transform.m_matrix;

			assert(boxTransform.m_row4.m_w == 1.0f);

			const PackedColor color(boxDebugData.m_color);
			boxTransform.m_row4.m_w = *reinterpret_cast<const float*>(&color.m_data);

			//m_graphicContext->prepareMatrixForShader(boxTransform, boxTransform);

			boxDataIter.next();
		}
	}
}

void EdgeDefRender::DefaultRenderer::prepareSphereRenderData(float deltaTime, const Edge::DebugVisualizationDataController& visualizationData)
{
	const uint32_t sphereCount = visualizationData.getSphereCount();
	m_sphereRenderData.m_sphereCount = sphereCount;

	m_sphereRenderData.m_sphereData.updateBuffers(deltaTime, sphereCount);

	if (sphereCount > 0)
	{
		RenderDataBufferCacheIterator sphereDataIter(m_sphereRenderData.m_sphereData, *m_graphicContext);

		for (uint32_t sphereIndex = 0; sphereIndex < sphereCount; ++sphereIndex)
		{
			const Edge::DebugVisualizationDataController::SphereData& sphereDebugData = visualizationData.getSphere(sphereIndex);
			SphereRenderData::SphereData& sphereData = *sphereDataIter.getCurrentTypedElement<SphereRenderData::SphereData>();
			sphereData.m_position = sphereDebugData.m_position;
			sphereData.m_directionForward = sphereDebugData.m_directionForward;
			sphereData.m_directionUp = sphereDebugData.m_directionUp;
			sphereData.m_radius = sphereDebugData.m_radius;
			sphereData.m_color = PackedColor(sphereDebugData.m_color);

			sphereDataIter.next();
		}
	}
}

void EdgeDefRender::DefaultRenderer::prepareWireframeSphereRenderData(float deltaTime, const Edge::DebugVisualizationDataController& visualizationData)
{
	const uint32_t sphereCount = visualizationData.getWireframeSphereCount();
	m_wireframeSphereRenderData.m_sphereCount = sphereCount;

	m_wireframeSphereRenderData.m_sphereData.updateBuffers(deltaTime, sphereCount);

	if (sphereCount > 0)
	{
		RenderDataBufferCacheIterator sphereDataIter(m_wireframeSphereRenderData.m_sphereData, *m_graphicContext);

		for (uint32_t sphereIndex = 0; sphereIndex < sphereCount; ++sphereIndex)
		{
			const Edge::DebugVisualizationDataController::SphereData& sphereDebugData = visualizationData.getWireframeSphere(sphereIndex);
			SphereRenderData::SphereData& sphereData = *sphereDataIter.getCurrentTypedElement<SphereRenderData::SphereData>();
			sphereData.m_position = sphereDebugData.m_position;
			sphereData.m_directionForward = sphereDebugData.m_directionForward;
			sphereData.m_directionUp = sphereDebugData.m_directionUp;
			sphereData.m_radius = sphereDebugData.m_radius;
			sphereData.m_color = PackedColor(sphereDebugData.m_color);

			sphereDataIter.next();
		}
	}
}

Edge::FloatVector3 EdgeDefRender::DefaultRenderer::calculateArrowHeadPerpendicular(const Edge::FloatVector3& arrowDirection)
{
	if (fabs(arrowDirection.m_x) > fabs(arrowDirection.m_y))
	{
		const float length = sqrtf(arrowDirection.m_x * arrowDirection.m_x + arrowDirection.m_z * arrowDirection.m_z);
		return (Edge::ComputeVector(Edge::FloatVector3(arrowDirection.m_z, 0.0f, -arrowDirection.m_x)) / length).getFloatVector3();
	}

	const float length = sqrtf(arrowDirection.m_y * arrowDirection.m_y + arrowDirection.m_z * arrowDirection.m_z);
	return (Edge::ComputeVector(Edge::FloatVector3(0.0f, arrowDirection.m_z, -arrowDirection.m_y)) / length).getFloatVector3();
}

void EdgeDefRender::DefaultRenderer::prepareData(const CameraTransforms& cameraTransforms, const Edge::DebugVisualizationDataController& visualizationData)
{
	const Edge::Application& application = Edge::FrameworkCore::getInstance().getApplication();
	const float deltaTime = application.getDeltaTime();

	m_cameraShaderData.m_transforms = cameraTransforms;

	preparePointRenderData(deltaTime, visualizationData);
	prepareLineRenderData(deltaTime, visualizationData);

	preparePolygonRenderData(deltaTime, visualizationData);

	preparePlaneRenderData(deltaTime, visualizationData);
	prepareWireframePlaneRenderData(deltaTime, visualizationData);

	prepareBoxRenderData(deltaTime, visualizationData);
	prepareWireframeBoxRenderData(deltaTime, visualizationData);

	prepareSphereRenderData(deltaTime, visualizationData);
	prepareWireframeSphereRenderData(deltaTime, visualizationData);
}

void EdgeDefRender::DefaultRenderer::drawPoints()
{
	if (m_pointRenderData.m_pointCount > 0)
	{
		m_graphicContext->setVertexShader(*m_pointRenderData.m_vertexShader);
		m_graphicContext->setPixelShader(*m_pointRenderData.m_pixelShader);

		m_graphicContext->setPrimitiveTopology(Edge::PrimitiveTopology::TriangleStrip);
		m_graphicContext->setInputLayout(*m_pointRenderData.m_inputLayout);

		uint32_t remainedPointCount = m_pointRenderData.m_pointCount;
		const uint32_t pointPerBuffer = m_pointRenderData.m_pointData.getElementCountPerBuffer();

		const uint32_t bufferCount = m_pointRenderData.m_pointData.getBufferCount();
		for (uint32_t bufferIndex = 0; bufferIndex < bufferCount && remainedPointCount > 0; ++bufferIndex)
		{
			const uint32_t drawingPointCount = std::min(remainedPointCount, pointPerBuffer);
			remainedPointCount -= pointPerBuffer;

			Edge::GPUBuffer* instanceDataBuffer = &m_pointRenderData.m_pointData.getBuffer(bufferIndex);

			m_graphicContext->setVertexBuffers(1, &instanceDataBuffer, m_pointRenderData.m_inputLayout->getDesc());
			m_graphicContext->drawInstanced(4, drawingPointCount);
		}
	}
}

void EdgeDefRender::DefaultRenderer::drawLines()
{
	if (m_lineRenderData.m_lineCount > 0)
	{
		m_graphicContext->setVertexShader(*m_lineRenderData.m_vertexShader);
		m_graphicContext->setPixelShader(*m_lineRenderData.m_pixelShader);

		m_graphicContext->setPrimitiveTopology(Edge::PrimitiveTopology::LineList);
		m_graphicContext->setInputLayout(*m_lineRenderData.m_inputLayout);

		uint32_t remainedLineCount = m_lineRenderData.m_lineCount;
		const uint32_t linePerBuffer = m_lineRenderData.m_lineData.getElementCountPerBuffer();

		const uint32_t bufferCount = m_lineRenderData.m_lineData.getBufferCount();
		for (uint32_t bufferIndex = 0; bufferIndex < bufferCount && remainedLineCount > 0; ++bufferIndex)
		{
			const uint32_t drawingLineCount = std::min(remainedLineCount, linePerBuffer);
			remainedLineCount -= linePerBuffer;

			Edge::GPUBuffer* instanceDataBuffer = &m_lineRenderData.m_lineData.getBuffer(bufferIndex);

			m_graphicContext->setVertexBuffers(1, &instanceDataBuffer, m_lineRenderData.m_inputLayout->getDesc());
			m_graphicContext->draw(drawingLineCount * 2);
		}
	}
}

void EdgeDefRender::DefaultRenderer::drawPolygons()
{
	if (m_polygonRenderData.m_polygonCount > 0)
	{
		m_graphicContext->setVertexShader(*m_polygonRenderData.m_vertexShader);
		m_graphicContext->setPixelShader(*m_polygonRenderData.m_pixelShader);

		m_graphicContext->setPrimitiveTopology(Edge::PrimitiveTopology::TriangleList);
		m_graphicContext->setInputLayout(*m_polygonRenderData.m_inputLayout);

		uint32_t remainedPolygonCount = m_polygonRenderData.m_polygonCount;
		const uint32_t polygonPerBuffer = m_polygonRenderData.m_polygonData.getElementCountPerBuffer();

		const uint32_t bufferCount = m_polygonRenderData.m_polygonData.getBufferCount();
		for (uint32_t bufferIndex = 0; bufferIndex < bufferCount && remainedPolygonCount > 0; ++bufferIndex)
		{
			const uint32_t drawingPolygonCount = std::min(remainedPolygonCount, polygonPerBuffer);
			remainedPolygonCount -= polygonPerBuffer;

			Edge::GPUBuffer* instanceDataBuffer = &m_polygonRenderData.m_polygonData.getBuffer(bufferIndex);

			m_graphicContext->setVertexBuffers(1, &instanceDataBuffer, m_polygonRenderData.m_inputLayout->getDesc());
			m_graphicContext->draw(drawingPolygonCount * 3);
		}
	}
}

void EdgeDefRender::DefaultRenderer::drawPlanes()
{
	if (m_planeRenderData.m_planeCount > 0)
	{
		m_graphicContext->setVertexShader(*m_planeRenderData.m_vertexShader);
		m_graphicContext->setPixelShader(*m_planeRenderData.m_pixelShader);

		m_graphicContext->setPrimitiveTopology(Edge::PrimitiveTopology::TriangleStrip);
		m_graphicContext->setInputLayout(*m_planeRenderData.m_inputLayout);

		uint32_t remainedPlaneCount = m_planeRenderData.m_planeCount;
		const uint32_t planePerBuffer = m_planeRenderData.m_planeData.getElementCountPerBuffer();

		const uint32_t bufferCount = m_planeRenderData.m_planeData.getBufferCount();
		for (uint32_t bufferIndex = 0; bufferIndex < bufferCount && remainedPlaneCount > 0; ++bufferIndex)
		{
			const uint32_t drawingPointCount = std::min(remainedPlaneCount, planePerBuffer);
			remainedPlaneCount -= planePerBuffer;

			Edge::GPUBuffer* instanceDataBuffer = &m_planeRenderData.m_planeData.getBuffer(bufferIndex);

			m_graphicContext->setVertexBuffers(1, &instanceDataBuffer, m_planeRenderData.m_inputLayout->getDesc());
			m_graphicContext->drawInstanced(4, drawingPointCount);
		}
	}
}

void EdgeDefRender::DefaultRenderer::drawWireframePlanes()
{
	if (m_wireframePlaneRenderData.m_planeCount > 0)
	{
		m_graphicContext->setVertexShader(*m_wireframePlaneRenderData.m_vertexShader);
		m_graphicContext->setPixelShader(*m_wireframePlaneRenderData.m_pixelShader);

		m_graphicContext->setPrimitiveTopology(Edge::PrimitiveTopology::LineStrip);
		m_graphicContext->setInputLayout(*m_wireframePlaneRenderData.m_inputLayout);

		uint32_t remainedPlaneCount = m_wireframePlaneRenderData.m_planeCount;
		const uint32_t planePerBuffer = m_wireframePlaneRenderData.m_planeData.getElementCountPerBuffer();

		const uint32_t bufferCount = m_wireframePlaneRenderData.m_planeData.getBufferCount();
		for (uint32_t bufferIndex = 0; bufferIndex < bufferCount && remainedPlaneCount > 0; ++bufferIndex)
		{
			const uint32_t drawingPointCount = std::min(remainedPlaneCount, planePerBuffer);
			remainedPlaneCount -= planePerBuffer;

			Edge::GPUBuffer* instanceDataBuffer = &m_wireframePlaneRenderData.m_planeData.getBuffer(bufferIndex);

			m_graphicContext->setVertexBuffers(1, &instanceDataBuffer, m_wireframePlaneRenderData.m_inputLayout->getDesc());
			m_graphicContext->drawInstanced(5, drawingPointCount);
		}
	}
}

void EdgeDefRender::DefaultRenderer::drawBoxes()
{
	if (m_boxRenderData.m_boxCount > 0)
	{
		m_graphicContext->setVertexShader(*m_boxRenderData.m_vertexShader);
		m_graphicContext->setPixelShader(*m_boxRenderData.m_pixelShader);

		m_graphicContext->setPrimitiveTopology(Edge::PrimitiveTopology::TriangleList);
		m_graphicContext->setInputLayout(*m_boxRenderData.m_inputLayout);

		m_graphicContext->setIndexBuffer(*m_boxRenderData.m_indexBuffer);

		uint32_t remainedBoxCount = m_boxRenderData.m_boxCount;
		const uint32_t boxPerBuffer = m_boxRenderData.m_transformData.getElementCountPerBuffer();

		const uint32_t bufferCount = m_boxRenderData.m_transformData.getBufferCount();
		for (uint32_t bufferIndex = 0; bufferIndex < bufferCount && remainedBoxCount > 0; ++bufferIndex)
		{
			const uint32_t drawingBoxCount = std::min(remainedBoxCount, boxPerBuffer);
			remainedBoxCount -= boxPerBuffer;

			Edge::GPUBuffer* instanceDataBuffer = &m_boxRenderData.m_transformData.getBuffer(bufferIndex);

			Edge::GPUBuffer* vertexBuffers[2] = { m_boxRenderData.m_vertexBuffer, instanceDataBuffer };
			m_graphicContext->setVertexBuffers(2, vertexBuffers, m_boxRenderData.m_inputLayout->getDesc());
			m_graphicContext->drawIndexedInstanced(36, drawingBoxCount);
		}
	}
}

void EdgeDefRender::DefaultRenderer::drawWireframeBoxes()
{
	if (m_wireframeBoxRenderData.m_boxCount > 0)
	{
		m_graphicContext->setVertexShader(*m_wireframeBoxRenderData.m_vertexShader);
		m_graphicContext->setPixelShader(*m_wireframeBoxRenderData.m_pixelShader);

		m_graphicContext->setPrimitiveTopology(Edge::PrimitiveTopology::LineList);
		m_graphicContext->setInputLayout(*m_wireframeBoxRenderData.m_inputLayout);

		m_graphicContext->setIndexBuffer(*m_wireframeBoxRenderData.m_indexBuffer);

		uint32_t remainedBoxCount = m_wireframeBoxRenderData.m_boxCount;
		const uint32_t boxPerBuffer = m_wireframeBoxRenderData.m_transformData.getElementCountPerBuffer();

		const uint32_t bufferCount = m_wireframeBoxRenderData.m_transformData.getBufferCount();
		for (uint32_t bufferIndex = 0; bufferIndex < bufferCount && remainedBoxCount > 0; ++bufferIndex)
		{
			const uint32_t drawingBoxCount = std::min(remainedBoxCount, boxPerBuffer);
			remainedBoxCount -= boxPerBuffer;

			Edge::GPUBuffer* instanceDataBuffer = &m_wireframeBoxRenderData.m_transformData.getBuffer(bufferIndex);

			Edge::GPUBuffer* vertexBuffers[2] = { m_wireframeBoxRenderData.m_vertexBuffer, instanceDataBuffer };
			m_graphicContext->setVertexBuffers(2, vertexBuffers, m_wireframeBoxRenderData.m_inputLayout->getDesc());
			m_graphicContext->drawIndexedInstanced(24, drawingBoxCount);
		}
	}
}

void EdgeDefRender::DefaultRenderer::drawSpheres()
{
	if (m_sphereRenderData.m_sphereCount > 0)
	{
		m_graphicContext->setVertexShader(*m_sphereRenderData.m_vertexShader);
		m_graphicContext->setPixelShader(*m_sphereRenderData.m_pixelShader);

		m_graphicContext->setPrimitiveTopology(Edge::PrimitiveTopology::TriangleList);
		m_graphicContext->setInputLayout(*m_sphereRenderData.m_inputLayout);

		m_graphicContext->setIndexBuffer(*m_sphereRenderData.m_indexBuffer);

		uint32_t remainedSphereCount = m_sphereRenderData.m_sphereCount;
		const uint32_t spherePerBuffer = m_sphereRenderData.m_sphereData.getElementCountPerBuffer();

		const uint32_t bufferCount = m_sphereRenderData.m_sphereData.getBufferCount();
		for (uint32_t bufferIndex = 0; bufferIndex < bufferCount && remainedSphereCount > 0; ++bufferIndex)
		{
			const uint32_t drawingSphereCount = std::min(remainedSphereCount, spherePerBuffer);
			remainedSphereCount -= spherePerBuffer;

			Edge::GPUBuffer* instanceDataBuffer = &m_sphereRenderData.m_sphereData.getBuffer(bufferIndex);

			Edge::GPUBuffer* vertexBuffers[2] = { m_sphereRenderData.m_vertexBuffer, instanceDataBuffer };
			m_graphicContext->setVertexBuffers(2, vertexBuffers, m_sphereRenderData.m_inputLayout->getDesc());
			m_graphicContext->drawIndexedInstanced(m_sphereRenderData.m_indexCountPerSphere, drawingSphereCount);
		}
	}
}

void EdgeDefRender::DefaultRenderer::drawWireframeSpheres()
{
	if (m_wireframeSphereRenderData.m_sphereCount > 0)
	{
		m_graphicContext->setVertexShader(*m_wireframeSphereRenderData.m_vertexShader);
		m_graphicContext->setPixelShader(*m_wireframeSphereRenderData.m_pixelShader);

		m_graphicContext->setPrimitiveTopology(Edge::PrimitiveTopology::LineList);
		m_graphicContext->setInputLayout(*m_wireframeSphereRenderData.m_inputLayout);

		m_graphicContext->setIndexBuffer(*m_wireframeSphereRenderData.m_indexBuffer);

		uint32_t remainedSphereCount = m_wireframeSphereRenderData.m_sphereCount;
		const uint32_t spherePerBuffer = m_wireframeSphereRenderData.m_sphereData.getElementCountPerBuffer();

		const uint32_t bufferCount = m_wireframeSphereRenderData.m_sphereData.getBufferCount();
		for (uint32_t bufferIndex = 0; bufferIndex < bufferCount && remainedSphereCount > 0; ++bufferIndex)
		{
			const uint32_t drawingSphereCount = std::min(remainedSphereCount, spherePerBuffer);
			remainedSphereCount -= spherePerBuffer;

			Edge::GPUBuffer* instanceDataBuffer = &m_wireframeSphereRenderData.m_sphereData.getBuffer(bufferIndex);

			Edge::GPUBuffer* vertexBuffers[2] = { m_wireframeSphereRenderData.m_vertexBuffer, instanceDataBuffer };
			m_graphicContext->setVertexBuffers(2, vertexBuffers, m_wireframeSphereRenderData.m_inputLayout->getDesc());
			m_graphicContext->drawIndexedInstanced(m_wireframeSphereRenderData.m_indexCountPerSphere, drawingSphereCount);
		}
	}
}

void EdgeDefRender::DefaultRenderer::prepareDepthBuffer(const Edge::Texture2DSize& bufferSize)
{
	bool needRecreation = false;

	if (!m_depthBuffer)
	{
		needRecreation = true;
	}
	else
	{
		const Edge::Texture2DSize& currentSize = m_depthBuffer->getDesc().m_size;
		if (currentSize.m_x != bufferSize.m_x || currentSize.m_y != bufferSize.m_y)
		{
			needRecreation = true;
		}
	}

	if (needRecreation)
	{
		EDGE_SAFE_DESTROY(m_depthBuffer);

		Edge::Texture2DDesc depthBufferDesc{};
		depthBufferDesc.m_size = bufferSize;
		depthBufferDesc.m_format = Edge::GraphicResourceFormat::D24_UNORM_S8_UINT;
		depthBufferDesc.m_usage = Edge::TEXTURE_USAGE_DEPTH_STENCIL;
		depthBufferDesc.m_access = Edge::GRAPHIC_RESOURCE_ACCESS_GPU_READ | Edge::GRAPHIC_RESOURCE_ACCESS_GPU_WRITE;

		Edge::GraphicDevice& device = Edge::FrameworkCore::getInstance().getApplication().getGraphicPlatform().getGraphicDevice();

		m_depthBuffer = device.createTexture2D(depthBufferDesc);
	}
}

void EdgeDefRender::DefaultRenderer::render(Edge::Texture2D& targetTexture)
{
	const Edge::Texture2DDesc& targetTextureDesc = targetTexture.getDesc();

	Edge::Viewport viewport(targetTextureDesc.m_size.m_x, targetTextureDesc.m_size.m_y);

	prepareDepthBuffer(targetTextureDesc.m_size);

	//m_graphicContext->prepareMatrixForShader(m_cameraShaderData.m_transforms.m_viewTransform, m_cameraShaderData.m_transforms.m_viewTransform);
	//m_graphicContext->prepareMatrixForShader(m_cameraShaderData.m_transforms.m_projTransform, m_cameraShaderData.m_transforms.m_projTransform);
	m_cameraShaderData.m_screenSize = targetTextureDesc.m_size;

	CameraShaderData* mappedCameraShaderData;
	m_graphicContext->mapBuffer(*m_cameraTransformBuffer, Edge::GRAPHIC_RESOURCE_MAPPING_TYPE_WRITE, Edge::GRAPHIC_RESOURCE_MAPPING_FLAG_DISCARD,
		reinterpret_cast<void**>(&mappedCameraShaderData));

	memcpy(mappedCameraShaderData, &m_cameraShaderData, sizeof(CameraShaderData));

	m_graphicContext->unmapBuffer(*m_cameraTransformBuffer);

	m_graphicContext->setConstantBuffer(*m_cameraTransformBuffer, 0, Edge::GRAPHIC_CONTEXT_BINDING_SHADER_STAGE_VERTEX);

	m_graphicContext->setRenderTarget(targetTexture, m_depthBuffer);

	m_graphicContext->setRasterizationState(*m_baseRasterizationState);
	m_graphicContext->setViewport(viewport);

	m_graphicContext->clearRenderTarget(targetTexture, Edge::FloatVector4(0.5f, 0.5f, 0.5f, 1.0f));
	m_graphicContext->clearDepthStencil(*m_depthBuffer);

	//

	drawPoints();
	drawLines();

	drawPolygons();

	drawPlanes();
	drawWireframePlanes();

	drawBoxes();
	drawWireframeBoxes();

	drawSpheres();
	drawWireframeSpheres();

	Edge::GraphicDevice& device = Edge::FrameworkCore::getInstance().getApplication().getGraphicPlatform().getGraphicDevice();
	device.executeGraphicContext(*m_graphicContext);
}
